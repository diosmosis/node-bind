///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012 Benaka Moorthi
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if !defined( NODE_BIND_WORKER_HPP )
#define NODE_BIND_WORKER_HPP

#include <node-bind/optional.hpp>
#include <node-bind/undefined.hpp>
#include <node-bind/function.hpp>
#include <node-bind/async_policy/nonblocking.hpp>
#include <node-bind/async_policy/simultaneous.hpp>
#include <node-bind/detail/set_argument_tuple.hpp>
#include <node-bind/detail/worker_base.hpp>
#include <tuple>
#include <v8.h>

namespace nodebind
{
    template <typename S>
    struct make_arg_tuple;
    
    template <typename R, typename... Args>
    struct make_arg_tuple<R(Args...)>
    {
        typedef std::tuple<Args...> type;
    };
    
    template <
        typename Signature,
        typename AsyncCallPolicy = nonblocking_async_policy
    >
    struct worker : worker_base, AsyncCallPolicy
    {
        typedef typename make_arg_tuple<Signature>::type arg_tuple_type;

        optional<std::string> error;
        arg_tuple_type stored_args;
        v8::Persistent<v8::Function> callback;
    
        bool store_arguments(v8::Arguments const& args)
        {
            set_argument_tuple(stored_args, callback, args);
        }

        void after(function const& callback)
        {
            callback(error, keyword::undefined);
        }
    };
}

#endif // #if !defined( NODE_BIND_WORKER_HPP )

