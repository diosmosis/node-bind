#if !defined( NODE_BIND_DETAIL_CALL_USING_NODE_ARGS_HPP )
#define NODE_BIND_DETAIL_CALL_USING_NODE_ARGS_HPP

#include <node-bind/detail/get_wrapped_object.hpp>
#include <node-bind/detail/extract_value.hpp>
#include <v8.h>

namespace nodebind
{
    // TODO: check validity of arguments
    template <typename R>
    inline R call_using_node_args(R(*f)(), v8::Arguments const& args)
    {
        return f();
    }
    
    template <typename R, typename A0>
    inline R call_using_node_args(R(*f)(A0), v8::Arguments const& args)
    {
        return f(extract_value<A0>(args[0]));
    }
    
    template <typename R, typename A0, typename A1>
    inline R call_using_node_args(R(*f)(A0,A1), v8::Arguments const& args)
    {
        return f(extract_value<A0>(args[0]),
                 extract_value<A1>(args[1]));
    }
    
    // member functions
    template <typename C, typename R>
    inline R call_using_node_args(R(C::*f)(), v8::Arguments const& args)
    {
        C & self = get_wrapped_object<C>(args); // TODO: check availability of self somewhere? Can't be null.
        return (self.*f)();
    }

    template <typename C, typename R, typename A0>
    inline R call_using_node_args(R(C::*f)(A0), v8::Arguments const& args)
    {
        C & self = get_wrapped_object<C>(args);
        return (self.*f)(extract_value<A0>(args[0]));
    }
}

#endif // #if !defined( NODE_BIND_DETAIL_CALL_USING_NODE_ARGS_HPP )

