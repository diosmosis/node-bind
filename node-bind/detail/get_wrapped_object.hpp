#if !defined( NODE_BIND_DETAIL_GET_WRAPPED_OBJECT_HPP )
#define NODE_BIND_DETAIL_GET_WRAPPED_OBJECT_HPP

#include <node-bind/detail/wrapped_type.hpp>
#include <v8.h>

namespace nodebind
{
    template <typename C>
    inline C & get_wrapped_object(v8::Arguments const& args)
    {
        return node::ObjectWrap::Unwrap<wrapped_type<C> >(args.This())->wrapped;
    }
}

#endif // #if !defined( NODE_BIND_DETAIL_GET_WRAPPED_OBJECT_HPP )

