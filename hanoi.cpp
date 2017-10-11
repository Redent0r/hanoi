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

  unsigned int moveCounter;

  void rHanoi(); // main / recursive function. Called by play
  std::stack<int> & getFrom();
  void move(std::stack<int> &, std::stack<int> &); // called by rHanoi
  void printStacks(); // called by move to output process
};


int main()
{
  const unsigned int DISKS = 5;
  Hanoi hanoi(DISKS);
  hanoi.play();
}

Hanoi::Hanoi(const unsigned int & n):
  stacks{3}, // 3 stacks
  moves{n}, // moves is size n
  lrud{-1}, // no recently used disk
  moveCounter{0}
{
  if(n < 1)
    {
      std::cerr << "Please choose a positive number of disks\n";
      exit(EXIT_FAILURE);
    }

  for(int i = n - 1; i >= 0; i--) // the disks are zero-based
    stacks[0].push(i); // all discs start on the left stack (stacks[0])
}

std::stack<int> & Hanoi::getFrom()
{

  /*
  for(auto & stack : stacks)
    {
      if(!stack.empty() && // not empty
	 stack.top() != lrud && // top is not recently used
	 stack.top() <= stacks[0].top() && // top is less than others
	 stack.top() <= stacks[1].top() &&
	 stack.top() <= stacks[2].top())
	return stack;
    }
  */

  for(int i = 0; i < 2; ++ i)
    {
      for(int j = 0; j < 2; ++j)
	{
	  if(i != j && // do not compare with itself
	     !stacks[i].empty() && // and not empty
	     stacks[i].top() != lrud && // and not recently used
	     stacks[i].top() < stacks[j].top()) // and there is space to move it
	    return stacks[i];
	}
    }
  std::cerr << "something went wrong in getFrom()\n";
  exit(EXIT_FAILURE);
}

void Hanoi::rHanoi()
{
  if(stacks[0].empty() && // left stack empty and
     (stacks[1].empty() || // middle or
      stacks[2].empty())) // right
    return; // base case

  std::stack<int> * sFrom, * sTo;

  * sFrom = getFrom();
}

void Hanoi::play()
{
  printStacks();
  rHanoi();
}

void Hanoi::printStacks()
{
  std::cout << "move counter: " << moveCounter++ << '\n';
  int i = 0;
  for(const auto & stack : stacks)
    {
      std::cout << "stack "  << i++ << " : ";
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
