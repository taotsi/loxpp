#ifndef SCANNER_HH
#define SCANNER_HH
#include "utility.hh"
#include "token.hh"

namespace loxpp
{

class Scanner
{
public:
  Scanner() {};
  DEFAULT_SPECIAL_FUNCTIONS(Scanner);
  Token scan_token();
private:
  size_t start_ = 0;
  size_t current_ = 0;
  size_t line_ = 0;
};

} // namespace loxpp


#endif // SCANNER_HH