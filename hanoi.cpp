#include <hanoi.h>
#include <iostream>
#include <cstdlib> // exit, EXIT_FAILURE
#include <algorithm> // std::max
#include <iomanip> // std::setw, std::setfill

Hanoi::Hanoi(const unsigned int & numberOfDisks):
  stacks{3}, // 3 stacks
  moves{numberOfDisks}, // moves is size n
  lrud{-1}, // no recently used disk
  moveCounter{0},
  disksWidth{1}
{
  if(numberOfDisks < 1)
    {
      std::cerr << "Please choose a number of disks greater than or equal to 1\n";
      exit(EXIT_FAILURE);
    }

  for(int i = numberOfDisks - 1; i >= 0; i--) // the disks are zero-based
    {
      stacks[0].push(i); // all discs start on the left stack (stacks[0])
      moves[i] = -1;
    }

  unsigned int numDisks = numberOfDisks - 1; // because disks are zero based
  while(true)
    {
      numDisks /= 10;
      if(numDisks) ++disksWidth;
      else break;
    }
}

std::stack<int> & Hanoi::getFrom()
{ 
  for(int i = 0; i < 3; ++ i)
    for(int j = 0; j < 3; ++j)
      if(i != j && // do not compare with itself
	 !stacks[i].empty() && // and not empty
	 stacks[i].top() != lrud && // and not recently used
	 (stacks[j].empty() ||       // there is an empty stack or
	  (stacks[i].top() < stacks[j].top())
	  )) // 
	return stacks[i];
  
  // control never should get to this point
  std::cerr << "something went wrong in getFrom()\n";
  exit(EXIT_FAILURE);
}

std::stack<int> & Hanoi::getTo(std::stack<int> & sFrom)
{
  // getFrom guarantees there is a viable space to move
  for(int i = 0; i < 3; ++i)
    if(sFrom != stacks[i] && // not move to the same place and
       i != moves[sFrom.top()]&& // not move to the last position and
       (stacks[i].empty() || (sFrom.top() < stacks[i].top()))) // move to a valid or empty stack
      return stacks[i];

  // control never should get to this point
  std::cerr << "something went wrong in getTo()\n";
  exit(EXIT_FAILURE);
}

void Hanoi::rHanoi()
{
  if(stacks[0].empty() && // left stack empty and
     (stacks[1].empty() || // middle or
      stacks[2].empty())) // right
    return; // base case

  std::stack<int> & sFrom = getFrom();
  std::stack<int> & sTo = getTo(sFrom);
  move(sFrom, sTo);
  
  return rHanoi();
}

void Hanoi::play()
{
  std::cout << "\nBegin:\n";
  printStacks();
  move(stacks[0], stacks[2]); // first move
  rHanoi();
}

void Hanoi::printStacks()
{
  std::cout << "move counter: " << moveCounter++ << "\n\n";

  // dummy stacks used for printing
  std::stack<int> s0 (stacks[0]);
  std::stack<int> s1 (stacks[1]);
  std::stack<int> s2 (stacks[2]);

  int s0Size = s0.size();
  int s1Size = s1.size();
  int s2Size = s2.size();
  
  int largest = s0Size;
  largest = std::max(largest, s1Size);
  largest = std::max(largest, s2Size);

  for(int i = largest; i != 0; --i)
    {
      if(((s0Size - i) >= 0) &&  !s0.empty())
	{
	  std::cout << "| " << std::setw(disksWidth)
		    << s0.top() << " |";
	  s0.pop();
	}
      else
	std::cout << std::setfill(' ') << std::setw(disksWidth + 4) << ' ';
      
      if(((s1Size - i) >= 0) && !s1.empty())
	{
	  std::cout << "| " << std::setw(disksWidth)
		    << s1.top() << " |";
	  s1.pop();
	}
      else
	std::cout << std::setfill(' ') << std::setw(disksWidth + 4) << ' ';
	
      if(((s2Size - i) >= 0) && !s2.empty())
	{
	  std::cout << "| " << std::setw(disksWidth)
		    <<s2.top() << " |";
	  s2.pop();
	}

      std::cout << '\n';
    }
  std::cout << std::internal  <<std::setw(disksWidth + 2) << "s1"
	    << std::setw(disksWidth + 4) << "s2"
	    << std::setw(disksWidth + 4) << "s3";
  std::cout << "\n\n";
  
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
