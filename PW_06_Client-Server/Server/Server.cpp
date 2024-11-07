#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE; // Позволяет наследовать дескриптор дочерним процессом
    saAttr.lpSecurityDescriptor = NULL;

    // Создание анонимного канала
    HANDLE hRead, hWrite;
    if (!CreatePipe(&hRead, &hWrite, &saAttr, 0)) {
        cerr << "Не удалось создать канал." << endl;
        return 1;
    }

    cout << "Отладочная информация: " << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "Сервер: дескриптор для записи: " << hWrite << endl;

    // Преобразование дескриптора записи
    string writeHandleStr = to_string(reinterpret_cast<uintptr_t>(hWrite));

    // Параметры для дочернего процесса
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Командная строка для дочернего процесса
    string commandLine = "Client.exe " + writeHandleStr;

    // Запуск дочернего процесса
    if (!CreateProcess(NULL, const_cast<char*>(commandLine.c_str()), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        cerr << "Не удалось создать дочерний процесс." << endl;
        return 1;
    }

    // Закрытие дескриптора записи
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(hWrite);

    // Чтение данных из анонимного канала
    char buffer[256];
    DWORD bytesRead;
    while (ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        cout << "Сервер получил сообщение: " << buffer << endl;
    }

    // Закрытие дескрипторов и завершение работы
    CloseHandle(hRead);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    system("pause");
    return 0;
}
