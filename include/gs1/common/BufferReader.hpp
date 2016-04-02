#ifndef GS1COMMON_BUFFERREADER_HPP
#define GS1COMMON_BUFFERREADER_HPP

#include <string>

namespace gs1
{
class BufferReader
{
public:
  BufferReader(const char *data, uint32_t len)
      : data(data), len(len), readPos(0){};

  template <typename T> bool Read(T &value) { return _Read(value); };

  template <typename T> bool ReadAsBytes(T *value)
  {
    if (readPos + sizeof(T) > len)
      return false;

    value = (T *)&data[readPos];

    readPos += sizeof(T);

    return true;
  };

  bool Skip(uint32_t size)
  {
    if (readPos + size > len)
      return false;

    readPos += size;

    return true;
  };

  void Seek(uint32_t pos) { readPos = pos; };

private:
  const char *data;

  template <typename T> bool _Read(T &value)
  {
    if (readPos + sizeof(T) > len)
      return false;

    value = *reinterpret_cast<const T *>(&data[readPos]);

    readPos += sizeof(T);

    return true;
  };

  bool _Read(std::string &value)
  {
    uint32_t length;
    if (!Read(length))
      return false;

    char next;
    for (uint32_t i = 0; i < length; i++) {
      if (!Read(next))
        return false;

      value += next;
    }

    return true;
  };

  uint32_t len;
  uint32_t readPos;
};
}

#endif