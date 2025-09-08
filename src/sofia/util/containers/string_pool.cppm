export module sofia.util.containers.string_pool;

import <concepts>;
import <unordered_map>;
import <utility>;

import sofia.util.containers.chunked_arena;
import sofia.util.typedefs;

export namespace sofia {
    class string_pool {
    public:
        // Types

        using value_type = s8;

        using reference = value_type&;
        using const_reference = const value_type&;

        using iterator = chunked_arena<s8>::iterator;
        using const_iterator = chunked_arena<s8>::const_iterator;

        using difference_type = isize;
        using size_type = usize;

        // Constructors

        explicit string_pool(const usize chunk_size = 4096) : m_values(chunk_size) {}

        // Iterators

        [[nodiscard]] iterator begin() noexcept { return m_values.begin(); }
        [[nodiscard]] const_iterator begin() const noexcept { return m_values.cbegin(); }
        [[nodiscard]] const_iterator cbegin() const noexcept { return m_values.cbegin(); }
        [[nodiscard]] iterator end() noexcept { return m_values.end(); }
        [[nodiscard]] const_iterator end() const noexcept { return m_values.cend(); }
        [[nodiscard]] const_iterator cend() const noexcept { return m_values.cend(); }

        // Size

        [[nodiscard]] size_type size() const noexcept { return m_values.size(); }
        [[nodiscard]] bool empty() const noexcept { return m_values.empty(); }

        // Modifiers

        reference insert(const s8 &value) { return m_insert(value); }
        reference insert(s8 &&value) { return m_insert(std::move(value)); }

        void clear() noexcept {
            m_values.clear();
            m_lookup.clear();
        }

    private:
        // Fields

        chunked_arena<s8> m_values;
        std::unordered_map<sv8, s8*> m_lookup{};

        // Insertion

        template<typename ValueType>
        requires std::convertible_to<ValueType, s8>
        reference m_insert(ValueType &&value) {
            if (const auto it = m_lookup.find(value); it != m_lookup.end())
                return *it->second;

            reference added_value = m_values.emplace_back(std::forward<ValueType>(value));

            m_lookup.emplace(added_value, &added_value);

            return added_value;
        }
    };
}