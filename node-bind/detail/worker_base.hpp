///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012 Benaka Moorthi
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if !defined( NODE_BIND_DETAIL_WORKER_BASE_HPP )
#define NODE_BIND_DETAIL_WORKER_BASE_HPP

#include <node-bind/detail/get_wrapped_object.hpp>
#include <node-bind/detail/invoke_worker.hpp>
#include <node-bind/undefined.hpp>
#include <node-bind/function.hpp>
#include <stdexcept>
#include <node.h>
#include <v8.h>

namespace nodebind
{
    struct worker_base
    {
        template <typename Instance, typename Worker>
        static v8::Handle<v8::Value> call(v8::Arguments const& args)
        {
            typedef Worker Instance::* member_ptr_t;
        
            v8::HandleScope scope;
        
            // get member pointer
            uint32_t member_ptr_value = args.Data()->NumberValue();
            member_ptr_t member_ptr = *reinterpret_cast<member_ptr_t *>(&member_ptr_value);
            
            // get instance
            Instance & instance = get_wrapped_object<Instance>(args);
            
            // get derived worker ref
            Worker & worker = instance.*member_ptr;
            
            // get the work request
            uv_work_t * work_req = worker.get_work_request();
            if (!work_req)
            {
                // error in arguments, return undefined
                return scope.Close(v8::Undefined());
            }

            // store the arguments
            worker.store_arguments(args);

            // queue work function
            work_req->data = &worker;
            uv_queue_work(uv_default_loop(),
                          work_req,
                          &worker_base::process_impl<Instance, Worker>,
                          &worker_base::after_impl<Instance, Worker>);
            
            return scope.Close(v8::Undefined());
        }
        
        template <typename Instance, typename Worker>
        static void process_impl(uv_work_t * work_req)
        {
            Worker & worker = *static_cast<Worker *>(work_req->data);
            
            worker.error = keyword::undefined;
            
            try
            {
                // call process w/ stored args
                invoke_worker(&Worker::process, worker, worker.stored_args);
            }
            catch (std::exception const& x)
            {
                // store error
                worker.error = x.what();
            }
            catch (...)
            {
                // store unknown error
                worker.error = "Unknown error.";
            }
        }
        
        template <typename Instance, typename Worker>
        static void after_impl(uv_work_t * work_req)
        {
            v8::HandleScope scope;
        
            Worker & worker = *static_cast<Worker *>(work_req->data);
            
            // release the work request
            worker.release_work_request(work_req);
            
            // invoke the callback w/ the error & result, if any
            worker.after(function(worker.callback));
            
            // TODO shouldn't use a persistent object, should store it somewhere...
            worker.callback.Dispose();
        }
    };
}

#endif // #if !defined( NODE_BIND_DETAIL_WORKER_BASE_HPP )

