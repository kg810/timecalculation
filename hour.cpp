#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

static constexpr char hhmmss[] = " 23:00:00";

// N.B. not thread safe, just in this simple usecase it can save cost of copy struct tm
extern "C" std::tm* strToTM(const std::string& date) {
    std::string fullTime = date + hhmmss;
    static std::tm tm_end;
    strptime(fullTime.c_str(), "%Y-%m-%d %H:%M:%S", &tm_end);
    return &tm_end;
}

extern "C" void GetHours(const std::string& date) {
    auto start_tp = std::chrono::system_clock::now();
    auto end_tp = std::chrono::system_clock::from_time_t(std::mktime(strToTM(date)));
    uint32_t mins = std::chrono::duration_cast<std::chrono::minutes>(end_tp - start_tp).count();
    uint32_t res = mins / 60;
    if(mins % 60 >= 30) ++res;

    std::cout << __func__ << ": " << res << std::endl;
}

#if 0
int main() {
    std::string date = "2020-05-06";
    GetHours(date);
}
#endif
