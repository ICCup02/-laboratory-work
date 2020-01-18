#include <iostream>
using namespace std;
const int PREC_VAR = 5;

int main()
{
	double a, b, c, D, res;
	setlocale(LC_ALL, "Russian");
	std::cout.precision(PREC_VAR);
	cout << "Введите аргументы a,b,c:\n";
	cin >> a >> b >> c;
	if (a != 0) {
		D = b * b - 4 * a * c;
		if (D < 0) { cout << "Уравнение с заданными аргументами решения не имеет\n"; return 0; }
		cout << "Решение с аргументами a=" << a << "   b=" << b << "   c=" << c << ":\n";
		if (D == 0) {
			cout << "x = " << -b / (2 * a);
		}
		else {
			res = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
			cout << "x1 = " << res << endl;

			res = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
			cout << "x2 = " << res << endl;
		}
	}
	else {
		if (b != 0) {
			cout << "Решение с аргументами a=" << a << "   b=" << b << "   c=" << c << ":\n";
			res = -c / b;
			cout << "x = " << res;
		}
		else if ((b == 0) and (c == 0)) {
			cout << "Решение с аргументами a=" << a << "   b=" << b << "   c=" << c << ":\n";
			cout << "x = любое число";
		}
		else {
			cout << "[Ошибка]Вычисление невозможно при заданных аргументах\n";
		}
	}
}