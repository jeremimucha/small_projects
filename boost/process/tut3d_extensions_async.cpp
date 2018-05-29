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
 * boost::process provides an interface to boost::asio, it is possible to get
 * a reference to the asio::io_service in the extended handler, to achieve that
 * it's necessary to inherit from
 * boost::process::extend::require_io_context;
 */

struct my_handler : public ex::handler, ex::require_io_context {
    template<typename Executor>
    void on_setup(Executor& exec)
    {
        // get a ref to the io_service; compiler error if not present
        boost::asio::io_service& ios = ex::get_io_context(exec.seq);
        // do something with io_service ref.
    }
};

/**
 * The handler can provide a function that's invoked when the child process exits, this is done
 * thourgh ex::async_handler;
 * ex::async_handler implies ex::require_io_context
 */
struct my_async_handler : public ex::async_handler {
    template<typename Executor>
    std::function<void(int,const std::error_code&)> on_exit_handler(Executor& exec)
    {
        // auto handler = this->handler;
        return [this](int exit_code, const std::error_code& ec)
                {
                    std::cout << "hello world, I exited with " << exit_code << std::endl;
                    std::cout << "error_code = " << ec << std::endl;
                };
    }
};


int main()
{
//    {
//        auto ch = bp::child{bp::search_path("g++"), "--version", my_handler{}};
//        ch.wait();
//        std::cout << "my_async_handler child process exit code = " << ch.exit_code() << std::endl;
//    }
    {
        auto ch = bp::child{bp::search_path("g++"), "--version", my_async_handler{}};
        ch.wait();
        std::cout << "my_async_handler child process exit code = " << ch.exit_code() << std::endl;
    }

}
