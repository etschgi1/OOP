//---------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// Errors.cpp
//
// Custom Exceptions class for various Exceptions which can occur during the game
//
// Group: 135
//
// Author: Elias Wachmann 12004232
//---------------------------------------------------------------------------------------------------------------------
//

#include "Errors.hpp"

//---------------------------------------------------------------------------------------------------------------------
CustomError::CustomError(string message) : message_{std::move(message)} {}

//---------------------------------------------------------------------------------------------------------------------
InvalidCommand::InvalidCommand()
{
  error_message_ = "Invalid command: ";
}

InvalidCommand::InvalidCommand(string command) : command_{std::move(command)}
{
  error_message_ = "Invalid command: \"" + command_ + "\"";
}

//---------------------------------------------------------------------------------------------------------------------
InvalidParameter::InvalidParameter()
{
  error_message_ = "Invalid parameter: ";
}

InvalidParameter::InvalidParameter(string parameter) : parameter_{std::move(parameter)}
{
  error_message_ = "Invalid parameter: \"" + parameter_ + "\"";
}

InvalidParameter::InvalidParameter(size_t parameter) : parameter_t{parameter}
{
  error_message_ = "Invalid parameter: \"" + std::to_string(parameter_t) + "\"";
}

//---------------------------------------------------------------------------------------------------------------------
CurrentlyNotAllowedCommand::CurrentlyNotAllowedCommand()
{
  error_message_ = " is currently not allowed";
}

CurrentlyNotAllowedCommand::CurrentlyNotAllowedCommand(string command) : command_{std::move(command)}
{
  error_message_ = "\"" + command_ + "\" is currently not allowed";
}

//---------------------------------------------------------------------------------------------------------------------
ImpossibleMove::ImpossibleMove()
{
  error_message_ = "Impossible move!";
}

//---------------------------------------------------------------------------------------------------------------------
CommandTakesNoArguments::CommandTakesNoArguments()
{
  error_message_ = "This command does not take any arguments!";
}

//---------------------------------------------------------------------------------------------------------------------
InvalidPosition::InvalidPosition()
{
  error_message_ = "Invalid Position!";
}

//---------------------------------------------------------------------------------------------------------------------
WrongNumberOfArguments::WrongNumberOfArguments()
{
  error_message_ = "Wrong number of arguments!";
}
