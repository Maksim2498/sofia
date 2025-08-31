module;

#include <cassert>

export module sofia.parsing.lexis.tokenizer;

import <optional>;
import <utility>;
import <variant>;
import <vector>;

import <cctype>;

import sofia.parsing.lexis.token;
import sofia.parsing.lexis.tokenizer_config;
import sofia.parsing.lexis.token_type;
import sofia.util.source.source_message;
import sofia.util.source.source_message_type;
import sofia.util.source.source_reference;
import sofia.util.containers.string_pool;
import sofia.util.typedefs;

/*
 * <id>:                [A-Za-z_][A-Za-z0-9_]*
 *
 * <bool>:              true|false
 *
 * <S>:                 "(\\.|[^"\\])"
 * <S8>:                <S>8?
 * <S16>:               <S>16
 * <S32>:               <S>32
 *
 * <I>:                 [0-9](_?[0-9])*
 *    |                 0x[A-Fa-f0-9](_?[A-Fa-f0-9])*
 *    |                 0o[0-7](_?[0-7])*
 *    |                 0b[01](_?[01])*
 *
 * <U8>:                <I>u8
 * <U16>:               <I>u16
 * <U32>:               <I>u(32)?
 * <U64>:               <I>u(64)? # "64" may be omitted if it's too big for U32
 * <USize>:             <I>usize
 *
 * <I8>:                <I>i8
 * <I16>:               <I>i16
 * <I32>:               <I>(i(32)?)?
 * <I64>:               <I>(i(64)?)? # "i64" or "64 may be omitted if it's too big for I32
 * <ISize>:             <I>isize
 *
 * <custom operator>:   [=+-*%/^|&<>@!~?:]+
 */

export namespace sofia {
    class tokenizer {
    public:
        // Constructors

        explicit tokenizer(
            const sv8 source,
            string_pool *string_pool = nullptr,
            std::vector<source_message> *messages = nullptr,
            const tokenizer_config &config = {}
        ) noexcept :
            m_config(config), m_source(source), m_string_pool(string_pool), m_messages(messages)
        {}

        // Lexical analysis

        [[nodiscard]] token peek_next() noexcept {
            // TODO
            return token(token_type::EOT);
        }

        [[nodiscard]] std::vector<token> read_all(const bool add_eot = false) noexcept {
            std::vector<token> tokens;

            while (true)
                if (const auto token = read_next(); token.type() == token_type::EOT) {
                    if (add_eot)
                        tokens.push_back(token);

                    break;
                } else
                    tokens.push_back(token);

            return tokens;
        }

        [[nodiscard]] token read_next() noexcept {
            // TODO
            return token(token_type::EOT, {}, source_reference{ .index = m_source.length(), .length = 0 });
        }

        // Getters and setters

        // - Messages

        [[nodiscard]] const std::vector<source_message> *messages() const noexcept { return m_messages; }
        [[nodiscard]] std::vector<source_message> *messages() noexcept { return m_messages; }
        void messages(std::vector<source_message> *messages) noexcept { m_messages = messages; }

        // - Config

        [[nodiscard]] const tokenizer_config &config() const noexcept { return m_config; }
        [[nodiscard]] tokenizer_config &config() noexcept { return m_config; }
        void config(const tokenizer_config &config) noexcept { m_config = config; }

        // - Source

        [[nodiscard]] sv8 source() const noexcept { return m_source; }

        void source(const sv8 source) noexcept {
            m_source = source;
            reset();
        }

        // - Index

        [[nodiscard]] usize index() const noexcept { return m_index; }

        void set_index(const usize index) noexcept {
            assert(index <= m_source.size());
            m_index = index;
        }

        // - Indents

        [[nodiscard]] const std::vector<usize> &indents() const noexcept { return m_indents; }
        [[nodiscard]] std::vector<usize> &indents() noexcept { return m_indents; }

        void indents(const std::vector<usize> &indents) noexcept { m_indents = indents; }
        void indents(std::vector<usize> &&indents) noexcept { m_indents = std::move(indents); }

        // - Indent level change ignored

        [[nodiscard]] bool indent_level_change_ignored() const noexcept { return m_indent_change_ignored; }

        void indent_change_ignored(const bool indent_level_change_ignored) noexcept {
            m_indent_change_ignored = indent_level_change_ignored;
        }

        // Miscellaneous

        void reset() noexcept {
            m_indents.clear();
            m_index = 0;
            m_indent_change_ignored = false;
        }

    private:
        std::vector<usize> m_indents;
        tokenizer_config m_config;
        sv8 m_source;
        string_pool *m_string_pool;
        std::vector<source_message> *m_messages;
        usize m_index = 0;
        bool m_indent_change_ignored = false;
    };
}