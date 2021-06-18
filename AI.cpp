#include "AI.hpp"

AI::AI(Game& game, shared_ptr<Player> current_player) : game_{game}, player_{current_player}
{
  starttime_ = std::chrono::steady_clock::now();
  fall_back_pos = (game_.getFordbiddenPosition() + 2 > 7) ? 2 : game.getFordbiddenPosition() + 2;
  string out = "insert ";
  out.push_back(fall_back_side);
  out += " " + to_string(fall_back_pos);
  commands.push_back(out);
  commands.push_back("go 0 0");
  commands.push_back("finish");

  // see if player has treasure and is not done otherwise set goal to start field
  if (!player_->getStack().empty())
  {
    auto player_treasure = player_->getStack().top();
    for (auto row : game_.getgameboard())
    {
      for (auto tile : row)
      {
        if (tile->getType() == TileType::T) // only T tiles are Treasure tiles
        {
          auto treasure_tile = std::dynamic_pointer_cast<TreasureTile>(tile);
          auto treasure_on_tile = treasure_tile->getTreasure();
          if (player_treasure == treasure_on_tile)
          {
            // correct tile
            goal_tile = tile;
            // goal_row = coords.row_;
            // goal_col = coords.column_;
          }
        }
      }
    }
  }
  else
  {
    for (auto row : game_.getgameboard())
    {
      for (auto tile : row)
      {
        try
        {
          auto starttile = std::dynamic_pointer_cast<StartTile>(tile);
          if (starttile->getPlayerColor() == player_->getColor())
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
  for (auto command : commands)
  {
    cout << INFO_PRINTOUT << command << endl;
  }
}
void AI::executeCommands()
{

  return;
}
void AI::setBestInsert(char side, size_t position) {}

void AI::run()
{
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
        catch (ImpossibleMove)
        {
          //! zurückschieben nicht vergessen!!!! falls move impossible
          side = game_.opposite_sides_[side];
          game_.pseudoinsertTile(side, position);
        }
      }
    }
  }
  if (!success_flag)
  {
    string insert_command = "insert ";
    insert_command.push_back(fall_back_side);
    insert_command += " " + to_string(fall_back_pos);
    insert_side = fall_back_side;
    insert_position = fall_back_pos;
    commands = {"", "finish"}; // no go!
    commands.at(0) = insert_command;
    game_.setForbiddenMove(game_.opposite_sides_[fall_back_side], fall_back_pos);
    //! Todo !!!! maybe go closer to finish field
  }
  // try every insert and chose best one then go to goal naiv
  // game_.pseudoinsertTile();
}