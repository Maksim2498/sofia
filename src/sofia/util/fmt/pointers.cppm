export module sofia.util.fmt.pointers;

import <algorithm>;
import <format>;

import sofia.util.typedefs;

export template<typename T>
struct std::formatter<T*> {
    template<class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext &context) { return context.begin(); }

    template<class FormatContext>
    typename FormatContext::iterator format(const T *value, FormatContext &context) const {
        return value != nullptr
            ? std::format_to(context.out(), "{}", *value)
            : std::ranges::copy(sofia::sv8{"null"}, context.out()).out;
    }
};