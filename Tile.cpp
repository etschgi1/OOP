//--------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// Tile.cpp
//
// Abstract Class to represent the tiles on the gameboard.
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//--------------------------------------------------------------------------------------------------------------------
//

#include "Tile.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Bitmap;

//---------------------------------------------------------------------------------------------------------------------
Tile::Tile(TileType type, Rotation rot) : type_{type}, rotation_{rot}
{
  Bitmap& bitmap = Bitmap::instance();
  repr_ = &bitmap.repr_;
}

//---------------------------------------------------------------------------------------------------------------------
int Tile::getRotationValue()
{
  return 90 * static_cast<unsigned long>(rotation_);
}

//---------------------------------------------------------------------------------------------------------------------
string Tile::getTileTypeString()
{
  switch (type_)
  {
    case TileType::T:
      return "T";
      break;
    case TileType::L:
      return "L";
      break;
    case TileType::I:
      return "I";
      break;
    case TileType::O:
      return "O";
      break;
    case TileType::U:
      return "U";
      break;
    case TileType::X:
      return "X";
      break;
  }
}

//---------------------------------------------------------------------------------------------------------------------
TileType Tile::getType()
{
  return type_;
}

//---------------------------------------------------------------------------------------------------------------------
Rotation Tile::getRotation()
{
  return rotation_;
}

//---------------------------------------------------------------------------------------------------------------------
vector<shared_ptr<Player>> Tile::getPlayers() const
{
  return players_on_tile_;
}

//---------------------------------------------------------------------------------------------------------------------
void Tile::setRotation(Rotation rot)
{
  rotation_ = rot;
}

//---------------------------------------------------------------------------------------------------------------------
void Tile::movePlayerToTile(const shared_ptr<Player>& player)
{
  players_on_tile_.push_back(player);
  // store current tile into player
}

//---------------------------------------------------------------------------------------------------------------------
string Tile::replaceCurrentPlayerSubstring(string substring_players_on_tile) const
{
  // replace ----- with current players on field
  auto to_replace = std::move(substring_players_on_tile);
  auto pos = to_replace.find("-----");
  string players_on_tile;
  size_t player_field_count = players_on_tile_.size();
  for (const auto& player : this->getPlayers())
  {
    players_on_tile += player->getColor();
  }
  string ordered_players = "P"; // order player colors right
  char players[4] = {'R', 'Y', 'G', 'B'};
  for (auto playercolor : players)
  {
    if (players_on_tile.find(playercolor) < 4) // 4 is player arrays lenght
    {
      ordered_players += playercolor;
    }
  }
  switch (player_field_count)
  {
    case 4: // nothing needed if 4 players on tile
      break;
    case 3:
      ordered_players = " " + ordered_players;
      break;
    case 2:
      ordered_players = " " + ordered_players + " ";
      break;
    case 1:
      ordered_players = " " + ordered_players + "  ";
      break;
    default:
      ordered_players = "     "; // default, when no player on tile
      break;
  }
  to_replace.replace(pos, 5, ordered_players);
  return to_replace;
}

//---------------------------------------------------------------------------------------------------------------------
void Tile::removePlayerFromTile(const shared_ptr<Player>& player)
{
  players_on_tile_.erase(std::find(players_on_tile_.begin(), players_on_tile_.end(), player));
}

void Tile::setGScore(double score)
{
  g_score_ = score;
}

void Tile::setFScore(double score)
{
  f_score_ = score;
}

double Tile::getGScore() const
{
  return g_score_;
}

double Tile::getFScore() const
{
  return f_score_;
}
