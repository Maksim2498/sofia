export module sofia.parsing.lexis.token_type;

import sofia.util.typedefs;

export namespace sofia {
    enum class token_type : u8 {
        // Specials

        ERROR, EOT,
        INDENT_SAME, INDENT_GROW, INDENT_SHRINK,
        COMMENT,

        // Identifiers

        ID,

        // Literals

        NULL_LITERAL,
        BOOL,
        S8, S16, S32,
        U8, U16, U32, U64, USIZE,
        I8, I16, I32, I64, ISIZE,
        F32, F64,

        // Keywords

        // - Modules

        IMPORT,

        // - Exception handling

        THROW, TRY, CATCH, FINALLY,

        // - Functions

        FUN, RETURN,

        // - Variables

        VAL, VAR,

        // - Types

        THIS,
        INIT, CONSTRUCT, FINALIZE,
        TYPE, STRUCT, ENUM,
        IS, AS, BY,
        PUB, PRIV, PROT,
        INLINE,
        OVERRIDE,

        // - Evaluation control

        ANYTIME, COMTIME, RUNTIME,

        // - Non-linear flow control

        DEFER,

        // - Branching

        IF, THEN, ELSE, WHEN,

        // - Cycles

        FOR, WHILE, DO,
        BREAK, CONTINUE,

        // Operators

        AT,
        ASSIGN,
        ARROW,
        QUESTION_MARK, EXCLAMATION_MARK,
        COMMA, DOT,
        COLON, SEMICOLON,
        OPEN_PAREN, CLOSE_PAREN,
        OPEN_BRACE, CLOSE_BRACE,
        OPEN_BRACK, CLOSE_BRACK,
        LESS, GREATER,
        IN, OUT,
        ELIPSIS,
        OPERATOR,
    };

    [[nodiscard]] sv8 name(const token_type type) noexcept {
        switch (type) {
            // Specials

            case token_type::COMMENT: return "<comment>";

            case token_type::ERROR: return "<error>";
            case token_type::EOT: return "<eot>";

            case token_type::INDENT_SAME: return "<indent same>";
            case token_type::INDENT_GROW: return "<indent grow>";
            case token_type::INDENT_SHRINK: return "<indent shrink>";

            // Identifiers

            case token_type::ID: return "<id>";

            // Literals

            // - Null

            case token_type::NULL_LITERAL: return "\"null\"";

            // - Boolean

            case token_type::BOOL: return "<Bool>";

            // - Strings

            case token_type::S8: return "<S8>";
            case token_type::S16: return "<S16>";
            case token_type::S32: return "<S32>";

            // - Integers

            // -- Unsigned

            case token_type::U8: return "<U8>";
            case token_type::U16: return "<U16>";
            case token_type::U32: return "<U32>";
            case token_type::U64: return "<U64>";
            case token_type::USIZE: return "<USize>";

            // -- Signed

            case token_type::I8: return "<I8>";
            case token_type::I16: return "<I16>";
            case token_type::I32: return "<I32>";
            case token_type::I64: return "<I64>";
            case token_type::ISIZE: return "<ISize>";

            // - Floats

            case token_type::F32: return "<F32>";
            case token_type::F64: return "<F64>";

            // Keywords

            // - Packages

            case token_type::IMPORT: return "\"import\"";

            // - Exception handling

            case token_type::THROW: return "\"throw\"";
            case token_type::TRY: return "\"try\"";
            case token_type::CATCH: return "\"catch\"";
            case token_type::FINALLY: return "\"finally\"";

            // - Functions

            case token_type::FUN: return "\"fun\"";
            case token_type::RETURN: return "\"return\"";

            // - Variables

            case token_type::VAL: return "\"val\"";
            case token_type::VAR: return "\"var\"";

            // - Types

            case token_type::THIS: return "\"this\"";

            case token_type::INIT: return "\"init\"";
            case token_type::CONSTRUCT: return "\"construct\"";
            case token_type::FINALIZE: return "\"finalize\"";

            case token_type::TYPE: return "\"type\"";
            case token_type::STRUCT: return "\"struct\"";
            case token_type::ENUM: return "\"enum\"";

            case token_type::IS: return "\"is\"";
            case token_type::AS: return "\"as\"";
            case token_type::BY: return "\"by\"";

            case token_type::PUB: return "\"pub\"";
            case token_type::PRIV: return "\"priv\"";
            case token_type::PROT: return "\"prot\"";

            case token_type::INLINE: return "\"inline\"";

            case token_type::OVERRIDE: return "\"override\"";

            // - Evaluation control

            case token_type::ANYTIME: return "\"anytime\"";
            case token_type::COMTIME: return "\"comtime\"";
            case token_type::RUNTIME: return "\"runtime\"";

            // - Non-linear flow control

            case token_type::DEFER: return "\"defer\"";

            // - Branching

            case token_type::IF: return "\"if\"";
            case token_type::THEN: return "\"then\"";
            case token_type::ELSE: return "\"else\"";
            case token_type::WHEN: return "\"when\"";

            // - Cycles

            case token_type::FOR: return "\"for\"";
            case token_type::WHILE: return "\"while\"";
            case token_type::DO: return "\"do\"";

            case token_type::BREAK: return "\"break\"";
            case token_type::CONTINUE: return "\"continue\"";

            // - Operators

            case token_type::AT: return "\"@\"";

            case token_type::ASSIGN: return "\"=\"";

            case token_type::QUESTION_MARK: return "\"?\"";
            case token_type::EXCLAMATION_MARK: return "\"!\"";

            case token_type::ARROW: return "\"->\"";

            case token_type::COMMA: return "\",\"";
            case token_type::DOT: return "\".\"";

            case token_type::COLON: return "\":\"";
            case token_type::SEMICOLON: return "\";\"";

            case token_type::OPEN_PAREN: return "\"(\"";
            case token_type::CLOSE_PAREN: return "\")\"";

            case token_type::OPEN_BRACE: return "\"{\"";
            case token_type::CLOSE_BRACE: return "\"}\"";

            case token_type::OPEN_BRACK: return "\"[\"";
            case token_type::CLOSE_BRACK: return "\"]\"";

            case token_type::LESS: return "\"<\"";
            case token_type::GREATER: return "\">\"";

            case token_type::IN: return "\"in\"";
            case token_type::OUT: return "\"out\"";

            case token_type::ELIPSIS: return "\"...\"";

            case token_type::OPERATOR: return "<operator>";
        }

        return "<uknown>";
    }
}