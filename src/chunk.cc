#include <stdio.h>
#include "chunk.hh"

template<typename CodeType>
void Chunk<CodeType>::Write(CodeType &&byte){
  code.push_back(std::forward<CodeType>(byte));
}

template void Chunk<OpCode>::Write(OpCode&&);

template<typename CodeType>
CodeType Chunk<CodeType>::operator[](size_t i){
  if(i < code.size()){
    return code[i];
  }
  return OpCode::OP_UNKNOWN;
}