#ifndef CHUNK_HH
#define CHUNK_HH

#include <vector>
#include "common.hh"

enum class OpCode : uint8_t{
  OP_UNKNOWN,
  OP_RETURN,
};

template<typename CodeType>
class Chunk{
public:
  Chunk(){};
  Chunk(const Chunk&) = default;
  Chunk(Chunk&&) = default;
  Chunk& operator=(const Chunk&) = default;
  Chunk& operator=(Chunk&&) = default;
  ~Chunk() = default;

  void Write(CodeType &&byte);
  CodeType operator[](size_t i);

private:
  std::vector<OpCode> code;
};

using Chunk8 = Chunk<OpCode>;

#endif // CHUNK_HH