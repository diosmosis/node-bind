///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012 Benaka Moorthi
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if !defined( NODE_BIND_DETAIL_CALL_JS_FUNCTION_HPP )
#define NODE_BIND_DETAIL_CALL_JS_FUNCTION_HPP

#include <node-bind/detail/to_value_handle.hpp>
#include <v8.h>

namespace nodebind
{
    inline void call_js_function(
        v8::Handle<v8::Function> const& function,
        v8::Handle<v8::Object> const& self)
    {
        v8::Handle<v8::Value> args[] = {};

        function->Call(self, 0, args);
    }
    
    template <typename A0>
    inline void call_js_function(
        v8::Handle<v8::Function> const& function,
        v8::Handle<v8::Object> const& self,
        A0 const& arg0)
    {
        v8::Handle<v8::Value> args[] = {to_value_handle(arg0)};

        function->Call(self, 1, args);
    }

    template <typename A0, typename A1>
    inline void call_js_function(
        v8::Handle<v8::Function> const& function,
        v8::Handle<v8::Object> const& self,
        A0 const& arg0,
        A1 const& arg1)
    {
        v8::Handle<v8::Value> args[] = {to_value_handle(arg0), to_value_handle(arg1)};

        function->Call(self, 2, args);
    }
}

#endif // #if !defined( NODE_BIND_DETAIL_CALL_JS_FUNCTION_HPP )

