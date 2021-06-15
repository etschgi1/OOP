//----------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// Request.hpp
//
// This class enables use to have a usable Interface with all the existing commands
// each command can be parsed with the correct constructor.
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#ifndef OOP1SS21_A2_135_REQUEST_HPP
#define OOP1SS21_A2_135_REQUEST_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Request
{
public:
  string command_;
  vector<int> direction_{};
  size_t num_params_;
  vector<string> params_{};
  string repr_;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for a Request with parameters and with a specific representation for the command e.g. CSI's
  /// need a string repr
  ///
  /// @param command this is the command representing this request
  /// @param num_params is the number of tokens the input should consist of including the command
  /// @param params is the vector of valid parameter for this request
  /// @param repr is the string representation of the command
  ///
  //
  explicit Request(string command, size_t num_params, vector<string> params, string repr);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for a Request with parameters
  ///
  /// @param command this is the command representing this request
  /// @param num_params is the number of tokens the input should consist of including the command
  /// @param params is the vector of valid parameter for this request
  ///
  //
  explicit Request(string command, size_t num_params, vector<string> params);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for a generic Request
  ///
  /// @param command this is the command representing this request
  ///
  //
  explicit Request(string command);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for a Movement Request with a specific representation for the command e.g. CSI's need a string repr
  ///
  /// @param command this is the command representing this request
  /// @param direction is a vector containing the heading and the number of steps
  /// @param repr is the string representation of the command
  ///
  //
  explicit Request(string command, vector<int> direction, string repr);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for a Movement Request
  ///
  /// @param command this is the command representing this request
  /// @param direction is a vector containing the heading and the number of steps
  ///
  //
  explicit Request(string command, vector<int> direction);
};

#endif // OOP1SS21_A2_135_REQUEST_HPP
