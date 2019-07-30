#ifndef CHUNK_HH
#define CHUNK_HH

#include <vector>
#include "common.hh"

enum class OpCode : uint8_t{
  OP_UNKNOWN,
  OP_RETURN,
};

class Chunk{
public:
  Chunk(){};
  Chunk(const Chunk&) = default;
  Chunk(Chunk&&) = default;
  Chunk& operator=(const Chunk&) = default;
  Chunk& operator=(Chunk&&) = default;
  ~Chunk() = default;

  void Write(OpCode &&byte);
  void Write(const OpCode &byte);
  OpCode operator[](size_t i) const;
  inline size_t size() const {return code.size();}

private:
  std::vector<OpCode> code;
};

#endif // CHUNK_HH