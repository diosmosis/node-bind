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

