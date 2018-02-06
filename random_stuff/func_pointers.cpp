#include <iostream>
#include <functional>
using namespace std::placeholders;

class Bla
{
public:
    void set_handler( void(*func)(int,int) )
    {
        fp = func;
    }
    void set_handler( void(Bla::*func)(int,int))
    {
        mfp = func;
    }

    void operator()(int a, int b)
    {
        if(fp)
            fp(a, b);
        if(mfp)
            (this->*mfp)(a,b);
    }

    void member_handler(int a, int b)
    {
        std::cout << "member_handler got " << a << ", " << b << std::endl;
    }
private:
    using FuncPtr = void(*)(int,int);
    using MemFuncPtr = void(Bla::*)(int,int);
    FuncPtr fp{nullptr};
    MemFuncPtr mfp{nullptr};
};


void handler(int a, int b)
{
    std::cout << "handler got " << a << ", " << b << std::endl;
}


class Foo
{
public:
    template<typename Function>
    void set_handler( Function func )
    {
        fp = func;
    }

    void operator()( int a, double b )
    {
        if(fp)
            fp(a, b);
    }

    void member_handler(int a, double b)
    {
        std::cout << "member_handler got " << a << ", " << b << std::endl;
    }
private:
    std::function<void(int,double)> fp;
};

void global_handler(int a, double b)
{
    std::cout << "handler got " << a << ", " << b << std::endl;
}


int main()
{
    Bla bla;
    bla.set_handler(handler);
    bla(1,2);
    bla.set_handler(&Bla::member_handler);
    bla(2,3);

    Foo foo;
    foo.set_handler( global_handler );
    foo(1,3.14);
    foo.set_handler( [obj=&foo](int a, double b)
                     { (obj->*Foo::member_handler)(a,b); } );
    foo(2,2.71828);
    foo.set_handler( [](int a, double b)
                { std::cout << "I'm a lambda " << a << ", " << b << std::endl;}
        );
    foo(3, 3.14159);

    return 0;
}
