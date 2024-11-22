#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <cctype>    

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Введите числа для записи в массив." << endl;
    cout << "Ввод команд: \nmin - поиск минимума в массиве.\nmax - поиск максимума в массиве.\nexit - выход из программы." << endl;
   

    HANDLE hRead, hWrite;
    SECURITY_ATTRIBUTES sa = { sizeof(sa), NULL,TRUE };
    CreatePipe(&hRead, &hWrite, &sa, 0);
    SetHandleInformation(hWrite, HANDLE_FLAG_INHERIT, 0);

    STARTUPINFO si = { 0 };
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = hRead;

    int fd = _open_osfhandle(intptr_t(hWrite), _O_TEXT);
    FILE* fp = _fdopen(fd, "w");
    _dup2(_fileno(fp), _fileno(stdout));

    PROCESS_INFORMATION pi;

    CreateProcess(NULL, (LPSTR)"MinMaxClient.exe", &sa, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

   

    string s;
    while (true)
    {
        cin >> s;       
        transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
        cout << s;

    }
    CloseHandle(hRead);
    CloseHandle(hWrite);
}

