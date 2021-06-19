//---------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// IOLoop.hpp
//
// This class is handling the input and output
// Basically the interface between User and Backend
//
// Group: 135
//
// Author: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#ifndef OOP1SS21_A2_135_IOLOOP_HPP
#define OOP1SS21_A2_135_IOLOOP_HPP

#include "AI.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Request.hpp"
#include <algorithm>
#include <iostream>
#include <memory>

using std::cin;
using std::cout;
using std::exception;
using std::find;
using std::find_if;
using std::getline;
using std::isdigit;
using std::shared_ptr;
using std::stol;
using std::stoul;
using std::string;
using std::vector;
class IOLoop
{
  Game& game_;
  shared_ptr<Player> current_player_;
  string current_color_;
  vector<string> tokens_;
  string input_;
  string command_;
  vector<string> params_;
  size_t auto_counter = 0;

  //  <<<<<Internal Flags>>>>>       to determine when to do what e.g. if print_map_ flag set it should print the map
  bool done_with_the_move_ = false;
  bool quit_ = false;
  bool print_map_ = true;
  bool has_inserted_ = false;
  bool show_treasure_ = false;
  bool game_over_ = false;
  bool didnt_execute_ = false;
  bool auto_player42 = false;

  //!---------Class Constants---------
  const size_t MOVE_DIRECTION_UP = 3;
  const size_t MOVE_DIRECTION_DOWN = 1;
  const size_t MOVE_DIRECTION_LEFT = 2;
  const size_t MOVE_DIRECTION_RIGHT = 0;
  const char double_quote_ = 34;      // ASCII for double quote "
  const size_t STEP_STRING_LIMIT = 2; // Strings for steps in go function must be smaller than this
  const size_t FIRST_PARAMETER_INPUT = 1;
  const size_t SECOND_PARAMETER_INPUT = 2;
  const size_t INSERT_ROW_COL_STRING_LIMIT = 2;
  const size_t UPPER_INSERT_ROW_COL_BOUNDARY = 7;
  const size_t LOWER_INSERT_ROW_COL_BOUNDARY = 1;
  const string ALL_TREASURES_FOUND_MESSAGE = "All Treasures found, return to your startfield to win!";
  const string TEAM_NAME = "ϾPlaceholderϿ¶";

  //  Internal Vector containing valid commands before tile is inserted
  vector<string> invalid_before_insert_ = {"w",      "a",      "s",  "d", "\x1b[A", "\x1b[B",
                                           "\x1b[C", "\x1b[D", "go", "f", "finish"};
  //  Internal Vector containing valid commands_
  vector<vector<string>> commands_ = {
      // all valid commands_. First part represents the basic tokens_, the second one the valid number of parameters and
      // the rest all valid paremeters.
      {"quit", "1"},
      {"exit", "1"},
      {"whoami", "1"},
      {"Whoami", "1"},
      {"play", "1"},
      {"ILoveSegfaults", "1"},
      // all available exit commands_
      {"gamefield", "2", "on", "off"},
      {"gamefield", "1"},
      {"g", "2", "on", "off"},
      {"g", "1"},
      // commands_ for showing the gamefield
      {"showtreasure", "1"},
      {"st", "1"},
      {"hidetreasure", "1"},
      {"ht", "1"},
      // showing and hiding treasure
      {"showfreetile", "1"},
      {"sft", "1"},
      // showing the available free tile
      {"w", "1"},
      {"\x1b[A", "1", "Arrow up"}, // arrow up key
      {"s", "1"},
      {"\x1b[B", "1", "Arrow down"}, // arrow down key
      {"d", "1"},
      {"\x1b[C", "1", "Arrow right"}, // arrow right key
      {"a", "1"},
      {"\x1b[D", "1", "Arrow left"}, // arrow left key
      {"go", "3", "up", "down", "left", "right"},
      // all movement commands_
      {"rotate", "2", "left", "l", "right", "r"},
      // rotate command
      {"insert", "3", "t", "top", "b", "bottom", "r", "right", "l", "left"},
      {"i", "3", "t", "top", "b", "bottom", "r", "right", "l", "left"},
      // insert commands_
      {"finish", "1"},
      {"f", "1"}};

