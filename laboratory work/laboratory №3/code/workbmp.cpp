#include <iostream>
#include<string>
#include "libbmp.h"
#include<fstream>
int8_t defcolor(int& x, int& y, BmpImg& img) {
	static int8_t count = 1;
	if (count == 1) {
		count = 2;
		return img.red_at(x, y);
	}
	else if (count == 2) {
		count = 3;
		return img.green_at(x, y);
	}
	count = 1;
	return img.blue_at(x, y);
};
int main()
{
	std::ofstream out;
	std::string msg;
	uint8_t letter = 0;
	BmpImg img;
	int8_t bit = 0;
	img.read("pic1.bmp");
	if (BMP_OK != 0) { return EXIT_FAILURE; }
	for (int y = img.get_height() - 1, x; y >= 0; y--)
	{
		for (x = img.get_width() - 1; x >= 0; x--)
		{
			for (int rgb = 0; rgb < 3; rgb++) {
				letter = (letter << 1) | (defcolor(x, y, img) & 1); bit++;
				if (bit == 8) {
					if ((letter & 255) == '\0' ) {
						out.open("output.txt");
						out << msg;
						out.close();return EXIT_SUCCESS;
					}
					msg = msg + static_cast<char>(letter); bit = 0;
					letter = 0;
				}
			}
		}
	}
	return EXIT_SUCCESS;
}