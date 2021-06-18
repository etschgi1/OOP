//---------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// IOLoop.cpp
//
// This class is handling the input and output
// Basically the interface between User and Backend
//
// Group: 135
//
// Author: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#include "IOLoop.hpp"

//---------------------------------------------------------------------------------------------------------------------
IOLoop::IOLoop(Game& game) : game_{game} {}

//---------------------------------------------------------------------------------------------------------------------
void IOLoop::runGame()
{
  auto players = game_.getPlayers();
  while (true)
  {
    for (const auto& player : players)
    {
      current_player_ = player;
      done_with_the_move_ = false;
      has_inserted_ = false;
      printMap(); // after player change always print map
      switch (current_player_->getColor())
      {
        case 'R':
          current_color_ = "RED";
          break;
        case 'Y':
          current_color_ = "YELLOW";
          break;
        case 'G':
          current_color_ = "GREEN";
          break;
        case 'B':
          current_color_ = "BLUE";
          break;
      }
      while (!done_with_the_move_)
      {
        do
        {
          cout << current_color_ << " > ";
          getline(cin, input_);
          if (cin.eof())
          {
            return;
          }
          tokens_ = parseCommand();
        } while (tokens_.empty());
        auto temp = tokens_;
        command_ = temp.front();
        temp.erase(temp.begin());
        params_ = temp;
        if (commandExists())
        {
          executeCommand();
          if (quit_ || game_over_)
          {
            return;
          }
        }
        else
        {
          cout << "Invalid command: " << double_quote_ << command_ << double_quote_ << endl;
        }
      }
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------
void IOLoop::executeCommand()
{
  didnt_execute_ = false;
  try
  {
    commandCurrentlyAllowed(); // first check if command is currently allowed
    // then check if command needs Args and if the number is sufficient
    if (!isNumberOfParametersValid())
    {
      if (!commandTakesArguments())
      {
        throw CommandTakesNoArguments();
      }
      throw WrongNumberOfArguments();
    }
    if (executeQuitGame() || executeShowFreeTile() || executeRotate() || executeWASDAndArrowKeys() || executeGo() ||
        executeInsert() || executeShowOrHideTreasure() || executeFinish() || executeGamefield() || executePlay() ||
        executeWhoami())
    {
      return;
    }
    throw CustomError("Oh looks like a bug in IOLoop::executeCommand()"); // For Testing
  }
  catch (const exception& e) // catch all ocurring exceptions if command with parameters didn't execute properly.
  {
    didnt_execute_ = true;
    cout << e.what() << endl;
    return;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void IOLoop::printMap()
{
  game_.printMap();
  checkTreasurePrint();
}

//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::executePlay()
{
  if (command_ == "play")
  {
    // cout << "Debug play: " << endl;
    auto ai_ = AI(game_, current_player_);
    ai_.run();
    ai_.printInfo();
    // cout << ai_.getLifeTime() << endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // cout << ai_.getLifeTime() << endl;
    input_ = ai_.getInsertCommand();
    tokens_ = parseCommand();
    command_ = tokens_.front();
    // tokens_ = {"insert", "", ""};
    // tokens_.at(1) = ai_.getInsertSidestring();
    // tokens_.at(2) = ai_.getInsertPositionstring();
    // cout << tokens_.at(1) << tokens_.at(2) << endl;
    // command_ = "insert";
    executeInsert();
    if (ai_.getSuccess())
    {
      input_ = ai_.getGoCommand();
      tokens_ = parseCommand();
      command_ = tokens_.front();
      // command_ = "go";
      // tokens_ = {"go", "", ""};
      // tokens_.at(1) = ai_.getGoalRowstring();
      // tokens_.at(2) = ai_.getGoalColstring();
      executeGo();
    }
    command_ = "finish";
    executeFinish();
    return true;
  }
  return false;
}
//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::executeWhoami()
{
  if (command_ == "whoami" || command_ == "Whoami")
  {
    cout << "[INFO] Team: " << TEAM_NAME << endl;
    return true;
  }
  return false;
}
//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::executeQuitGame()
{
  if (command_ == "quit" || command_ == "exit")
  {
    quit_ = true;
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::executeWASDAndArrowKeys()
{
  if (command_ == "\x1b[A" || command_ == "\x1b[B" || command_ == "\x1b[C" || command_ == "\x1b[D" || command_ == "w" ||
      command_ == "a" || command_ == "s" || command_ == "d")
  {
    auto it = find_if(valid_requests_.begin(), valid_requests_.end(),
                      [this](const Request& req) { return req.command_ == this->command_; });
    if (it != valid_requests_.end())
    {
      game_.movePlayer(current_player_, it->direction_.at(0), it->direction_.at(1));
      if (print_map_)
      {
        printMap();
      }
      return true;
    }
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::executeGo()
{
  size_t steps = 0;
  if (command_ == "go")
  {
    if (tokens_.size() == 3)
    { // check for go with coords:
      if (isPositiveNumber(tokens_.at(FIRST_PARAMETER_INPUT)) == true &&
          isPositiveNumber(tokens_.at(SECOND_PARAMETER_INPUT)) == true && tokens_.at(1).size() < 2 &&
          tokens_.at(2).size() < 2)
      {
        size_t x = stol(tokens_.at(FIRST_PARAMETER_INPUT));
        size_t y = stol(tokens_.at(SECOND_PARAMETER_INPUT));
        if (x < 1 || x > 7)
        {
          throw InvalidParameter(x);
        }
        else if (y < 1 || y > 7)
        {
          throw InvalidParameter(y);
        }
        game_.goTo(current_player_, x - 1, y - 1, true);
        if (print_map_)
        {
          printMap();
        }
        return true; // if no exception
      }
    }
    auto direction_input = tokens_.at(FIRST_PARAMETER_INPUT);
    if (!isFirstParameterValid())
    {
      throw InvalidParameter(direction_input);
    }
    if (tokens_.size() == 2) // go without optional steps
    {
      steps = 1;
    }
    else if (tokens_.size() == 3) // go with optional steps or coords
    {
      auto steps_input = tokens_.at(SECOND_PARAMETER_INPUT);
      // intijk July 5th 2015
      // from: https://stackoverflow.com/questions/25726531/how-to-remove-leading-zeros-from-string-using-c/31226728
      // begin
      steps_input.erase(
          0, std::min(steps_input.find_first_not_of('0'), steps_input.size() - 1)); // min to account for 0000
      // end
      if (steps_input.size() < STEP_STRING_LIMIT && isPositiveNumber(steps_input)) // steps cannot be larger than 10!!
      {
        steps = stol(steps_input);
        if (!steps) // check for 0 steps -> not allowed
        {
          throw InvalidParameter(steps_input);
        }
      }
      else
      {
        if (isPositiveNumber(steps_input))
        {
          throw ImpossibleMove();
        }
        throw InvalidParameter(steps_input);
      }
    }
    if (direction_input == "up")
    {
      game_.movePlayer(current_player_, MOVE_DIRECTION_UP, steps);
    }
    else if (direction_input == "down")
    {
      game_.movePlayer(current_player_, MOVE_DIRECTION_DOWN, steps);
    }
    else if (direction_input == "left")
    {
      game_.movePlayer(current_player_, MOVE_DIRECTION_LEFT, steps);
    }
    else if (direction_input == "right")
    {
      game_.movePlayer(current_player_, MOVE_DIRECTION_RIGHT, steps);
    }
    if (print_map_)
    {
      printMap();
    }
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::executeInsert()
{
  if (command_ == "insert" || command_ == "i")
  {
    if (tokens_.size() == 3)
    {
      auto insert_side_input = tokens_.at(FIRST_PARAMETER_INPUT);
      auto insert_row_col_input = tokens_.at(SECOND_PARAMETER_INPUT);
      if (!isFirstParameterValid())
      {
        throw InvalidParameter(insert_side_input);
      }
      if (!isPositiveNumber(insert_row_col_input))
      {
        throw InvalidParameter(insert_row_col_input);
      }
      if (insert_row_col_input.size() > INSERT_ROW_COL_STRING_LIMIT ||
          stoul(insert_row_col_input) > UPPER_INSERT_ROW_COL_BOUNDARY ||
          stoul(insert_row_col_input) < LOWER_INSERT_ROW_COL_BOUNDARY)
      {
        throw InvalidParameter(insert_row_col_input);
      }
      auto insert_row_col_number = stol(insert_row_col_input); // stol now save because size <=2
      //.at(0) to account for both valid params t and top, etc.
      game_.insertTile(tokens_, insert_side_input.at(0), insert_row_col_number); // only pass first letter of side
      has_inserted_ = true;
    }
    printMap();
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::executeRotate()
{
  if (command_ == "rotate")
  {
    auto rotation_direction = tokens_.at(FIRST_PARAMETER_INPUT);
    if (rotation_direction == "l" || rotation_direction == "left")
    {
      game_.rotateFreeTile(false);
      return true;
    }
    else if (rotation_direction == "r" || rotation_direction == "right")
    {
      game_.rotateFreeTile(true);
      return true;
    }
    else
    {
      throw InvalidParameter(rotation_direction);
    }
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::executeShowFreeTile()
{
  if (command_ == "showfreetile" || command_ == "sft")
  {
    printFreeTile();
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::executeShowOrHideTreasure()
{
  if (command_ == "showtreasure" || command_ == "st")
  {
    show_treasure_ = true;
    if (print_map_)
    {
      printMap();
    }
    else
    {
      checkTreasurePrint();
    }
    return true;
  }
  else if (command_ == "hidetreasure" || command_ == "ht") // on top otherwise double printing of st
  {
    show_treasure_ = false;
    cout << "\x1b[2J";
    printMap();
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::executeGamefield()
{
  if (command_ == "gamefield" || command_ == "g")
  {
    if (tokens_.size() == 2)
    {
      auto gameboard_flag = tokens_.at(FIRST_PARAMETER_INPUT);
      if (gameboard_flag == "on")
      {
        print_map_ = true;
      }
      else if (gameboard_flag == "off")
      {
        print_map_ = false;
      }
      else
      {
        throw InvalidParameter(gameboard_flag);
      }
    }
    if (tokens_.size() == 1)
    {
      printMap();
    }
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::executeFinish()
{
  if (command_ == "finish" || command_ == "f")
  {
    show_treasure_ = false;
    auto winning_player = game_.finishMove(current_player_);
    if (winning_player != "") // Some player has won
    {
      cout << "The Player " << winning_player << " has won the game!" << endl;
      game_over_ = true;
      return true;
    }
    done_with_the_move_ = true;
    has_inserted_ = false;
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------
void IOLoop::printFreeTile()
{
  cout << "Free tile:" << endl;
  for (const auto& row : game_.getFreeTileString())
  {
    cout << row << endl;
  }
}

//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::isFirstParameterValid()
{
  for (auto& command : commands_)
  {
    if (command_ == command.at(0))
    {
      for (auto& param : command)
      {
        // Number check to avoid helper numbers in commands_ to pass!
        auto first_parameter = tokens_.at(FIRST_PARAMETER_INPUT);
        if (first_parameter == param && !isPositiveNumber(first_parameter) && first_parameter != command_)
        {
          return true;
        }
      }
    }
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::isNumberOfParametersValid()
{
  for (auto& command : commands_)
  {
    if (command_ == "go")
    {
      if (tokens_.size() == 2)
      {
        return true;
      }
    }
    if (command_ == command.at(0))
    {
      if (tokens_.size() == stoul(command.at(1)))
      {
        return true;
      }
    }
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::commandTakesArguments()
{
  for (auto& command : commands_)
  {
    if (command.at(0) == command_ && command.at(1) != "1") // check max parameter number in commands_
    {
      return true;
    }
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------
void IOLoop::commandCurrentlyAllowed()
{
  if (has_inserted_)
  {
    if (command_.at(0) == 'i' || command_ == "rotate" || command_ == "play")
      throw CurrentlyNotAllowedCommand(command_);
  }
  else if (!has_inserted_ &&
           find(invalid_before_insert_.begin(), invalid_before_insert_.end(), command_) != invalid_before_insert_.end())
  {
    auto it = find_if(valid_requests_.begin(), valid_requests_.end(),
                      [this](const Request& req) { return req.command_ == this->command_; });
    throw CurrentlyNotAllowedCommand(it->repr_); // throw representation to account for arrow keys
  }
  return;
}

//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::isPositiveNumber(const string& s)
{
  std::string::const_iterator it = s.begin();
  while (it != s.end() && isdigit(*it))
  {
    ++it;
  }
  return !s.empty() && it == s.end();
}

//---------------------------------------------------------------------------------------------------------------------
void IOLoop::checkTreasurePrint()
{
  if (show_treasure_ && !didnt_execute_)
  {
    if (current_player_->getStack().empty())
    {
      cout << ALL_TREASURES_FOUND_MESSAGE << endl;
    }
    else
    {
      auto treasure = current_player_->getStack().top();
      cout << "Current Treasure: " << treasure->getName() << " Nr.: " << treasure->getTreasureId() << endl;
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------
vector<string> IOLoop::parseCommand()
{
  vector<string> incoming_tokens = vector<string>();
  if (!input_.empty())
  {
    tokenize(input_, ' ', incoming_tokens);
  }
  return incoming_tokens;
}

//---------------------------------------------------------------------------------------------------------------------
// Tokenize function
// from: https://www.techiedelight.com/split-string-cpp-using-delimiter/
// begin
void IOLoop::tokenize(const string& str, const char delimiter, vector<string>& out)
{
  size_t start;
  size_t end = 0;
  while ((start = str.find_first_not_of(delimiter, end)) != std::string::npos)
  {
    end = str.find(delimiter, start);
    out.push_back(str.substr(start, end - start));
  }
}
// end

//---------------------------------------------------------------------------------------------------------------------
bool IOLoop::commandExists()
{
  for (auto& request : valid_requests_)
  {
    if (command_ == request.command_)
    {
      return true;
    }
  }
  return false;
}
