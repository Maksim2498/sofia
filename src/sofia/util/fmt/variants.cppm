export module sofia.util.fmt.variants;

import <algorithm>;
import <format>;
import <variant>;

import sofia.util.typedefs;

export template<typename ...Ts>
struct std::formatter<std::variant<Ts...>> {
    template<class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext &context) { return context.begin(); }

    template<class FormatContext>
    typename FormatContext::iterator format(const std::variant<Ts...> &value, FormatContext &context) const {
        return value.valueless_by_exception()
            ? std::ranges::copy(sofia::sv8{"empty"}, context.out()).out
            : std::visit([&](const auto &entry) { return std::format_to(context.out(), "{}", entry); }, value);
    }
};

export template<>
struct std::formatter<std::monostate> {
    template<class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext &context) { return context.begin(); }

    template<class FormatContext>
    typename FormatContext::iterator format(const std::monostate&, FormatContext &context) const {
        return std::ranges::copy(sofia::sv8{"empty"}, context.out()).out;
    }
};