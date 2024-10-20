#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    string text = "This is sample text for lexical analysis. It contains - several words.";
    bool runAverage = false; // true запуск калькулятора, false запуск анализа текста

    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

    wstring commandLine;
    if (runAverage) {
        commandLine = L"average_calculator.exe ";
        wostringstream wss;
        for (int num : numbers) wss << num << L" ";
        commandLine += wss.str();
    }
    else {
        commandLine = L"lexWord.exe \"" + wstring(text.begin(), text.end()); // Добавили кавычки для обработки пробелов в тексте
    }

    if (!CreateProcess(NULL, const_cast<LPWSTR>(commandLine.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        cerr << "Ошибка создания процесса: " << GetLastError() << endl;
        return 1;
    }
    DWORD dwMilliseconds = 10000;
    DWORD dwResult = WaitForSingleObject(pi.hProcess, dwMilliseconds);

    DWORD id = GetProcessId(pi.hProcess);

    if (dwResult == WAIT_OBJECT_0) {
        DWORD exitCode;
        GetExitCodeProcess(pi.hProcess, &exitCode);
        cout << "Дочерний процесс завершился с кодом: " << exitCode << endl;

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else if (dwResult == WAIT_TIMEOUT) {
        DWORD exitCode;
        GetExitCodeProcess(pi.hProcess, &exitCode);
        cout << "Время вышло, принудительное завершение дочернего процесса " << exitCode << endl;

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        
    }
    else {
        cout << "Произошла ошибка, завершение процесса принудительно. " << endl;

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);        
    }

    return 0;
}