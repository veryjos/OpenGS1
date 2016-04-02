#ifndef GS1COMMON_UTIL_HPP
#define GS1COMMON_UTIL_HPP

#include <deque>
#include <exception>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace gs1
{
using std::deque;
using std::string;
using std::vector;
using std::function;
using std::shared_ptr;
using std::unordered_map;

class Exception : public std::exception
{
public:
  Exception(const char *fmt, ...);

  const char *what() const noexcept;

private:
  static const int bufferSize = 1024;
  char message[bufferSize];
};

struct Pos {
  Pos() : offset(-1) {}
  Pos(size_t offset) : offset(offset) {}
  Pos(size_t offset, uint32_t line) : offset((int)offset), line(line) {}

  int offset;
  uint32_t line;
};

struct Range {
  Range() {}
  Range(Pos beg, Pos end) : beg(beg), end(end) {}

  Pos beg;
  Pos end;
};

bool HasPrefix(const std::string &str, const std::string &prefix);
}

#endif
