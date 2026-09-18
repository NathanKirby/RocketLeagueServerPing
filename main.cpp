#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <array>
#include <cstdio>

#ifdef _WIN32
#define popen  _popen
#define pclose _pclose
#endif

struct Server {
    const char* name;
    const char* ip;
    const char* origin;
};

static const std::vector<Server> servers = {
    {"SAF",  "15.240.66.181",  "Cape Town, South Africa"},
    {"ASC",  "16.162.44.0",    "Hong Kong"},
    {"JPN",  "35.79.104.14",   "Tokyo, Japan"},
    {"IND",  "15.207.126.110", "Mumbai, India"},
    {"ASM",  "13.212.141.113", "Singapore"},
    {"OCE",  "3.26.124.153",   "Sydney, Australia"},
    {"EU",   "18.157.34.74",   "Frankfurt, Germany"},
    {"EU1",  "13.60.90.86",    "Stockholm, Sweden"},
    {"EU3",  "52.208.27.33",   "Dublin, Ireland"},
    {"EU5",  "18.133.98.200",  "London, England"},
    {"EU7",  "35.180.227.57",  "Paris, France"},
    {"ME",   "34.18.71.245",   "Doha, Qatar"},
    {"ME1",  "34.165.88.11",   "Tel Aviv, Israel"},
    {"SAM",  "15.228.137.173", "Sao Paulo, Brazil"},
    {"USE",  "3.237.167.92",   "Ashburn, Virginia"},
    {"USC",  "3.144.61.165",   "Columbus, Ohio"},
    {"USC1", "18.88.9.98",     "Dallas, Texas"},
    {"USW",  "3.101.179.49",   "San Francisco, California"},
    {"USW1", "52.12.91.222",   "Portland, Oregon"}
};

static std::mutex print_mutex;

void ping_server(const Server& s) {
    std::string cmd = "ping -n 2 " + std::string(s.ip);
    std::array<char, 256> buf{};
    std::string out;

    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return;

    while (fgets(buf.data(), (int)buf.size(), pipe))
        out += buf.data();
    pclose(pipe);

    std::lock_guard<std::mutex> lock(print_mutex);
    std::cout << s.name << " | " << s.origin << " | " << s.ip << "\n" << out << "\n";
}

int main() {
    std::vector<std::thread> threads;
    threads.reserve(servers.size());

    for (const auto& s : servers)
        threads.emplace_back(ping_server, s);

    for (auto& t : threads)
        t.join();

    return 0;
}
