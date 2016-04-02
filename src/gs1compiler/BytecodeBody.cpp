#include <gs1/common/Operation.hpp>
#include <gs1/common/PackedValue.hpp>
#include <gs1/compiler/BytecodeBody.hpp>

#include <stdio.h>

using namespace gs1;

BytecodeBody::BytecodeBody(){};

BytecodeBody::~BytecodeBody(){};

void BytecodeBody::Emit(Opcode op)
{
  printf("%5d EMIT OPER: %s\n", byteBuffer.GetLength(),
         OpcodeToString(op).c_str());

  byteBuffer.WriteU8(op);
}

void BytecodeBody::Emit(int constant)
{
  printf("%5d EMIT CNST: %d\n", byteBuffer.GetLength(), constant);

  byteBuffer.Write32(constant);
}

void BytecodeBody::Emit(unsigned int constant)
{
  printf("%5d EMIT CNST %d\n", byteBuffer.GetLength(), constant);

  byteBuffer.WriteU32(constant);
}

void BytecodeBody::Emit(const PackedValue &value)
{
  std::string typeString;

  switch (value.valueType) {
  case PACKVALUE_CONST_NUMBER:
    typeString = "PACKVALUE_CONST_NUMBER";
    break;

  case PACKVALUE_CONST_STRING:
    typeString = "PACKVALUE_CONST_STRING";
    break;

  case PACKVALUE_CONST_ARRAY:
    typeString = "PACKVALUE_CONST_ARRAY";
    break;

  case PACKVALUE_NAMED:
    typeString = "PACKVALUE_NAMED";
    break;
  }

  printf("%5d EMIT %s : %d\n", byteBuffer.GetLength(), typeString.c_str(),
         value.value);

  byteBuffer.WriteBytes((char *)&value, sizeof(PackedValue));
}

unsigned int BytecodeBody::GetCurrentPosition()
{
  return byteBuffer.GetLength();
}

Reservation BytecodeBody::Reserve(unsigned int numBytes)
{
  printf("%5d EMIT RESERVED %d\n", byteBuffer.GetLength(), numBytes);
  return Reservation(&byteBuffer, byteBuffer.Reserve(numBytes));
}

ByteBuffer BytecodeBody::GetByteBuffer() { return byteBuffer; }