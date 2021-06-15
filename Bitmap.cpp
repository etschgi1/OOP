//----------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// Bitmap.hpp
//
// Bitmap class (singelton); This contains all of the tiles graphical string representations in an ordered fashion,
// which allows use to leverage the structures order to access the correct repr for each tile with a type and
// a rotation.
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#include "Bitmap.hpp"

//----------------------------------------------------------------------------------------------------------------------
Bitmap::Bitmap()
{
  // crossing right
  const vector<string> gang_T0 = {"██     ██", "██       ", "██ ***   ", "██-----  ", "██     ██"};
  // crossing up
  const vector<string> gang_T1 = {"██     ██", "         ", "   ***   ", "  -----  ", "█████████"};
  // crossing left
  const vector<string> gang_T2 = {"██     ██", "       ██", "   *** ██", "  -----██", "██     ██"};
  // crossing bottom
  const vector<string> gang_T3 = {"█████████", "         ", "   ***   ", "  -----  ", "██     ██"};
  // turn top-right
  const vector<string> gang_L0 = {"██     ██", "██       ", "██ ***   ", "██-----  ", "█████████"};
  // turn left-top
  const vector<string> gang_L1 = {"██     ██", "       ██", "   *** ██", "  -----██", "█████████"};
  // turn left-bottom
  const vector<string> gang_L2 = {"█████████", "       ██", "   *** ██", "  -----██", "██     ██"};
  // turn bottom-right
  const vector<string> gang_L3 = {"█████████", "██       ", "██ ***   ", "██-----  ", "██     ██"};
  // horizontal Corridor
  const vector<string> gang_I0 = {"█████████", "         ", "   ***   ", "  -----  ", "█████████"};
  // vertical Corridor
  const vector<string> gang_I1 = {"██     ██", "██     ██", "██ *** ██", "██-----██", "██     ██"};
  // closed
  const vector<string> closed_O = {"█████████", "██     ██", "██ *** ██", "██-----██", "█████████"};
  // dead end bottom
  const vector<string> end_U0 = {"██     ██", "██     ██", "██ *** ██", "██-----██", "█████████"};
  // dead end right
  const vector<string> end_U1 = {"█████████", "       ██", "  ***  ██", "  -----██", "█████████"};
  // dead end up
  const vector<string> end_U2 = {"█████████", "██     ██", "██ *** ██", "██-----██", "██     ██"};
  // dead end left
  const vector<string> end_U3 = {"█████████", "██       ", "██ ***   ", "██-----  ", "█████████"};
  // all open
  const vector<string> gang_X = {"██     ██", "         ", "   ***   ", "  -----  ", "██     ██"};

  T_.push_back(gang_T3);
  T_.push_back(gang_T0);
  T_.push_back(gang_T1);
  T_.push_back(gang_T2);

  L_.push_back(gang_L0);
  L_.push_back(gang_L1);
  L_.push_back(gang_L2);
  L_.push_back(gang_L3);

  I_.push_back(gang_I1);
  I_.push_back(gang_I0);
  I_.push_back(gang_I1);
  I_.push_back(gang_I0);

  O_.push_back(closed_O);
  O_.push_back(closed_O);
  O_.push_back(closed_O);
  O_.push_back(closed_O);

  U_.push_back(end_U0);
  U_.push_back(end_U1);
  U_.push_back(end_U2);
  U_.push_back(end_U3);

  X_.push_back(gang_X);
  X_.push_back(gang_X);
  X_.push_back(gang_X);
  X_.push_back(gang_X);

  repr_.push_back(T_);
  repr_.push_back(L_);
  repr_.push_back(I_);
  repr_.push_back(O_);
  repr_.push_back(U_);
  repr_.push_back(X_);
}
