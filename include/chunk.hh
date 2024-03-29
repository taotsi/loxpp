#ifndef CHUNK_HH
#define CHUNK_HH

#include <vector>
#include <array>
#include "value.hh"
#include "common.hh"
#include "utility.hh"

namespace loxpp{

// TODO: maybe I should reserve some digits for OpCode and leave others for addresses, by using a union
enum class OpCode : uint8_t
{
  OP_RESERVED,
  OP_UNKNOWN,
  OP_RETURN,
  OP_CONSTANT,
  OP_NEGATE,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE
};

class ConstantAddress;
class LineNumber;

class Chunk
{
public:
  Chunk();
  DEFAULT_SPECIAL_FUNCTIONS(Chunk);

  void write(OpCode byte, size_t line_num);
  // TODO: combine Write(address) and AddConstant()
  void write(ConstantAddress address, size_t line_num);
  ConstantAddress add_constant(Value value);
  OpCode operator[](size_t i) const;
  inline OpCode at(size_t i) const {return (*this)[i];}
  inline size_t size() const {return code_.size();}
  Value constant(size_t i) const {return constants_[i];}
  LineNumber get_line_num(size_t offset) const;
  inline std::vector<LineNumber> line_numbers() const {return line_numbers_;}

  static constexpr int LEN_SIZE_T = sizeof(size_t)/sizeof(uint8_t);

private:
  std::vector<OpCode> code_;
  std::vector<Value> constants_;
  std::vector<LineNumber> line_numbers_;
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
    // if(idx < Chunk::LEN_SIZE_T){
      return address_[idx];
    // }
    // std::cout << "address index out of range!\n";
    // return 256; // magic code
  }
private:
  std::array<uint8_t, Chunk::LEN_SIZE_T> address_;
};

class LineNumber
{
public:
  LineNumber(size_t line_number, size_t len_continuous, size_t len_accumulated)
    : line_number_{line_number},
      len_continuous_{len_continuous},
      len_accumlated_{len_accumulated}
  {}
  inline size_t line_number() const {return line_number_;};
  inline size_t len_continuous() const {return len_continuous_;}
  inline size_t len_accumulated() const {return len_accumlated_;}
  inline void len_advance(size_t offset)
  {
    len_continuous_ += offset;
    len_accumlated_ += offset;
  }
private:
  size_t line_number_ = 0;
  size_t len_continuous_ = 1;
  size_t len_accumlated_ = 1;
};

}

#endif // CHUNK_HH