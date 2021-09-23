#include "functions.h"


/*
std::string functions::exec(const char* cmd)
{
    char buffer[256];
    std::string result = "";
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
        try {
            while (fgets(buffer, sizeof buffer, pipe) != NULL) {
                result += buffer;
            }
    } catch (...) {
        _pclose(pipe);
        throw;
    }
    _pclose(pipe);
    return result;
}

QString functions::exec(const QString execf)//, const QStringList params)
{
    QProcess process;
    process.start(execf);
    process.waitForFinished(); // sets current thread to sleep and waits for pingProcess end
    return process.readAllStandardOutput();
}
*/
// formating number for "nn" format
std::string functions::to_format(const int number) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << number;
    return ss.str();
}

// getting cmd output to variable
double functions::exec(const char *cmd)
{
    std::array<char, 256> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    double temp = ::atof(result.c_str());
    return temp;
}

// round function
double functions::round_up(double value, int decimal_places)
{
    const double multiplier = std::pow(10.0, decimal_places);
    return std::ceil(value * multiplier) / multiplier;
}
