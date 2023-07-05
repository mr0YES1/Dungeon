#pragma once

#include "Bat.h"      // Подключаем класс летучей мыши
#include "Coffin.h"   // Подключаем класс гроба

class Level_1 // Первый уровень
{
private:

	TmxLevel Main_Objects; // Создаем -> основные объекты
	TmxLevel Decorations;  // Создаем -> декорации 
	TmxLevel Jug_1;		   // Создаем -> кувшин 1
	TmxLevel Jug_2;		   // Создаем -> кувшин 2
	TmxLevel Jug_3;		   // Создаем -> кувшин 3
	TmxLevel Candle_1;	   // Создаем -> свечи 1
	TmxLevel Candle_2;	   // Создаем -> свечи 2
	TmxLevel Coffin_2;	   // Создаем -> гроб 2
	TmxLevel Right_Wall;   // Создаем -> правую стену
	TmxLevel Lower_Wall;   // Создаем -> нижнюю стену

	TmxObject player;	   // Создаём игрока
	TmxObject enemy;	   // Создаём врага
	TmxObject exit;		   // Создаём выход

	bool characterDrawn;   // Отрисовка персонажа   

public:

	Skeleton skeleton;							  // Создаем скелета
	Bat bat;									  // Создаем летучую мышь
	Coffin coffin;								  // Создаем гроб

	Level_1();                                    // Конструктор первого уровня

	void update(int& level, float time);          // Обновление уровня

	void orderOfRenderings(RenderWindow& window); // Последовательность отрисовки
};

class Level_2 // Второй уровень
{
private:

	TmxLevel Main_Objects; // Создаем -> основные объекты
	TmxLevel Decorations;  // Создаем -> декорации
	TmxLevel Arches;	   // Создаем -> арку
	TmxLevel Jug_1;		   // Создаем -> кувшин 1
	TmxLevel Jug_2;		   // Создаем -> кувшин 2
	TmxLevel Jug_3;		   // Создаем -> кувшин 3
	TmxLevel Jug_4;		   // Создаем -> кувшин 4
	TmxLevel Jug_5;		   // Создаем -> кувшин 5
	TmxLevel Jug_6;		   // Создаем -> кувшин 6
	TmxLevel Jug_7;		   // Создаем -> кувшин 7
	TmxLevel Jug_8;		   // Создаем -> кувшин 8
	TmxLevel Jug_9;		   // Создаем -> кувшин 9
	TmxLevel Jug_10;	   // Создаем -> кувшин 10
	TmxLevel Candle_1;	   // Создаем -> свечи 1
	TmxLevel Candle_2;	   // Создаем -> свечи 2
	TmxLevel Candle_3;	   // Создаем -> свечи 3
	TmxLevel Candle_4;	   // Создаем -> свечи 4
	TmxLevel Coffin_1;	   // Создаем -> гроб 1
	TmxLevel Coffin_2;	   // Создаем -> гроб 2
	TmxLevel Chests;	   // Создаем -> ящики
	TmxLevel Lower_Wall;   // Создаем -> нижнюю стену

	TmxObject player;	   // Создаём игрока
	TmxObject enemy_1;	   // Создаём врага 1 
	TmxObject enemy_2;	   // Создаём врага 2
	TmxObject exit;		   // Создаём выход

	bool characterDrawn;   // Отрисовка персонажа   

public:

	Skeleton skeleton;							  // Создаем скелета
	Bat bat_1;									  // Создаем летучую мышь 1
	Bat bat_2;									  // Создаем летучую мышь 2 

	Level_2();									  // Конструктор второго уровня

	void update(int& level, float time);		  // Обновление уровня

	void orderOfRenderings(RenderWindow& window); // Последовательность отрисовки
};

class Level_3 // Третий уровень
{
private:

	TmxLevel Main_Objects;     // Создаем -> основные объекты
	TmxLevel Decorations;      // Создаем -> декорации
	TmxLevel Skeletal_Сorpses; // Создаем -> трупы скелетов
	TmxLevel Jug_1;			   // Создаем -> кувшин 1
	TmxLevel Jug_2;			   // Создаем -> кувшин 2
	TmxLevel Jug_3;			   // Создаем -> кувшин 3
	TmxLevel Jug_4;			   // Создаем -> кувшин 4
	TmxLevel Jug_5;			   // Создаем -> кувшин 5
	TmxLevel Jug_6;			   // Создаем -> кувшин 6
	TmxLevel Jug_7;			   // Создаем -> кувшин 7
	TmxLevel Candle_1;		   // Создаем -> свечи 1
	TmxLevel Candle_2;		   // Создаем -> свечи 2
	TmxLevel Candle_3;		   // Создаем -> свечи 3
	TmxLevel Chests_1;		   // Создаем -> ящики 1
	TmxLevel Chests_2;		   // Создаем -> ящики 2
	TmxLevel Wooden_Beams_1;   // Создаем -> деревянные балки 1
	TmxLevel Wooden_Beams_2;   // Создаем -> деревянные балки 2
	TmxLevel Lower_Wall;       // Создаем -> нижнюю стену

	TmxObject player;          // Создаём игрока

	bool characterDrawn;	   // Отрисовка персонажа   

public:

	Skeleton skeleton;							  // Создаем скелета

	Level_3();		 				              // Конструктор третьего уровня

	void update(float time);					  // Обновление уровня

	void orderOfRenderings(RenderWindow& window); // Последовательность отрисовки
};
