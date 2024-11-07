#include <windows.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc != 2) {
        cerr << "Неверное количество аргументов." << endl;
        return 1;
    }

    // Получение дескриптора записи из командной строки
    HANDLE hWrite = reinterpret_cast<HANDLE>(strtoull(argv[1], nullptr, 10));

    // Сообщение, которое клиент отправит серверу
    const char* message = "Привет от клиента!";
    DWORD bytesWritten;

    if (hWrite == INVALID_HANDLE_VALUE || hWrite == NULL) {
        std::cerr << "Некорректный дескриптор канала. Код ошибки: " << GetLastError() << std::endl;
        return 1;
    }

    cout << "Клиент: Переданный дескриптор: " << argv[1] << endl;
    cout << "Клиент: Дескриптор для записи: " << hWrite << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    // Запись данных в канал
    if (!WriteFile(hWrite, message, strlen(message), &bytesWritten, NULL)) {
        cerr << "Ошибка записи в канал." << GetLastError() << endl;
        return 1;
    }

    // Закрытие дескриптора записи после отправки
    CloseHandle(hWrite);

    return 0;
}
