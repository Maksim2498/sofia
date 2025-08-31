export module sofia.util.source.source_message_type;

import sofia.util.typedefs;

export namespace sofia {
    enum class source_message_type : u8 {
        WARNING,
        ERROR,
    };

    [[nodiscard]] sv8 name(const source_message_type type) noexcept {
        switch (type) {
            case source_message_type::WARNING: return "warning";
            case source_message_type::ERROR: return "error";
        }

        return "UNKNOWN";
    }
}