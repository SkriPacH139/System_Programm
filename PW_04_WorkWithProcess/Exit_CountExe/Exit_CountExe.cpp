#include <iostream>
#include <Windows.h>

using namespace std;

volatile UINT cnt;

void thread() {
	for (; ;)
	{
		cnt++;
		Sleep(100);
	}
}


//Создание счетчика и завершение процесса через ExitProcess;
int main()
{
	char sym;

	HANDLE hThread;
	DWORD IDThread;

	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0, &IDThread);

	if (hThread == NULL)
		return GetLastError();

	for (; ;)
	{
		cout << "Input 'y' to display count or any char for exit: ";
		cin >> sym;
		if (sym == 'y')
			cout << "count = " << cnt << endl;

		else
			ExitProcess(1);
	}
}
