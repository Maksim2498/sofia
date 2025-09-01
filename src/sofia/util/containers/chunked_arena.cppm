module;

#include <cassert>

export module sofia.util.containers.chunked_arena;

import <algorithm>;
import <list>;
import <memory>;
import <type_traits>;
import <utility>;
import <vector>;

import sofia.util.typedefs;

// Without this doesn't compile for some reason
export import <list>;
export import <vector>;

export namespace sofia {
    template<typename T>
    class chunked_arena {
        struct m_chunk;

    public:
        // Types

        using value_type = T;

        using reference = value_type&;
        using const_reference = const value_type&;

        using difference_type = isize;
        using size_type = usize;

        class iterator {
        public:
            // Types

            using value_type = T;
            using reference = value_type&;
            using pointer = value_type*;
            using difference_type = difference_type;
            using iterator_category = std::forward_iterator_tag;

            // Constructors

            iterator() noexcept :
                m_chunk(nullptr), m_chunk_size(0), m_last_chunk_size(0), m_value_index(0), m_is_last_chunk(true)
            {}

            iterator(const iterator &) noexcept = default;
            iterator(iterator &&) noexcept = default;

            // Operators

            [[nodiscard]] reference operator*() const noexcept { return *(m_chunk->data() + m_value_index); }
            [[nodiscard]] pointer operator->() const noexcept { return &**this; }

            iterator &operator++() noexcept {
                const usize current_chunk_size = m_is_last_chunk
                    ? m_last_chunk_size
                    : m_chunk_size;

                if (m_value_index >= current_chunk_size - 1) {
                    if (m_chunk != nullptr)
                        m_chunk = m_chunk->previous;

                    m_value_index = 0;
                    m_is_last_chunk = false;
                } else
                    ++m_value_index;

                return *this;
            }

            iterator operator++(int) noexcept {
                auto tmp = *this;
                ++*this;
                return tmp;
            }

            bool operator==(const iterator &other) const noexcept {
                return m_chunk == other.m_chunk
                    && m_value_index == other.m_value_index;
            }

            bool operator!=(const iterator &other) const noexcept {
                return m_chunk != other.m_chunk
                    || m_value_index != other.m_value_index;
            }

            iterator &operator=(const iterator &) noexcept = default;
            iterator &operator=(iterator &&) noexcept = default;

        private:
            using chunks_iterator = typename std::list<std::vector<value_type>>::iterator;

            explicit iterator(
                m_chunk *chunk,
                const usize chunks_size,
                const usize last_chunk_size,
                const usize value_index = 0,
                const bool is_last_chunk = true
            ) noexcept :
                m_chunk(chunk), m_chunk_size(chunks_size),
                m_last_chunk_size(last_chunk_size), m_value_index(value_index),
                m_is_last_chunk(is_last_chunk)
            {}

            m_chunk *m_chunk;
            usize m_chunk_size;
            usize m_last_chunk_size;
            usize m_value_index;
            bool m_is_last_chunk;

            friend class chunked_arena;
        };

        static_assert(std::forward_iterator<iterator>);

        class const_iterator {
        public:
            // Types

            using value_type = const T;
            using reference = value_type&;
            using pointer = value_type*;
            using difference_type = difference_type;
            using iterator_category = std::forward_iterator_tag;

            // Constructors

            const_iterator() noexcept = default;
            const_iterator(const const_iterator &) noexcept = default;
            const_iterator(const_iterator &&) noexcept = default;

            // Operators

            [[nodiscard]] reference operator*() const noexcept { return *m_it; }
            [[nodiscard]] pointer operator->() const noexcept { return m_it.operator->(); }

            const_iterator &operator++() noexcept {
                ++m_it;
                return *this;
            }

            const_iterator operator++(int) noexcept {
                auto tmp = *this;
                ++*this;
                return tmp;
            }

            bool operator==(const const_iterator &other) const noexcept { return m_it == other.m_it; }
            bool operator!=(const const_iterator &other) const noexcept { return m_it != other.m_it; }

            const_iterator &operator=(const const_iterator &) noexcept = default;
            const_iterator &operator=(const_iterator &&) noexcept = default;

        private:
            explicit const_iterator(const iterator &it) noexcept : m_it(it) {}

            iterator m_it;

            friend class chunked_arena;
        };

        static_assert(std::forward_iterator<const_iterator>);

        // Constructors

        explicit chunked_arena(const usize chunk_size = 256) noexcept : m_chunk_size(chunk_size) { assert(chunk_size); }

        chunked_arena(const chunked_arena &other) : m_chunk_size(0) { m_copy_from(other); }
        chunked_arena(chunked_arena &&other) noexcept : m_chunk_size(0) { m_move_from(other); }

        // Destructors

        ~chunked_arena() noexcept { clear(); }

        // Iterators

        // - Begin

        [[nodiscard]] iterator begin() noexcept {
            return iterator(m_last_chunk, m_chunk_size, m_last_chunk_size, 0, true);
        }

        [[nodiscard]] const_iterator begin() const noexcept {
            return cbegin();
        }

        [[nodiscard]] const_iterator cbegin() const noexcept {
            return const_iterator(const_cast<chunked_arena*>(this)->begin());
        }

        // - End

