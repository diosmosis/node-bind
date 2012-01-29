///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012 Benaka Moorthi
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if !defined( NODE_BIND_CONSTRUCT_HPP )
#define NODE_BIND_CONSTRUCT_HPP

namespace nodebind
{
    template <typename... Args>
    struct construct
    {
        template <typename T>
        struct apply
        {
            static T * call(Args&&... args)
            {
                return new T(args...);
            }
        };
    };
}

#endif // #if !defined( NODE_BIND_CONSTRUCT_HPP )

