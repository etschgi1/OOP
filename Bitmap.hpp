//----------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// Bitmap.hpp
//
// Bitmap class (singelton); This contains all of the tiles graphical string representations in an ordered fashion,
// which allows use to leverage the structures order to access the correct repr for each tile with a type and
// a rotation.
//
// Group: 135
//
// Authors: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#ifndef OOP1SS21_A2_135_BITMAP_HPP
#define OOP1SS21_A2_135_BITMAP_HPP

#include <string>
#include <vector>

using std::string;
using std::vector;

class Bitmap
{
  // Vectors containing all the rotations of a specific tile
  vector<vector<string>> T_;
  vector<vector<string>> L_;
  vector<vector<string>> I_;
  vector<vector<string>> O_;
  vector<vector<string>> U_;
  vector<vector<string>> X_;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Constructor
  ///
  //
  explicit Bitmap();

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Copy-Constructor
  ///
  //
  Bitmap(const Bitmap&) = delete;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Overload assign; Assignment hands over reference
  ///
  //
  void operator=(const Bitmap&) = delete;

public:
  vector<vector<vector<string>>> repr_;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Destructor
  ///
  //
  ~Bitmap() = default;

  //------------------------------------------------------------------------------------------------------------------
  ///
  /// Creates a Bitmap class (singelton)
  ///
  /// @return the only instance of the class
  //
  static Bitmap& instance()
  {
    static Bitmap bitmap;
    return bitmap;
  }
};

#endif // OOP1SS21_A2_135_BITMAP_HPP
