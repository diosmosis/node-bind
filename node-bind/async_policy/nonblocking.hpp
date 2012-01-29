///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012 Benaka Moorthi
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if !defined( NODE_BIND_ASYNC_POLICY_NONBLOCKING_HPP )
#define NODE_BIND_ASYNC_POLICY_NONBLOCKING_HPP

#include <node.h>
#include <v8.h>

namespace nodebind
{
    struct nonblocking_async_policy
    {
        nonblocking_async_policy()
        {
            req.data = 0;
        }

        uv_work_t * get_work_request()
        {
            if (req.data)
            {
                v8::ThrowException(v8::Exception::Error(
                  v8::String::New("Can't execute async operation simultaneously.")));
                return 0;
            }
            
            return &req;
        }

        void release_work_request(uv_work_t * work_req)
        {
            work_req->data = 0;
        }
        
        uv_work_t req;
    };
}

#endif // #if !defined( NODE_BIND_ASYNC_POLICY_NONBLOCKING_HPP )

