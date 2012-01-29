#include <iostream>
#include <node-bind/node-bind.hpp>
#include <sstream>
#include <ctime>

struct DoSomethingElse : nodebind::worker<void ()>
{
    void process()
    {
        uint32_t now = time(0);
        
        while (time(0) < now + 2);
    }
};

struct MyType
{
    MyType(int t1 = 2, int t2 = 4)
      : thing1(t1)
      , thing2(t2)
    {
    }

    nodebind::string toString()
    {
        std::cout << "size: " << sizeof(uv_work_t) << std::endl;
        std::stringstream ss;
        ss << "MyType[thing1 = " << thing1 << ", thing2 = " << thing2 << "]";
        return nodebind::string(ss.str());
    }
    
    void doSomethingElseSync(nodebind::function const& f)
    {
        nodebind::optional<std::string> var1;
        f(var1, nodebind::keyword::undefined);
    }

    int thing1;
    int thing2;

    DoSomethingElse doSomethingElse;
};

NODE_BIND_MODULE( test_ext )
{
    using namespace nodebind;
    
    class_<MyType>("MyType", construct<int, int>()) // TODO: how to specify optional args?
        .set("thing1", &MyType::thing1)
        .set("thing2", &MyType::thing2)
        .set("toString", &MyType::toString)
        .set("doSomethingElse", &MyType::doSomethingElse)
        ;
}
