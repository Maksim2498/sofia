export module sofia.util.fmt.optionals;

import <algorithm>;
import <format>;
import <optional>;

import sofia.util.typedefs;

export template<typename T>
struct std::formatter<std::optional<T>> {
    template<class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext &context) { return m_t_formatter.parse(context); }

    template<class FormatContext>
    typename FormatContext::iterator format(const std::optional<T> &value, FormatContext &context) const {
        return value.has_value()
            ? m_t_formatter.format(value.value(), context)
            : std::ranges::copy(sofia::sv8{"null"}, context.out()).out;
    }

private:
    std::formatter<T> m_t_formatter;
};