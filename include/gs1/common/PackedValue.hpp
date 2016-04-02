#ifndef GS1COMMON_PACKEDVALUE_HPP
#define GS1COMMON_PACKEDVALUE_HPP

namespace gs1
{
enum PackedValueType {
  PACKVALUE_CONST_NUMBER,
  PACKVALUE_CONST_STRING,
  PACKVALUE_CONST_ARRAY,
  PACKVALUE_NAMED
};

// FIXME: Don't rely on bitpacking..
struct PackedValue {
  PackedValue(PackedValueType valueType, unsigned int index = 0)
      : valueType(valueType), value(index){};

  // The type of value, see enum PackedValueType
  unsigned int valueType : 4;
  unsigned int value : 16;
  unsigned int unused : 12;
} __attribute__((packed));

// FIXME: Deserialize properly. For the sake of testing/iterating quickly, do it
// lazy.

// FIXME: Could use this + endianness to detect when the target platform needs a
// slow/safe deserialize option.
static_assert(
    sizeof(PackedValue) == 4,
    "Size of PackedValue isn't 4 bytes, can cause problems when deserializing");
};

#endif