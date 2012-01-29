///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012 Benaka Moorthi
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if !defined( NODE_BIND_DETAIL_ACCESSOR_PROXY_HPP )
#define NODE_BIND_DETAIL_ACCESSOR_PROXY_HPP

#include <node-bind/detail/wrapped_type.hpp>
#include <node-bind/detail/extract_value.hpp>
#include <node.h>
#include <v8.h>

namespace nodebind
{
    template <typename T, typename C>
    struct accessor_proxy
    {
        typedef T C::* member_ptr_t;
    
        static v8::Handle<v8::Value> get(v8::Local<v8::String> property, v8::AccessorInfo const& info)
        {
            uint32_t member_ptr_value = info.Data()->NumberValue();
            member_ptr_t member_ptr = *reinterpret_cast<member_ptr_t *>(&member_ptr_value);
            
            C & instance = node::ObjectWrap::Unwrap<wrapped_type<C> >(info.This())->wrapped;

            return to_value_handle(instance.*member_ptr);
        }
        
        static void set(v8::Local<v8::String> property, v8::Local<v8::Value> value, v8::AccessorInfo const& info)
        {
            uint32_t member_ptr_value = info.Data()->NumberValue();
            member_ptr_t member_ptr = *reinterpret_cast<member_ptr_t *>(&member_ptr_value);
            
            C & instance = node::ObjectWrap::Unwrap<wrapped_type<C> >(info.This())->wrapped;
            
            instance.*member_ptr = extract_value<T>(value);
        }
    };
}

#endif // #if !defined( NODE_BIND_DETAIL_ACCESSOR_PROXY_HPP )

