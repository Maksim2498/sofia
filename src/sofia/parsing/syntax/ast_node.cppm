export module sofia.parsing.syntax.ast_node;

import <any>;
import <memory>;
import <optional>;
import <span>;
import <unordered_map>;

import sofia.util.source.source_reference;
import sofia.util.typedefs;

export namespace sofia {
    class ast_node {
    public:
        // Types

        using ptr = std::unique_ptr<ast_node>;
        using const_ptr = const ptr;

        using tag_map = std::unordered_map<s8, std::any>;

        // Constants

        static constexpr sv8 TYPE_TAG = "type";

        // Destructors

        virtual ~ast_node() = default;

        // Getters and setters

        [[nodiscard]] virtual std::span<ptr> children() noexcept { return {}; }
        [[nodiscard]] std::span<const_ptr> children() const noexcept { return const_cast<ast_node&>(*this).children(); }

        [[nodiscard]] std::optional<source_reference> reference() const noexcept { return m_reference; }
        void reference(const std::optional<source_reference> &reference) noexcept { m_reference = reference; }

        [[nodiscard]] const tag_map& tags() const noexcept { return m_tags; }
        [[nodiscard]] tag_map &tags() noexcept { return m_tags; }

    protected:
        // Constructors

        explicit ast_node(const std::optional<source_reference> &reference = std::nullopt) noexcept :
            m_reference(reference)
        {}

    private:
        // Fields
        
        std::optional<source_reference> m_reference;
        tag_map m_tags;
    };
}