#include "Logger.h"

int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "ru");
    LoggerManager loggerManager;
    int choice;

    do {
        cout << "\n����:\n"
            << "1. �������� ���\n"
            << "2. �������� ��� ����\n"
            << "3. ������� ���\n"
            << "4. ��������� ���� �� �����\n"
            << "5. ��������� ���� � ����\n"
            << "6. ����������� ���� �� ��������\n"
            << "7. ����������� ���� �� �������\n"
            << "8. ����� �� �������� ������\n"
            << "0. �����\n"
            << "�������� ��������: ";
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
            cout << "������� ��� ����� ��� ��������: ";
            cin >> file;
            loggerManager.loadLogsFromFile(file);
            break;
        }
        case 5: {
            string file;
            cout << "������� ��� ����� ��� ����������: ";
            cin >> file;
            loggerManager.saveLogsToFile(file);
            break;
        }
        case 6: {
            int orderChoice;
            cout << "�������� ������� ����������:\n"
                << "1. �����������\n"
                << "2. ��������\n"
                << "�����: ";
            cin >> orderChoice;
            loggerManager.sortImportance(orderChoice == 1);
            break;
        }
        case 7: {
            int orderChoice;
            cout << "�������� ������� ���������� �� �������:\n"
                << "1. �����������\n"
                << "2. ��������\n"
                << "�����: ";
            cin >> orderChoice;
            loggerManager.sortLogsByTime(orderChoice == 1);
            break;
        }
        case 8: {
            string keywords;
            cout << "������� �������� ����� ��� ������: ";
            cin.ignore();
            getline(cin, keywords);
            loggerManager.searchKeywords(keywords);
            break;
        }
        case 0:
            break;
        default:
            cout << "�������� �����. ����������, ���������� �����." << endl;
        }
    } while (choice != 0);

    return 0;
}