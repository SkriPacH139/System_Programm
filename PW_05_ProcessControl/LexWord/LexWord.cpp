#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm> // для функции erase
#include <synchapi.h>

using namespace std;

// Функция для удаления символов из строки
string removeChars(string str, const string& charsToRemove) {
    for (char c : charsToRemove) {
        str.erase(remove(str.begin(), str.end(), c), str.end());
    }
    return str;
}


int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc <= 1) {
        cerr << "Ошибка: Текст не предоставлен." << endl;
        return 1;
    }

    string text;

    for (int i = 1; i < argc; i++)
    {
        text += argv[i];    
        text += " ";
    }
    

    // Удаляем знаки препинания, кроме дефиса
    text = removeChars(text, ".,;:!?()[]{}<>-\"");

    stringstream ss(text);
    string word;
    vector<string> words;

    while (ss >> word) {
        // Обработка слов с дефисом
        size_t hyphenPos = word.find('-');
        if (hyphenPos != string::npos) {
            size_t nextSpace = word.find(' ', hyphenPos);
            if (nextSpace == string::npos) {
                words.push_back(word);
            }
            else {
                words.push_back(word.substr(0, hyphenPos));
                words.push_back(word.substr(hyphenPos + 1));
            }
        }
        else {
            words.push_back(word);
        }
    }

    cout << "Слова:" << endl;
    for (const string& w : words) {
        cout << w << endl;
    }
    
    system("pause");

    return 0;
}