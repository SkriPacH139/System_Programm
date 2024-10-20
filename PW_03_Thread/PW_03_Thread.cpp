#include <iostream>
#include <windows.h>
#include <process.h> 

using namespace std;

DWORD WINAPI ThreadProc(LPVOID lpParameter) {
    
    int threadId = reinterpret_cast<int>(lpParameter);

    cout << "Поток " << threadId << " запущен.\n";
    for (int i = 0; i < 100001; i++)
    {
        i++;
        Sleep(100);
    }

    return 0;
}

unsigned __stdcall _ThreadProc(LPVOID lpParameter) {   

    int threadId = reinterpret_cast<int>(lpParameter);

    cout << "Поток " << threadId << " запущен.\n";
    for (int i = 0; i < 100001; i++)
    {
        i++;
        Sleep(100);
    }

    return 0;
}

// 1. Создание потока функцией CreateThread
HANDLE CreateThreadWrapper(LPTHREAD_START_ROUTINE threadProc, LPVOID threadParam) {

    HANDLE hThread = CreateThread(nullptr, 0, threadProc, threadParam, 0, nullptr);
    if (hThread == nullptr) {
        cerr << "Ошибка при создании потока с CreateThread.\n";
        return nullptr;
    }

    return hThread;
}

// 2. Создание потока макрокомандой _beginthreadex
HANDLE BeginThreadWrapper(unsigned(__stdcall* threadProc)(void*), void* threadParam) {
    unsigned threadId = 0;
    HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, threadProc, threadParam, 0, &threadId);

    if (hThread == nullptr) {
        cerr << "Ошибка при создании потока с _beginthreadex.\n";
        return nullptr;
    }
         
    return hThread;
}

// 3. Завершение потоков функцией TerminateThread
bool TerminateThreadWrapper(HANDLE hThread, DWORD exitCode, int i) {
   
    if (TerminateThread(hThread, exitCode)) {
       
        cout << "Поток " << i << " завершен с помощью TerminateThread.\n";
        return true;
        
    }
    else {
        cerr << "Ошибка при завершении потока с TerminateThread.\n";
        return false;
    }
}

// 4. Приостановка и возобновление потоков
bool SuspendThreadWrapper(HANDLE hThread, int i) {

    if (SuspendThread(hThread) == -1) {
        cerr << "Ошибка при приостановке потока " << i << ".\n";
        return false;
    }
    else {
        cout << "Поток " << i << " приостановлен.\n";
        return true;
    }
}

bool ResumeThreadWrapper(HANDLE hThread,int i) {
    if (ResumeThread(hThread) != -1) {
        cout << "Поток " << i << " возобновлен.\n";
        return true;
    }
    else {
        cerr << "Ошибка при возобновлении потока" << i << ".\n";
        return false;
    }
}

// 5. Псевдодескрипторы потоков
DWORD GetCurrentThreadIdWrapper() {    
    cout << "Псевдодескриптор потоков.";
    return GetCurrentThreadId();
}

int main() {
 
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Создание потока с помощью CreateThread
    HANDLE hThread1 = CreateThreadWrapper(ThreadProc, reinterpret_cast<LPVOID>(1));  

    Sleep(2000);
  
    // Создание потока с помощью _beginthreadex
    HANDLE hThread2 = BeginThreadWrapper(_ThreadProc, reinterpret_cast<LPVOID>(2));
    Sleep(2000);

    cout << "\n";
    // Получение идентификатора текущего потока  
    cout << "\nИдентификатор текущего потока: " << GetCurrentThreadIdWrapper() << endl;
    
    Sleep(2000);    

    cout << "\n";
    // Приостановка и возобновление потока
    SuspendThreadWrapper(hThread1, 1);
    ResumeThreadWrapper(hThread1, 1);

    cout << "\n";
    // Приостановка и возобновление потока
    SuspendThreadWrapper(hThread2, 2);
    ResumeThreadWrapper(hThread2, 2);
       
    cout << "\n";
    // Завершение потока с помощью TerminateThread
    TerminateThreadWrapper(hThread1, 0, 1);
    TerminateThreadWrapper(hThread2, 0, 2);

    // Ожидание завершения потоков
    WaitForSingleObject(hThread2, INFINITE);
  
    cout << "\n";
    // Закрытие дескрипторов потоков
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    
    cout << "Главный поток завершен.\n";
    return 0;
}
