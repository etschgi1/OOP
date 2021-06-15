//----------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// Request.cpp
//
// This class enables use to have a usable Interface with all the existing commands
// each command can be parsed with the correct constructor.
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#include "Request.hpp"

//----------------------------------------------------------------------------------------------------------------------
Request::Request(string command, size_t num_params, vector<string> params, string repr) :
    command_{std::move(command)}, num_params_{num_params}, params_{std::move(params)}, repr_{std::move(repr)}
{
}

//----------------------------------------------------------------------------------------------------------------------
Request::Request(string command, size_t num_params, vector<string> params) :
    command_{command}, num_params_{num_params}, params_{std::move(params)}, repr_{command}
{
}

//----------------------------------------------------------------------------------------------------------------------
Request::Request(string command) : command_{command}, num_params_{1}, params_{}, repr_{command} {}

//----------------------------------------------------------------------------------------------------------------------
Request::Request(string command, vector<int> direction, string repr) :
    command_{std::move(command)}, direction_{std::move(direction)}, num_params_{1}, repr_{std::move(repr)}
{
}

//----------------------------------------------------------------------------------------------------------------------
Request::Request(string command, vector<int> direction) :
    command_{command}, direction_{std::move(direction)}, num_params_{1}, repr_{command} // command cannot be moved 2
                                                                                        // times! Fixed it
{
}
