#if !defined( NODE_BIND_STRING_HPP )
#define NODE_BIND_STRING_HPP

#include <node-bind/detail/js_object_wrap.hpp>
#include <algorithm>
#include <v8.h>

namespace nodebind
{
    struct string : js_object_wrap
    {
        typedef js_object_wrap base_type;

        string()
            : base_type(v8::String::New(""))
        {}

        explicit string(char const* str)
            : base_type(v8::String::New(str))
        {}
        
        explicit string(std::string const& x)
            : base_type(v8::String::New(x.c_str()))
        {}

        string(string const& x)
            : base_type(x.handle)
        {}

        string & operator = (string const& x)
        {
            handle = x.handle;
            return *this;
        }
        
        string & operator = (char const* str)
        {
            string(str).swap(*this);
            return *this;
        }
        
        string & operator = (std::string const& x)
        {
            string(x).swap(*this);
            return *this;
        }
        
        void swap(string & other)
        {
            std::swap(handle, other.handle);
        }
        
        // TODO: other methods like indexOf
    };
}

#endif // #if !defined( NODE_BIND_STRING_HPP )

