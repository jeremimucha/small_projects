#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>

namespace as = boost::asio;
using namespace std::chrono_literals;

int main()
{
    as::io_service ioservice;
    as::steady_timer timer{ioservice, 3s};

    std::cout << "calling async_wait\n";

    timer.async_wait([](const boost::system::error_code& ec){
        std::cout << "3 sec\n";});
    
    std::cout << "async_wait called" << std::endl;

    ioservice.run();
}