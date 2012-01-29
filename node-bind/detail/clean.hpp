///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012 Benaka Moorthi
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if !defined( NODE_BIND_DETAIL_CLEAN_HPP )
#define NODE_BIND_DETAIL_CLEAN_HPP

namespace nodebind
{
    template <typename T>
    struct clean
    {
        typedef T type;
    };
    
    template <typename T>
    struct clean<T &>
        : clean<T>
    {};
    
    template <typename T>
    struct clean<T &&>
        : clean<T>
    {};
    
    template <typename T>
    struct clean<T *>
        : clean<T>
    {};
    
    template <typename T>
    struct clean<T const>
        : clean<T>
    {};
}

#endif // #if !defined( NODE_BIND_DETAIL_CLEAN_HPP )

