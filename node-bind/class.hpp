///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012 Benaka Moorthi
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if !defined( NODE_BIND_CLASS_HPP )
#define NODE_BIND_CLASS_HPP

#include <node-bind/construct.hpp>
#include <node-bind/call_policy/sync.hpp>
#include <node-bind/detail/accessor_proxy.hpp>
#include <node-bind/detail/wrapped_type.hpp>
#include <node-bind/detail/call_using_node_args.hpp>
#include <node-bind/detail/worker_base.hpp>
#include <list>
#include <string>
#include <type_traits>
#include <v8.h>

namespace nodebind
{
    template <
        typename T,
        typename Constructor = construct<>
    >
    struct class_export
    {
        typedef class_export<T, Constructor> self_type;
    
        class_export(
            v8::Handle<v8::Object> target_
          , std::string const& name_
          , Constructor constructor = 0
        ) : target(target_)
          , name(name_)
          , klass(v8::FunctionTemplate::New(&self_type::New))
        {
            klass->SetClassName(v8::String::New(name.c_str()));
            klass->InstanceTemplate()->SetInternalFieldCount(1);
        }
        
        ~class_export()
        {
            try
            {
                v8::Persistent<v8::Function> constructor = v8::Persistent<v8::Function>::New(klass->GetFunction());
                target->Set(v8::String::New(name.c_str()), constructor);
            }
            catch (...)
            {
                // TODO (log to console? what else can I do?)
            }
        }
        
        template <typename Field>
        typename std::enable_if<
            std::is_member_object_pointer<Field T::*>::value && !std::is_base_of<worker_base, Field>::value,
            class_export &
        >::type set(std::string const& name, Field T::* member)
        {
            // sanity check
            static_assert(sizeof(Field T::*) == sizeof(uint32_t), "member pointer not the size of uint32_t");
        
            typedef accessor_proxy<Field, T> proxy_t;

            klass->PrototypeTemplate()->SetAccessor(
                v8::String::New(name.c_str()),
                &proxy_t::get,
                &proxy_t::set,
                v8::Number::New(*reinterpret_cast<uint32_t*>(&member))
            );
            return *this;
        }

        template <typename Field>
        typename std::enable_if<
            std::is_base_of<worker_base, Field>::value,
            class_export &
        >::type set(std::string const& name, Field T::* member)
        {
            // sanity check
            static_assert(sizeof(Field T::*) == sizeof(uint32_t), "member pointer not the size of uint32_t");

            v8::InvocationCallback func = &worker_base::call<T, Field>;
            
            klass->PrototypeTemplate()->Set(
                v8::String::New(name.c_str()),
                v8::FunctionTemplate::New(func, v8::Number::New(*reinterpret_cast<uint32_t*>(&member)))
            );
            
            return *this;
        }
        
        template <typename F, typename CallPolicy>
        class_export & set(std::string const& name, F method_, CallPolicy policy)
        {// TODO: make sure F is a method of type T w/ static_assert
            // pointer-to-member-functions are bigger than pointers... can't simply wrap them.
            // this hack gets around it. but its not a very good hack...
            static std::list<F> pointers;
            
            pointers.push_back(method_);
            
            v8::InvocationCallback func = &CallPolicy::template apply<F>::call;
            
            klass->PrototypeTemplate()->Set(
                v8::String::New(name.c_str()),
                v8::FunctionTemplate::New(func, v8::External::Wrap(&pointers.back()))->GetFunction()
            );

            return *this;
        }
        
        template <typename F>
        typename std::enable_if<
            std::is_member_function_pointer<F>::value,
            class_export &
        >::type set(std::string const& name, F method_)
        {
            return set(name, method_, sync_call_policy());
        }
        
        static v8::Handle<v8::Value> New(const v8::Arguments& args)
        {
            v8::HandleScope scope;
            
            wrapped_type<T> * instance = call_using_node_args(
                &Constructor::template apply<wrapped_type<T> >::call, args);
            instance->Wrap(args.This());
            
            return args.This();
        }
    
        v8::Handle<v8::Object> target;
        std::string name;
        v8::Local<v8::FunctionTemplate> klass;
    };
}

#endif // #if !defined( NODE_BIND_CLASS_HPP )

