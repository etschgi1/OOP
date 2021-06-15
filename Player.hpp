//---------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// Player.hpp
//
// Class to model the players playing the game
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef OOP1SS21_A2_135_PLAYER_H
#define OOP1SS21_A2_135_PLAYER_H

#include "Treasure.hpp"
#include <memory>
#include <stack>
#include <vector>

using std::shared_ptr;
using std::stack;

class Player
{
  stack<shared_ptr<Treasure>> covered_stack_;
  int number_found_treasures_;
  char color_;
  bool done_ = false;

public:
  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor
  ///
  /// @param name - the name of the Player
  /// @param pos - the coordinates of the Player
  ///
  //
  explicit Player(char color);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Deleted Copy-Constructor
  ///
  //
  Player(Treasure&) = delete;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor
  ///
  //
  ~Player() = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the color of the Player
  ///
  /// @return color of player
  //
  [[nodiscard]] char getColor() const;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Increments the number_found_treasures_ counter
  ///
  /// @return no return
  //
  void found();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Gets the player's Treasure Card Stack
  ///
  /// @return stack with shared_ptr to the Treasures
  //
  stack<shared_ptr<Treasure>>& getStack();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Gets number of found treasures for player
  ///
  /// @return number of found treasures
  //
  [[nodiscard]] int getNumberFoundTreasures() const { return number_found_treasures_; }

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets done to the given value
  ///
  /// @param done set done_ to given bool
  ///
  //
  void setDone(bool done);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Gets done_ status
  ///
  /// @returns done_ status
  //
  [[nodiscard]] bool getDone() const;
};

#endif // OOP1SS21_A2_135_PLAYER_H
