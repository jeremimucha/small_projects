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

// To aid reusability we can use inheritance to implement the handlers:
struct trace_handler : public ex::handler {
    template<typename Executor>
    void on_setup(Executor& exec) const
    {
        std::cout << "Setting up the child process: " << exec.exe << std::endl;
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


// We can also specialize further by overloading on executor type
struct specialized_handler : public ex::handler {
    template<typename Sequence>
    void on_setup(ex::posix_executor<Sequence>& exec) const
    {
        std::cout << "posix-exec setup: " << exec.exe << std::endl;
    }

    template<typename Sequence>
    void on_setup(ex::windows_executor<char, Sequence>& exec) const
    {
        if(exec.exe != nullptr)
            std::cout << "windows-exec <char> setup: " << exec.exe << std::endl;
        else
            std::cout << "windows-exec <char> setup, exec.exe == nullptr" << std::endl;
    }

    template<typename Sequence>
    void on_setup(ex::windows_executor<wchar_t, Sequence>& exec) const
    {
        if(exec.exe !=nullptr)
            std::wcout << L"windows exec <wchar_t> setup: " << exec.exe << std::endl;
        else
            std::cout << "windows exec <wchar_t> setup, exec.exe == nullptr" << std::endl;
    }
};


int main()
{
    {
    auto ch = bp::child{bp::search_path("g++"), "--version", trace_handler{}};

    ch.wait();
    auto res = ch.exit_code();
    std::cout << "child exit code = " << res << std::endl;
    }

    {
        auto ch = bp::child{bp::search_path(L"g++"), L"--version", specialized_handler{}};

        ch.wait();
        auto res = ch.exit_code();
        std::wcout << "child exit code = " << res << std::endl;
    }
}
