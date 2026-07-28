#include "ConsoleLoggerMiddleware.hpp"
#include <iostream>

void ConsoleLoggerMiddleware::log(const Log& log)
{
  std::cout << log.message << '\n';
}
