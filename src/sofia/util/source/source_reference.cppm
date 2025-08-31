module;

#include <sofia/util/meta/macros.hpp>

export module sofia.util.source.source_reference;

import sofia.util.typedefs;

export namespace sofia {
    struct source_reference {
        usize index{};
        usize length{};
    };
}

SOFIA_REFLECT_STRUCT(sofia::source_reference, index, length);