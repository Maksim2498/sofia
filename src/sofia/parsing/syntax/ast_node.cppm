export module sofia.parsing.syntax.ast_node;

import <any>;
import <optional>;
import <span>;
import <unordered_map>;

import sofia.semantic.type;
import sofia.util.source.source_reference;
import sofia.util.typedefs;

export namespace sofia {
    class ast_node {
    public:
        // Types

        using tag_map = std::unordered_map<s8, std::any>;

        // Destructors

        virtual ~ast_node() = default;

        // Getters and setters

        [[nodiscard]] virtual std::span<ast_node*> children() noexcept { return {}; }
        [[nodiscard]] std::span<ast_node*> children() const noexcept { return const_cast<ast_node&>(*this).children(); }

        [[nodiscard]] const std::optional<source_reference> &reference() const noexcept { return m_reference; }
        [[nodiscard]] std::optional<source_reference> &reference() noexcept { return m_reference; }
        void reference(const std::optional<source_reference> &reference) noexcept { m_reference = reference; }

        [[nodiscard]] const sofia::type *type() const noexcept { return m_type; }
        [[nodiscard]] sofia::type *type() noexcept { return m_type; }
        void type(sofia::type *type) noexcept { m_type = type; }

        [[nodiscard]] const tag_map& tags() const noexcept { return m_tags; }
        [[nodiscard]] tag_map &tags() noexcept { return m_tags; }

    protected:
        // Constructors

        explicit ast_node(
            const std::optional<source_reference> &reference = std::nullopt,
            sofia::type *type = nullptr
        ) noexcept :
            m_reference(reference), m_type(type)
        {}

    private:
        // Fields

        std::optional<source_reference> m_reference;
        sofia::type* m_type;
        tag_map m_tags;
    };
}