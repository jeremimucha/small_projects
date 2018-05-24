#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
#include <boost/asio.hpp>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>

namespace bp = boost::process;
namespace basio = boost::asio;
namespace fs = boost::filesystem;
using namespace std::chrono_literals;

/**
 * Boost::process allows use of boost::asio to implement asynchronous io
 */
void asio_with_boostasio()
{
    auto ios = basio::io_service{};
    auto ap = bp::async_pipe{ios};

    bp::child ch{bp::search_path("g++"), "--version", bp::std_out > ap};
    
    auto buf = std::vector<unsigned char>(4096);
    basio::async_read(ap, basio::buffer(buf),
        [](const std::error_code&/*ec*/, std::size_t/*size*/){});

    ios.run();
    int res = ch.exit_code();
    std::cerr << "asio_with_boostasio res = " << res << std::endl;
}

/**
 * Boost::process also provides a simpler interface
 */
void asio_simpler()
{
    auto ios = basio::io_service{};
    auto buf = std::vector<unsigned char>{};

    bp::child ch{bp::search_path("g++"), "--version",
                 bp::std_out > basio::buffer(buf), ios};
    
    ios.run();
    int res = ch.exit_code();
    std::cerr << __FUNCTION__ << " res = " << res << std::endl;
}

/**
 * It's eaven easier to use an std::future for asychronous operations
 */
void asio_with_futures()
{
    auto ios = basio::io_service{};
    auto data = std::future<std::string>{};

    bp::child ch{bp::search_path("g++"), "--not-an-argument",
                 bp::std_in.close(),
                 bp::std_out > bp::null,
                 bp::std_err > data,
                 ios};

    ios.run();  // this will block untill the child process is finished

    const auto err = data.get();
    std::cerr << __FUNCTION__ << " data = " << err << std::endl;
}

int main( )
{
    asio_with_boostasio();
    asio_simpler();
    asio_with_futures();
}
