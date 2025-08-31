export module sofia.util.containers.string_pool;

import <concepts>;
import <unordered_map>;
import <utility>;
import <vector>;

import sofia.util.typedefs;

export namespace sofia {
    class string_pool {
    public:
        // Types

        using key_type = usize;

        using value_type = s8;

        using reference = value_type&;
        using const_reference = const value_type&;

        using iterator = std::vector<value_type>::iterator;
        using const_iterator = std::vector<value_type>::const_iterator;

        using difference_type = isize;
        using size_type = usize;

        // Constructors

        explicit string_pool(const usize reserve = 4096) {
            m_values.reserve(reserve);
            m_lookup.reserve(reserve / 2);
        }

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

        key_type insert(const s8 &value) { return m_insert(value); }
        key_type insert(s8 &&value) { return m_insert(std::move(value)); }

        void clear() noexcept {
            m_values.clear();
            m_lookup.clear();
        }

        // Accessors

        [[nodiscard]] sv8 at(const key_type key) const { return m_values.at(key); }
        [[nodiscard]] sv8 operator[](const key_type key) const noexcept { return m_values[key]; }

        [[nodiscard]] bool contains(const sv8 value) const noexcept { return m_lookup.contains(value); }
        [[nodiscard]] bool valid_key(const key_type key) const noexcept { return key < size(); }

    private:
        std::vector<s8> m_values{};
        std::unordered_map<sv8, usize> m_lookup{};

        template<typename ValueType>
        requires std::convertible_to<ValueType, s8>
        key_type m_insert(ValueType &&value) {
            if (const auto it = m_lookup.find(value); it != m_lookup.end())
                return it->second;

            const key_type key = m_values.size();
            const sv8 added_value = m_values.emplace_back(std::forward<ValueType>(value));

            m_lookup.emplace(added_value, key);

            return key;
        }
    };
}