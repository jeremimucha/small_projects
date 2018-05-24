#include <iostream>
#include <system_error>
#include <vector>
#include <string>
#include <utility>
#include <boost/process.hpp>

namespace bp = boost::process;

/**
 * Function that runs "nm" which outputs an "outline" of an executable.
 * The output is mangled.
 */
std::vector<std::string> read_outline(const std::string& file)
{
    bp::ipstream is; // reading pipe-stream
    bp::child ch(bp::search_path("nm"), file, bp::std_out > is);

    auto data = std::vector<std::string>{};

// Warning! The pipe will cause a deadlock if we try reading from it after
// the child process exits
    for(std::string line; ch.running() && getline(is,line) && !line.empty();)
        data.push_back(std::move(line));

    ch.wait();

    return data;
}

/**
 * Function which runs "nm" and then streams the output to stdin of c++filt
 * which demangles the output
 */
std::vector<std::string> read_demangled_outline(const std::string& file)
{
    bp::pipe p;
    bp::ipstream is;

    // use the same pipe to connect the stdin/stdout of the processes
    bp::child nm(bp::search_path("nm"), file, bp::std_out > p);
    bp::child filt(bp::search_path("c++filt"), bp::std_in < p, bp::std_out > is);

    std::vector<std::string> outline;
    for(std::string line; filt.running() && getline(is,line);)
        outline.push_back(std::move(line));

    nm.wait();
    filt.wait();
    return outline;
}

int main()
{
// Write to stdin of a pipe and read from it's stdout
    bp::opstream in;
    bp::ipstream out;

    bp::child ch("c++filt", bp::std_out > out, bp::std_in < in);
    in << "_ZN5boost7process8tutorialE" << std::endl;
    std::string value;
    out >> value;

    std::cout << "value = " << value << std::endl;

    ch.terminate();

// Run nm and print part of it's output
    const auto nm_result = read_outline("./hello_world.exe");
    std::cout << "Partial output of \"nm hello_world.exe\"" << std::endl;
    for(int i=200; i<300; ++i)
        std::cout << nm_result[i] << std::endl;

// Run nm and pipe it's output to c++filt, we'll get demagnled output.
    const auto filt_result = read_demangled_outline("./hello_world.exe");
    std::cout << "Partial output of \"nm hello_world.exe | c++filt\"" << std::endl;
    for(int i=200; i<300; ++i)
        std::cout << filt_result[i] << std::endl;
}
