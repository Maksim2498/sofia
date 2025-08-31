export module sofia.semantic.type;

import <variant>;

import sofia.util.typedefs;

export namespace sofia {
    class union_type {
    public:

    private:

    };

    class struct_type {
    public:

    private:

    };

    using type = std::variant<union_type, struct_type>;
}