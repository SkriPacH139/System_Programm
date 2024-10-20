#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

//1. С использованием библиотеки C
int copyFileC(char* sourcePath, char* destinationPath) {
    FILE* sourceFile, * destinationFile;
    errno_t err;

    // Открываем исходный файл для чтения
    err = fopen_s(&sourceFile, sourcePath, "rb");
    if (err != 0) {
        fprintf(stderr, "Ошибка открытия исходного файла: %s\n", sourcePath);
        return 1;
    }

    // Открываем целевой файл для записи
    err = fopen_s(&destinationFile, destinationPath, "wb");
    if (err != 0) {
        fprintf(stderr, "Ошибка открытия целевого файла: %s\n", destinationPath);
        fclose(sourceFile);
        return 1;
    }

    // Копируем данные из исходного файла в целевой
    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        if (fwrite(buffer, 1, bytesRead, destinationFile) != bytesRead) {
            fprintf(stderr, "Ошибка записи в целевой файл.\n");
            fclose(sourceFile);
            fclose(destinationFile);
            return 1;
        }
    }

    // Закрываем файлы
    fclose(sourceFile);
    fclose(destinationFile);

    return 0;
}


// 2. С использованием Windows
void copyFileWindows(const string& source, const string& destination) {
    HANDLE sourceFile = CreateFileA(source.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    HANDLE destinationFile = CreateFileA(destination.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (sourceFile == INVALID_HANDLE_VALUE || destinationFile == INVALID_HANDLE_VALUE) {
        cerr << "Ошибка открытия файла." << endl;
        return;
    }

    char buffer[1024];
    DWORD bytesRead;

    while (ReadFile(sourceFile, buffer, sizeof(buffer), &bytesRead, nullptr) && bytesRead > 0) {
        DWORD bytesWritten;
        WriteFile(destinationFile, buffer, bytesRead, &bytesWritten, nullptr);
    }

    CloseHandle(sourceFile);
    CloseHandle(destinationFile);
}

// 3. С использованием вспомогательной функции Windows – CopyFile
void copyFileCopyFile(const string& source, const string& destination) {
    if (!CopyFileA(source.c_str(), destination.c_str(), FALSE)) {
        cerr << "Ошибка копирования файла." << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Получаем путь к текущей директории
    char currentPath[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentPath);

    // Формируем полные пути к файлам
    string sourceFile = string(currentPath) + "\\OriginalFile.txt";

    string copyCStr = string(currentPath) + "\\CopyC.txt";
    string copyWindows = string(currentPath) + "\\CopyWindows.txt";
    string copyFile = string(currentPath) + "\\CopyFileFunc.txt";


    char* copyCOrigin = new char[sourceFile.length() + 1];
    strcpy_s(copyCOrigin, sourceFile.length() + 1, sourceFile.c_str());

    char* copyC = new char[copyCStr.length() + 1];
    strcpy_s(copyC, copyCStr.length() + 1, copyCStr.c_str());

    cout << "Копирование файла с использованием библиотеки C..." << endl;
    if (copyFileC(copyCOrigin, copyC) != 0) {
        fprintf(stderr, "Ошибка копирования файла.\n");
        return 1;
    }

    delete[] copyCOrigin;
    delete[] copyC;

    cout << "Копирование файла с использованием Windows API..." << endl;
    copyFileWindows(sourceFile, copyWindows);

    cout << "Копирование файла с использованием CopyFile..." << endl;
    copyFileCopyFile(sourceFile, copyFile);

    return 0;
}