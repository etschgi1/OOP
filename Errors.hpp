//---------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// Errors.hpp
//
// Custom Exceptions class for various Exceptions which can occur during the game
//
// Group: 135
//
// Author: Elias Wachmann 12004232
//---------------------------------------------------------------------------------------------------------------------
//

#include <iostream>
#include <string>

using std::exception;
using std::string;

//---------------------------------------------------------------------------------------------------------------------
///
/// Multipurpose CustomError class
/// error message can be specified in the constructor
///
//
class CustomError : public exception
{
private:
  string message_;

public:
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for CustomError class
  ///
  //
  explicit CustomError(string message);

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Function which returns the Errormessage for CustomError class
  ///
  /// @return returns the specified Error Message
  //
  [[nodiscard]] const char* what() const noexcept override { return message_.c_str(); }

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor for CustomError class
  ///
  //
  ~CustomError() override = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Copy-Constructor
  ///
  //
  CustomError(const CustomError&) = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Overload assign; Assignment hands over reference
  ///
  //
  CustomError& operator=(const CustomError&) = default;
};

//---------------------------------------------------------------------------------------------------------------------
///
/// Class for Invalid Command Error
/// Called if invalid command in given
/// Can be called as if or with specified (invalid) <command>
///
//
class InvalidCommand : public exception
{
private:
  string command_;
  string error_message_;

public:
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for InvalidCommand class
  ///
  //
  explicit InvalidCommand(string command);

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for InvalidCommand class without specified Invalid Command
  ///
  //
  InvalidCommand();

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Function which returns the Errormessage for InvalidCommand class
  ///
  /// @return returns the specified Error Message
  //
  [[nodiscard]] const char* what() const noexcept override { return error_message_.c_str(); }

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor for CustomError class
  ///
  //
  ~InvalidCommand() override = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Copy-Constructor
  ///
  //
  InvalidCommand(const InvalidCommand&) = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Overload assign; Assignment hands over reference
  ///
  //
  InvalidCommand& operator=(const InvalidCommand&) = default;
};

//---------------------------------------------------------------------------------------------------------------------
///
/// Class for Invalid Parameter Error
/// Called if invalid Parameters for the command are given
/// Can be called as if or with (invalid) <parameter>
///
//
class InvalidParameter : public exception
{
private:
  string parameter_;
  size_t parameter_t;
  string error_message_;

public:
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for InvalidParameter class with invalid parameter passed as string
  ///
  //
  explicit InvalidParameter(string parameter);

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for InvalidParameter class with invalid parameter passed as size_t
  //
  explicit InvalidParameter(size_t parameter);

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for InvalidParameter class with no invalid parameter passed
  ///
  //
  InvalidParameter();

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Function which returns the Errormessage for InvalidParameter class
  ///
  //
  [[nodiscard]] const char* what() const noexcept override { return error_message_.c_str(); }

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor for InvalidParameter class
  ///
  //
  ~InvalidParameter() override = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Copy-Constructor
  ///
  //
  InvalidParameter(const InvalidParameter&) = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Overload assign; Assignment hands over reference
  ///
  //
  InvalidParameter& operator=(const InvalidParameter&) = default;
};

//---------------------------------------------------------------------------------------------------------------------
///
/// Class for CurrentlyNotAllowedCommand Error
/// Called if the command is currently not allowed (because of gamerules etc.)
/// Can be called as if or with (invalid) <command_>
///
//
class CurrentlyNotAllowedCommand : public exception
{
private:
  string command_;
  string error_message_;

public:
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for CurrentlyNotAllowedCommand class with currently not allowed command passed as string
  ///
  //
  explicit CurrentlyNotAllowedCommand(string command);

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for CurrentlyNotAllowedCommand class with no currently not allowed command passed
  ///
  //
  CurrentlyNotAllowedCommand();

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Function which returns the Errormessage for CurrentlyNotAllowedCommand class
  ///
  //
  [[nodiscard]] const char* what() const noexcept override { return error_message_.c_str(); }

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor for CurrentlyNotAllowedCommand class
  ///
  //
  ~CurrentlyNotAllowedCommand() override = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Copy-Constructor
  ///
  //
  CurrentlyNotAllowedCommand(const CurrentlyNotAllowedCommand&) = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Overload assign; Assignment hands over reference
  ///
  //
  CurrentlyNotAllowedCommand& operator=(const CurrentlyNotAllowedCommand&) = default;
};

//---------------------------------------------------------------------------------------------------------------------
///
/// Class for ImpossibleMove Error
/// Called if the Move is impossible
///
//
class ImpossibleMove : public exception
{
private:
  string error_message_;

public:
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for ImpossibleMove class
  ///
  //
  ImpossibleMove();

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Function which returns the Errormessage for ImpossibleMove class
  ///
  //
  [[nodiscard]] const char* what() const noexcept override { return error_message_.c_str(); }

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor for ImpossibleMove class
  ///
  //
  ~ImpossibleMove() override = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Copy-Constructor
  ///
  //
  ImpossibleMove(const ImpossibleMove&) = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Overload assign; Assignment hands over reference
  ///
  //
  ImpossibleMove& operator=(const ImpossibleMove&) = default;
};

//---------------------------------------------------------------------------------------------------------------------
///
/// Class for CommandTakesNoArguments Error
/// Called if the Command takes no Arguments
///
//
class CommandTakesNoArguments : public exception
{
private:
  string error_message_;

public:
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for CommandTakesNoArguments class
  ///
  //
  CommandTakesNoArguments();

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Function which returns the Errormessage for CommandTakesNoArguments class
  ///
  //
  [[nodiscard]] const char* what() const noexcept override { return error_message_.c_str(); }

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor for CommandTakesNoArguments class
  ///
  //
  ~CommandTakesNoArguments() override = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Copy-Constructor
  ///
  //
  CommandTakesNoArguments(const CommandTakesNoArguments&) = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Overload assign; Assignment hands over reference
  ///
  //
  CommandTakesNoArguments& operator=(const CommandTakesNoArguments&) = default;
};

//---------------------------------------------------------------------------------------------------------------------
///
/// Class for WrongNumberOfArguments Error
/// Called if Wrong Number of Args is supplied
///
//
class WrongNumberOfArguments : public exception
{
private:
  string error_message_;

public:
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for WrongNumberOfArguments class
  ///
  //
  WrongNumberOfArguments();

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Function which returns the Errormessage for WrongNumberOfArguments class
  ///
  //
  [[nodiscard]] const char* what() const noexcept override { return error_message_.c_str(); }

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor for WrongNumberOfArguments class
  ///
  //
  ~WrongNumberOfArguments() override = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Copy-Constructor
  ///
  //
  WrongNumberOfArguments(const WrongNumberOfArguments&) = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Overload assign; Assignment hands over reference
  ///
  //
  WrongNumberOfArguments& operator=(const WrongNumberOfArguments&) = default;
};

//---------------------------------------------------------------------------------------------------------------------
///
/// Class for InvalidPosition Error
/// Called if Tile cannot be placed at the current Position
///
//
class InvalidPosition : public exception
{
private:
  string error_message_;

public:
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for InvalidPosition class
  ///
  //
  InvalidPosition();

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Function which returns the Errormessage for InvalidPosition class
  ///
  //
  [[nodiscard]] const char* what() const noexcept override { return error_message_.c_str(); }

  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor for InvalidPosition class
  ///
  //
  ~InvalidPosition() override = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Copy-Constructor
  ///
  //
  InvalidPosition(const InvalidPosition&) = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Overload assign; Assignment hands over reference
  ///
  //
  InvalidPosition& operator=(const InvalidPosition&) = default;
};
