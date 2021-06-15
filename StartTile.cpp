//----------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// StartTile.cpp
//
// Concrete class which models the StartTile of the players
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#include "StartTile.hpp"
#include <string>

//----------------------------------------------------------------------------------------------------------------------
StartTile::StartTile(TileType type, Rotation rot, char player_color) : Tile{type, rot}, player_color_{player_color} {}

//----------------------------------------------------------------------------------------------------------------------
vector<string> StartTile::getTileString() const
{
  auto field = this->repr_->at(static_cast<unsigned long>(type_)).at(static_cast<unsigned long>(rotation_));
  // replace fixed Player emblem
  auto to_replace = field.at(2);
  string replacement = "(" + string(1, player_color_) + ")";
  auto pos = to_replace.find("***");
  to_replace.replace(pos, 3, replacement);
  field.at(2) = to_replace;
  field.at(3) = replaceCurrentPlayerSubstring(field.at(3));
  return field;
}
