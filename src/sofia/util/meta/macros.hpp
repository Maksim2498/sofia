#ifndef SOFIA_UTIL_META_MACROS_HPP
#define SOFIA_UTIL_META_MACROS_HPP

import sofia.util.meta.all;

// Properties

#define SOFIA_FIELD_PROPERTY(Type, name) \
    SOFIA_PROPERTY(Type, name, name)

#define SOFIA_GETTER_PROPERTY(Type, name) \
    SOFIA_PROPERTY(Type, name, name())

#define SOFIA_PROPERTY(Type, name, getter) \
    sofia::make_property(#name, +[](const Type &o) { return o.getter; })

// Properties expansion

// - Field

#define SOFIA_EXPAND_FIELD_PROPERTIES_1(Type, name)       SOFIA_FIELD_PROPERTY(Type, name)
#define SOFIA_EXPAND_FIELD_PROPERTIES_2(Type, name, ...)  SOFIA_FIELD_PROPERTY(Type, name), SOFIA_EXPAND_FIELD_PROPERTIES_1(Type, __VA_ARGS__)
#define SOFIA_EXPAND_FIELD_PROPERTIES_3(Type, name, ...)  SOFIA_FIELD_PROPERTY(Type, name), SOFIA_EXPAND_FIELD_PROPERTIES_2(Type, __VA_ARGS__)
#define SOFIA_EXPAND_FIELD_PROPERTIES_4(Type, name, ...)  SOFIA_FIELD_PROPERTY(Type, name), SOFIA_EXPAND_FIELD_PROPERTIES_3(Type, __VA_ARGS__)
#define SOFIA_EXPAND_FIELD_PROPERTIES_5(Type, name, ...)  SOFIA_FIELD_PROPERTY(Type, name), SOFIA_EXPAND_FIELD_PROPERTIES_4(Type, __VA_ARGS__)
#define SOFIA_EXPAND_FIELD_PROPERTIES_6(Type, name, ...)  SOFIA_FIELD_PROPERTY(Type, name), SOFIA_EXPAND_FIELD_PROPERTIES_5(Type, __VA_ARGS__)
#define SOFIA_EXPAND_FIELD_PROPERTIES_7(Type, name, ...)  SOFIA_FIELD_PROPERTY(Type, name), SOFIA_EXPAND_FIELD_PROPERTIES_6(Type, __VA_ARGS__)
#define SOFIA_EXPAND_FIELD_PROPERTIES_8(Type, name, ...)  SOFIA_FIELD_PROPERTY(Type, name), SOFIA_EXPAND_FIELD_PROPERTIES_7(Type, __VA_ARGS__)
#define SOFIA_EXPAND_FIELD_PROPERTIES_9(Type, name, ...)  SOFIA_FIELD_PROPERTY(Type, name), SOFIA_EXPAND_FIELD_PROPERTIES_8(Type, __VA_ARGS__)
#define SOFIA_EXPAND_FIELD_PROPERTIES_10(Type, name, ...) SOFIA_FIELD_PROPERTY(Type, name), SOFIA_EXPAND_FIELD_PROPERTIES_9(Type, __VA_ARGS__)

#define SOFIA_GET_EXPAND_FIELD_PROPERTIES_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME

#define SOFIA_EXPAND_FIELD_PROPERTIES(Type, ...)    \
    SOFIA_GET_EXPAND_FIELD_PROPERTIES_N(            \
        __VA_ARGS__,                                \
        SOFIA_EXPAND_FIELD_PROPERTIES_10,           \
        SOFIA_EXPAND_FIELD_PROPERTIES_9,            \
        SOFIA_EXPAND_FIELD_PROPERTIES_8,            \
        SOFIA_EXPAND_FIELD_PROPERTIES_7,            \
        SOFIA_EXPAND_FIELD_PROPERTIES_6,            \
        SOFIA_EXPAND_FIELD_PROPERTIES_5,            \
        SOFIA_EXPAND_FIELD_PROPERTIES_4,            \
        SOFIA_EXPAND_FIELD_PROPERTIES_3,            \
        SOFIA_EXPAND_FIELD_PROPERTIES_2,            \
        SOFIA_EXPAND_FIELD_PROPERTIES_1             \
    )(Type, __VA_ARGS__)

// - Getter

#define SOFIA_EXPAND_GETTER_PROPERTIES_1(Type, name)       SOFIA_GETTER_PROPERTY(Type, name)
#define SOFIA_EXPAND_GETTER_PROPERTIES_2(Type, name, ...)  SOFIA_GETTER_PROPERTY(Type, name), SOFIA_EXPAND_GETTER_PROPERTIES_1(Type, __VA_ARGS__)
#define SOFIA_EXPAND_GETTER_PROPERTIES_3(Type, name, ...)  SOFIA_GETTER_PROPERTY(Type, name), SOFIA_EXPAND_GETTER_PROPERTIES_2(Type, __VA_ARGS__)
#define SOFIA_EXPAND_GETTER_PROPERTIES_4(Type, name, ...)  SOFIA_GETTER_PROPERTY(Type, name), SOFIA_EXPAND_GETTER_PROPERTIES_3(Type, __VA_ARGS__)
#define SOFIA_EXPAND_GETTER_PROPERTIES_5(Type, name, ...)  SOFIA_GETTER_PROPERTY(Type, name), SOFIA_EXPAND_GETTER_PROPERTIES_4(Type, __VA_ARGS__)
#define SOFIA_EXPAND_GETTER_PROPERTIES_6(Type, name, ...)  SOFIA_GETTER_PROPERTY(Type, name), SOFIA_EXPAND_GETTER_PROPERTIES_5(Type, __VA_ARGS__)
#define SOFIA_EXPAND_GETTER_PROPERTIES_7(Type, name, ...)  SOFIA_GETTER_PROPERTY(Type, name), SOFIA_EXPAND_GETTER_PROPERTIES_6(Type, __VA_ARGS__)
#define SOFIA_EXPAND_GETTER_PROPERTIES_8(Type, name, ...)  SOFIA_GETTER_PROPERTY(Type, name), SOFIA_EXPAND_GETTER_PROPERTIES_7(Type, __VA_ARGS__)
#define SOFIA_EXPAND_GETTER_PROPERTIES_9(Type, name, ...)  SOFIA_GETTER_PROPERTY(Type, name), SOFIA_EXPAND_GETTER_PROPERTIES_8(Type, __VA_ARGS__)
#define SOFIA_EXPAND_GETTER_PROPERTIES_10(Type, name, ...) SOFIA_GETTER_PROPERTY(Type, name), SOFIA_EXPAND_GETTER_PROPERTIES_9(Type, __VA_ARGS__)

#define SOFIA_GET_EXPAND_GETTER_PROPERTIES_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME

#define SOFIA_EXPAND_GETTER_PROPERTIES(Type, ...)   \
    SOFIA_GET_EXPAND_GETTER_PROPERTIES_N(           \
        __VA_ARGS__,                                \
        SOFIA_EXPAND_GETTER_PROPERTIES_10,          \
        SOFIA_EXPAND_GETTER_PROPERTIES_9,           \
        SOFIA_EXPAND_GETTER_PROPERTIES_8,           \
        SOFIA_EXPAND_GETTER_PROPERTIES_7,           \
        SOFIA_EXPAND_GETTER_PROPERTIES_6,           \
        SOFIA_EXPAND_GETTER_PROPERTIES_5,           \
        SOFIA_EXPAND_GETTER_PROPERTIES_4,           \
        SOFIA_EXPAND_GETTER_PROPERTIES_3,           \
        SOFIA_EXPAND_GETTER_PROPERTIES_2,           \
        SOFIA_EXPAND_GETTER_PROPERTIES_1            \
    )(Type, __VA_ARGS__)

// Reflection

#define SOFIA_REFLECT_STRUCT(Type, ...) \
    template<> \
    struct sofia::reflection<Type> { \
        static auto get() { \
            return std::make_tuple(SOFIA_EXPAND_FIELD_PROPERTIES(Type, __VA_ARGS__)); \
        } \
    }

#define SOFIA_REFLECT_CLASS(Type, ...) \
    template<> \
    struct sofia::reflection<Type> { \
        static auto get() { \
            return std::make_tuple(SOFIA_EXPAND_GETTER_PROPERTIES(Type, __VA_ARGS__)); \
        } \
    }

#endif