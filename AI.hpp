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

  // inserts:
  char insert_side;
  unsigned long insert_position;

  // field_goal
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
};
#endif // OOP1SS21_A2_135_AI