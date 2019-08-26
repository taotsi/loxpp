#ifndef COUNTER_HH
#define COUNTER_HH

// #include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include "macros.hh"

namespace taotsi{

class Counter
{
public:
  static Counter& instance()
  {
    static Counter counter;
    return counter;
  }
  ~Counter()
  {
    ShowCounts();
  }
  void HereOnce(const char* file, int line)
  {
    std::stringstream ss;
    ss << file << "(" << line << ")";
    if(counters_.find(ss.str()) != counters_.end())
    {
      counters_[ss.str()] ++;
    }
    else
    {
      counters_[ss.str()] = 1;
    }
  }
  void ShowCounts()
  {
    std::stringstream ss;
    ss.imbue(std::locale(""));
    ss << "\033[0;44mCOUNTER:\033[0m\n";
    for(auto &it : counters_)
    {
      ss << "  " << it.first << ":\t" << it.second << " times\n";
    }
    std::cout << ss.str();
  }
private:
  Counter() {}

  std::unordered_map<std::string, unsigned long long> counters_{};
};


#define COUNT_HERE() Counter::instance().HereOnce(__FILENAME__, __LINE__)
#define SHOW_COUNTS() Counter::instance().ShowCounts()
}

#endif // COUNTER_HH