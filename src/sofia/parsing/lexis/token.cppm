module;

#include <cassert>

#include <sofia/util/meta/macros.hpp>

export module sofia.parsing.lexis.token;

import <optional>;
import <utility>;
import <variant>;

import sofia.parsing.lexis.token_type;
import sofia.util.source.source_reference;
import sofia.util.typedefs;

export namespace sofia {
    class token {
    public:
        // Types

        using value_type = std::variant<
            std::monostate,
            bool,
            u64, // For integers and references to the string pool
            f32, f64
        >;

        // Constructors

        explicit token(
            const token_type type,
            const value_type value = std::monostate(),
            const std::optional<source_reference> &reference = std::nullopt
        ) noexcept :
            m_value(value), m_reference(reference), m_type(type)
        {
            assert(m_type_matching_value(type, value));
        }

        // Getters and setters

        // - Plain

        // -- Value

        [[nodiscard]] const value_type &value() const noexcept { return m_value; }

        void value(const value_type &value) noexcept {
            assert(m_type_matching_value(m_type, value));
            m_value = value;
        }

        // -- Reference

        [[nodiscard]] const std::optional<source_reference> &reference() const noexcept { return m_reference; }
        [[nodiscard]] std::optional<source_reference> &reference() noexcept { return m_reference; }

        void reference(const std::optional<source_reference> &reference) noexcept { m_reference = reference; }

        // -- Type

        [[nodiscard]] token_type type() const noexcept { return m_type; }

        // - With value conversion

        template<typename T>
        [[nodiscard]] const T &value_as() const { return std::get<T>(m_value); }

        template<typename T>
        [[nodiscard]] std::optional<T> value_as_or_nullopt() const noexcept {
            return std::holds_alternative<T>(m_value)
                ? std::get<T>(m_value)
                : std::nullopt;
        }

    private:
        // Validation

        static bool m_type_matching_value(const token_type type, const value_type &value) {
            switch (type) {
                case token_type::ERROR:
                    return std::holds_alternative<std::monostate>(value) || std::holds_alternative<u64>(value);

                case token_type::BOOL:
                    return std::holds_alternative<bool>(value);

                case token_type::F32:
                    return std::holds_alternative<f32>(value);

                case token_type::F64:
                    return std::holds_alternative<f64>(value);

                case token_type::COMMENT:

                case token_type::INDENT_SAME:
                case token_type::INDENT_GROW:
                case token_type::INDENT_SHRINK:

                case token_type::ID:

                case token_type::S8:
                case token_type::S16:
                case token_type::S32:

                case token_type::U8:
                case token_type::U16:
                case token_type::U32:
                case token_type::U64:
                case token_type::USIZE:

                case token_type::I8:
                case token_type::I16:
                case token_type::I32:
                case token_type::I64:
                case token_type::ISIZE:

                case token_type::OPERATOR:
                    return std::holds_alternative<u64>(value);

                default:
                    return std::holds_alternative<std::monostate>(value);
            }
        }

        // Fields

        value_type m_value;
        std::optional<source_reference> m_reference;
        token_type m_type;
    };
}

SOFIA_REFLECT_CLASS(sofia::token, value, reference, type);