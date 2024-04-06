#include <cstdint>
#include <ctime>
namespace pts {

class DateUtils {
  public:
    static int32_t GetCurrentDate() {
        time_t now = time(nullptr);
        struct tm* t = localtime(&now);
        return (t->tm_year + 1900) * 10000 + (t->tm_mon + 1) * 100 + t->tm_mday;
    }
};

}  // namespace pts