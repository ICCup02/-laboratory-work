#include<iostream>
#include "implementation.h"
int main() {
	char userchar;
	Game game;
	std::cout << "Enter a character for player X or 0: ";

	std::cin >> userchar;
	while ((userchar != 'X') && (userchar != '0')) {
		std::cout << "\n Enter a character for player X or 0: ";

		std::cin >> userchar;
	}
	game = initGame(userchar);
	int i = 0;
	while (game.status==PLAY) {
		updateDisplay(game);
		updateGame(&game);
	}
	if (game.status == USER_WIN) { std::cout << "Congratulations you won!!!\n"; }
	else if (game.status == BOT_WIN) std::cout << "The bot won!\n";
	else {
		std::cout << "Draw!\n";
	}
	std::cout << "Want to play again? (1-yes, any other character-no) ";
	std::cin >> i;
	if (i == 1) { main(); }
	return EXIT_SUCCESS;
}