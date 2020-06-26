#include<string>
#include <iostream>
#include<vector>
std::string map[25] = {
"####B######################",
"# #       #   #      #    #",
"# # # ###### #### ####### #",
"# # # #       #   #       #",
"#   # # ######### # ##### #",
"# # # #   #       #     # #",
"### ### ### ############# #",
"# #   #     # #           #",
"# # #   ####### ###########",
"# # # #       # #         C",
"# # ##### ### # # ####### #",
"# # #     ### # #       # #",
"#   ##### ### # ######### #",
"######### ### #           #",
"# ####### ### #############",
"A           #   ###   #   #",
"# ############# ### # # # #",
"# ###       # # ### # # # #",
"# ######### # # ### # # # F",
"#       ### # #     # # # #",
"# ######### # ##### # # # #",
"# #######   #       #   # #",
"# ####### ######### #######",
"#         #########       #",
"#######E############D######"
};
struct Coordinate {
	int X, Y;
	Coordinate(int x, int y) {
		X = x; Y = y;
	}
};
std::vector<Coordinate> Close;
bool CheckWrongData(int x, int y) {
	if ((x < 25) && (x >= 0) && (y < 27) && (y >= 0))
		return true;
	else return false;
}
void Search(int x, int y) {


	if (CheckWrongData) {
		for (int i = 0; i < Close.size(); i++) {
			if ((x == Close[i].X) && (y == Close[i].Y))
			return;
		}
		if ((map[x][y] != '#') && (map[x][y] != ' ')) {
			std::cout << map[x][y] << "\n";
		}
		else if (map[x][y] == ' ') {
			Coordinate temp(x,y);
			Close.push_back(temp);
			Search(x - 1, y);
			Search(x + 1, y);
			Search(x, y - 1);
			Search(x, y + 1);
		}
	}
}
int main()
{
	int x, y;
	std::cout << "Write the column you would like to start with: ";
	std::cin >> x;
	std::cout << "Write the line you would like to start with: ";
	std::cin >> y;
	if (CheckWrongData) {
		if (map[x][y] == '#') {
			std::cout << "You entered incorrect data";
			return EXIT_FAILURE;
		}
	}
	Search(x, y);
}
