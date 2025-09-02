export module sofia.semantic.type;

import <optional>;
import <variant>;

import sofia.util.source.source_reference;
import sofia.util.typedefs;

export namespace sofia {
    class type_base {
    public:
        virtual ~type_base() = default;

        [[nodiscard]] const s8 *name() const noexcept { return m_name; }
        [[nodiscard]] s8 *name() noexcept { return m_name; }
        void name(s8 *name) noexcept { m_name = name; }

        [[nodiscard]] std::optional<source_reference> reference() const noexcept { return m_reference; }
        void reference(const std::optional<source_reference> &reference) noexcept { m_reference = reference; }

        [[nodiscard]] bool is_inline() const noexcept { return m_is_inline; }
        void is_inline(const bool is_inline) noexcept { m_is_inline = is_inline; }

    protected:
        type_base(
            s8 *name = nullptr,
            const std::optional<source_reference> &reference = std::nullopt,
            const bool is_inline = false
        ) noexcept :
            m_name(name), m_reference(reference), m_is_inline(is_inline)
        {}

    private:
        s8 *m_name;
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