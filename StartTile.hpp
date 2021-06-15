//----------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// StartTile.hpp
//
// Concrete class which models the StartTile of the players
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#ifndef OOP1SS21_A2_135_STARTTILE_H
#define OOP1SS21_A2_135_STARTTILE_H

#include "Tile.hpp"
using std::string;
using std::vector;
class StartTile : public Tile
{

  char player_color_;

public:
  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor
  ///
  /// @param name - the name of the StartTile
  /// @param pos - the coordinates of the StartTile
  ///
  //
  explicit StartTile(TileType type, Rotation rot, char player_color);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Deleted Copy-Constructor
  ///
  //
  StartTile(StartTile&) = delete;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor
  ///
  //
  ~StartTile() override = default;

  [[nodiscard]] std::vector<string> getTileString() const override;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the player color of itself
  ///
  /// @return returns player color of tile
  //
  [[nodiscard]] char getPlayerColor() const { return player_color_; };
};

#endif // OOP1SS21_A2_135_STARTTILE_H
