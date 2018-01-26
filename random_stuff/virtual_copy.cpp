#include <iostream>


class Base
{
    virtual Base* do_clone() const
    {
        return new Base(*this);
    }
public:
    Base() = default;

    std::unique_ptr<Base> clone() const;
    {
        return std::unique_ptr<Base>(do_clone());
    }
};

class Derived
{
private:
    virtual Derived* do_clone() const override
    {
        return new Derived(*this);
    }
public:
    Derived() = default;

    std::unique_ptr<Derived> clone() const
    {
        return do_clone();
    }
}


int main()
{

}
