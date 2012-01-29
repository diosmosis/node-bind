#if !defined( NODE_BIND_DETAIL_GET_FUNCTION_FROM_HANDLE_HPP )
#define NODE_BIND_DETAIL_GET_FUNCTION_FROM_HANDLE_HPP

#include <v8.h>

namespace nodebind
{
    template <typename F>
    inline F * get_function_from_handle(v8::Handle<v8::Value> const& val)
    {
        static_assert(sizeof(void*) == sizeof(F*), "void * is not same size as F *");

        return reinterpret_cast<F *>(v8::External::Unwrap(val));
    }
}

#endif // #if !defined( NODE_BIND_DETAIL_GET_FUNCTION_FROM_HANDLE_HPP )

