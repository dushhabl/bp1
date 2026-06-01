#include "error_handler.h"
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

ErrorHandler::ErrorHandler(const string& log) : logFile(log) {}

void ErrorHandler::logError(const string& errorMsg) {
    ofstream log(logFile, ios::app);

    if (log.is_open()) {
        // Get current time
        auto now = chrono::system_clock::now();
        time_t time = chrono::system_clock::to_time_t(now);

        // Safe time conversion
        struct tm timeInfo;
        localtime_s(&timeInfo, &time);

        // Format time
        log << "[";
        log << (1900 + timeInfo.tm_year) << "-";
        log << setfill('0') << setw(2) << (1 + timeInfo.tm_mon) << "-";
        log << setw(2) << timeInfo.tm_mday << " ";
        log << setw(2) << timeInfo.tm_hour << ":";
        log << setw(2) << timeInfo.tm_min << ":";
        log << setw(2) << timeInfo.tm_sec;
        log << "]" << endl;

        log << "ERROR: " << errorMsg << endl;
        log << "------------------------" << endl;

        log.close();
    }
}

void ErrorHandler::logException(const exception& e) {
    logError(e.what());
}