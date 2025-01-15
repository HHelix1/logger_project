Logger Manager — это консольное приложение на C++, предназначенное для управления логами. Оно позволяет добавлять, отображать, удалять, загружать и сохранять логи, 
а также сортировать их по важности и времени, а также осуществлять поиск по ключевым словам. 
Программа использует многопоточность для безопасного доступа к логам, что делает её подходящей для использования в многопоточных приложениях.

void getCurrentTimeAndDate(Logger& entry) - данная функция получает время и дату добавления лога.
void addLogEntry() - функция добавления нового лога в текстовый файл. Выполнена защита от некорректного ввода.
void displayLogs() - функция вывода всех логов в консоль.
void deleteLogEntry() - функция удаления лога. Пользователь вводит номер лога. При вводе некорректного ввода, программа требует повторный ввод.
void loadLogsFromFile(const string& filename) - функция загрузки текстового файла. Пользователь может загрузить только файлы формата .txt.
void saveLogsToFile(const string& filename) - функция сохранения в текстовый файл. Пользователь может сохранить логи только в файл формата .txt.
void sortImportance(bool ascending) - функция сортировки логов. Пользователь сам выбирает сортировку по возрастанию или выбыванию.
void sortLogsByTime(bool ascending) - функция сортировки логов по времени. Пользователь сам выбирает сортировку по возрастанию или выбыванию.
void searchKeywords(const string& keywords) - функция поиска логов по ключевым словам. Программа выводит все логи, у которых найдены введенные ключевые слова.
