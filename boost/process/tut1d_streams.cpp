#include <iostream>
#include <system_error>
#include <boost/process.hpp>

namespace bp = boost::process;

int main()
{
// Streams can be redirected explicitly
    std::cerr << "Starting first process..." << std::endl;
    bp::system("g++ --version", bp::std_out > stdout
                              , bp::std_err > stderr
                              , bp::std_in  < stdin);

// Output can be ignored by redirecting to  null device
    std::cerr << "Starting second process..." << std::endl;
    bp::system("g++ --version", bp::std_out > bp::null);

// Or easily to a file
    std::cerr << "starting third process, output redirected to tut1d_out.log"
    << std::endl;
    bp::system("g++ --version", bp::std_out > "tut1d_out.log");
}
