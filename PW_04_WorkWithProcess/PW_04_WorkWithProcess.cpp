#include <windows.h>
#undef max
#include <iostream>
#include <string>

using namespace std;

void startProgramm() { //Заупск CreateExe
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    wstring exePath = L"CreateExe.exe Проверка параметров exe";

    if (!CreateProcess(NULL, const_cast<LPWSTR>(exePath.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        cerr << "Ошибка запуска процесса: " << GetLastError() << endl;
        exit(0);
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    cout << "Процесс запущен успешно!" << endl; 
}

void startNotepadd() { //Запуск блокнота
    ShellExecute(NULL, L"open", L"notepad.exe", NULL, NULL, SW_SHOWNORMAL);
}

void therminateProc() { //Завершение через Therminate
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    wstring exePath = L"Exit_CountExe.exe";

    if (!CreateProcess(NULL, const_cast<LPWSTR>(exePath.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        cerr << "Ошибка запуска процесса: " << GetLastError() << endl;
        exit(0);
    }

    cout << "Процесс запущен успешно!" << endl;

    while (true)
    {
        char c;
        cout << "Введите 't' для завершения процесса: ";
        cin >> c;

        if (c == 't')
        {
            cout << '\n';
            TerminateProcess(pi.hProcess, 1);
            ExitProcess(1);
        }
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    int choice;

    for (;;)
    {
        cout << "Меню:\n\n";
        cout << "1. Запустить CreateExe.exe\n";
        cout << "2. Запустить блокнот.\n";
        cout << "3. Запуск программы с завершением через Therminate\n";
        cout << "\n-1. Выход\n\n";

        while (true) {
            cout << "Введите ваш выбор: ";
            if (cin >> choice) {
                break;
            }
            else {
                cout << "Ошибка! Введите целое число.\n\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        switch (choice) {
        case 1:
            startProgramm();
            break;

        case 2:
            startNotepadd();
            break;

        case 3:
            therminateProc();
            break;

        case -1:
            cout << "Завершение программы...\n";
            return 0;

        default:
            cout << "Неверный выбор!\n\n";

        }
    }


    return 0;
}
