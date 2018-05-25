#include <iostream>
#include <chrono>
#include <boost/process.hpp>
#include <boost/asio.hpp>

namespace bp = boost::process;
using namespace std::chrono_literals;

/**
 * Groups are usefull if we want to make sure that":
 * 1. Terminating a child process also terminates all of the processes the child
 *    started.
 * 2. Grouping several processes into one, so that they can be terminated at once.
 */

int main()
{
// 1. Terminating a child process and all of it's children
    {
        auto gr = bp::group{};
        auto ch = bp::child{"make"};
        if(!gr.wait_for(std::chrono::seconds(10))){
            gr.terminate(); // also terminates all the processes that make might
                            // have spawned, like gcc
        }

        ch.wait(); // to avoid a zombie process and get the exit code later
        int res = ch.exit_code();
        std::cerr << "1. ch exit code = " << res << std::endl;
    }

// 2. Grouping several processes to make sure we can terminate all of them at once
    {
        auto gr = bp::group{};
        bp::spawn("make", gr);
        bp::spawn("gcc", gr);

        // do something here; if an exception occurs both proccesses will be
        // terminated.

        gr.wait();  // wait for both processes
    }
}
