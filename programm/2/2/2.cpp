#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	system("COLOR 02");
	int		firstint		= 3;
	int		secondint		= 3.14;
	double	firstdouble		= 3;
	double	seconddouble	= 3.14;
	cout	<< "INTEGER" << endl;
	cout	<< "Первая переменная = " << firstint << endl
			<< "Вторая переменная = " << secondint << endl;
	cout	<< endl; // Разделение между блоками
	cout	<< "DOUBLE" << endl;
	cout	<< "Первая переменная = " << firstdouble << endl
			<< "Вторая переменная = " << seconddouble << endl;
	system("pause");
	return 0;
}