        [[nodiscard]] iterator end() noexcept {
            return iterator(nullptr, m_chunk_size, m_last_chunk_size, 0);
        }

        [[nodiscard]] const_iterator end() const noexcept {
            return cend();
        }

        [[nodiscard]] const_iterator cend() const noexcept {
            return const_iterator(const_cast<chunked_arena*>(this)->end());
        }

        // Size

        [[nodiscard]] usize chunk_count() const noexcept {
            usize count = 0;

            for (m_chunk *chunk = m_last_chunk; chunk != nullptr; chunk = chunk->previous)
                ++count;

            return count;
        }

        [[nodiscard]] usize chunk_size() const noexcept { return m_chunk_size; }
        [[nodiscard]] usize last_chunk_size() const noexcept { return m_chunk_size; }

        [[nodiscard]] size_type size() const noexcept {
            return m_last_chunk != nullptr
                ? m_chunk_size * (chunk_count() - 1) + m_last_chunk_size
                : 0;
        }

        [[nodiscard]] size_type capacity() const noexcept { return m_chunk_size * chunk_count(); }

        [[nodiscard]] bool empty() const noexcept { return m_last_chunk == nullptr; }

        // Modifiers

        reference push_back(const_reference value) {
            m_add_chunk_if_needed();
            auto &new_value = m_last_chunk->emplace_back(m_last_chunk_size, value);
            ++m_last_chunk_size;
            return new_value;
        }

        reference push_back(value_type &&value) {
            m_add_chunk_if_needed();
            auto &new_value = m_last_chunk->emplace_back(m_last_chunk_size, std::move(value));
            ++m_last_chunk_size;
            return new_value;
        }

        template <class ...Args>
        reference emplace_back(Args &&...args) {
            m_add_chunk_if_needed();
            auto &new_value = m_last_chunk->emplace_back(m_last_chunk_size, std::forward<Args>(args)...);
            ++m_last_chunk_size;
            return new_value;
        }

        void clear() noexcept {
            m_chunk *current_chunk = m_last_chunk;

            while (current_chunk != nullptr) {
                const usize current_chunk_size = current_chunk == m_last_chunk
                    ? m_last_chunk_size
                    : m_chunk_size;

                current_chunk->clear(current_chunk_size);

                m_chunk *new_current_chunk = current_chunk->previous;

                delete current_chunk;
                current_chunk = new_current_chunk;
            }

            m_last_chunk = nullptr;
        }

        // Operators

        chunked_arena &operator=(const chunked_arena &other) {
            m_copy_from(other);
            return *this;
        }

        chunked_arena &operator=(chunked_arena &&other) noexcept {
            m_move_from(other);
            return *this;
        }

    private:
        // Types

        struct m_chunk {
            // Iterators

            const value_type *cdata() const noexcept { return static_cast<m_chunk*>(this)->data(); }
            const value_type *data() const noexcept { return cdata(); }

            value_type *data() noexcept {
                return reinterpret_cast<value_type*>(reinterpret_cast<char*>(this) + M_ALIGNED_CHUNK_SIZE);
            }

            // Modifiers

            void clear(const usize size) noexcept {
                if (!std::is_trivially_destructible_v<value_type>)
                    for (auto it = data(), end = it + size; it != end; ++it)
                        it->~value_type();
            }

            template<typename ...Args>
            value_type &emplace_back(usize size, Args &&...args) {
                value_type *new_value = new(data() + size) value_type(std::forward<Args>(args)...);
                return *new_value;
            }

            // Fields

            m_chunk *previous;
        };

        // Utilities

        static constexpr usize M_CHUNK_ALIGNMENT = std::max(alignof(m_chunk), alignof(value_type));
        static constexpr usize M_ALIGNED_CHUNK_SIZE = (sizeof(m_chunk) + M_CHUNK_ALIGNMENT - 1) & ~(M_CHUNK_ALIGNMENT - 1);

        void m_add_chunk_if_needed() {
            if (m_need_new_chunk())
                m_add_chunk();
        }

        void m_add_chunk() {
            const auto data_size = m_chunk_size * sizeof(value_type);
            const auto new_chunk_size = M_ALIGNED_CHUNK_SIZE + data_size;
            const auto new_last_chunk = reinterpret_cast<m_chunk*>(new char[new_chunk_size]);

            new_last_chunk->previous = m_last_chunk;

            m_last_chunk = new_last_chunk;
            m_last_chunk_size = 0;
        }

        bool m_need_new_chunk() const noexcept {
            return m_last_chunk == nullptr || m_last_chunk_size >= m_chunk_size;
        }

        void m_copy_from(const chunked_arena &other) {
            if (this == &other)
                return;

            clear();

            m_chunk_size = other.m_chunk_size;

            for (const auto &value : other)
                emplace_back(value);
        }

        void m_move_from(chunked_arena &&other) noexcept {
            if (this == &other)
                return;

            clear();

            m_last_chunk = other.m_last_chunk;
            m_last_chunk_size = other.m_last_chunk_size;
            m_chunk_size = other.m_chunk_size;

            other.m_last_chunk = nullptr;
            other.m_last_chunk_size = 0;
            other.m_chunk_size = 0;
        }

        // Fields

        m_chunk *m_last_chunk{};
        usize m_last_chunk_size{};
        usize m_chunk_size;
    };
}