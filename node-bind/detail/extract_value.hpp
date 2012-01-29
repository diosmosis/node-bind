///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012 Benaka Moorthi
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if !defined( NODE_BIND_DETAIL_EXTRACT_VALUE_HPP )
#define NODE_BIND_DETAIL_EXTRACT_VALUE_HPP

#include <node-bind/detail/clean.hpp>
#include <node-bind/function.hpp>
#include <string>
#include <cstdint>
#include <v8.h>

namespace nodebind
{
    template <typename T>
    struct extract_value_impl;
    
    template <>
    struct extract_value_impl<bool>
    {
        static bool apply(v8::Handle<v8::Value> const& value)
        {
            return value->BooleanValue();
        }
    };
    
    template <>
    struct extract_value_impl<double>
    {
        static double apply(v8::Handle<v8::Value> const& value)
        {
            return value->NumberValue();
        }
    };

    template <>
    struct extract_value_impl<int64_t>
    {
        static int64_t apply(v8::Handle<v8::Value> const& value)
        {
            return value->IntegerValue();
        }
    };
    
    template <>
    struct extract_value_impl<uint64_t>
    {
        static uint64_t apply(v8::Handle<v8::Value> const& value)
        {
            return value->IntegerValue();
        }
    };
    
    template <>
    struct extract_value_impl<uint32_t>
    {
        static uint32_t apply(v8::Handle<v8::Value> const& value)
        {
            return value->Uint32Value();
        }
    };
    
    template <>
    struct extract_value_impl<int32_t>
    {
        static int32_t apply(v8::Handle<v8::Value> const& value)
        {
            return value->Int32Value();
        }
    };
    
    template <>
    struct extract_value_impl<std::string>
    {
        // TODO: use a const_string class. would be much faster.
        static std::string apply(v8::Handle<v8::Value> const& value)
        {
            v8::String::AsciiValue ascii(value);

            char const* result = *ascii;
            return result ? std::string(result) : "<string conversion failed>";
        }
    };

    template <>
    struct extract_value_impl<function>
    {
        static function apply(v8::Handle<v8::Value> const& value)
        {
            return function(v8::Handle<v8::Function>::Cast(value));
        }
    };
    
    template <typename T>
    struct extract_value_impl<T const>
        : extract_value_impl<T>
    {};

    template <typename T>
    inline typename clean<T>::type extract_value(v8::Handle<v8::Value> value)
    {
        return extract_value_impl<typename clean<T>::type>::apply(value);
    }
}

#endif // #if !defined( NODE_BIND_DETAIL_EXTRACT_VALUE_HPP )

