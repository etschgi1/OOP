//----------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// NormalTile.hpp
//
// Concrete class which models all the normal Tiles (without treasures)
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#ifndef OOP1SS21_A2_135_NORMALTILE_H
#define OOP1SS21_A2_135_NORMALTILE_H

#include "Tile.hpp"

using std::string;
using std::vector;

class NormalTile : public Tile
{

public:
  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor
  ///
  /// @param name - the name of the NormalTile
  /// @param pos - the coordinates of the NormalTile
  //
  NormalTile(TileType type, Rotation rot);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Deleted Copy-Constructor
  ///
  //
  NormalTile(NormalTile&) = delete;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor
  ///
  //
  ~NormalTile() override = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Getter for the string representation of the tile.
  ///
  /// @return a vector of strings representing the current state of the tile
  //
  [[nodiscard]] vector<string> getTileString() const override;
};

#endif // OOP1SS21_A2_135_NORMALTILE_H
