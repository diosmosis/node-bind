Description
-----------

node-bind is a header-only C++ library that takes the grunt work out of creating node.js extensions.

A Quick Example
---------------

    struct MyType
    {
        MyType(int first_, int second_)
            : first(first_)
            , second(second_)
        {}
        
        std::string toString()
        {
            return "<<MyType>>";
        }
        
        void doSomething(nodebind::string const& val, nodebind::function const& cb)
        {
            cb(val, nodebind::keywords::undefined);
        }
        
        int first;
        int second;
    };
    
    void doSomethingElse()
    {
        // ...
    }
    
    NODE_BIND_MODULE( my_extension )
    {
        using namespace nodebind;
        
        set("doSomethingElse", &doSomethingElse);
        
        class_<MyType>("MyType", construct<int, int>())
            .set("first", &MyType::first)
            .set("second", &MyType::second)
            .set("toString", &MyType::toString)
            .set("doSomething", &MyType::doSomething)
            ;
    }

