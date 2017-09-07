#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
#include "List.hpp"

TEST_CASE( "List constructors", "[List]" )
{
    List<int> list1;
    List<int> list2(42);
    List<int> list3{1,2,3,4};

}
