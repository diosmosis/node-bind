///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012 Benaka Moorthi
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if !defined( NODE_MODULE_HPP )
#define NODE_MODULE_HPP

#include <node-bind/call_policy/sync.hpp>
#include <node-bind/class.hpp>

#include <v8.h>
#include <string>

#define NODE_BIND_MODULE( module_name )                         \
    struct module_name ## module : nodebind::module_export      \
    {                                                           \
        module_name ## module(v8::Handle<v8::Object> target)    \
            : nodebind::module_export(#module_name, target)     \
        {                                                       \
        }                                                       \
                                                                \
        static void init(v8::Handle<v8::Object> target)         \
        {                                                       \
            module_name ## module(target).init();               \
        }                                                       \
                                                                \
        void init();                                            \
    };                                                          \
                                                                \
    NODE_MODULE(module_name, module_name ## module::init)       \
                                                                \
    void module_name ## module::init()

namespace nodebind
{
    struct module_export
    {
        module_export(std::string const& name, v8::Handle<v8::Object> target_)
            : target(target_)
        {
        }
        
        template <typename F, typename CallPolicy>
        module_export & set(std::string const& name, F method, CallPolicy policy)
        {
            v8::InvocationCallback func = &CallPolicy::template apply<F>::call;

            target->Set(
                v8::String::NewSymbol(name.c_str()),
                v8::FunctionTemplate::New(func, v8::External::Wrap(method))->GetFunction()
            );

            return *this;
        }
        
        template <typename F>
        module_export & set(std::string const& name, F method)
        {
            return set(name, method, sync_call_policy());
        }
        
        template <typename T, typename C>
        class_export<T, C> class_(std::string const& name, C constructor)
        {
            return class_export<T, C>(target, name, constructor);
        }

    protected:
        v8::Handle<v8::Object> target;
    };
}

#endif // #if !defined( NODE_MODULE_HPP )

