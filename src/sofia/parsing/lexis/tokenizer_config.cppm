module;

#include <sofia/util/meta/macros.hpp>

export module sofia.parsing.lexis.tokenizer_config;

import sofia.util.typedefs;

export namespace sofia {
    struct tokenizer_config {
        bool is_indent_types_mixture_allowed = true;
        u8 spaces_in_tab = 4;
    };
}

SOFIA_REFLECT_STRUCT(sofia::tokenizer_config, is_indent_types_mixture_allowed, spaces_in_tab);