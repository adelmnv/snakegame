#include <iostream>
#include<fstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
//Snake
int snake_size;
int change_x, change_y;
int coordinates_x[1000], coordinates_y[1000];
// Map
const int H = 30, W = 20;
int INTERVAL, level, rec;
char symbol;
int map[W][H];
bool game;

void standart_settings();
void change_direction();
void show_snake_on_table();
void clear_snake_on_table();
void clearScreen();
void generateFood();
void set_record();
int get_record();
void initMap();
char getMapValue(int v);
void printMap();
void move(int dx, int dy);
bool game_over();
bool check_coordinates();
void update();
void run();

int main()
{
	run();
	return 0;
}

void change_direction() {
	symbol = _getch();
	switch (symbol) {
	case 'w': if (change_x != 1 || change_y != 0) {
		change_x = -1; change_y = 0;
	}
			break;
	case 'a': if (change_x != 0 || change_y != 1) {
		change_x = 0; change_y = -1;
	}
			break;
	case 's': if (change_x != -1 || change_y != 0) {
		change_x = 1; change_y = 0;
	}
			break;
	case 'd': if (change_x != 0 || change_y != -1) {
		change_x = 0; change_y = 1;
	}
			break;
	default: break;
	}
}

void clearScreen()
{
	system("cls");
}

void generateFood()
{
	int x = 0;
	int y = 0;
	std::srand(std::time(NULL));
	do {
		x = rand() % (W - 1);
		y = rand() % (H - 1);
	} while (map[x][y] != 0);
	map[x][y] = -2;
}

void standart_settings() {
	snake_size = 2;

	coordinates_x[1] = 1;
	coordinates_y[1] = 2;
	coordinates_x[2] = 1;
	coordinates_y[2] = 1;
	map[1][2] = 2;
	map[1][1] = 1;
	change_x = 0;
	change_y = 1;
}
void initMap()
{
	game = true;
	for (size_t i = 0; i < W; i++)
	{
		for (size_t j = 0; j < H; j++)
		{
			if (i == 0 || j == 0 || i == W - 1 || j == H - 1)
				map[i][j] = -1;
			else
				map[i][j] = 0;
		}
	}
	standart_settings();
	generateFood();
}

char getMapValue(int v)
{
	if (v == -1)
		return '#';
	else if (v == -2)
		return '+';
	else if (v == 1)
		return '@';
	else if (v == 2)
	{
		if (change_x == 1 && change_y == 0)
			return 'v';
		if (change_x == -1 && change_y == 0)
			return '^';
		if (change_x == 0 && change_y == 1)
			return '>';
		if (change_x == 0 && change_y == -1)
			return'<';
	}
	else
		return ' ';

}

void printMap()
{
	map[0][0] = -1;
	for (size_t i = 0; i < W; i++)
	{
		for (size_t j = 0; j < H; j++)
		{
			std::cout << getMapValue(map[i][j]);
		}
		std::cout << '\n';
	}
}

void clear_snake_on_table() {
	for (int i = 1; i <= snake_size; ++i)
		map[coordinates_x[i]][coordinates_y[i]] = 0;
}

void show_snake_on_table() {
	map[coordinates_x[1]][coordinates_y[1]] = 2;
	for (int i = 2; i <= snake_size; ++i)
		map[coordinates_x[i]][coordinates_y[i]] = 1;
}

bool game_over()
{
	for (int i = 2; i <= snake_size; ++i)
	{
		if (coordinates_x[1] == coordinates_x[i] && coordinates_y[1] == coordinates_y[i])
			game = false;
	}
	return game;
}

bool check_coordinates() {
	if (coordinates_x[1] >= W - 1 || coordinates_x[1] < 1 || coordinates_y[1] >= H - 1 || coordinates_y[1] < 1)
		game = false;
	return game;
}
void move(int dx, int dy)
{
	clear_snake_on_table();

	for (int i = snake_size; i >= 2; --i) {
		coordinates_x[i] = coordinates_x[i - 1];
		coordinates_y[i] = coordinates_y[i - 1];
	}

	coordinates_x[1] += dx;
	coordinates_y[1] += dy;

	check_coordinates();

	if (map[coordinates_x[1]][coordinates_y[1]] == -2)
	{
		snake_size++;
		generateFood();
	}
	game_over();
	show_snake_on_table();
}

void update()
{
	std::cout << "hello everyone" << std::endl;
	move(change_x, change_y);
}

void set_record()
{
	if (snake_size > rec)
	{
		rec = snake_size;
		std::ofstream file("record.txt");

		if (!file.is_open())
			std::cout << "Error" << std::endl;
		else
		{
			file << rec;
		}
		file.close();
		std::cout << "CONGRATULATIONS YOU HAVE BROKEN THE RECORD!" << '\n';
		std::cout << "NOW THE RECORD IS " << rec;
	}

}
int get_record()
{
	std::ifstream fin;

	fin.open("record.txt");

	if (!fin.is_open())
	{
		std::cout << "Error" << std::endl;
	}
	else
	{
		int r;
		while (!fin.eof())
		{
			fin >> r;
		}
		rec = r;
	}
	fin.close();
	return rec;
}
void run()
{
	std::cout << "GAME RECORD = " << get_record() << '\n';
	std::cout << '\n';
	do
	{
		std::cout << "Choose level (1-3)" << std::endl;
		std::cin >> level;
	} while (level < 1 || level > 3);

	if (level == 1)
		INTERVAL = 200;
	else if (level == 2)
		INTERVAL = 100;
	else if (level == 3)
		INTERVAL = 50;


	initMap();
	while (game)
	{
		if (_kbhit())
			change_direction();
		update();
		clearScreen();
		printMap();
		Sleep(INTERVAL);

	}
	std::cout << '\n';
	std::cout << "YOU LOST!" << '\n';
	std::cout << "YOUR SCORE IS " << snake_size << '\n';
	set_record();
}
