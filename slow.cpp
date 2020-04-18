#include <iostream>
#include <random>
#include <thread>
#include <chrono>

/*
rank is the n in probability 1/(2*n)

|   rand      |probability|rank|
--------------------------------
|[0,    0.5  )|1/2        |1   |
|[0.5,  0.75 )|1/4        |2   |
|[0.75, 0.875)|1/8        |3   |
      ...
 * */
extern "C" uint32_t rank(double rand)
{
    uint32_t rank = 1;
    double leftEnd = 0.0;
    while(true)
    {
        double rightEnd = leftEnd + 1.0 / std::pow(2, rank);
        if(rand >= leftEnd && rand < rightEnd)
            break;

        leftEnd = rightEnd;
        ++rank;
    }

    return rank;
}

using namespace std::chrono_literals;
static constexpr std::chrono::microseconds du = 1234us;

extern "C" void SlowFunc()
{
    // generate a random number in range [0, 1)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    auto r = dis(gen);
    uint32_t rk = rank(r);

    std::this_thread::sleep_for(du * rk);
}

#if 0
int main()
{
    SlowFunc();
    return 1;
}
#endif
