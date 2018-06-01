#include <iostream>
#include <system_error>
#include <string>
#include <utility>
#include <boost/process.hpp>
#include <boost/process/extend.hpp>
#include <boost/asio.hpp>

namespace bp = boost::process;
namespace ex = bp::extend;

/**
 * If an error occurs in the initializers it should be told to the executor and not handlers directly.
 */
struct my_handler : public ex::handler
{
    template<typename Executor>
    void on_setup(Executor& exec) const
    {
        std::cout << "Setting up the child process: " << exec.exe << std::endl;
        std::cout << "setting fake error..." << std::endl;
        std::error_code ec{42, std::system_category()};
        exec.set_error(ec, "a fake error");
    }

    template<typename Executor>
    void on_success(Executor& exec) const
    {
        std::cout << "Child process " << exec.exe << " started!" << std::endl;
    }

    template<typename Executor>
    void on_error(Executor& exec, const std::error_code& ec) const
    {
        std::cout << "Error starting child process " << exec.exe
            << ", ec = " << ec << std::endl;
    }
};

int main()
{
    std::error_code ec;
    auto ch = bp::child{bp::search_path("g++"), "--version", my_handler{}, ec};
    ch.wait();
    if(ec)
        std::cerr << "child process failed with an exit code ec = " << ec << std::endl;
    std::cerr << "child exit code = " << ch.exit_code() << std::endl;
}
