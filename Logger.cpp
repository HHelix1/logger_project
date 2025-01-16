#define _CRT_SECURE_NO_WARNINGS
#include "Logger.h"

// Конструктор для инициализации значений
Logger::Logger() {
    timemark = { 0, 0, 0 };
    text[0] = '\0';
    importance = "Информационная";
    date = "";
}

// Получение текущего времени и даты
void LoggerManager::getCurrentTimeAndDate(Logger& entry) {
    time_t now = time(0);
    tm* localTime = localtime(&now);

    entry.timemark.hour = localTime->tm_hour;
    entry.timemark.min = localTime->tm_min;
    entry.timemark.sec = localTime->tm_sec;

    entry.date = to_string(localTime->tm_mday) + "/" + to_string(localTime->tm_mon + 1) + "/" + to_string(localTime->tm_year + 1900);
}

// Добавление новой записи в логи
void LoggerManager::addLogEntry() {
    Logger entry;

    {
        std::lock_guard<std::mutex> lock(logMutex);
        cout << "Введите сообщение для лога: ";
        cin.ignore();
        cin.getline(entry.text, 256);

        cout << "Введите важность (1 - Информационная, 2 - Важная, 3 - Критическая): ";
        string importanceInput;
        int importanceChoice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, importanceInput);

        if (importanceInput.empty()) {
            entry.importance = "Информационная";
        }
        else {
            try {
                importanceChoice = stoi(importanceInput);
                if (importanceChoice < 1 || importanceChoice > 3) {
                    throw out_of_range("Выбор вне диапазона");
                }
            }
            catch (...) {
                entry.importance = "Информационная";
            }

            switch (importanceChoice) {
            case 1: entry.importance = "Информационная"; break;
            case 2: entry.importance = "Важная"; break;
            case 3: entry.importance = "Критическая"; break;
            default: entry.importance = "Информационная"; break;
            }
        }
    }

    getCurrentTimeAndDate(entry);

    {
        std::lock_guard<std::mutex> lock(logMutex);
        logArray.push_back(entry);
    }

    cout << "Добавлено сообщение: '" << entry.text << "'"
        << " с важностью [" << entry.importance << "]"
        << " во времени: " << setw(2) << setfill('0') << entry.timemark.hour << ":"
        << setw(2) << setfill('0') << entry.timemark.min << ":"
        << setw(2) << setfill('0') << entry.timemark.sec
        << " на дату: " << entry.date << endl;
}

// Показать все логи
void LoggerManager::displayLogs() {
    std::lock_guard<std::mutex> lock(logMutex);
    cout << "\n--- Лог сообщений ---\n";
    for (size_t i = 0; i < logArray.size(); ++i) {
        const auto& entry = logArray[i];
        cout << "[" << i + 1 << "] Сообщение: " << entry.text
            << " | Важность: [" << entry.importance << "]"
            << " | [Дата: " << entry.date << "] "
            << "[Время: "
            << setw(2) << setfill('0') << entry.timemark.hour << ":"
            << setw(2) << setfill('0') << entry.timemark.min << ":"
            << setw(2) << setfill('0') << entry.timemark.sec << "]\n";
    }
    cout << "---------------------\n";
}

// Удаление записи из логов
void LoggerManager::deleteLogEntry() {
    int index;
    displayLogs();
    cout << "Введите номер сообщения для удаления: ";

    while (true) {
        cin >> index;

        if (cin.fail() || index < 1 || index > logArray.size()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный номер сообщения. Введите номер от 1 до " << logArray.size() << "." << endl;
            continue;
        }
        break;
    }

    {
        std::lock_guard<std::mutex> lock(logMutex);
        logArray.erase(logArray.begin() + (index - 1));
        cout << "Сообщение номер " << index << " удалено." << endl;
    }
}

