#include "AI.hpp"

#include <utility>

AI::AI(Game& game, shared_ptr<Player> current_player) : game_{game}, player_{std::move(current_player)}
{
  starttime_ = std::chrono::steady_clock::now();
  fall_back_pos = (game_.getFordbiddenPosition() + 2 > 7) ? 2 : game.getFordbiddenPosition() + 2;
  fall_back_side = insert_sides.at((rand() % 4));
  string out = "insert ";
  out.push_back(fall_back_side);
  out += " " + to_string(fall_back_pos);
  commands.push_back(out);
  commands.emplace_back("go 0 0");
  commands.emplace_back("finish");
  success_flag = false;
  // see if player has treasure and is not done otherwise set goal to start field
  if (!player_->getStack().empty())
  {
    auto player_treasure = player_->getStack().top();
    auto done = false;
    auto free_tile = game_.getFreeTile();
    if (free_tile->getType() == TileType::T)
    {
      auto treasure_tile = std::dynamic_pointer_cast<TreasureTile>(free_tile);
      auto treasure_on_tile = treasure_tile->getTreasure();
      if (player_treasure == treasure_on_tile)
      {
        goal_tile = free_tile;
        done = true;
      }
    }

    for (const auto& row : game_.getgameboard())
    {
      if (done)
      {
        break;
      }
      for (const auto& tile : row)
      {
        if (tile->getType() == TileType::T) // only T tiles are Treasure tiles
        {
          auto treasure_tile = std::dynamic_pointer_cast<TreasureTile>(tile);
          auto treasure_on_tile = treasure_tile->getTreasure();
          if (player_treasure == treasure_on_tile)
          {
            // correct tile
            //            cout << player_treasure->getName() << treasure_on_tile->getName() << "&&&&&&&&&" << endl;
            goal_tile = tile;
            done = true;
            break;
            // goal_row = coords.row_;
            // goal_col = coords.column_;
          }
        }
      }
    }
  }
  else
  {
    for (const auto& row : game_.getgameboard())
    {
      for (const auto& tile : row)
      {
        try
        {
          auto starttile = std::dynamic_pointer_cast<StartTile>(tile);
          if (starttile == nullptr)
          {
            continue;
          }
          else if (starttile->getPlayerColor() == player_->getColor())
          {
            goal_tile = tile;
          }
        }
        catch (const std::exception& e)
        {
          continue;
        }
      }
    }
  }
  // set goal to treasure of player
};

long AI::getLifeTime()
{
  auto now = std::chrono::steady_clock::now();
  long dur = std::chrono::duration_cast<std::chrono::milliseconds>(now - starttime_).count();
  return dur;
}

void AI::printInfo()
{
  bool finish_check = false;
  for (const auto& command : commands)
  {
    cout << INFO_PRINTOUT << command << endl;
    if (command == "finish")
    {
      finish_check = true;
    }
  }
  if (!finish_check)
  {
    cout << INFO_PRINTOUT << "finish" << endl;
  }
}

void AI::onlyGo()
{
  commands = {"", "finish"};
  try
  {
    Coordinates goal_coords = game_.getCoordsOf(goal_tile);
    goal_row = goal_coords.row_;
    goal_col = goal_coords.column_;
    game_.goTo(player_, goal_row, goal_col, false);
    string go_command = "go " + to_string(goal_row + 1) + " " + to_string(goal_col + 1);
    commands.at(0) = go_command;
    success_flag = true;
    only_go_flag = true;
  }
  catch (ImpossibleMove& e)
  {
    commands = {"finish"};
    return;
  }
}

void AI::run()
{
  std::shared_ptr<Tile> bestTile = goal_tile;

  for (auto side : insert_sides)
  {
    for (size_t position = 2; position < 7; position = position + 2)
    {
      if (position != game_.getFordbiddenPosition() || side != game_.getForbiddenSide())
      {
        // verschieben
        game_.pseudoinsertTile(side, position);
        // probing phase
        try
        {
          if (goal_tile == game_.getFreeTile())
          {
            //! zurückschieben nicht vergessen!!!! falls move impossible
            side = game_.opposite_sides_[side];
            game_.pseudoinsertTile(side, position);
            continue; // pathfinding wenn free tile rausgeschoben sinnlos.
          }
          Coordinates goal_coords = game_.getCoordsOf(goal_tile);
          goal_row = goal_coords.row_;
          goal_col = goal_coords.column_;
          game_.goTo(player_, goal_row, goal_col, false);
          // if move succeded:
          success_flag = true;
          string insert_command = "insert ";
          insert_command.push_back(side);
          insert_command += " " + to_string(position);
          string go_command = "go " + to_string(goal_row + 1) + " " + to_string(goal_col + 1);
          commands.at(1) = go_command;
          commands.at(0) = insert_command;
          // set right forbidden move
          game_.setForbiddenMove(game_.opposite_sides_[side], position);
          //! zurückschieben nicht vergessen!!!! falls move impossible
          side = game_.opposite_sides_[side];
          game_.pseudoinsertTile(side, position);
          return;
        }
        catch (ImpossibleMove& e)
        {
          //! zurückschieben nicht vergessen!!!! falls move impossible
          side = game_.opposite_sides_[side];
          game_.pseudoinsertTile(side, position);
        }
      }
    }
    // set fallback
    if (!success_flag)
    {
      //! Todo !!!! maybe go closer to finish field
      // find best go:
      string go_command = "";
      for (auto side : insert_sides)
      {
        for (size_t position = 2; position < 7; position = position + 2)
        {
          if (position != game_.getFordbiddenPosition() || side != game_.getForbiddenSide())
          {
            // verschieben
            game_.pseudoinsertTile(side, position);
            for (long row = 0; row < 7; row++)
            {
              for (long col = 0; col < 7; col++)
              {
                try
                {
                  game_.goTo(player_, row, col, false);
                  if (getDistancetogoal(row, col) < best_distance && getDistancetogoal(row, col) > 1)
                  {
                    go_command = "";
                    best_distance = getDistancetogoal(row, col);
                    go_command += "go " + to_string(row + 1) + " " + to_string(col + 1);
                    fall_back_side = side;
                    fall_back_pos = position;
                  }
                }
                catch (ImpossibleMove& e)
                {
                  continue;
                }
              }
            }
            //! zurückschieben nicht vergessen!!!! falls move impossible
            side = game_.opposite_sides_[side];
            game_.pseudoinsertTile(side, position);
          }
        }
      }
      string insert_command = "insert ";
      insert_command.push_back(fall_back_side);
      insert_command += " " + to_string(fall_back_pos);
      commands = {"", "finish"}; // no go!
      commands.at(0) = insert_command;
      if (go_command != "")
      {
        success_flag = true;
        commands = {"", "", "finish"}; // no go!
        commands.at(0) = insert_command;
        commands.at(1) = go_command;
        commands.at(2) = "finish";
      }
      game_.setForbiddenMove(game_.opposite_sides_[fall_back_side], fall_back_pos);
    }
    // try every insert and chose best one then go to goal naiv
    // game_.pseudoinsertTile();
  }
}
size_t AI::getDistancetogoal(long row, long col)
{
  return std::abs((row - goal_row)) + std::abs((col - goal_col));
}
