#include <iostream>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>


namespace bp = boost::process;
namespace fs = boost::filesystem;

int main(/* int argc, char* argv[] */)
{
    fs::path p = bp::search_path("g++");
    int res = bp::system(p, "--version");
    std::cout << "res = " << res << std::endl;
}
