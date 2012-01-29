///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012 Benaka Moorthi
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if !defined( NODEBIND_DETAIL_SET_ARGUMENT_TUPLE_HPP )
#define NODEBIND_DETAIL_SET_ARGUMENT_TUPLE_HPP

#include <node-bind/detail/extract_value.hpp>
#include <tuple>
#include <v8.h>

namespace nodebind
{
    inline void set_argument_tuple(std::tuple<> &, v8::Persistent<v8::Function> & cb, v8::Arguments const& args)
    {
        // TODO check args
        cb = v8::Persistent<v8::Function>::New(v8::Handle<v8::Function>::Cast(args[0]));
    }
    
    template <typename T0>
    inline void set_argument_tuple(std::tuple<T0> & stored, v8::Persistent<v8::Function> & cb, v8::Arguments const& args)
    {
        // TODO check args
        std::get<0>(stored) = extract_value<T0>(args[0]);
        cb = v8::Persistent<v8::Function>::New(v8::Handle<v8::Function>::Cast(args[1]));
    }
    
    template <typename T0, typename T1>
    inline void set_argument_tuple(std::tuple<T0, T1> & stored, v8::Persistent<v8::Function> & cb, v8::Arguments const& args)
    {
        // TODO check args
        std::get<0>(stored) = extract_value<T0>(args[0]);
        std::get<1>(stored) = extract_value<T1>(args[1]);
        cb = v8::Persistent<v8::Function>::New(v8::Handle<v8::Function>::Cast(args[2]));
    }
}

#endif // #if !defined( NODEBIND_DETAIL_SET_ARGUMENT_TUPLE_HPP )

