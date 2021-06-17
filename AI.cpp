#include "AI.hpp"

AI::AI(Game& game) : game_{game}
{
  starttime_ = std::chrono::steady_clock::now();
  fall_back_pos = (game_.getFordbiddenPosition() + 2 > 7) ? 2 : game.getFordbiddenPosition() + 2;
};

long AI::getLifeTime()
{
  auto now = std::chrono::steady_clock::now();
  long dur = std::chrono::duration_cast<std::chrono::milliseconds>(now - starttime_).count();
  return dur;
}