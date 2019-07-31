#include <stdio.h>
#include "common.hh"
#include "chunk.hh"
#include "debug.hh"

int main(int argc, const char **argv){
  Chunk chunk;
  chunk.Write(OpCode::OP_UNKNOWN, 123);
  chunk.Write(OpCode::OP_RETURN, 123);
  chunk.Write(OpCode::OP_UNKNOWN, 123);

  auto address = chunk.AddConstant(3.14);
  chunk.Write(OpCode::OP_CONSTANT, 42);
  chunk.Write(address, 43);

  chunk.Write(OpCode::OP_RETURN, 50);

  Debuger debug;
  debug.Disassemble(chunk, "test");

  // auto ln = chunk.line_numbers();
  // for(auto &it : ln)
  // {
  //   std::cout << it.line_number() << "\t" << it.len_continuous() << "\t" << it.len_accumulated() << "\n";
  // }

  printf("~ done ~\n");
  return 0;
}