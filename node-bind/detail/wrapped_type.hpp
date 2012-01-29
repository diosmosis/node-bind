#if !defined( NODE_BIND_DETAIL_WRAPPED_TYPE_HPP )
#define NODE_BIND_DETAIL_WRAPPED_TYPE_HPP

#include <v8.h>
#include <node.h>

namespace nodebind
{
    template <typename T>
    struct wrapped_type : node::ObjectWrap
    {
        template <typename... Args>
        wrapped_type(Args&&... args)
            : wrapped(args...)
        {}

        void Wrap(v8::Handle<v8::Object> handle)
        {
            node::ObjectWrap::Wrap(handle);
        }

        T wrapped;
    };
}

#endif // #if !defined( NODE_BIND_DETAIL_WRAPPED_TYPE_HPP )

