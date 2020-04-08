МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>
​
### Отчёт по лабораторной работе №4 <br/> по дисциплине "Программирование"
<br/>
​
студента 1 курса группы ИВТ-192(1)<br/>
Абибулаев Ремзи Энверовича 
направления подготовки 09.03.01 "Информатика и Вычислительная Техника"
<br/>
​
<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)<br/></td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>

Симферополь, 2019
<br/><br/>

**Цель:**
1. Закрепить навыки работы с перечислениями;
2. Закрепить навыки работы с структурами;
3. Освоить методы составления многофайловых программ.

**Ход работы:**
Создайть три файла:
1. Файл реализующий игру «Иксики-нолики» используя функции описанные в вспомогательном файле;
2. Вспомогательный файл. Содержит реализацию основных функций игры;
3. Заголовочный файл. Нужен для связи главного и вспомогательного файлов. 
 <br>

Итак, перейдем к выполнению заданий.
1. Главный файл содержащий функцию main():
```cpp
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

```
<br>

2. Вспомогательный файл содржащий реализацию основных функция implementation.cpp:

```cpp
#include<iostream>
#include<fstream>
#include<string>
#include <cstdlib>
#include <ctime> 
#include"implementation.h"
Game initGame(char& userChar) {
	srand(time(NULL));
	Game templ;
	for (int i = 0; i <= 2; i++)
	{
		for (int k = 0; k <= 2; k++)
			templ.bord[i][k] = ' ';
	}
	templ.isUserTurn = rand() % 2;
	templ.userChar = userChar;
	if (templ.userChar == '0') templ.botChar = 'X';
	else templ.botChar = '0';
	templ.status = PLAY;
	return templ;
};

void updateDisplay(const Game& game) {
	system("cls");
	std::cout << '\n';
	std::cout << "-----------------\n 1  | "
		<< game.bord[0][0] << " | " << game.bord[0][1] << " | " << game.bord[0][2] << " |\n"
		<< "-----------------\n 2  | "
		<< game.bord[1][0] << " | " << game.bord[1][1] << " | " << game.bord[1][2] << " |\n"
		<< "-----------------\n 3  | "
		<< game.bord[2][0] << " | " << game.bord[2][1] << " | " << game.bord[2][2] << " |\n"
		<< "-----------------\n";

};
void botTurn(Game* game) {
	srand(time(NULL));
	int i = 0, k = 0, counter = 0, firstxi = 0, firstxk = 0;
	while (!game->isUserTurn) {
		if ((counter > 0) && (game->bord[i][k] == game->userChar)) {
			// vertical |
			if ((firstxi == 0) && (k == firstxk) && (firstxi == (i - 2))) {
				if (game->bord[i - 1][k] == ' ') {
					game->isUserTurn = 1;
					game->bord[i - 1][k] = game->botChar;	break;
				}
			}
			if ((firstxi == 0) && (k == firstxk) && (firstxi == (i - 1))) {
				if (game->bord[i + 1][k] == ' ') {
					game->bord[i + 1][k] = game->botChar;
					game->isUserTurn = 1;	break;
				}
			}
			 if ((firstxi == 1) && (firstxk == k) && (i - firstxi == 1)) {
				if (game->bord[i - 2][k] == ' ') {
					game->bord[i - 2][k] = game->botChar;
					game->isUserTurn = 1;	break;
				}
			}
			// horizontal --
			if ((firstxk == 0) && (firstxi == i) && (firstxk == (k - 1))) {
				if (game->bord[i][k + 1] == ' ') {
					game->bord[i][k + 1] = game->botChar;
					game->isUserTurn = 1;	break;
				}
			}
			if ((firstxk == 0) && (firstxi == i) && (firstxk == (k - 2))) {

				if (game->bord[i][k - 1] == ' ') {
					game->bord[i][k - 1] = game->botChar;
					game->isUserTurn = 1;	break;
				}
			}
			 if ((firstxk == 1) && (firstxi == i) && (k - firstxk == 1)) {
				if (game->bord[i][k - 2] == ' ') {
					game->bord[i][k - 2] = game->botChar;
					game->isUserTurn = 1;	break;
				}
			}
			//diagonal \//
			 if ((firstxi == 0) && (firstxi == firstxk) && (i == k) && (firstxi == (i - 1) && (i > firstxi))) {
				if (game->bord[i + 1][k + 1] == ' ') {
					game->bord[i + 1][k + 1] = game->botChar;
					game->isUserTurn = 1;	break;
				}
			}
			 if ((firstxi == 0)&& (firstxi == firstxk) && (i == k) && (firstxi == (i - 2) && (i > firstxi))) {
				if (game->bord[i - 1][k - 1] == ' ') {
					game->bord[i - 1][k - 1] = game->botChar;
					game->isUserTurn = 1;	break;
				}
			}
			 if ((firstxi == 1) && (firstxi == firstxk) && (i == k) && (firstxi == (i - 1) && (i > firstxi))) {
				if (game->bord[i - 2][k - 2] == ' ') {
					game->bord[i - 2][k - 2] = game->botChar;
					game->isUserTurn = 1;	break;
				}
			}
			//diagonal /
			if ((firstxi == 0) && (i + k == 2) &&(firstxk==2)&& (firstxi == (i - 1))) {
				if (game->bord[i + 1][k - 1] == ' ') {
					game->bord[i + 1][k - 1] = game->botChar;
					game->isUserTurn = 1;	break;
				}
			}
			 if ((firstxi == 0) && (i + k == 2) && (firstxk == 2) && (firstxi == (i - 2))) {
				if (game->bord[i - 1][k + 1] == ' ') {
					game->bord[i - 1][k + 1] = game->botChar;
					game->isUserTurn = 1;	break;
				}
			}
			 if ((firstxi == 1) && (i == 2) && (firstxk == 1)) {
				if (game->bord[i - 2][k + 2] == ' ') {
					game->bord[i - 2][k + 2] = game->botChar;
					game->isUserTurn = 1;	break;
				}
			}
			 counter ++;
		}
		else if (game->bord[i][k] == game->userChar) {
			firstxi = i;
			firstxk = k;
			counter++;
		}
		k++;
		
		if ((i == 2) && (k == 3) && (counter > 1)) {
			if ((firstxi == 2) && (firstxk == 2)) { break; }
			if (firstxk == 2) { i = firstxi + 1; k = 0; counter = 0; }
			else {
				i = firstxi; k = firstxk + 1; counter = 0;
			}
		}

		if ((k == 3) && (i == 2)) { break; }
		if (k == 3) { i++; k = 0; }
	}
	//   рандомный ход
	i = 0; k = 0; counter = 0;
	while ((i != 3) && (!game->isUserTurn)) {
		if (game->bord[i][k] == ' ') { counter++; }
		k++;
		if (k == 3) { i++; k = 0; }
	}
	if ((counter == 9) && (game->bord[1][1] != game->userChar) && (!game->isUserTurn)) {
		game->bord[1][1] = game->botChar; game->isUserTurn = 1;
	}
	else if (!game->isUserTurn) {
		i = 0; k = 0; int random_number = rand() % counter + 1;
		std::cout << random_number;
		counter = 0;
		while (i != 3) {
			if (game->bord[i][k] == ' ') { counter++; }
			if (counter == random_number) { game->bord[i][k] = game->botChar; break; }
			k++;
			if (k == 3) { i++; k = 0; }
		}
	}
};

void userTurn(Game* game) {
	int i = 0, k = 0;
	std::cout << "Your move:";
	if (game->isUserTurn) {
		std::cin >> i >> k; i--; k--;
		if ((i >= 0) && (k >= 0) && (i <= 2) && (k <= 2) && (int(game->bord[i][k]) != int(game->botChar)) && (int(game->bord[i][k]) != int(game->userChar))) {
			game->bord[i][k] = game->userChar; game->isUserTurn = 0;
		}
		else { std::cout << "\nnot the right move, try again:"; userTurn(game); }
	}
};

bool updateGame(Game* game) {
	srand(time(NULL));
	int i = 0, k = 0, counterx = 0, counter0 = 0;
	while (true) {
		if (game->bord[i][k] == game->userChar) {
			counterx++;
		}
		if (game->bord[i][k] == game->botChar) {
			counter0++;
		}
		k++;
		if (counterx == 3) { game->status = USER_WIN; return true; }
		if (counter0 == 3) { game->status = BOT_WIN; return false; }
		if ((i == 2) && (k == 3)) { break; }
		if (k == 3) { i++; k = 0; counterx = 0; counter0 = 0; }
	}
	i = 0, k = 0, counterx = 0, counter0 = 0;
	while (true) {
		if (game->bord[i][k] == game->userChar) {
			counterx++;
		}
		if (game->bord[i][k] == game->botChar) {
			counter0++;
		}
		i++;
		if (counterx == 3) { game->status = USER_WIN; return true; }
		if (counter0 == 3) { game->status = BOT_WIN; return false; }
		if ((i == 3) && (k == 2)) { break; }
		if (i == 3) { k++; i = 0; counterx = 0; counter0 = 0; }
	}

	i = 0, k = 0, counterx = 0, counter0 = 0;
	while (true) {
		if (game->bord[i][k] == game->userChar) {
			counterx++;
		}
		if (game->bord[i][k] == game->botChar) {
			counter0++;
		}
		k++; i++;
		if (counterx == 3) { game->status = USER_WIN; return true; }
		if (counter0 == 3) { game->status = BOT_WIN; return false; }
		if ((i == 3) && (k == 3)) { break; }
	}
	i = 0, k = 2, counterx = 0, counter0 = 0;
	while (true) {
		if (game->bord[i][k] == game->userChar) {
			counterx++;
		}
		if (game->bord[i][k] == game->botChar) {
			counter0++;
		}
		k--; i++;
		if (counterx == 3) { game->status = USER_WIN; return true; }
		if (counter0 == 3) { game->status = BOT_WIN; return false; }
		if ((i == 3) && (k == -1)) { break; }
	}
	i = 0, k = 0;
	while (game->bord[i][k] != ' ') {
		k++;
		if ((i == 2) && (k == 3)) { game->status = NOT_WIN; return true; }
		if (k == 3) { i++; k = 0; }

	}
	if (game->isUserTurn) { userTurn(game); game->isUserTurn = false; game->status = PLAY; return false; }
	else { botTurn(game); game->isUserTurn = true; game->status = PLAY; return false; }
	game->status = PLAY;
	return false;
};

```   

