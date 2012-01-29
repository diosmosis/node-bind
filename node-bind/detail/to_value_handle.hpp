#if !defined( NODE_BIND_DETAIL_TO_VALUE_HANDLE_HPP )
#define NODE_BIND_DETAIL_TO_VALUE_HANDLE_HPP

#include <node-bind/undefined.hpp>
#include <node-bind/optional.hpp>
#include <v8.h>
#include <string>

namespace nodebind
{
    template <typename T>
    inline v8::Handle<v8::Value> to_value_handle(T const& value)
    {
        return static_cast<v8::Handle<v8::Value> >(value);
    }
    
    inline v8::Handle<v8::Value> to_value_handle(keyword::undefined_t)
    {
        return v8::Handle<v8::Value>(v8::Undefined());
    }
    
    inline v8::Handle<v8::Value> to_value_handle(int32_t value)
    {
        return v8::Integer::New(value);
    }
    
    inline v8::Handle<v8::Value> to_value_handle(uint32_t value)
    {
        return v8::Integer::NewFromUnsigned(value);
    }
    
    inline v8::Handle<v8::Value> to_value_handle(bool value)
    {
        return v8::Boolean::New(value);
    }
    
    inline v8::Handle<v8::Value> to_value_handle(double value)
    {
        return v8::Number::New(value);
    }
    
    inline v8::Handle<v8::Value> to_value_handle(std::string const& value)
    {
        return v8::String::New(value.c_str());
    }
    
    template <typename T>
    inline v8::Handle<v8::Value> to_value_handle(optional<T> const& value)
    {
        return value ? to_value_handle(value.get()) : v8::Handle<v8::Value>(v8::Undefined());
    }
}

#endif // #if !defined( NODE_BIND_DETAIL_TO_VALUE_HANDLE_HPP )

