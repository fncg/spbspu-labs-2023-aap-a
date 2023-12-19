#include "input_output_string.hpp"
#include <iostream>
#include <stdexcept>

char* erohin::inputString(std::istream & input, char* str, const size_t iter_size)
{
  size_t size = iter_size;
  char elem = 0;
  size_t i = 0;
  input >> std::noskipws;
  while (input >> elem)
  {
    if (size == i)
    {
      str = resize(str, size, iter_size);
      size += iter_size;
    }
    str[i++] = elem;
    if (elem == '\n')
    {
      str[i - 1] = '\0';
      break;
    }
    if (!input)
    {
      throw std::logic_error("Wrong string input\n");
    }
  }
  input >> std::skipws;
  return str;
}

void erohin::outputString(std::ostream& output, char* str)
{
  size_t i = 0;
  while (str[i] != '\0')
  {
    output << str[i++];
  }
}
