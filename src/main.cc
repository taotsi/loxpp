#include <stdio.h>
#include "common.hh"
#include "chunk.hh"
#include "debuger.hh"
#include "utility.hh"
#include "vm.hh"

using namespace loxpp;

int main(int argc, const char **argv){
  VM vm;
  auto chunk = std::make_shared<Chunk>();
  // chunk->Write(OpCode::OP_UNKNOWN, 1);

  auto address = chunk->AddConstant(3.14);
  chunk->Write(OpCode::OP_CONSTANT, 2);
  chunk->Write(address, 3);
  chunk->Write(OpCode::OP_NEGATE, 5);

  chunk->Write(OpCode::OP_RETURN, 6);

  // Debuger debug;
  // debug.Disassemble(*chunk, "test");

  vm.Interpret(chunk);

  // auto ln = chunk->line_numbers();
  // for(auto &it : ln)
  // {
  //   std::cout << it.line_number() << "\t" << it.len_continuous() << "\t" << it.len_accumulated() << "\n";
  // }

  // printf("~ done ~\n");
  return 0;
}