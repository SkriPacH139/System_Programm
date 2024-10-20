#include <iostream>
#include <fstream>
#include <windows.h>
#undef max
#include <string>
#include <filesystem>
#include <limits>

using namespace std;

void cerateFile(string fileName) {

    ofstream outputFile(fileName);

    if (outputFile.is_open()) {

        outputFile << "Азаров А. А. Группа - 1623." << endl;
        outputFile.close();

        cout << "Новый файл " << fileName << " успешно создан и сохранен: " << filesystem::current_path() << endl << endl;;
    }

    else {
        cerr << "Ошибка открытия файла!" << endl;
    }

}

void renameFile(string fileName, string newFileName) {

    const int maxPath = 256;

    char old_path[maxPath];
    char new_path[maxPath];

    strcpy_s(old_path, fileName.c_str());
    strcpy_s(new_path, newFileName.c_str());

    if (rename(old_path, new_path) == 0) {
        cout << "Файл '" << old_path << "' переименован в '" << new_path << "'" << filesystem::current_path() << endl << endl;
    }
    else
    {
        cerr << "Ошибка переименования файла!" << endl;
    }
}

void createDir(string dirName) {

    if (!CreateDirectory(wstring(dirName.begin(), dirName.end()).c_str(), NULL)) {
        cerr << "Ошибка создания каталога!" << endl;
    }
    else
    {
        cout << "Каталог " << dirName << " создан и сохранен: " << filesystem::current_path() << endl << endl;
    }
}

void deleteDir(string dirName) {

    if (!RemoveDirectory(wstring(dirName.begin(), dirName.end()).c_str())) {
        cerr << "Ошибка удаления каталога!" << endl;
    }
    else
    {
        cout << "Каталог " << dirName << " удален!" << endl;
    }
}

void printDir(const filesystem::path& path) {
    for (const auto& entry : filesystem::directory_iterator(path)) {
        cout << entry.path() << endl;
        if (entry.is_directory()) {
            printDir(entry.path());
        }
    }
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string fileName, newFileName, dirName;
   
    int choice;

    for (;;)
    {           
        cout << "Меню:\n\n";
        cout << "1. Создать файл\n";
        cout << "2. Переименовать файл\n";
        cout << "3. Создать директорию\n";
        cout << "4. Удалить директорию\n";
        cout << "5. Вывести содержимое текущей директории\n";
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
            cout << "Введите имя файла: ";
            cin >> fileName;
            cerateFile(fileName);
            break;

        case 2:
            cout << "Введите имя файла: ";
            cin >> fileName;
            cout << "Введите новое имя файла: ";
            cin >> newFileName;
            renameFile(fileName, newFileName);
            break;

        case 3:
            cout << "Введите имя директории: ";
            cin >> dirName;
            createDir(dirName);
            break;

        case 4:
            cout << "Введите имя директории: ";
            cin >> dirName;
            deleteDir(dirName);
            break;

        case 5:
            printDir(filesystem::current_path());
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
