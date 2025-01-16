#include "Logger.h"

int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "ru");
    LoggerManager loggerManager;
    int choice;

    do {
        cout << "\nМеню:\n"
            << "1. Добавить лог\n"
            << "2. Показать все логи\n"
            << "3. Удалить лог\n"
            << "4. Загрузить логи из файла\n"
            << "5. Сохранить логи в файл\n"
            << "6. Сортировать логи по важности\n"
            << "7. Сортировать логи по времени\n"
            << "8. Поиск по ключевым словам\n"
            << "0. Выход\n"
            << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            loggerManager.addLogEntry();
            break;
        case 2:
            loggerManager.displayLogs();
            break;
        case 3:
            loggerManager.deleteLogEntry();
            break;
        case 4: {
            string file;
            cout << "Введите имя файла для загрузки: ";
            cin >> file;
            loggerManager.loadLogsFromFile(file);
            break;
        }
        case 5: {
            string file;
            cout << "Введите имя файла для сохранения: ";
            cin >> file;
            loggerManager.saveLogsToFile(file);
            break;
        }
        case 6: {
            int orderChoice;
            cout << "Выберите порядок сортировки:\n"
                << "1. Возрастание\n"
                << "2. Убывание\n"
                << "Выбор: ";
            cin >> orderChoice;
            loggerManager.sortImportance(orderChoice == 1);
            break;
        }
        case 7: {
            int orderChoice;
            cout << "Выберите порядок сортировки по времени:\n"
                << "1. Возрастание\n"
                << "2. Убывание\n"
                << "Выбор: ";
            cin >> orderChoice;
            loggerManager.sortLogsByTime(orderChoice == 1);
            break;
        }
        case 8: {
            string keywords;
            cout << "Введите ключевые слова для поиска: ";
            cin.ignore();
            getline(cin, keywords);
            loggerManager.searchKeywords(keywords);
            break;
        }
        case 0:
            break;
        default:
            cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
        }
    } while (choice != 0);

    return 0;
}