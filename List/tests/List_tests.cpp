#include "List.hpp"
#include <iostream>


template<typename Cont>
void print_container(const Cont& cont, const char* msg="", bool newline=true)
{
    std::cout << msg;
    for( typename Cont::const_iterator it(cont.cbegin());
         it!=cont.cend(); /*  */ ){
            std::cout << *it++ << " ";
        }
    if(newline)
       std::cout << std::endl;
}


int main()
{
    List<int> li{1,2,3,4};
    for(List<int>::const_iterator it(li.cbegin()); it!=li.cend(); ++it){
        std::cout << *it << " ";
    }
    li.insert(li.begin(), 42);
    li.insert(li.end(), 42);
    std::cout << std::endl;
    print_container(li, "after inserting 42: ");
    li.insert(++li.begin(), {1, 11, 111, 1111} );
    print_container(li, "after inserting init list: ");
}
