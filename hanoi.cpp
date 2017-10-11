#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cstdlib> /* exit, EXIT_FAILURE */

class Hanoi
{
public:
  Hanoi(const unsigned int &);
  void play();
  
private:
  std::vector <std::stack<int>> stacks; // the 3 stacks
  std::unordered_map <int, int> moves; // maps disks to their last position before current one
  int lrud; // least recently used disk

  void move(std::stack<int> &, std::stack<int> &);
  void printStacks(); // called by move to output process
};


int main()
{
  const unsigned int DISKS = 5;
  Hanoi hanoi(DISKS);
}

Hanoi::Hanoi(const unsigned int & n):
  stacks{3}, // 3 stacks
  moves{n}, // moves is size n
  lrud{-1} // no recently used disk
{
  if(n < 1)
    {
      std::cerr << "Please choose a positive number of disks\n";
      exit(EXIT_FAILURE);
    }

  for(int i = n - 1; i >= 0; i--) // the disks are zero-based
    stacks[0].push(i); // all discs start on the left stack (stacks[0])

  std::cout << "initial position:\n";
  printStacks();
}

void Hanoi::printStacks()
{
  int i = 0;
  for(const auto & stack : stacks)
    {
      std::cout << i++ << " : ";
      for(auto dump = stack; !dump.empty(); dump.pop())
	std::cout << dump.top() << " - ";
      std::cout << '\n';
    }
  std::cout << '\n';
}

void Hanoi::move(std::stack<int> & from, std::stack<int> & to)
{
  int fromPosition;
  for(int i = 0; i < 3; i++)
    if (stacks[i] == from)
      fromPosition = i;

  moves[from.top()] = fromPosition; // remember from last position before moving it to "to" 
  lrud = from.top(); // lrud is the disk being moved "from" to "to"
  to.push(from.top()); // move disk
  from.pop(); // pop it from "from"

  printStacks();
}
