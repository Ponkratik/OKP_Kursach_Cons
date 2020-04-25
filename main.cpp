#include <iostream>
#include <string>
#include "auth.h"
#include "sells.h"
#include "Windows.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (true)
	{
		int Role = 0;
		Role = Loginning();

		ShowMainMenu(Role);
	}
}