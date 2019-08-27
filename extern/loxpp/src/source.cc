#include "source.hh"

namespace loxpp
{

inline std::string Source::data() const
{
  return data_;
}

Source::Source(std::ofstream &of)
{
  data_ << of;
}

std::ostream& operator<<(std::ostream &os, const Source &src)
{
  os << src.data();
  return os;
}
} // namespace loxpp
