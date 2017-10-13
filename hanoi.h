#include <vector>
#include <stack>
#include <unordered_map>

#ifndef _HANOI_H
#define _HANOI_H

class Hanoi
{
 public:
  Hanoi(const unsigned int &);
  void play();

 private:
  std::vector <std::stack<int>> stacks; // the 3 stacks
  std::unordered_map <int, int> moves; // maps disks to their last position before current one
  int lrud; // least recently used disk

  unsigned int moveCounter; // tracks the number of moves
  unsigned int disksWidth; // used to format output

  void rHanoi(); // main, recursive function. Called by play
  std::stack<int> & getFrom(); // rHanoi helper
  std::stack<int> & getTo(std::stack<int> &); //rHanoi helper
  void move(std::stack<int> &, std::stack<int> &); // called by rHanoi
  void printStacks(); // called by move to output process
};

#endif
