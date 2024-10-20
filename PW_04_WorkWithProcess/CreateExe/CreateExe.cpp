#include <windows.h>
#include <iostream>

using namespace std;

//Создание exe (CreateExe) для запуска через StartProgramm
int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("Имя программы: %s\n", argv[0]);

    for (int i = 1; i < argc; ++i) {
        printf("Параметр %d: %s\n", i, argv[i]);
    }

    printf("\n");

    cout << "Нажмите любую клавишу для выхода..." << endl;
    cin.get();

    return 0;
}
