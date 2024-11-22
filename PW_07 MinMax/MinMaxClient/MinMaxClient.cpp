#include <iostream>
#include <Windows.h>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm> // для min_element и max_element

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    const int MAXLEN = 1024;
    vector<double> numbers; // Вектор для хранения чисел

    while (true)
    {
        DWORD dwRead;
        char buff[MAXLEN + 1];

        if (!ReadFile(hIn, buff, MAXLEN, &dwRead, nullptr) || !dwRead)
        {
            break; // выходим из цикла, если произошла ошибка чтения или не считано ничего
        }

        buff[min(MAXLEN, dwRead)] = 0; // Заменяем последний байт на нуль-терминатор

        // Обрабатываем ввод как строку
        string input(buff);
        stringstream ss(input);
        string command;

        // Проверяем, является ли ввод командой или числом
        if (ss >> command)
        {
            if (command == "min")
            {
                // Определяем минимальное значение
                if (!numbers.empty())
                {
                    double min_value = *min_element(numbers.begin(), numbers.end());
                    cout << "Минимальное значение: " << min_value << endl;
                }
                else
                {
                    cout << "Массив пуст, минимума нет." << endl;
                }
                continue; 
            }
            else if (command == "max")
            {
                // Определяем максимальное значение
                if (!numbers.empty())
                {
                    double max_value = *max_element(numbers.begin(), numbers.end());
                    cout << "Максимальное значение: " << max_value << endl;
                }
                else
                {
                    cout << "Массив пуст, максимума нет." << endl;
                }
                continue; 
            }
            else if (command == "exit")
            {
                cout << "Выход из программы." << endl;
                break; 
            }
            else // Если это не команда, пытаемся считать число
            {
                ss.putback(' '); // Восстанавливаем пробел для обработки других чисел
                ss >> command;    
                double number;
                // Пытаемся прочитать число
                if (stringstream(command) >> number) {
                    numbers.push_back(number); // Сохраняем число в вектор
                }
                else {
                    cout << "Неверный ввод. Введите числа или команды." << endl;
                }
            }
        }

        // Для демонстрации выведем все считанные числа
        cout << "Данные в массиве: ";
        for (double num : numbers)
        {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}

