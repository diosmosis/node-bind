#if !defined( NODE_BIND_CALL_POLICY_SYNC_HPP )
#define NODE_BIND_CALL_POLICY_SYNC_HPP

#include <node-bind/detail/get_function_from_handle.hpp>
#include <node-bind/detail/to_value_handle.hpp>
#include <node-bind/detail/call_using_node_args.hpp>
#include <v8.h>

namespace nodebind
{
    template <typename F>
    struct function_proxy;
    
    template <typename R, typename... Args>
    struct function_proxy<R(Args...)>
    {
        typedef R(function_type)(Args...);

        static v8::Handle<v8::Value> call(v8::Arguments const& args)
        {
            v8::HandleScope scope;
            
            // TODO arg checking
        /*if (args.Length() < 1)
        {
            v8::ThrowException(
                v8::Exception::TypeError(v8::String::New("Wrong number of arguments, expected 1.")));
            return scope.Close(v8::Undefined());
        }*/

            function_type * f = get_function_from_handle<function_type>(args.Data());
            v8::Handle<v8::Value> result = to_value_handle(call_using_node_args(f, args));

            return scope.Close(result);
        }
    };
    
    template <typename... Args>
    struct function_proxy<void(Args...)>
    {
        typedef void(function_type)(Args...);

        static v8::Handle<v8::Value> call(v8::Arguments const& args)
        {
            v8::HandleScope scope;
            
            function_type * f = get_function_from_handle<function_type>(args.Data());
            call_using_node_args(f, args);
            
            return scope.Close(v8::Undefined());
        }
    };
    
    template <typename C, typename R, typename... Args>
    struct function_proxy<R(C::*)(Args...)>
    {
        typedef R(C::*function_ptr_type)(Args...);

        static v8::Handle<v8::Value> call(v8::Arguments const& args)
        {
            v8::HandleScope scope;
            
            function_ptr_type f = *static_cast<function_ptr_type*>(v8::External::Unwrap(args.Data()));
            v8::Handle<v8::Value> result = to_value_handle(call_using_node_args(f, args));
            
            return scope.Close(result);
        }
    };

    template <typename C, typename... Args>
    struct function_proxy<void(C::*)(Args...)>
    {
        typedef void(C::*function_ptr_type)(Args...);
        
        static v8::Handle<v8::Value> call(v8::Arguments const& args)
        {
            v8::HandleScope scope;
            
            function_ptr_type f = *static_cast<function_ptr_type*>(v8::External::Unwrap(args.Data()));
            call_using_node_args(f, args);
            
            return scope.Close(v8::Undefined());
        }
    };

    template <typename F>
    struct function_proxy<F*>
        : function_proxy<F>
    {};
    
    struct sync_call_policy
    {
        template <typename F>
        struct apply
            : function_proxy<F>
        {};
    };
}

#endif // #if !defined( NODE_BIND_CALL_POLICY_SYNC_HPP )

