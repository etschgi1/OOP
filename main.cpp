//----------------------------------------------------------------------------------------------------------------------
// Assignment 2 - OOP1 SS2021
// main.cpp
//
// Main functions; creates game instance and calls Game member functions (Gameloop)
//
// Group: 135
//
// Author: Maximilian Philipp 11839611, Elias Wachmann 12004232, Marko Gugleta 12016483
//----------------------------------------------------------------------------------------------------------------------
//

#include "main.hpp"

//---------------------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  try
  {
    const string bonus_flag = "-bonus";
    if (argc == 2 && bonus_flag == argv[1])
    {
      cout << "42" << endl; //:)
    }
    if (argc != 1)
    {
      cout << "Wrong arguments!" << endl;
      return WRONG_ARGUMENTS;
    }
    int number_of_players = start_game();
    if (!number_of_players) // Check if EOF happened
    {
      return REGULAR_ENDING;
    }
    Game& game = Game::getInstance(number_of_players);
    auto loop = IOLoop{game};
    loop.runGame();
    return REGULAR_ENDING;
  }
  catch (const bad_alloc& e)
  {
    return BAD_MEMORY_ALLOCATION;
  }
}

//---------------------------------------------------------------------------------------------------------------------
int start_game()
{
  int number_of_players = 0;
  cout << "Welcome to the Wild OOP Labyrinth!!!" << endl;
  while (true)
  {
    string input;
    cout << "Player Count (2-4): ";
    getline(cin, input);
    // trim string
    input = trim(input);
    if (cin.eof())
    {
      return 0; // EOF End Game
    }
    else if (input.size() == 1 && isdigit(input[0])) // invalid string length, to catch overflows + checks if integer
    {
      number_of_players = stoi(input);
      if (number_of_players >= 2 && number_of_players <= 4)
      {
        break;
      }
    }
    cout << "Wrong Input only a Number from 2 to 4 is allowed!" << endl;
  }
  return number_of_players;
}

// https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
// begin
string ltrim(const string& s)
{
  return regex_replace(s, regex("^\\s+"), string(""));
}

string rtrim(const string& s)
{
  return regex_replace(s, regex("\\s+$"), string(""));
}

string trim(const string& s)
{
  return ltrim(rtrim(s));
}
// end