#include <iostream>
#include <system_error>
#include <boost/process.hpp>

namespace bp = boost::process;

int main()
{
// By default if starting a process fails (for example the requested program isn't found)
// an std::system_error exception is thrown.
    try{
        bp::system("no_such_program.exe");
    } catch(std::system_error& err){
        std::cerr << "Exception caught: " << err.what() << std::endl;
    }

// If we pass an std::error_code as the second argument the call sets an
// error code instead.
    std::error_code ec;
    bp::system("no_such_program.exe", ec);
    std::cerr << "ec = " << ec << std::endl;
}
