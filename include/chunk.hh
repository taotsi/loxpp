#ifndef CHUNK_HH
#define CHUNK_HH

#include <vector>
#include <array>
#include "value.hh"
#include "common.hh"

enum class OpCode : uint8_t
{
  OP_UNKNOWN,
  OP_RETURN,
  OP_CONSTANT
};

class ConstantAddress;

class Chunk
{
public:
  Chunk(){};
  Chunk(const Chunk&) = default;
  Chunk(Chunk&&) = default;
  Chunk& operator=(const Chunk&) = default;
  Chunk& operator=(Chunk&&) = default;
  ~Chunk() = default;

  void Write(OpCode byte);
  void Write(ConstantAddress address);
  ConstantAddress AddConstant(Value value);
  OpCode operator[](size_t i) const;
  inline size_t size() const {return code_.size();}
  Value constant(size_t i) const {return constants_[i];}

  static constexpr int LEN_SIZE_T = sizeof(size_t)/sizeof(uint8_t);

private:
  std::vector<OpCode> code_;
  std::vector<Value> constants_;
};

class ConstantAddress
{
public:
  ConstantAddress(size_t address)
  {
    for (size_t idx = 0; idx < Chunk::LEN_SIZE_T; idx++)
    {
      address_[idx] = static_cast<uint8_t>(address >> 8*(7-idx) & 0xFF);
    }
  }
  uint8_t operator[](size_t idx) const
  {
    // if(idx < Chunk::LEN_SIZE_T && idx >= 0){
      return address_[idx];
    // }
    // std::cout << "address index out of range!\n";
    // return 256; // magic code
  }
private:
  std::array<uint8_t, Chunk::LEN_SIZE_T> address_;
};

#endif // CHUNK_HH