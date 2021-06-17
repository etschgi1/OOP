#ifndef OOP1SS21_A2_135_AI
#define OOP1SS21_A2_135_AI
#include "Game.hpp"
class AI
{
private:
  Game& game_;

public:
  // supply game instance to AI
  AI(Game& game);
  ~AI() = default;
};
#endif // OOP1SS21_A2_135_AI