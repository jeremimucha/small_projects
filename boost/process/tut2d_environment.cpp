#include <iostream>
#include <boost/process.hpp>

namespace bp = boost::process;


/**
 * The library provides access to the environment of the current process
 * and allows setting the environment for the child process
 */

int main()
{
// This is the verbose way
    std::cerr << "Setting up the environment for a child process 1" << std::endl;
    // get a handle to the current environment
    auto env = boost::this_process::environment();
    // add a variable to the currenet env;
    env["VALUE_1"] = "foo";

    // copy it into an environment separate to the one of this process
    bp::environment new_env = env;
    // append two vlaues to a variable in the new env
    // new_env["VALUE_2"] += {"bar1","bar2"}; // this causes basic_string to throw an exception...
    new_env["VALUE_2"] += "bar1";
    new_env["VALUE_2"] += "bar2";

    // // launch a process with `new_env`
    bp::system("printenv VALUE_1 VALUE_2", new_env);

// This is the easy way
    std::cerr << "Now the second environment" << std::endl;
    bp::system("printenv VALUE_1 VALUE_2",
                bp::env["VALUE_1"]="More foo",
                bp::env["VALUE_2"]+={"Bar3","Bar4"});
}
