//----------------------------------------------------------------------------------------------------------------------
// NormalTile.cpp
//
// Concrete class which models all the normal Tiles (without treasures)
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#include "NormalTile.hpp"

//----------------------------------------------------------------------------------------------------------------------
NormalTile::NormalTile(TileType type, Rotation rot) : Tile{type, rot} {}

//----------------------------------------------------------------------------------------------------------------------
vector<string> NormalTile::getTileString() const
{
  auto field = repr_->at(static_cast<unsigned long>(type_)).at(static_cast<unsigned long>(rotation_));
  // replace *** with spaces
  string to_replace = field.at(2);
  auto pos = to_replace.find("***");
  to_replace.replace(pos, 3, "   ");
  field.at(2) = to_replace;
  field.at(3) = replaceCurrentPlayerSubstring(field.at(3));
  return field;
}
