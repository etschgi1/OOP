//----------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// main.hpp
//
// Main functions; creates game instance and calls Game member functions (Gameloop)
//
// Group: 135
//
// Author: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#ifndef OOP1SS21_A2_135_MAIN
#define OOP1SS21_A2_135_MAIN

#include "Game.hpp"
#include "IOLoop.hpp"
#include "Random.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <regex>
#include <utility>

using std::bad_alloc;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::regex;
using std::regex_replace;
using std::string;
using std::unique_ptr;
using std::vector;

//<<<<Return-Values>>>>
const int REGULAR_ENDING = 0;
const int BAD_MEMORY_ALLOCATION = 1;
const int WRONG_ARGUMENTS = 2;

//------------------------------------------------------------------------------------------------------------------
/// Main function runs the game
/// @param argc command line argument count
/// @param argv command line arguments
/// @return 0 if game is closed normally, 1 if memory allocation failed, 2 if there are to many command-line args
//
int main(int argc, char* argv[]);

//------------------------------------------------------------------------------------------------------------------
/// Prints out welcome message and user prompt.
/// Avoids overflows
/// @return number of players
//
int start_game();

// https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
// begin
//------------------------------------------------------------------------------------------------------------------
/// Trims Whitespaces on the left
/// @param s string which needs trimming
/// @return string with Withespaces on left trimmed
//
string ltrim(const string& s);
//------------------------------------------------------------------------------------------------------------------
/// Trims Whitespaces on the right
/// @param s string which needs trimming
/// @return string with Withespaces on right trimmed
//
string rtrim(const string& s);
//------------------------------------------------------------------------------------------------------------------
/// Trims Whitespaces on the left and right
/// @param s string which needs trimming
/// @return string with Withespaces on left and right side trimmed
//
string trim(const string& s);
// end

#endif // OOP1SS21_A2_135_MAIN