module;

#include <sofia/util/meta/macros.hpp>

export module sofia.util.source.source_message;

import sofia.util.containers.string_pool;
import sofia.util.source.source_message_type;
import sofia.util.source.source_reference;
import sofia.util.typedefs;

export namespace sofia {
    struct source_message {
        source_reference reference{};
        string_pool::key_type key{};
        source_message_type type{source_message_type::WARNING};
    };
}

SOFIA_REFLECT_STRUCT(sofia::source_message, reference, key, type);