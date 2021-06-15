//----------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// TreasureTile.cpp
//
// Concrete class which models all the TreasureTiles
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#include "TreasureTile.hpp"
#include <iostream>

//----------------------------------------------------------------------------------------------------------------------
vector<string> TreasureTile::getTileString() const
{
  vector<string> field = repr_->at(static_cast<unsigned long>(type_)).at(static_cast<unsigned long>(rotation_));
  // replace *** with treasure if not found
  auto to_replace = field.at(2);
  auto pos = to_replace.find("***");
  if (!collected_)
  {
    to_replace.replace(pos, 3, "T" + treasure_->getTreasureId());
  }
  else
  {
    to_replace.replace(pos, 3, "   ");
  }
  field.at(2) = to_replace;
  // replace ----- with current players on field
  field.at(3) = replaceCurrentPlayerSubstring(field.at(3));
  return field;
}

//----------------------------------------------------------------------------------------------------------------------
TreasureTile::TreasureTile(TileType type, Rotation rot) : Tile{type, rot}
{
  collected_ = false;
}

//----------------------------------------------------------------------------------------------------------------------
void TreasureTile::collectTreasure(bool collected)
{
  collected_ = collected;
  treasure_->setFound(collected); // also set the corresponding treasure
}

//----------------------------------------------------------------------------------------------------------------------
void TreasureTile::setTreasure(shared_ptr<Treasure> treasure)
{
  treasure_ = treasure;
}

//----------------------------------------------------------------------------------------------------------------------
shared_ptr<Treasure> TreasureTile::getTreasure() const
{
  return treasure_;
}
