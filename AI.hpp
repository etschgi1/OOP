#ifndef OOP1SS21_A2_135_AI
#define OOP1SS21_A2_135_AI
#include "Game.hpp"
#include "chrono"
#include <thread>
class AI
{
private:
  Game& game_;
  std::chrono::steady_clock::time_point starttime_;

  // ermergency fallback move
  char fall_back_side = 'b';
  unsigned long fall_back_pos;

public:
  // supply game instance to AI
  AI(Game& game);
  ~AI() = default;
  long getLifeTime();
};
#endif // OOP1SS21_A2_135_AI