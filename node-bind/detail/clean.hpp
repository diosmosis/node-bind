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

