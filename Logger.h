#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <iomanip>
#include <ctime>
#include <limits>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <mutex>

using namespace std;

// Структура для времени, включающее в себя часы, минуты и секунды
struct Time {
    int hour;
    int min;
    int sec;
};

// Класс для логов. Лог будет состоять из даты, времени, текста сообщения и важности этого сообщения
class Logger {
public:
    Time timemark;
    char text[256];
    string importance;
    string date;

    Logger();
};

// Класс для управления логами, который определяет функционал работы с логами
class LoggerManager {
private:
    vector<Logger> logArray;
    std::mutex logMutex;

    void getCurrentTimeAndDate(Logger& entry);

public:
    void addLogEntry();
    void displayLogs();
    void deleteLogEntry();
    void loadLogsFromFile(const string& filename);
    void saveLogsToFile(const string& filename);
    void sortImportance(bool ascending);
    void sortLogsByTime(bool ascending);
    void searchKeywords(const string& keywords);
};

#endif