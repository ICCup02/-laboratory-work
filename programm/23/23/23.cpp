#include <iostream>
#include <string>
using namespace std;
bool polinom(char* a, int n) {
	bool o = 0;
	for (int i = 0, k = n - 1; i < n && k >= 0;)
	{
		o = 0;
		if (k == i) { o = 12; break; }
		if ((a[k] < 48) || (a[k] > 122) || ((a[k] > 90) && (a[k] < 97)) || ((a[k] < 65) && (a[k] > 57))) {
			k--; continue;
		}
		else
			if ((a[i] < 48) || (a[i] > 122) || ((a[i] > 90) && (a[i] < 97)) || ((a[i] < 65) && (a[i] > 57))) {
				i++; continue;
			}
		if ((a[i] == a[k] - 32) || (a[i] == a[k]) || (a[i] == a[k] + 32)) { o = 1; i++; k--; }
		else i = n;
	}
	return o;

}
int main() {
	setlocale(LC_ALL, "RUS");
	char a[21];
	cin.getline ( a,21);
	int i = strlen(a);
	if (polinom(&a[0], i)) {
		cout << "Палиндром";
	}
	else cout << "Не палиндром";
	// //a==97 z=122 A==65 0==48 ; 9 =57;Z==90
}