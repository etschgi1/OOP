//----------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// TreasureTile.hpp
//
// Models the Treasures on the gameboard
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#ifndef OOP1SS21_A2_135_TREASURE_H
#define OOP1SS21_A2_135_TREASURE_H
#include <string>
#include <vector>
using std::string;
class Treasure
{
  string name_;
  string treasure_id_;
  bool found_ = false;

public:
  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor
  ///
  /// @param name - the name of the Treasure
  /// @param treasure_id - the unique id of the treasure
  ///
  //
  explicit Treasure(string name, string treasure_id);

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Deleted Copy-Constructor
  ///
  //
  Treasure(Treasure&) = delete;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor
  ///
  //
  ~Treasure() = default;
  ;

  //----------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the name of the Treasure
  ///
  /// @return name of the Treasure
  //
  [[nodiscard]] string getName() const;

  //----------------------------------------------------------------------------------------------------------------------
  ///
  /// Returns the id of the Treasure
  ///
  /// @return id of the Treasure
  //
  [[nodiscard]] string getTreasureId() const;

  //----------------------------------------------------------------------------------------------------------------------
  ///
  /// Return if a Treasure is collected
  ///
  /// @return true if Treasure is already found otherwise false
  //
  [[nodiscard]] bool isFound() const;

  //----------------------------------------------------------------------------------------------------------------------
  ///
  /// Sets Treasure either to be found or not found
  ///
  /// @param found sets the found_ value to the given bool value
  ///
  /// @return no return
  //
  void setFound(bool found);
};

#endif // OOP1SS21_A2_135_TREASURE_H
