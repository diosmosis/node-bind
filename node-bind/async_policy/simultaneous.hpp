#if !defined( NODE_BIND_ASYNC_POLICY_SIMULTANEOUS_HPP )
#define NODE_BIND_ASYNC_POLICY_SIMULTANEOUS_HPP

#include <list>
#include <node.h>

namespace nodebind
{
    // TODO: should be able to cache some work requests. although, really, shouldn't have to allocate
    //       anything...
    struct simultaneous_async_policy
    {
        uv_work_t * get_work_request()
        {
            all_items.push_back(uv_work_t());
            return &all_items.back();
        }

        void release_work_request(uv_work_t * work_req)
        {
            for (std::list<uv_work_t>::iterator i = all_items.begin(); i != all_items.end(); ++i)
            {
                if (&*i == work_req)
                {
                    all_items.erase(i);
                    return;
                }
            }
        }
        
        std::list<uv_work_t> all_items;
    };
}

#endif // #if !defined( NODE_BIND_ASYNC_POLICY_SIMULTANEOUS_HPP )

