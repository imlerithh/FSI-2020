#include <ctime>
#include <iostream>
extern "C"
{
	int _stdcall randomness()
	{
		srand(time(NULL));
		return rand() % 1000;
	}

	int _stdcall transformatio(char c) {
		return (int)c;
	}

	int _stdcall quadrum(int a)
	{
		return a * a;
	}

	void _stdcall outChar(char s)
	{
		setlocale(LC_ALL, "ru");
		std::cout << s << std::endl;
	}

	void _stdcall outInt(int a)
	{
		setlocale(LC_ALL, "ru");
		std::cout << a << std::endl;
	}

	void _stdcall outBool(int c)
	{
		setlocale(LC_ALL, "ru");
		if (c == 1)
			std::cout << "verum" << std::endl;
		else std::cout << "falsus" << std::endl;
	}
}
