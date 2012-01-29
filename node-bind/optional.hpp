#if !defined( NODE_BIND_OPTIONAL_HPP )
#define NODE_BIND_OPTIONAL_HPP

#include <node-bind/undefined.hpp>

namespace nodebind
{
    // lightweight optional type
    template <typename T>
    struct optional
    {
        typedef bool optional<T>::* safe_bool_type;

        optional()
            : value()
            , is_set(false)
        {}
        
        optional(optional const& x)
            : value(x.value)
            , is_set(x.is_set)
        {}
        
        optional(T const& x)
            : value(x)
            , is_set(true)
        {}
        
        optional & operator = (optional const& x)
        {
            value = x.value;
            is_set = x.is_set;
            return *this;
        }
        
        optional & operator = (T const& x)
        {
            value = x;
            is_set = true;
            return *this;
        }
        
        optional & operator = (keyword::undefined_t)
        {
            value = T();
            is_set = false;
            return *this;
        }
        
        operator safe_bool_type() const
        {
            return is_set ? &optional<T>::is_set : 0;
        }
        
        T & get()
        {
            return value;
        }
        
        T const& get() const
        {
            return value;
        }
        
        T value;
        bool is_set;
    };
}

#endif // #if !defined( NODE_BIND_OPTIONAL_HPP )

