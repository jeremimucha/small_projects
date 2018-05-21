#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>
#include <type_traits>


template<typename Iterator
        ,typename Reference = std::iterator_traits<Iterator>::value_type
        ,typename Value = std::iterator_traits<Iterator>::value_type
        >
class toupper_iterator
{
    using self = toupper_iterator;
public:
    using value_type = Value;
};