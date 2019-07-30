#ifndef CHUNK_HH
#define CHUNK_HH

#include <vector>
#include "value.hh"
#include "common.hh"

enum class OpCode : size_t{
  OP_UNKNOWN,
  OP_RETURN,
  OP_CONSTANT
};

class Chunk{
public:
  Chunk(){};
  Chunk(const Chunk&) = default;
  Chunk(Chunk&&) = default;
  Chunk& operator=(const Chunk&) = default;
  Chunk& operator=(Chunk&&) = default;
  ~Chunk() = default;

  void Write(OpCode byte);
  size_t AddConstant(Value value);
  OpCode operator[](size_t i) const;
  inline size_t size() const {return code_.size();}
  Value constant(size_t i) const {return constants_[i];}

private:
  std::vector<OpCode> code_;
  std::vector<Value> constants_;
};

#endif // CHUNK_HH