#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <regex>
#include <utility>

using std::cout; using std::endl;



int main()
{
    std::string s = "This, string; for: regex : library.";
    std::regex re_sep( R"(\s*[,;.:]\s*)" );
    std::sregex_token_iterator p(s.cbegin(), s.cend(),
                                 re_sep,
                                 -1 // values not matching the regex
                                );
    std::sregex_token_iterator e;   // end iterator
    std::vector<std::string> result;
    std::copy( std::make_move_iterator(p), std::make_move_iterator(e),
               std::back_inserter(result)
             );
    for( const auto& r : result ){
        cout << r << " ";
    }
}