#include <iostream>
#include <thread>
#include <chrono>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>

namespace bp = boost::process;
namespace fs = boost::filesystem;
using namespace std::chrono_literals;

/**
 * There are multiple ways of passing arguments to the child process
 * overloading:
 * system("grep -c false /etc/passwd"); //cmd style
 * system("grep", "-c", "false", "/etc/passwd"); //exe-/args-
 * explicitly set `exe` and `args` arguments
 * system(cmd="grep -c false /etc/passwd"); //cmd style
 * system(exe="grep", args={"-c", "false", "/etc/passwd"}); //exe-/args-
 */

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
