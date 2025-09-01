module;

#include <cassert>

#include <sofia/util/meta/macros.hpp>

export module sofia.util.source.detailed_source_reference;

import sofia.util.source.source_reference;
import sofia.util.typedefs;

export namespace sofia {
    struct detailed_source_reference : source_reference {
        [[nodiscard]] static detailed_source_reference from_source_and_reference(
            const sv8 source,
            const source_reference reference
        ) noexcept {
            assert(reference.index <= source.length() && reference.index + reference.length <= source.length());

            detailed_source_reference detailed_reference{reference.index, reference.length};

            for (usize i = 0; i < detailed_reference.index; ++i)
                if (source[i] == '\n') {
                    ++detailed_reference.row_index;
                    detailed_reference.column_index = 0;
                } else
                    ++detailed_reference.column_index;

            return detailed_reference;
        }

        usize column_index{};
        usize row_index{};
    };
}

SOFIA_REFLECT_STRUCT(sofia::detailed_source_reference, index, length, column_index, row_index);