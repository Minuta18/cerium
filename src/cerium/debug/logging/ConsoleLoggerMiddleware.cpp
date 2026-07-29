#include "ConsoleLoggerMiddleware.hpp"
#include <iostream>

void ConsoleLoggerMiddleware::log(const Log& log)
{
  std::cout << '[' << log.time << ']' << '\t' << '[' << logLevelToString(log.level) << ']' << '\t'
            << '[' << log.name << ']' << '\t' << log.message << '\n';
}
