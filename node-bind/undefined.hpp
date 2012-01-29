///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012 Benaka Moorthi
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if !defined( NODE_BIND_UNDEFINED_HPP )
#define NODE_BIND_UNDEFINED_HPP

namespace nodebind
{
    namespace keyword
    {
        struct dummy
        {
            int var;
        };
        
        typedef int dummy::* undefined_t;

        undefined_t const undefined = 0;
    }
}

#endif // #if !defined( NODE_BIND_UNDEFINED_HPP )

