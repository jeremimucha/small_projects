#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include <gsl/gsl>


struct bla {
    int some;
    double random;
    std::pair<double, int> params;
};


int some_func(int a, int b)
{
    Expects( a < b );
    auto result = a * b;
    Ensures( result > b );
    return result;
}

int main()
try{
    std::cout << "bind to pair:" << std::endl;
    auto p = std::make_pair(42, std::string("no hej"));
    std::cout << p.first << ", " << p.second << std::endl;
    const auto& [one, two] = p;
    std::cout << one << ", " << two << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    std::cout << "\nBind to struct:" << std::endl;
    bla bb{42, 3.14159265359, {2.71828, 11}};
    const auto& [a, b, c] = bb;
    std::cout << "a = "  << a <<"\n"
              << "b = "  << b << "\n"
              << "c = {" << c.first << "," << c.second << "}\n"
    << std::endl;

    some_func(4, 5);
    some_func(5,4);
}
catch( std::exception& e )
{
    std::cerr << e.what() << std::endl;
}