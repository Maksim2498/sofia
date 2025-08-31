export module sofia.util.meta.enums;

import <concepts>;
import <type_traits>;

import sofia.util.typedefs;

export namespace sofia {
    template<typename T>
    concept named_enum = std::is_enum_v<T> && requires(T t) {
        { name(t) } -> std::convertible_to<sv8>;
    };
}