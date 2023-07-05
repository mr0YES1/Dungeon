#pragma once

#include "TmxLevel.h" // Библиотека для чтения карт
#include <vector>     // Подключаем векторы

using namespace sf;  // Устанавливаем пространство имен sf
using namespace std; // Устанавливаем пространство имен std

////////////////////////////////////ОБЩИЙ КЛАСС-РОДИТЕЛЬ//////////////////////////
class Entity
{
protected:

	vector <TmxObject> solidObject;			   // Создаем общую переменную объектов стены карты

	float dx, dy, x, y, speed;				   // Создаем общие переменные направление по x, y; а так-же координаты x, y и скорость

	int w, h;								   // Создаем общие переменные ширина и высота

	void generalСonstructor(float X, float Y); // Конструктор общего класса

public:

	float currentFrame;              // Создаем общую переменную раскадровщик

	bool goingForward;               // Создаем общую переменную направление
	
	FloatRect getRect(bool changeTheWidth = false, int X = 0, int W = 0, bool changeTheHeight = false, int Y = 0, int H = 0); // Функция передачи координат и размеров объекта
};