  //  Vector of all valid Request objects
  vector<Request> valid_requests_{
      // all valid commands_. First part represents the basic tokens_, the second one the valid number of
      // parameters and
      // the rest all valid paremeters.
      Request{"ILoveSegfaults"}, Request{"quit"}, Request{"exit"}, Request{"whoami"}, Request{"Whoami"},
      Request{"play"},
      // all available exit commands_
      Request{"gamefield", 2, {"on", "off"}}, Request{"gamefield"}, Request{"g", 2, {"on", "off"}}, Request{"g"},
      // commands_ for showing the gamefield
      Request{"showtreasure"}, Request{"st"}, Request{"hidetreasure"}, Request{"ht"},
      // showing and hiding treasure
      Request{"showfreetile"}, Request{"sft"},
      // showing the available free tile
      Request{"w", {3, 1}, "w"}, Request{"\x1b[A", {3, 1}, "arrow up"},    // arrow up key
      Request{"s", {1, 1}, "s"}, Request{"\x1b[B", {1, 1}, "arrow down"},  // arrow down key
      Request{"d", {0, 1}, "d"}, Request{"\x1b[C", {0, 1}, "arrow right"}, // arrow right key
      Request{"a", {2, 1}, "a"}, Request{"\x1b[D", {2, 1}, "arrow left"},  // arrow left key
      Request{"go", 3, {"up", "down", "left", "right"}},
      // all movement commands
      Request{"rotate", 2, {"left", "l", "right", "r"}},
      // rotate command
      Request{"insert", 3, {"t", "top", "b", "bottom", "r", "right", "l", "left"}},
      Request{"i", 3, {"t", "top", "b", "bottom", "r", "right", "l", "left"}},
      // insert commands
      Request{"finish"}, Request{"f"}};

public:
  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor for the IOLoop
  ///
  /// @param game pointer to the Game object
  ///
  //
  explicit IOLoop(Game& game);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Copy-Constructor
  ///
  //
  IOLoop(const IOLoop&) = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Overload assign; Assignment hands over reference
  ///
  //
  void operator=(const IOLoop&) = delete;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor for the IOLoop
  ///
  //
  ~IOLoop() = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Starts the game-eventloop, which handles the games session
  ///
  //
  void runGame();

private:
  bool executePlay();
  bool executeWhoami();
  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Tries to execute the parsed command, but throws the appropriate errors if needed
  ///
  //
  void executeCommand();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Accesses the internal Game object and prints the map and also calls the checkTreasurePrint method
  ///
  //
  void printMap();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the parsed command is quit or exit and sets the quit_ flag to true
  ///
  /// @return true if the parsed command_ is quit or exit, else false
  ///
  //
  bool executeQuitGame();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the parsed command is one of the following w,a,s,d or one of the arrow keys. Afterwards it calls
  /// movePlayer of the Game object and moves the player according to the README in the appropriate direction.
  ///
  /// @return true if the parsed command_ is one of the following w,a,s,d or one of the arrow keys, else false
  ///
  //
  bool executeWASDAndArrowKeys();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the parsed command is go and checks if the parameters are valid. If the input is valid the number of
  /// steps are converted to long which is then used to call movePlayer of the Game object. It moves the player
  /// according to the README in the appropriate direction.
  ///
  /// @return true if the parsed command_ is quit or exit, else false
  ///
  //
  bool executeGo();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the parsed command is insert or i and checks if the parameters are valid. If the input is valid the
  /// input is passed to the insertTile method of the Game object. It inserts the free tile in the desired place with
  /// schema described in the README. Furthermore if it finishes executing the command it will set the has_inserted_
  /// flag to true, which signalises to the IOLoop that the player has already inserted and that it needs start
  /// to allow the commands_ in the invalid_before_insert_ vector and block the insert and rotate command.
  ///
  /// @return true if the parsed command_ is insert or i, else false
  ///
  //
  bool executeInsert();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the parsed command is rotate and rotates the free tile in the appropriate direction if the parameters
  /// are valid.
  ///
  /// @return true if the parsed command_ is rotate, else false
  ///
  //
  bool executeRotate();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the parsed command is showfreetile or sft and calls printFreeTile to print the currently free tile out.
  ///
  /// @return true if the parsed command_ is showfreetile or sft, else false
  ///
  //
  bool executeShowFreeTile();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the parsed command is showtreasure, hidetreasure, st or ht and sets the show_treasure_ flag to true
  /// if showtreasure or st was entered or sets it to false if hidetreasure or ht was entered. If ht or hidetreasure
  /// was entered the screen is also cleared.
  ///
  /// @return true if the parsed command_ is showtreasure, hidetreasure, st or ht, else false
  ///
  //
  bool executeShowOrHideTreasure();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the parsed command is gamefield or g and sets the print_map_ flag to true if the the parameter is
  /// the string on or false if the string is off
  ///
  /// @return true if the parsed command_ is gamefield or g, else false
  ///
  //
  bool executeGamefield();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the parsed command is finish or f and sets the show_treasure_ to false, done_with_the_move_ to true,
  /// has_inserted_ to false and the game_over flag to true if a player won the game.
  ///
  /// @return true if the parsed command_ is finish or f, else false
  ///
  //
  bool executeFinish();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Prints the currently free tile to the stdout
  ///
  //
  void printFreeTile();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the first parameter parsed is a valid parameter of the parsed command.
  ///
  /// @return true if the first parsed parameter is valid for the parsed command, if it is not valid then false
  ///
  //
  bool isFirstParameterValid();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the number of parameters is the correct number of parameters of the parsed command.
  ///
  /// @return true if the number of parameters passed matches the number of parameter expected with the parsed command
  /// and if doesn't match it returns false
  ///
  //
  bool isNumberOfParametersValid();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the parsed command takes any arguments (parameters).
  ///
  /// @return true if the parsed command takes arguments and false if it doesn't take arguments
  ///
  //
  bool commandTakesArguments();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the parsed command is currently allow or not
  ///
  /// @return true if the parsed command is currently allowed and false if the command is currently not allowed
  ///
  //
  void commandCurrentlyAllowed();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the passed string is a positive Integer.
  ///
  /// @return true if the passed string is positive and an integer, else false
  ///
  //
  bool isPositiveNumber(const string& s);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// If the show_treasure_ flag and not the didnt_execute_ flag were set, then will this function print the
  /// currently searched treasure of the current player.
  ///
  //
  void checkTreasurePrint();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Parses the input from stdin and returns the tokeni
  ///
  /// @return true if the parsed command_ is quit or exit, else false
  ///
  //
  vector<string> parseCommand();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Splits a string into tokens using a specific delimiter and stores the tokens into the passed out vector.
  ///
  //
  void tokenize(string const& str, char delimiter, vector<string>& out);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Checks if the parsed command exists.
  ///
  /// @return true if the parsed command_ exists, if it doesn't then false
  ///
  //
  bool commandExists();
  bool autoplayer42()
  {
    if (command_ == "ILoveSegfaults")
    {
      auto_player42 = true;
      return true;
    }
    return false;
  }
};

#endif // OOP1SS21_A2_135_IOLOOP_HPP
