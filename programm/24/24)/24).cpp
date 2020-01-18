#include <iostream>
size_t strlen(const char* string)
{
	int i = 0;
	while (string[i] != '\0')
	{
		i++;
	}
	return i;
}

char *strcats(char* combination, const char* srcptr)
{
	int max = strlen(combination) + strlen(srcptr) + 1;
	int one_longitude = strlen(combination);
	for (int i = one_longitude , count_srcptr = 0; i <= max; i++, count_srcptr++)
	{
		combination[i] = srcptr[count_srcptr];
	}
	combination[max] = '\0';
	return combination;
}

int strcmp(const char* string1, const char* string2)
{
	int i = 0;
	while ((string1[i] == string2[i]) && (string1[i] != '\0') && (string2[i] != '\0'))
	{
		i++;
	}
	if ((string1[i] == string2[i]) && (string1[i] == '\0') && (string2[i] == '\0')) { return 0; }
	if (string1 > string2) {
		return -1;
	}
	else return 1;
}

char *str_str(char *string1, const char* string2)
{
	int i = 0;
	int count = 0, p;
	while (strlen(string1) > i)
	{
		if (string1[i] == string2[count]) { count++; }
		else if (count != strlen(string2)) { count = 0; }

		if (count == strlen(string2)) { i++; break; }
		i++;
	}
	if ((count != strlen(string2)) && (string1[i] != string2[count])) { count = i + 1; }
	if (i - count<0) { return 0; }

	return 	string1+i-count ;

}

int main()
{
	setlocale(LC_ALL, "RUS");
	char* one = new char[50];
	std::cin.getline(one, 50);

	char* two = new char[50];
	std::cin.getline(two, 50);
	std::cout << strcmp(one, two);
	std::cout << std::endl << "str--->";
	int k = (str_str(one, two)-one);
	std::cout <<k;
	std::cout << std::endl;
	//std::cout << str_str(one, two) << std::endl;
	std::cout << strcats(one, two);
	delete[] one;
	delete[] two;

}
