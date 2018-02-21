#include <iostream>
#include <vector>
#include <memory>


class Base
{
    virtual Base* do_clone() const
    {
        return new Base(*this);
    }
public:
    Base() = default;

    std::unique_ptr<Base> clone() const
    {
        return std::unique_ptr<Base>(do_clone());
    }
};

class Derived : public Base
{
private:
    Derived* do_clone() const override
    {
        return new Derived(*this);
    }
public:
    Derived() = default;

    std::unique_ptr<Derived> clone() const
    {
        return std::unique_ptr<Derived>(do_clone());
    }
};


int main()
{
    
}