// Загрузка логов из файла
void LoggerManager::loadLogsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл " << filename << endl;
        return;
    }

    {
        std::lock_guard<std::mutex> lock(logMutex);
        logArray.clear();
    }

    while (file.peek() != EOF) {
        Logger t;
        string timeStr;

        if (!getline(file, timeStr, ',')) break;

        stringstream ss(timeStr);
        char delimiter;
        if (!(ss >> t.timemark.hour >> delimiter >> t.timemark.min >> delimiter >> t.timemark.sec)) {
            cout << "Ошибка при чтении времени: " << timeStr << endl;
            continue;
        }

        if (!file.getline(t.text, 256, ',')) break;
        if (!getline(file, t.importance, ',')) break;
        if (!getline(file, t.date)) break;

        {
            std::lock_guard<std::mutex> lock(logMutex);
            logArray.push_back(t);
        }
    }

    file.close();
    cout << "Логи загружены из файла " << filename << endl;
}

// Сохранение логов в файл
void LoggerManager::saveLogsToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл " << filename << endl;
        return;
    }

    {
        std::lock_guard<std::mutex> lock(logMutex);
        for (const auto& entry : logArray) {
            file << setw(2) << setfill('0') << entry.timemark.hour << ":"
                << setw(2) << setfill('0') << entry.timemark.min << ":"
                << setw(2) << setfill('0') << entry.timemark.sec << ","
                << entry.text << ","
                << entry.importance << ","
                << entry.date << endl;
        }
    }

    file.close();
    cout << "Логи сохранены в файл " << filename << endl;
}

// Сортировка логов по важности. Поотзователь сам выбирает, в каком порядке выбирать сортировку по важности
void LoggerManager::sortImportance(bool ascending) {
    {
        std::lock_guard<std::mutex> lock(logMutex);
        if (ascending) {
            sort(logArray.begin(), logArray.end(), [](const Logger& a, const Logger& b) {
                return a.importance < b.importance;
                });
        }
        else {
            sort(logArray.begin(), logArray.end(), [](const Logger& a, const Logger& b) {
                return a.importance > b.importance;
                });
        }
        cout << "Логи отсортированы по важности " << (ascending ? "в порядке возрастания." : "в порядке убывания.") << endl;
    }
}

// Сортировка логов по времени
void LoggerManager::sortLogsByTime(bool ascending) {
    {
        std::lock_guard<std::mutex> lock(logMutex);
        if (ascending) {
            sort(logArray.begin(), logArray.end(), [](const Logger& a, const Logger& b) {
                if (a.timemark.hour != b.timemark.hour) return a.timemark.hour < b.timemark.hour;
                if (a.timemark.min != b.timemark.min) return a.timemark.min < b.timemark.min;
                return a.timemark.sec < b.timemark.sec;
                });
        }
        else {
            sort(logArray.begin(), logArray.end(), [](const Logger& a, const Logger& b) {
                if (a.timemark.hour != b.timemark.hour) return a.timemark.hour > b.timemark.hour;
                if (a.timemark.min != b.timemark.min) return a.timemark.min > b.timemark.min;
                return a.timemark.sec > b.timemark.sec;
                });
        }
        cout << "Логи отсортированы по времени " << (ascending ? "в порядке возрастания." : "в порядке убывания.") << endl;
    }
}

// Поиск логов по ключевым словам
void LoggerManager::searchKeywords(const string& keywords) {
    std::lock_guard<std::mutex> lock(logMutex);
    cout << "\n--- Результаты поиска по ключевым словам: \"" << keywords << "\" ---\n";

    stringstream ss(keywords);
    string keyword;
    vector<string> keywordList;

    while (ss >> keyword) {
        keywordList.push_back(keyword);
    }

    bool found = false;
    for (const auto& entry : logArray) {
        for (const auto& word : keywordList) {
            if (strstr(entry.text, word.c_str()) != nullptr) {
                cout << "Сообщение: " << entry.text
                    << " | Важность: [" << entry.importance << "]"
                    << " | [Дата: " << entry.date << "] "
                    << "[Время: "
                    << setw(2) << setfill('0') << entry.timemark.hour << ":"
                    << setw(2) << setfill('0') << entry.timemark.min << ":"
                    << setw(2) << setfill('0') << entry.timemark.sec << "]\n";
                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "Совпадений не найдено." << endl;
    }
    cout << "-----------------------------------------\n";
}