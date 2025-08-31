export module sofia.util.meta.property;

export namespace sofia {
    template<typename HolderType, typename ValueType>
    struct property {
        // Types

        using holder_type = HolderType;
        using value_type = ValueType;

        // Fields

        const char *name;
        ValueType (*getter)(const HolderType&);
    };

    template<typename HolderType, typename ValueType>
    property<HolderType, ValueType> make_property(const char* name, ValueType (*getter)(const HolderType&)) noexcept {
        return { name, getter };
    }
}