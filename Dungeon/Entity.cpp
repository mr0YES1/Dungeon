#include "Entity.h" // Подключаем общий класс родителя

void Entity::generalСonstructor(float X, float Y) // Конструктор общего класса
{
	dx    = 0;			  // Задаем направление по x
	dy    = 0;			  // Задаем направление по y
	x     = X;            // Задаем координаты x
	y     = Y;            // Задаем координаты y
	speed = 0;		      // Задаем скорость

	currentFrame = 0;     // Задаем значение раскадровщику

	w = 1;				  // Задаем ширину
	h = 1;				  // Задаем высоту

	goingForward = true;  // Задаем направление движения
}

FloatRect Entity::getRect(bool changeTheWidth, int X, int W, bool changeTheHeight, int Y, int H)  // Функция передачи координат и размеров объекта
{
	if (changeTheWidth && changeTheHeight)    // Если изменяем ширину и высоту
	{
		return FloatRect(x + X, y + Y, W, H); // Возвращаем координаты и размеры объекта
	}
	else if (changeTheWidth)				  // Если изменяем ширину
	{
		return FloatRect(x + X, y, W, h);	  // Возвращаем координаты и размеры объекта
	}
	else if (changeTheHeight)				  // Если изменяем высоту					
	{
		return FloatRect(x, y + Y, w, H);	  // Возвращаем координаты и размеры объекта
	}
	else									  // Если ничего не изменяем
	{
		return FloatRect(x, y, w, h);		  // Возвращаем координаты и размеры объекта
	}
}