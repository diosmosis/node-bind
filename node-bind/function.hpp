#if !defined( NODE_BIND_FUNCTION_HPP )
#define NODE_BIND_FUNCTION_HPP

#include <node-bind/detail/call_js_function.hpp>
#include <node-bind/detail/js_object_wrap.hpp>
#include <v8.h>

namespace nodebind
{
    struct function : js_object_wrap
    {
        typedef js_object_wrap base_type;

        function()
            : base_type(v8::Undefined())
        {}
        
        explicit function(v8::Handle<v8::Function> const& x)
            : base_type(x)
        {}

        // TODO: allow return type to be used. right now, its ignored.
        // TODO: allow self to be overridden
        template <typename... Args>
        void operator()(Args&&... args) const
        {
            call_js_function(
                v8::Handle<v8::Function>::Cast(handle),
                v8::Handle<v8::Object>::Cast(handle),
                args...
            );
        }
    };
}

#endif // #if !defined( NODE_BIND_FUNCTION_HPP )