3. И наконец заголовочный файл, (для защиты от повторного включения файла использую макрос ```#pragma once```):
```cpp
#pragma once 
enum Status {
	PLAY,            // Игра продолжается
	USER_WIN,        // Игрок победил
	BOT_WIN,         // Бот победил
	NOT_WIN
	// Ничья. Победителя нет, но и на поле нет свободной ячейки
};
struct Game {

	char bord[3][3];  // Игровое поле
	bool isUserTurn;  // Чей ход. Если пользователя, то isUserTurn = true
	char userChar;    // Символ которым играет пользователь
	char botChar;     // Символ которым играет бот
	Status status;
};
/**
* Выполняет следующие действия:
*  1. Очищает игровое поле заполняя его пробелами
*  2. Случайным образом определяет чей ход
*  3. Устанавливает символ для Игрока (Задаётся параметром userChar)
*  4. Устанавливает символ для бота
*  5. Возвращает заполненную структуру
*/
Game initGame(char &userChar);
/**
* Выполняет следующие действия:
*  1. Очищает экран
*  2. Отображает содержимое игрового поля. Например так (можно по своему):
*         a   b   c
*       -------------
*     1 | O | O | X |
*       -------------
*     2 |   |   |   |
*       -------------
*     3 |   |   | X |
*       -------------
*/
void updateDisplay(const Game& game);
/**
* Выполняет ход бота. В выбранную ячейку устанавливается символ которым играет бот.
* Бот должен определять строку, столбец или диагональ в которой у игрока больше всего иксиков/ноликов и ставить туда свой символ. Если на поле ещё нет меток, бот должен ставить свой знак в центр. В остальных случаях бот ходит рандомно.
*/
void botTurn(Game* game);
/**
* Функция отвечает за ход игрока. Если игрок вводит не допустимые
* значения, ругнуться и попросить ввести заново
*/
void userTurn(Game* game);
/**
* Функция определяет как изменилось состояние игры после последнего хода.
* Функция сохраняет новое состояние игры в структуре game и передаёт ход другому
* игроку.
* Функция возвращает true, если есть победитель или ничья, иначе false.
*/
bool updateGame(Game* game);
/* Состояния игры */
```
1. А вот и сам результат кода:
<center>
<img src="resources\images\1.PNG"><br>
Рис. 1. Иксики-нолики</center>

**Вывод:** Таким образом все цели и задачи лабораторной работы были выполнены в полном объеме. Были получены навыки работы с перечислениями, структурами. Освоил методы составления многофайловых программ. А также закрепляются знания в работе с markdown , C++.