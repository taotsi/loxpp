#include "source.hh"

namespace loxpp
{

inline std::string Source::data() const
{
  return data_;
}

std::ostream& operator<<(std::ostream &os, const Source &src)
{
  os << src.data();
  return os;
}
} // namespace loxpp
