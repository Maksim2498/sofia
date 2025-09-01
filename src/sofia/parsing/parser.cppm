export module sofia.parsing.parser;

import <memory>;
import <vector>;

import sofia.parsing.lexis.tokenizer;
import sofia.parsing.lexis.tokenizer_config;
import sofia.parsing.syntax.ast_builder;
import sofia.parsing.syntax.ast_node;
import sofia.util.typedefs;
import sofia.util.source.source_message;
import sofia.util.containers.string_pool;

export namespace sofia {
    class parser {
    public:
        // Constructors

        explicit parser(
            string_pool *string_pool = nullptr,
            std::vector<source_message> *messages = nullptr,
            const tokenizer_config &tokenizer_config = {}
        ) noexcept :
            m_string_pool(string_pool), m_messages(messages), m_tokenizer_config(tokenizer_config)
        {}

        // Parsing

        [[nodiscard]] ast_node *parse(const sv8 source) const noexcept {
            tokenizer tokenizer(source, m_string_pool, m_messages);
            ast_builder ast_builder(tokenizer, m_string_pool, m_messages);

            return ast_builder.build();
        }

        // Getters

        [[nodiscard]] const std::vector<source_message> *messages() const noexcept { return m_messages; }
        [[nodiscard]] std::vector<source_message> *messages() noexcept { return m_messages; }
        void messages(std::vector<source_message> *messages) noexcept { m_messages = messages; }

        [[nodiscard]] const sofia::string_pool *string_pool() const noexcept { return m_string_pool; }
        [[nodiscard]] sofia::string_pool *string_pool() noexcept { return m_string_pool; }
        void string_pool(sofia::string_pool *string_pool) noexcept { m_string_pool = string_pool; }

        [[nodiscard]] const sofia::tokenizer_config &tokenizer_config() const noexcept { return m_tokenizer_config; }
        [[nodiscard]] sofia::tokenizer_config &tokenizer_config() noexcept { return m_tokenizer_config; }
        void tokenizer_config(const sofia::tokenizer_config &config) noexcept { m_tokenizer_config = config; }

    private:
        // Fields

        sofia::string_pool *m_string_pool;
        std::vector<source_message> *m_messages;
        sofia::tokenizer_config m_tokenizer_config;
    };
}