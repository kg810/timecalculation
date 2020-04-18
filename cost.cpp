#include <chrono>
#include <iostream>
#include <thread>

extern "C" void SlowFunc();

extern "C" void GetCost(const std::string& date) {
    auto start = std::chrono::high_resolution_clock::now();
    SlowFunc();
    auto end = std::chrono::high_resolution_clock::now();
    auto res = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << __func__ << "cost: " << res.count() << "ms\n";
}

#if 0
void SlowFunc()
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
}

int main()
{
    GetCost("2020-05-06");
    return 1;
}
#endif
