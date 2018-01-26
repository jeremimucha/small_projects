#include <iostream>
#include <vector>
#include <memory>


template<typename Derived>
class Base
{

public:

    void do_something() const noexcept
    {
        static_cast<const Derived*>(this)->do_something_impl();
    }

private:
    void do_something_impl() const noexcept
    {
        std::cout << "Hello from Base" << std::endl;
    }
};


class Foo : public Base<Foo>
{
public:
    void do_something_impl() const noexcept
    {
        std::cout << "Hello from Foo" << std::endl;
    }
};

class Bar : public Base<Bar>
{ }; // default implementation of do_something_impl


template<typename Derived>
void use(const Base<Derived>& obj)
{
    std::cout << "use: ";
    obj.do_something();
}

template<typename Derived>
void usep(Base<Derived>* const ptr)
{
    std::cout << "usep: ";
    ptr->do_something();
}

template<typename Derived>
void use_shared_ptr(const std::shared_ptr<Base<Derived>>& sptr)
{
    std::cout << "use_shared_ptr: ";
    sptr->do_something();
}

template<typename Derived>
void use_unique_ptr(const std::unique_ptr<Base<Derived>> uptr)
{
    std::cout << "use_unique_ptr: ";
    uptr->do_something();
}

int main()
{

    Foo f;
    Bar b;
    auto sptr_foo = static_cast<std::shared_ptr<Base<Foo>>>(std::make_shared<Foo>());

    use(f);
    use(b);
    usep(&f);
    usep(&b);
    use_shared_ptr(sptr_foo);
    use_shared_ptr(static_cast<std::shared_ptr<Base<Bar>>>(std::make_shared<Bar>()));
    use_unique_ptr(static_cast<std::unique_ptr<Base<Foo>>>(std::make_unique<Foo>()));
    use_unique_ptr(static_cast<std::unique_ptr<Base<Bar>>>(std::make_unique<Bar>()));
}
