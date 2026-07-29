#include "Clock.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string Clock::getFormattedCurrentTime()
{
  auto now = std::chrono::system_clock::now();
  std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

  std::tm localTime;

#ifdef _WIN32
  localtime_s(&localTime, &currentTime);
#else
  localtime_r(&currentTime, &localTime);
#endif

  std::ostringstream stream;
  stream << std::put_time(&localTime, "%H:%M:%S");

  return stream.str();
}
