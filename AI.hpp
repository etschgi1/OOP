#ifndef OOP1SS21_A2_135_AI
#define OOP1SS21_A2_135_AI
#include "Game.hpp"
#include "chrono"
#include <thread>
using std::to_string;
class AI
{
private:
  // Constants:
  const string INFO_PRINTOUT = "[INFO] Command: ";
  Game& game_;
  shared_ptr<Player> player_;

  std::chrono::steady_clock::time_point starttime_;
  // vector with all commands for string output
  vector<string> commands;
  // ermergency fallback move
  char fall_back_side = 'b';
  unsigned long fall_back_pos;
  bool success_flag = false;
  // inserts:
  vector<char> insert_sides = {'t', 'l', 'b', 'r'};
  char insert_side;
  unsigned long insert_position;

  // field_goal
  shared_ptr<Tile> goal_tile;
  unsigned long goal_row;
  unsigned long goal_col;

public:
  // supply game instance to AI
  AI(Game& game, shared_ptr<Player> current_player);
  ~AI() = default;
  void setBestInsert(char side, size_t position); //! Does not check if insert is valid
  long getLifeTime();
  void printInfo();
  void executeCommands();
  void run();
  bool getSuccess() const { return success_flag; }
  string getInsertSidestring() const
  {
    string out;
    out.push_back(insert_side);
    return out;
  }
  string getInsertPositionstring() const { return to_string(insert_position); }
  string getGoalRowstring() const { return to_string(goal_row + 1); }
  string getGoalColstring() const { return to_string(goal_col + 1); }
  string getInsertCommand() const { return commands.at(0); }
  string getGoCommand() const { return commands.at(1); }
};
#endif // OOP1SS21_A2_135_AI