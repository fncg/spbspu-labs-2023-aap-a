#include <iostream>
#include "deleteFigures.hpp"
#include "creatingFigures.hpp"
#include "stringManipulations.hpp"
#include "inputString.hpp"
#include "outputResults.hpp"
#include "isoscale.hpp"

int main()
{
  using namespace isaychev;
  Shape * figures[1000] = {};
  const char * scaleStr = "SCALE ";
  char * currDesc = nullptr;
  size_t i = 0, figuresCount = 0, figDescMistakeCheck = 0;
  bool eofCheck = false;
  while (i < 1000)
  {
    try
    {
      currDesc = inputString(std::cin);
      if (checkString(currDesc, scaleStr) == 1 || std::cin.eof())
      {
        if (std::cin.eof())
        {
          eofCheck = true;
        }
        break;
      }
      figures[i++] = createFigure(currDesc);
    }
    catch (const std::bad_alloc &)
    {
      deleteFigures(figures, figuresCount);
      delete [] currDesc;
      std::cerr << "can't allocate memory for description of figure or a figure itself\n";
      return 1;
    }
    catch (const std::logic_error &)
    {
      figDescMistakeCheck++;
    }
    if (figures[i - 1] == nullptr)
    {
      i--;
    }
    else
    {
      figuresCount++;
    }
    delete [] currDesc;
  }
  if (figuresCount == 0 && checkString(currDesc, scaleStr) == 1)
  {
    delete [] currDesc;
    std::cerr << "nothing to scale\n";
    return 2;
  }
  else if (eofCheck == 1 && checkString(currDesc, scaleStr) == 0)
  {
    deleteFigures(figures, figuresCount);
    delete [] currDesc;
    std::cerr << "input was finished with eof symbol; scale wasn't inputed\n";
    return 3;
  }
  else
  {
    outputResults(figures, figuresCount);
    std::cout << "\n";
    try
    {
      isoscale(currDesc, figures, figuresCount);
    }
    catch (const std::invalid_argument & e)
    {
      std::cerr << e.what() << "\n";
      delete [] currDesc;
      deleteFigures(figures, figuresCount);
      return 4;
    }
    outputResults(figures, figuresCount);
    std::cout << "\n";
  }
  if (figDescMistakeCheck > 0)
  {
    std::cerr << "There were mistakes in figure descriptions\n";
  }
  deleteFigures(figures, figuresCount);
  delete [] currDesc;
}
