//----------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// TreasureTile.hpp
//
// Concrete class which models all the TreasureTiles
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#ifndef OOP1SS21_A2_135_TREASURETILE_H
#define OOP1SS21_A2_135_TREASURETILE_H

#include "Tile.hpp"

class Treasure;

using std::shared_ptr;
using std::string;
using std::vector;
class TreasureTile : public Tile
{
  shared_ptr<Treasure> treasure_;
  bool collected_;

public:
  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor
  ///
  /// @param type - the type of the TreasureTile
  /// @param rot - the rotation of the TreasureTile
  ///
  //
  TreasureTile(TileType type, Rotation rot);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Deleted Copy-Constructor
  ///
  //
  TreasureTile(TreasureTile&) = delete;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor
  ///
  //
  ~TreasureTile() override = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets Tile Status to collected
  ///
  /// @param collected true if Treasure on tile is collected
  ///
  /// @return no return
  //
  void collectTreasure(bool collected);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets Tiles Treasure to a given Treasure
  ///
  /// @param treasure the Treasure which should be set for the Tile
  ///
  /// @return no return
  //
  void setTreasure(shared_ptr<Treasure> treasure);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Gets the Treasure which is on the tile
  ///
  /// @return a shared_ptr to the Treasure which is on the tile
  //
  [[nodiscard]] shared_ptr<Treasure> getTreasure() const;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns a vector of strings which represents this tile
  ///
  /// @return vector of strings representing the tile
  //
  [[nodiscard]] vector<string> getTileString() const override;
};

#endif // OOP1SS21_A2_135_TREASURETILE_H
