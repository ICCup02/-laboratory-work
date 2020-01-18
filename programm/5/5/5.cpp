#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	double	x_0, v_0, t;
	double	a = -9.8;
	double	result, resulttwo;
	cout << "Введите значение x0, v0, t: " << endl;
	cin >> x_0 >> v_0 >> t;
	result = x_0 + (v_0 * t) + ((a * pow(t, 2)) / 2);
	resulttwo = x_0 + (v_0 * t) + 1 / 2.0 * ((a * pow(t, 2)));
	cout << endl << "Результат вычислений: " << result << endl << resulttwo << endl;
	return 0;
}