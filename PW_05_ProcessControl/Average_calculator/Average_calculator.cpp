#include <iostream>
#include <vector>
#include <cstdlib> 
#include <Windows.h>

using namespace std;

int main(int argc, char* argv[]) {    
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc <= 1) {
        cerr << "Ошибка: Числа не предоставлены." << endl;
        return 1;
    }

    vector<int> numbers;
    for (int i = 1; i < argc; ++i) {
        try {
            numbers.push_back(atoi(argv[i]));
        }
        catch (const exception& e) {
            cerr << "Ошибка: Неверный формат числа: " << argv[i] << endl;
            return 1;
        }
    }

    if (numbers.empty()) {
        cerr << "Ошибка: Числа не предоставлены." << endl;
        return 1;
    }

    double average = 0;
    for (int n : numbers) {
        average += n;
    }
    average /= numbers.size();

    cout<<"Среднее число: " << average << endl;
    system("pause");

    return 0;
}