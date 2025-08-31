export module sofia.util.meta.reflection;

import <concepts>;
import <tuple>;
import <type_traits>;

import sofia.util.meta.property;

export namespace sofia {
    // Types

    template<typename ObjectType>
    struct reflection {};

    // Concepts

    template<typename T, typename HolderType>
    concept property_tuple_for =
        std::same_as<T, std::tuple<>> ||
        (
            std::tuple_size_v<T> >= 1 &&
             []<typename... Ts>(std::type_identity<std::tuple<Ts...>>) {
                 return (std::is_same_v<Ts, property<HolderType, typename Ts::value_type>> && ...);
             }(std::type_identity<T>{})
         );

    template<typename T>
    concept validly_reflectable = requires {
        { reflection<T>::get() };
        requires property_tuple_for<decltype(reflection<T>::get()), T>;
    };
}