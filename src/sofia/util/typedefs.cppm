export module sofia.util.typedefs;

import <limits>;
import <string>;
import <string_view>;

import <cinttypes>;
import <cstddef>;

export import <string>;
export import <string_view>;

export namespace sofia {
    using s8 = std::string;
    using s16 = std::u16string;
    using s32 = std::u32string;

    using sv8 = std::string_view;
    using sv16 = std::u16string_view;
    using sv32 = std::u32string_view;

    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;
    using usize = std::size_t;

    using i8 = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;
    using isize = std::ptrdiff_t;

    using f32 = float;
    using f64 = double;

    static_assert(
        sizeof(f32) == 4 && std::numeric_limits<f32>::is_iec559,
        "Non IEEE 754 float types aren't supported"
    );

    static_assert(
        sizeof(f64) == 8 && std::numeric_limits<f64>::is_iec559,
        "Non IEEE 754 double types aren't supported"
    );
}