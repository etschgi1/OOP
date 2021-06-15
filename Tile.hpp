//----------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// Tile.hpp
//
// Abstract Class to represent the tiles on the gameboard.
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#ifndef OOP1SS21_A2_135_TILE_H
#define OOP1SS21_A2_135_TILE_H

#include <string>
#include <vector>

#include "Bitmap.hpp"
#include "Player.hpp"
#include "Treasure.hpp"

using std::shared_ptr;
using std::string;
using std::vector;

// some enums used by the Tile class
enum class TileType
{
  T,
  L,
  I,
  O,
  U,
  X
};

enum class Rotation
{
  DEG0 = 0,
  DEG90 = 1,
  DEG180 = 2,
  DEG270 = 3
};

inline Rotation& operator++(Rotation& rot)
{
  switch (rot)
  {
    case Rotation::DEG0:
      return rot = Rotation::DEG90;
    case Rotation::DEG90:
      return rot = Rotation::DEG180;
    case Rotation::DEG180:
      return rot = Rotation::DEG270;
    case Rotation::DEG270:
      return rot = Rotation::DEG0;
  }
  return rot; // some compilers might warn otherwise
}

inline Rotation& operator--(Rotation& rot)
{
  switch (rot)
  {
    case Rotation::DEG0:
      return rot = Rotation::DEG270;
    case Rotation::DEG90:
      return rot = Rotation::DEG0;
    case Rotation::DEG180:
      return rot = Rotation::DEG90;
    case Rotation::DEG270:
      return rot = Rotation::DEG180;
  }
  return rot; // some compilers might warn otherwise
}

class Tile
{
  // childs can use these
protected:
  TileType type_;
  Rotation rotation_;
  vector<shared_ptr<Player>> players_on_tile_;
  vector<vector<vector<string>>>* repr_;

public:
  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor
  ///
  /// @param type - the type of the tile e.g. L
  /// @param rot - the rotation of the tile
  ///
  //
  explicit Tile(TileType type, Rotation rot);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Deleted Copy-Constructor
  ///
  //
  Tile(Tile&) = delete;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor
  ///
  //
  virtual ~Tile() = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Purely virtual methode which is implemented in the children and returns a vector of strings representing the
  /// tile
  ///
  /// @return vector of strings representing the tile
  //
  [[nodiscard]] virtual vector<string> getTileString() const = 0;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Gets the current rotation as an int. It can be on of the following: 0 90 180 270
  ///
  /// @return the current rotation either 0 90 180 or 270
  //
  int getRotationValue();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns type_ of the Tile as a string
  ///
  /// @return type_ as a string
  //
  string getTileTypeString();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Getter for the type of the Tile
  ///
  /// @return the TileType type of the Tile
  //
  TileType getType();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Gets the rotation of the Tile
  ///
  /// @return the Rotation of the Tile
  //
  Rotation getRotation();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Gets the vector containing the pointers to the current players on this Tile
  ///
  /// @return the vector of the current players on a Tile
  //
  [[nodiscard]] vector<shared_ptr<Player>> getPlayers() const;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets the rotation of a tile
  ///
  /// @param rot - the rotation which is set
  ///
  /// @return no return
  //
  void setRotation(Rotation rot);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Replaces the placeholder in the substring_players_on_tile with the players currently standing on the tile
  ///
  /// @param substring_players_on_tile - substring which should be replaced which players
  ///
  /// @return returns substring with players in it
  //
  [[nodiscard]] string replaceCurrentPlayerSubstring(string substring_players_on_tile) const;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Moves player to internal player vector of a tile
  /// moves a player to the players_on_tile_ vector
  ///
  /// @param player - the coordinates of a Field
  ///
  /// @return no return
  //
  void movePlayerToTile(const shared_ptr<Player>& player);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Removes a player from the internal player vector of a tile
  ///
  /// @param pos - the coordinates of a Field
  ///
  /// @return no return
  //
  void removePlayerFromTile(const shared_ptr<Player>& player);
};

#endif // OOP1SS21_A2_135_TILE_H
