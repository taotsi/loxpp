#ifndef RAND_HH
#define RAND_HH

#include <random>
#include <functional>

namespace taotsi
{

class Rand
{
public:
  static auto RealRandomDice()
  {
    double begin = 0.0, end = 1.0;
    std::random_device rd;
    std::mt19937 mt{rd()};
    std::uniform_real_distribution<double> dist{begin, end};
    auto dice = std::bind(dist, mt);
    return dice;
  }

  static auto IntRandomDice(int begin, int end)
  {
    std::random_device rd;
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<int> dist{begin, end};
    auto dice = std::bind(dist, mt);
    return dice;
  }
private:

};

} // namespace taotsi

#endif // RAND_HH