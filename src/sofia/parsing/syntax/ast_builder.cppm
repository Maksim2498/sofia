export module sofia.parsing.syntax.ast_builder;

import <memory>;
import <vector>;

import sofia.parsing.lexis.tokenizer;
import sofia.parsing.syntax.ast_node;
import sofia.util.typedefs;
import sofia.util.source.source_message;
import sofia.util.containers.string_pool;

export namespace sofia {
    class ast_builder {
    public:
        // Constructors

        explicit ast_builder(
            sofia::tokenizer &tokenizer,
            string_pool *string_pool = nullptr,
            std::vector<source_message> *messages = nullptr
        ) noexcept :
            m_tokenizer(&tokenizer), m_string_pool(string_pool), m_messages(messages)
        {}

        // Building

        [[nodiscard]] ast_node *build() noexcept {
            // TODO
            return nullptr;
        }

        // Getters

        [[nodiscard]] const sofia::tokenizer &tokenizer() const noexcept { return *m_tokenizer; }
        [[nodiscard]] sofia::tokenizer &tokenizer() noexcept { return *m_tokenizer; }
        void tokenizer(sofia::tokenizer &tokenizer) noexcept { m_tokenizer = &tokenizer; }

        [[nodiscard]] const std::vector<source_message> *messages() const noexcept { return m_messages; }
        [[nodiscard]] std::vector<source_message> *messages() noexcept { return m_messages; }
        void messages(std::vector<source_message> *messages) noexcept { m_messages = messages; }

        [[nodiscard]] const sofia::string_pool *string_pool() const noexcept { return m_string_pool; }
        [[nodiscard]] sofia::string_pool *string_pool() noexcept { return m_string_pool; }
        void string_pool(sofia::string_pool *string_pool) noexcept { m_string_pool = string_pool; }

    private:
        // Fields

        sofia::tokenizer *m_tokenizer;
        sofia::string_pool *m_string_pool;
        std::vector<source_message> *m_messages;
    };
}