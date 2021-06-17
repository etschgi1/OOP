#include "AI.hpp"

AI::AI(Game& game, shared_ptr<Player> current_player) : game_{game}, player_{current_player}
{
  starttime_ = std::chrono::steady_clock::now();
  fall_back_pos = (game_.getFordbiddenPosition() + 2 > 7) ? 2 : game.getFordbiddenPosition() + 2;
  string out = "insert ";
  out.push_back(fall_back_side);
  out += " " + to_string(fall_back_pos);
  commands.push_back(out);
  commands.push_back("go 0 0");
  commands.push_back("finish");

  // see if player has treasure and is not done otherwise set goal to start field

  // set goal to treasure of player
};

long AI::getLifeTime()
{
  auto now = std::chrono::steady_clock::now();
  long dur = std::chrono::duration_cast<std::chrono::milliseconds>(now - starttime_).count();
  return dur;
}

void AI::printInfo()
{
  for (auto command : commands)
  {
    cout << INFO_PRINTOUT << command << endl;
  }
}
void AI::executeCommands()
{

  return;
}
void AI::setBestInsert(char side, size_t position) {}