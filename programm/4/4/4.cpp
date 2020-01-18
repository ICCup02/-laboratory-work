#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int	first;
	int	second;
	int	temp;
	cout << "Введите значение переменных: " << endl;
	cin >> first >> second;
	temp = second;
	second = first;
	first = second;
	cout << "Первая переменная: " << first << endl << "Вторая переменная: " << second << endl;
	system("pause");
	return 0;
}