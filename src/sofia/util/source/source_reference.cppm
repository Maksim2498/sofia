module;

#include <cassert>

#include <sofia/util/meta/macros.hpp>

export module sofia.util.source.source_reference;

import sofia.util.typedefs;

export namespace sofia {
    struct source_reference {
        usize index{};
        usize length{};

        [[nodiscard]] sv8 extract_text(const sv8 source) const noexcept {
            assert(index <= source.length() && index + length <= source.length());
            return source.substr(index, length);
        }
    };
}

SOFIA_REFLECT_STRUCT(sofia::source_reference, index, length);