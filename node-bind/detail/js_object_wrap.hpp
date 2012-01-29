#if !defined( NODE_BIND_DETAIL_JS_OBJECT_WRAP_HPP )
#define NODE_BIND_DETAIL_JS_OBJECT_WRAP_HPP

#include <v8.h>

namespace nodebind
{
    struct js_object_wrap
    {
        explicit js_object_wrap(v8::Handle<v8::Value> const& x)
            : handle(x)
        {}

        operator v8::Handle<v8::Value>() const
        {
            return handle;
        }

    protected:
        v8::Handle<v8::Value> handle;
    };
}

#endif // #if !defined( NODE_BIND_DETAIL_JS_OBJECT_WRAP_HPP )

