export module sofia.util.fmt.objects;

import <format>;
import <typeinfo>;

import sofia.util.meta.all;
import sofia.util.typedefs;

export template<sofia::validly_reflectable T>
struct std::formatter<T> {
    template<class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext &context) { return context.begin(); }

    template<class FormatContext>
    typename FormatContext::iterator format(const T &object, FormatContext &context) const {
        auto fields = sofia::reflection<T>::get();
        auto out = context.out();

        out = std::format_to(out, "{{");

        std::apply(
            [&]<typename ...Args>(Args &&...args) {
                constexpr sofia::usize size = sizeof...(Args);
                sofia::usize index = 0;

                ([&](auto &&arg) {
                    out = std::format_to(out, "{}={}", arg.name, arg.getter(object));

                    if (index++ < size - 1)
                        out = std::format_to(out, ", ");
                }(args), ...);
            },
            fields
        );

        return std::format_to(out, "}}");
    }
};