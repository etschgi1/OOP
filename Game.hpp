//----------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// Game.hpp
//
// Game class (singleton); Main Class which manages the gameboard, players and treasures, includes member functions
// to alter the state of the board.
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#ifndef OOP1SS21_A2_135_GAME
#define OOP1SS21_A2_135_GAME

#include <memory>
#include <stack>
#include <unordered_set>

// Include all Game objects
#include "Errors.hpp"
#include "NormalTile.hpp"
#include "Player.hpp"
#include "Random.hpp"
#include "StartTile.hpp"
#include "Tile.hpp"
#include "Treasure.hpp"
#include "TreasureTile.hpp"

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::string;
using std::unordered_set;
using std::vector;

struct ForbiddenMove
{
  char side = 'b'; // set arbitrary (not valid) value for side and position
  size_t position = 10;
};

//----------------------------------------------------------------------------------------------------------------------
class Game
{
private:
  vector<string> cards_{"01Totenkopf",   "02Schwert",       "03Goldsack", "04Schlüsselbund", "05Sombrero",
                        "06Ritterhelm",  "07Buch",          "08Krone",    "09Schatztruhe",   "10Kerzenleuchte",
                        "11Schatzkarte", "12Goldring",      "13Eule",     "14Hofnarr",       "15Eidechse",
                        "16Käfer",       "17Flaschengeist", "18Kobold",   "19Schlange",      "20Geist",
                        "21Fledermaus",  "22Spinne",        "23Ratte",    "24Motte"};
  vector<shared_ptr<Player>> players_;
  vector<char> player_colors_{'R', 'Y', 'G', 'B'};
  vector<vector<shared_ptr<Tile>>> gameboard_;
  vector<vector<int>> start_tiles_ = {{0, 0}, {0, 6}, {6, 0}, {6, 6}};
  unordered_set<shared_ptr<Tile>> tiles_containing_players_;
  ForbiddenMove forbidden_move_;
  shared_ptr<Tile> free_tile_;
  int playercount_;

  //<<<<<Constants>>>>>
  const size_t NUMBER_OF_STATIC_TREASURES = 12;
  static const size_t LINE_HEIGHT_OF_TILE = 5;
  static const size_t MIDDLE_LINE_OF_TILE = 2;
  const int TREASURE_TOTAL = 24;
  const int DOUBLE_DIGIT = 10;
  const int MOVE_DIRECTION_UP = 3;
  const int MOVE_DIRECTION_DOWN = 1;
  const int MOVE_DIRECTION_LEFT = 2;
  const int MOVE_DIRECTION_RIGHT = 0;
  const size_t NUMBER_OF_ROWS = 7;
  const size_t NUMBER_OF_COLUMNS = 7;
  const char SPACE_KEY = '\x20';
  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor
  ///
  /// @param playercount number of players playing the game
  ///
  //
  explicit Game(int playercount);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Copy-Constructor
  ///
  //
  Game(const Game&);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Overload assign; Assignment hands over reference
  ///
  //
  Game& operator=(const Game&);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Getter for playercount
  ///
  //
  [[nodiscard]] size_t getPlayerCount() const { return playercount_; }

public:
  unsigned long getFordbiddenPosition() { return forbidden_move_.position; }
  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor
  ///
  //
  ~Game() = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Creates a Game class (singelton)
  ///
  /// @param playercount number of players playing the game
  ///
  /// @return the only instance of the class
  //
  static Game& getInstance(int playercount)
  {
    static Game game_instance(playercount);
    return game_instance;
  }

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Prints a row of the vector of Tile with the appropriate formatting
  ///
  /// @param row is the vector containing pointers to the Tiles being printed
  /// @param row_number is the current row number is needed for correct formatting
  ///
  /// @return nothing
  //
  static void printRow(const vector<shared_ptr<Tile>>& row, int row_number);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Prints the current state of the game that means all Tiles and all player stats
  ///
  /// @return nothing
  //
  void printMap();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Gets the correct StartTileColor for specific pair of coordinates
  ///
  /// @param x is the x-coordinate of in the internal vector
  /// @param y is the y-coordinate of in the internal vector
  ///
  /// @return color char or X if not start Tile
  //
  [[nodiscard]] char getStartTileColor(int x, int y) const;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Moves player designated amount in a direction
  ///
  /// @param player is a shared_ptr to a Player
  /// @param direction the direction in which the player should move
  /// @param steps how many tiles the player should move in the given direction
  ///
  //
  void movePlayer(const shared_ptr<Player>& player, int direction, int steps);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Check if a move is possible in a certain direction starting from a certain point. (IMPROVED)
  ///
  /// @param rowcol the current position as a int[2] array including row and col number
  /// @param direction the direction in which the player should move
  /// @param steps how many tiles the player should move in the given direction
  ///
  /// @return true if the move is valid otherwise false
  //
  bool checkMoveIsValid(int* rowcol, int direction, int steps);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns a vector including all participating players
  ///
  /// @return player vector
  //
  vector<shared_ptr<Player>> getPlayers();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Gets the Vector of Strings representing the Free Tile
  ///
  /// @return a vector of strings for the Free Tile
  //
  vector<string> getFreeTileString();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Rotates the free tile right
  ///
  /// @param clockwise rotates clockwise if true otherwise counterclockwise
  ///
  /// @return no return
  //
  void rotateFreeTile(bool clockwise);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Inserts the Free Tile at a given position and moves the Tiles in gameboard_ accordingly
  /// Potentially throws Currently_not_allowed_Command, Invalid_Command or Invalid_Parameter Exceptions
  ///
  /// @param tokens the full input tokens of the user with whitespace trimmed for exceptions
  /// @param side side where the tile should be inserted (t,b,r,l)
  /// @param position row / column number valid numbers are (2,4,6)
  ///
  /// @return no return
  //
  void insertTile(vector<string> tokens, char side, size_t position);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Helper for insertTile. Inserts Tiles horizontally either from the top or from the bottom
  ///
  /// @param top if true top insert otherwise bottom insert
  /// @param position row / column number valid numbers are (2,4,6)
  ///
  /// @return no return
  //
  void insertTileVertical(bool top, size_t position);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Helper for insertTile. Inserts Tiles vertically either from the left or from the right
  ///
  /// @param left if true left insert otherwise right insert
  /// @param position row / column number valid numbers are (2,4,6)
  ///
  /// @return no return
  //
  void insertTileHorizontal(bool left, size_t position);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Ends a turn of a player, collects the treasure if it's the right one
  /// Also checks if the player has won the game
  ///
  /// @return String of the winning player otherwise empty string ""
  //
  string finishMove(const shared_ptr<Player>& current_player);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// This function is only used for the construction of the singleton.
  /// Populates the tiles into the internal gameboard_ 2d vector of tiles and also initialises the vector
  /// tiles_containing_players_ with the StarTiles and the corresponding players.
  ///
  /// @param movable_tiles is a vector containing the tiles which are not stationary
  /// @param static_treasures is a vector containing the static treasures
  ///
  //
  void populateTiles(vector<shared_ptr<Tile>>& movable_tiles, vector<shared_ptr<Treasure>>& static_treasures);
};

#endif // OOP1SS21_A2_135_Game