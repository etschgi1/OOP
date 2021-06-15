//---------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// Game.cpp
//
// Game class (singleton); Main Class which manages the gameboard, players and treasures, includes member functions
// to alter the state of the board.
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//---------------------------------------------------------------------------------------------------------------------
//

#include "Game.hpp"
#include <algorithm>
#include <iostream>

//---------------------------------------------------------------------------------------------------------------------
Game::Game(int playercount) : playercount_{playercount}
{
  for (size_t i = 0; i < this->getPlayerCount(); i++)
  {
    auto player = make_shared<Player>(player_colors_.at(i));
    players_.push_back(player);
  }
  Oop::Random& rand = Oop::Random::getInstance();
  // initialize treasures into treasures vector
  vector<shared_ptr<Treasure>> treasures;
  {
    int counter = 0;
    for (auto card : cards_)
    {
      string t_id = card.substr(0, 2);
      card.erase(0, 2);
      auto treasure = make_shared<Treasure>(card, t_id);
      treasures.push_back(treasure);
      counter++;
    }
  }
  // Treasure Vector with all treasures
  auto static_treasures =
      vector<shared_ptr<Treasure>>(treasures.begin(), treasures.begin() + NUMBER_OF_STATIC_TREASURES);
  auto movable_treasures =
      vector<shared_ptr<Treasure>>(treasures.begin() + NUMBER_OF_STATIC_TREASURES, treasures.end());
  // Vector with all free
  vector<int> tiles_order = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2,
                             2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  vector<shared_ptr<Tile>> movable_tiles;
  {
    int moveable_treasure_counter = 0;
    for (auto tile_type : tiles_order)
    {
      if (tile_type)
      {
        auto rot = Rotation::DEG0;
        auto type = static_cast<TileType>(tile_type);
        auto tile = make_shared<NormalTile>(type, rot);
        movable_tiles.push_back(tile);
      }
      else
      {
        auto rot = Rotation::DEG0;
        auto type = static_cast<TileType>(tile_type);
        auto tile = make_shared<TreasureTile>(type, rot);
        tile->setTreasure(movable_treasures.at(moveable_treasure_counter));
        movable_tiles.push_back(tile);
        moveable_treasure_counter++;
      }
    }
  }
  populateTiles(movable_tiles, static_treasures);
  for (size_t count = 0; !treasures.empty(); count++)
  {
    auto treasure_index = rand.getRandomCard(treasures.size()) - 1; //-1 for indexing treasures later
    auto treasure = treasures.at(treasure_index);
    players_.at(count % players_.size())->getStack().push(treasure);
    treasures.erase(treasures.begin() + treasure_index);
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Game::printRow(const vector<shared_ptr<Tile>>& row, int row_number)
{
  for (size_t row_n = 0; row_n < LINE_HEIGHT_OF_TILE; row_n++)
  {
    if (row_n == MIDDLE_LINE_OF_TILE)
    {
      if (row_number % 2 == 0)
      {
        cout << "-->" << row_number;
      }
      else
      {
        cout << "   " << row_number;
      }
    }
    else
    {
      cout << "    ";
    }
    for (auto& tile : row)
    {
      vector<string> sub_strings = tile->getTileString();
      cout << sub_strings.at(row_n);
    }
    if (row_n == MIDDLE_LINE_OF_TILE)
    {
      if (row_number % 2 == 0)
      {
        cout << "<--";
      }
    }
    cout << endl;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Game::printMap()
{
  cout << "Player Red(R)    |                 |                 |    Player Yellow(Y)" << endl; //  printing header
  if (this->getPlayerCount() > 2)
  {
    if (players_.at(0)->getNumberFoundTreasures() < DOUBLE_DIGIT)
    {
      cout << "Treasure: " << players_.at(0)->getNumberFoundTreasures() << "/"
           << TREASURE_TOTAL / this->getPlayerCount()
           << "    V                 V                 V    Treasure: " << players_.at(1)->getNumberFoundTreasures()
           << "/" << TREASURE_TOTAL / this->getPlayerCount() << endl;
    }
    else
    {
      cout << "Treasure: " << players_.at(0)->getNumberFoundTreasures() << "/"
           << TREASURE_TOTAL / this->getPlayerCount()
           << "   V                 V                 V    Treasure: " << players_.at(1)->getNumberFoundTreasures()
           << "/" << TREASURE_TOTAL / this->getPlayerCount() << endl;
    }
  }
  if (this->getPlayerCount() == 2)
  {
    if (players_.at(0)->getNumberFoundTreasures() < DOUBLE_DIGIT)
    {
      cout << "Treasure: " << players_.at(0)->getNumberFoundTreasures() << "/"
           << TREASURE_TOTAL / this->getPlayerCount()
           << "   V                 V                 V    Treasure: " << players_.at(1)->getNumberFoundTreasures()
           << "/" << TREASURE_TOTAL / this->getPlayerCount() << endl;
    }
    else
    {
      cout << "Treasure: " << players_.at(0)->getNumberFoundTreasures() << "/"
           << TREASURE_TOTAL / this->getPlayerCount()
           << "  V                 V                 V    Treasure: " << players_.at(1)->getNumberFoundTreasures()
           << "/" << TREASURE_TOTAL / this->getPlayerCount() << endl;
    }
  }
  cout << "        1        2        3        4        5        6        7    " << endl;
  for (size_t i = 0; i < this->gameboard_.size(); i++) // printing each row of the gameboard
  {
    printRow(this->gameboard_.at(i), i + 1);
  }
  switch (this->getPlayerCount()) //  printing footer
  {
    case 2:
      cout << "                 Ʌ                 Ʌ                 Ʌ" << endl
           << "                 |                 |                 |" << endl;
      break;
    case 3:
      if (players_.at(2)->getNumberFoundTreasures() < DOUBLE_DIGIT)
      {
        cout << "Player Green(G)  Ʌ                 Ʌ                 Ʌ" << endl
             << "Treasure: " << players_.at(2)->getNumberFoundTreasures() << "/"
             << TREASURE_TOTAL / this->getPlayerCount() << "    |                 |                 |" << endl;
      }
      else
      {
        cout << "Player Green(G)  Ʌ                 Ʌ                 Ʌ" << endl
             << "Treasure: " << players_.at(2)->getNumberFoundTreasures() << "/"
             << TREASURE_TOTAL / this->getPlayerCount() << "   |                 |                 |" << endl;
      }
      break;
    case 4:
      if (players_.at(2)->getNumberFoundTreasures() < DOUBLE_DIGIT)
      {
        cout << "Player Green(G)  Ʌ                 Ʌ                 Ʌ    Player Blue(B)" << endl
             << "Treasure: " << players_.at(2)->getNumberFoundTreasures()
             << "/6    |                 |                 |   Treasure: " << players_.at(3)->getNumberFoundTreasures()
             << "/6" << endl;
      }
      else
      {
        cout << "Player Green(G)  Ʌ                 Ʌ                 Ʌ    Player Blue(B)" << endl
             << "Treasure: " << players_.at(2)->getNumberFoundTreasures()
             << "/6   |                 |                 |   Treasure: " << players_.at(3)->getNumberFoundTreasures()
             << "/6" << endl;
      }
      break;
  }
}

//---------------------------------------------------------------------------------------------------------------------
char Game::getStartTileColor(int x, int y) const
{
  int count = 0;
  for (auto& start_tile : start_tiles_)
  {
    if (start_tile.at(0) == x && start_tile.at(1) == y)
    {
      return player_colors_.at(count);
    }
    count++;
  }
  return 'X';
}

//---------------------------------------------------------------------------------------------------------------------
void Game::movePlayer(const shared_ptr<Player>& player, int direction, int steps)
{
  shared_ptr<Tile> new_tile = nullptr;
  bool found = false;
  for (const auto& tile : tiles_containing_players_)
  {
    for (const auto& player_in_tile : tile->getPlayers())
    {
      if (player_in_tile == player)
      {
        int coords[2] = {};
        for (auto row : gameboard_)
        {
          auto iter = find(row.begin(), row.end(), tile);
          if (iter != row.end())
          {
            coords[1] = std::distance(row.begin(), iter);
            break;
          }
          coords[0] = coords[0] + 1;
        }
        //        check if move is valid checkvalidmove(coords,direction,steps)
        if (checkMoveIsValid(coords, direction, steps))
        {
          if (direction == MOVE_DIRECTION_RIGHT)
          {
            new_tile = gameboard_.at(coords[0]).at(coords[1] + steps);
          }
          else if (direction == MOVE_DIRECTION_DOWN)
          {
            new_tile = gameboard_.at(coords[0] + steps).at(coords[1]);
          }
          else if (direction == MOVE_DIRECTION_LEFT)
          {
            new_tile = gameboard_.at(coords[0]).at(coords[1] - steps);
          }
          else if (direction == MOVE_DIRECTION_UP)
          {
            new_tile = gameboard_.at(coords[0] - steps).at(coords[1]);
          }
          new_tile->movePlayerToTile(player);
          tile->removePlayerFromTile(player);
          if (tile->getPlayers().empty())
          {
            tiles_containing_players_.erase(tile);
          }
        }
        else
        {
          throw ImpossibleMove();
        }
        found = true;
        break;
      }
    }
    if (found)
    {
      break;
    }
  }
  if (new_tile != nullptr)
  {
    tiles_containing_players_.insert(new_tile);
  }
}

//---------------------------------------------------------------------------------------------------------------------
bool Game::checkMoveIsValid(int* rowcol, int direction, int steps)
{
  auto odd = direction % 2;
  //  moving down 1 moving up -1, 0 not moving vertically
  int row_step = odd ? ((direction - odd) ? (-1) : (1)) : 0;
  //  moving right 1 moving left -1, 0 not moving horizontally
  int col_step = odd ? 0 : ((direction) ? (-1) : (1));
  auto current = gameboard_.at(rowcol[0]).at(rowcol[1]);
  //  Static cast conversion is valid because if the int were negative the check just before would have caught it
  if ((-1 > (rowcol[0] + row_step * steps)) ||
      (static_cast<size_t>(rowcol[0] + row_step * steps) >= (gameboard_.size())) ||
      (-1 > (rowcol[1] + col_step * steps)) ||
      (static_cast<size_t>(rowcol[1] + col_step * steps) >= (gameboard_.size())))
  {
    return false;
  }
  for (int i = 0; i < steps; i++)
  {
    auto next = gameboard_.at(rowcol[0] + row_step * (i + 1)).at(rowcol[1] + col_step * (i + 1));
    auto current_string = current->getTileString().at(2 + row_step * 2);
    auto next_string = next->getTileString().at(2 - row_step * 2);
    bool passed = false;
    //   check if a space ASCII \x20 is somewhere in the middle of the direction we are heading
    switch (col_step)
    {
      case -1:
        passed = (current_string.front() == SPACE_KEY && next_string.back() == SPACE_KEY);
        break;
      case 0:
        // we take the sixth character of the string because it wouldn't overshoot the target of the middle of the
        // string
        passed = (current_string.at(6) == SPACE_KEY && next_string.at(6) == SPACE_KEY);
        break;
      case 1:
        passed = (current_string.back() == SPACE_KEY && next_string.front() == SPACE_KEY);
        break;
    }
    if (passed)
    {
      current = next;
    }
    else
    {
      return false;
    }
  }
  return true;
}

//---------------------------------------------------------------------------------------------------------------------
vector<shared_ptr<Player>> Game::getPlayers()
{
  return players_;
}

//---------------------------------------------------------------------------------------------------------------------
vector<string> Game::getFreeTileString()
{
  return free_tile_->getTileString();
}

//---------------------------------------------------------------------------------------------------------------------
void Game::rotateFreeTile(bool clockwise)
{
  auto rot = free_tile_->getRotation();
  free_tile_->setRotation(clockwise ? --rot : ++rot);
}

//---------------------------------------------------------------------------------------------------------------------
void Game::insertTile(vector<string> tokens, char side, size_t position)
{
  // check forbidden moves
  if (side == forbidden_move_.side && position == forbidden_move_.position)
  {
    string error_message = tokens.at(0) + " " + tokens.at(1) + " " + tokens.at(2);
    throw CurrentlyNotAllowedCommand(error_message);
  }
  if (position != 2 && position != 4 && position != 6) // check if position is valid
  {
    throw InvalidPosition();
  }
  // only valid sides and positions left
  switch (side)
  {
    case 't':
      insertTileVertical(true, position);
      forbidden_move_.side = 'b';
      break;
    case 'b':
      insertTileVertical(false, position);
      forbidden_move_.side = 't';
      break;
    case 'r':
      insertTileHorizontal(false, position);
      forbidden_move_.side = 'l';
      break;
    case 'l':
      insertTileHorizontal(true, position);
      forbidden_move_.side = 'r';
      break;
  }
  forbidden_move_.position = position;
}

//---------------------------------------------------------------------------------------------------------------------
void Game::insertTileVertical(bool top, size_t position)
{
  auto to_insert = free_tile_;
  position--; // internal representation starts at 0
  if (top)
  {
    for (auto& row : gameboard_)
    {
      auto temporary = row.at(position);
      row.at(position) = to_insert;
      to_insert = temporary;
    }
  }
  else
  {
    for (int count = gameboard_.size() - 1; count >= 0; count--)
    {
      auto temporary = gameboard_.at(count).at(position);
      gameboard_.at(count).at(position) = to_insert;
      to_insert = temporary;
    }
  }
  if (!to_insert->getPlayers().empty())
  {
    for (const auto& player : to_insert->getPlayers())
    {
      free_tile_->movePlayerToTile(player);
      to_insert->removePlayerFromTile(player);
    }
    if (to_insert->getPlayers().empty())
    {
      tiles_containing_players_.erase(to_insert);
    }
    tiles_containing_players_.insert(free_tile_);
  }
  free_tile_ = to_insert;
}

//---------------------------------------------------------------------------------------------------------------------
void Game::insertTileHorizontal(bool left, size_t position)
{
  auto to_insert = free_tile_;
  shared_ptr<Tile> temporary_free_tile;
  position--; // internal representation starts at 0
  if (left)
  {
    temporary_free_tile = gameboard_.at(position).at(6); // rightmost is now temporary_free_tile
    gameboard_.at(position).pop_back();
    vector<shared_ptr<Tile>> temporary = {to_insert};
    for (const auto& element : gameboard_.at(position))
    {
      temporary.push_back(element);
    }
    gameboard_.at(position) = temporary;
  }
  else
  {
    temporary_free_tile = gameboard_.at(position).at(0); // leftmost is now temporary_free_tile
    vector<shared_ptr<Tile>> temporary = gameboard_.at(position);
    temporary.erase(temporary.begin());
    temporary.push_back(to_insert);
    gameboard_.at(position) = temporary;
  }
  if (!temporary_free_tile->getPlayers().empty())
  {
    for (const auto& player : temporary_free_tile->getPlayers())
    {
      free_tile_->movePlayerToTile(player);
      temporary_free_tile->removePlayerFromTile(player);
    }
    if (temporary_free_tile->getPlayers().empty())
    {
      tiles_containing_players_.erase(temporary_free_tile);
    }
    tiles_containing_players_.insert(free_tile_);
  }
  free_tile_ = temporary_free_tile;
}

//---------------------------------------------------------------------------------------------------------------------
string Game::finishMove(const shared_ptr<Player>& current_player)
{
  // get Treasure if stack not empty
  if (!current_player->getStack().empty())
  {
    auto players_current_treasure = current_player->getStack().top();
    // get Tile of player
    for (const auto& tile : tiles_containing_players_) // check for treasures
    {
      for (const auto& player : tile->getPlayers())
      {
        // Tiles with TileType 0/T are T-Treasure Tiles // static_cast<TileType>(0))
        if (player->getColor() == current_player->getColor() && tile->getType() == TileType::T)
        {
          auto treasure_tile = std::dynamic_pointer_cast<TreasureTile>(tile); // only if treasure
          auto treasure_on_tile = treasure_tile->getTreasure();
          if (players_current_treasure == treasure_on_tile)
          {
            treasure_tile->collectTreasure(true); // also sets the treasure to found
            current_player->getStack().pop();
            current_player->found();
            if (current_player->getNumberFoundTreasures() == (TREASURE_TOTAL / playercount_))
            {
              current_player->setDone(true);
              break;
            }
          }
        }
      }
    }
  }
  // check if player is on starting field and done
  if (current_player->getDone())
  {
    for (const auto& tile : tiles_containing_players_)
    {
      for (const auto& player_on_tile : tile->getPlayers())
      {
        if (player_on_tile->getColor() == current_player->getColor())
        {
          auto potential_start_tile = std::dynamic_pointer_cast<StartTile>(tile);
          if (potential_start_tile == nullptr)
          {
            return "";
          }
          else if (potential_start_tile->getPlayerColor() == current_player->getColor())
          {
            switch (current_player->getColor())
            {
              case 'R':
                return "RED";
              case 'Y':
                return "YELLOW";
              case 'G':
                return "GREEN";
              case 'B':
                return "BLUE";
            }
          }
        }
      }
    }
  }
  return "";
}

//---------------------------------------------------------------------------------------------------------------------
void Game::populateTiles(vector<shared_ptr<Tile>>& movable_tiles, vector<shared_ptr<Treasure>>& static_treasures)
{
  vector<vector<int>> fix_points{{1, 3}, {0, 0}, {0, 0}, {1, 2}, {0, 1}, {0, 1}, {0, 0}, {0, 3},
                                 {0, 1}, {0, 2}, {0, 3}, {0, 3}, {1, 0}, {0, 2}, {0, 2}, {1, 1}};
  size_t counter = 0;
  size_t player_init_counter = 0;
  size_t static_treasure_counter = 0;
  size_t static_field_counter = 0;
  for (size_t row = 0; row < NUMBER_OF_ROWS; row++)
  {
    vector<shared_ptr<Tile>> row_of_tiles;
    for (size_t column = 0; column < NUMBER_OF_COLUMNS; column++)
    {
      counter++;
      if (row % 2 == 0 && column % 2 == 0)
      {
        // static tiles
        auto data = fix_points.at(static_field_counter++);
        auto rot = static_cast<Rotation>(data.at(1));
        auto type = static_cast<TileType>(data.at(0));
        if ((row == 0 || row == NUMBER_OF_ROWS - 1) && (column == 0 || column == NUMBER_OF_COLUMNS - 1))
        {
          auto tile = make_shared<StartTile>(type, rot, getStartTileColor(row, column));
          if (player_init_counter < this->getPlayerCount())
          {
            tile->movePlayerToTile(
                players_.at(player_init_counter++)); // move the players to there respective start tiles
            tiles_containing_players_.insert(tile);
          }
          row_of_tiles.push_back(tile);
        }
        else
        {
          // otherwise Treasure Tile
          auto tile = make_shared<TreasureTile>(type, rot);
          auto treasure = static_treasures.at(static_treasure_counter);
          tile->setTreasure(treasure);
          static_treasure_counter++;
          row_of_tiles.push_back(tile);
        }
      }
      else
      {
        // dynamic tiles
        auto index = Oop::Random::getInstance().getRandomCard(movable_tiles.size());
        auto tile = movable_tiles.at(index - 1); // get Random Tile
        tile->setRotation(static_cast<Rotation>(Oop::Random::getInstance().getRandomOrientation()));
        row_of_tiles.push_back(tile);
        movable_tiles.erase(movable_tiles.begin() + index - 1);
      }
    }
    gameboard_.push_back(row_of_tiles);
  }
  //    assignment of the free tile
  free_tile_ = movable_tiles.back();
  movable_tiles.pop_back();
}
