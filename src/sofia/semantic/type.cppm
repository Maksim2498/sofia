export module sofia.semantic.type;

import <optional>;
import <variant>;

import sofia.util.containers.string_pool;
import sofia.util.source.source_reference;
import sofia.util.typedefs;

export namespace sofia {
    class type_base {
    public:
        virtual ~type_base() = default;

        [[nodiscard]] std::optional<string_pool::key_type> name_key() const noexcept { return m_name_key; }
        void name_key(const std::optional<string_pool::key_type> key) noexcept { m_name_key = key; }

        [[nodiscard]] std::optional<source_reference> reference() const noexcept { return m_reference; }
        void reference(const std::optional<source_reference> &reference) noexcept { m_reference = reference; }

        [[nodiscard]] bool is_inline() const noexcept { return m_is_inline; }
        void is_inline(const bool is_inline) noexcept { m_is_inline = is_inline; }

    protected:
        type_base(
            const std::optional<string_pool::key_type> name_key = std::nullopt,
            const std::optional<source_reference> &reference = std::nullopt,
            const bool is_inline = false
        ) noexcept :
            m_name_key(name_key), m_reference(reference), m_is_inline(is_inline)
        {}

    private:
        std::optional<string_pool::key_type> m_name_key;
        std::optional<source_reference> m_reference;
        bool m_is_inline;
    };

    class union_type : public type_base {
    public:

    private:

    };

    class struct_type : public type_base  {
    public:

    private:
    };

    using type = std::variant<union_type, struct_type>;
}