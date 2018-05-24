#include <iostream>
#include <thread>
#include <chrono>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>

namespace bp = boost::process;
namespace fs = boost::filesystem;
using namespace std::chrono_literals;

int main(/* int argc, char* argv[] */)
{
// calling bp::system() will wait untill the child process is completed (blocking call)
    // int res = bp::system("g++", "--version");

// --- boost::process::spawn diectly launches a process and immediately detaches it
// no handle will be returned an the process will be ignored.
    // bp::spawn(bp::search_path("g++"), "--version");

//  Non-blocking execution with explicitly contructing a child process
    bp::child ch(bp::search_path("g++"), "--version");

    while(ch.running()){
        std::cerr << "Hello from main" << std::endl;
        std::this_thread::sleep_for(10ms);
    }

    ch.wait(); // wait for the process to exit
    int result = ch.exit_code();

    std::cerr << "result = " << result << std::endl;
}
