#ifndef VM_HH
#define VM_HH

#include <memory>
#include "chunk.hh"

namespace loxpp
{
// NOTE: only one VM instance is needed
class VM
{
public:
  VM();
  VM(const VM&) = default;
  VM(VM&&) = default;
  VM& operator=(const VM&) = default;
  VM& operator=(VM&&) = default;
  ~VM() = default;

private:
  std::shared_ptr<Chunk> chunk_ptr_;
};
}

#endif // VM_HH
