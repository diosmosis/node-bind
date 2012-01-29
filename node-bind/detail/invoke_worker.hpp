#if !defined( NODE_BIND_DETAIL_INVOKE_WORKER_HPP )
#define NODE_BIND_DETAIL_INVOKE_WORKER_HPP

#include <tuple>

namespace nodebind
{
    // TODO: should be invoke_function(f, tuple...)
    template <typename Worker, typename Args>
    void invoke_worker(void (Worker::*process_func)(), Worker & worker, Args const& args)
    {
        (worker.*process_func)();
    }

    template <typename Worker, typename Args, typename A0>
    void invoke_worker(void (Worker::*process_func)(A0), Worker & worker, Args const& args)
    {
        (worker.*process_func)(std::get<0>(args));
    }

    template <typename Worker, typename Args, typename A0, typename A1>
    void invoke_worker(void (Worker::*process_func)(A0, A1), Worker & worker, Args const& args)
    {
        (worker.*process_func)(std::get<0>(args), std::get<1>(args));
    }
}

#endif // #if !defined( NODE_BIND_DETAIL_INVOKE_WORKER_HPP )

