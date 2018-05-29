#include <iostream>
#include <system_error>
#include <string>
#include <boost/process.hpp>
#include <boost/process/extend.hpp>

namespace bp = boost::process;
namespace ex = bp::extend;

/**
 * It is possible to extend the process initialization.
 *
 * Extending is achieved either in a functional way or by inheriting from
 * a `handler` class defined in the boost::process::extend namespace.
 * 
 * The following handlers (or handler methods) can be overloaded:
 * a. on_setup() -- required signature: void(auto& exec);
 * b. on_error() -- required signature: void(auto& exec, const std::error_code& ec);
 * c. on_success() -- required signature: void(auto& exec);
 * 
 * posix also provides:
 * d. on_fork_error() -- void(auto& exec);
 * e. on_exec_setup() -- void(auto& exec);
 * f. on_exec_error() -- void(auto& exec);
 */

int main()
{
// The simplest extension - using a functional style
    auto ch = bp::child{bp::search_path("g++"), "--version"
                ,ex::on_setup=[](auto& /*exec*/)
                    {std::cout << "Setting up child process..." << std::endl;}
                ,ex::on_success=[](auto& /*exec*/)
                    {std::cout << "Child process started!" << std::endl;}
                ,ex::on_error=[](auto& /*exec*/, const std::error_code& ec)
                    {std::cerr << "Error setting up new process, ec = " << ec << std::endl;}
                };
    ch.wait();
    auto res = ch.exit_code();
    std::cout << "Child ec = " << res << std::endl;
}
