#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <sys/utsname.h>

namespace {

std::string read_cpu_model() {
    std::ifstream file("/proc/cpuinfo");
    std::string key;
    std::string value;

    while (std::getline(file, value)) {
        const auto separator = value.find(':');
        if (separator == std::string::npos) {
            continue;
        }

        key = value.substr(0, separator);
        if (key.find("model name") != std::string::npos) {
            return value.substr(separator + 1);
        }
    }

    return "unavailable";
}

std::string format_uptime() {
    std::ifstream file("/proc/uptime");
    double seconds = 0.0;

    if (!(file >> seconds)) {
        return "unavailable";
    }

    const auto total = static_cast<long long>(seconds);
    const long long days = total / 86400;
    const long long hours = (total % 86400) / 3600;
    const long long minutes = (total % 3600) / 60;

    std::ostringstream out;
    out << days << "d " << hours << "h " << minutes << "m";
    return out.str();
}

std::string memory_usage() {
    std::ifstream file("/proc/meminfo");

    long long total_kb = 0;
    long long available_kb = 0;
    std::string key;
    long long value;
    std::string unit;

    while (file >> key >> value >> unit) {
        if (key == "MemTotal:") {
            total_kb = value;
        } else if (key == "MemAvailable:") {
            available_kb = value;
        }
    }

    if (total_kb <= 0) {
        return "unavailable";
    }

    const double used_percent =
        (1.0 - static_cast<double>(available_kb) / total_kb) * 100.0;

    std::ostringstream out;
    out << std::fixed << std::setprecision(1) << used_percent << "% used";
    return out.str();
}

} // namespace

int main() {
    struct utsname system {};

    std::cout << "System Info\n";
    std::cout << "-----------\n";

    if (uname(&system) == 0) {
        std::cout << "Hostname : " << system.nodename << '\n';
        std::cout << "Kernel   : " << system.sysname << ' ' << system.release << '\n';
        std::cout << "Machine  : " << system.machine << '\n';
    } else {
        std::cout << "Kernel information unavailable\n";
    }

    std::cout << "CPU      :" << read_cpu_model() << '\n';
    std::cout << "CPUs     : " << std::thread::hardware_concurrency() << '\n';
    std::cout << "Memory   : " << memory_usage() << '\n';
    std::cout << "Uptime   : " << format_uptime() << '\n';

    return 0;
}
