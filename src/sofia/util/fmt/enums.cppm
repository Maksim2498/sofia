export module sofia.util.fmt.enums;

import <algorithm>;
import <format>;

import sofia.util.meta.enums;
import sofia.util.typedefs;

export template<sofia::named_enum T>
struct std::formatter<T> {
    template<class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext &context) { return context.begin(); }

    template<class FormatContext>
    typename FormatContext::iterator format(T entry, FormatContext &context) const {
        const sofia::sv8 entry_name = name(entry);
        return std::ranges::copy(entry_name, context.out()).out;
    }
};