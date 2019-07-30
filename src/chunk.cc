#include <stdio.h>
#include "chunk.hh"

void Chunk::Write(const OpCode &byte){
  code.push_back(byte);
}
void Chunk::Write(OpCode &&byte){
  code.push_back(std::move(byte));
}

OpCode Chunk::operator[](size_t i) const {
  if(i < code.size()){
    return code[i];
  }
  return OpCode::OP_UNKNOWN;
}