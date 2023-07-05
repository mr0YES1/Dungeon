#pragma once

#include "Skeleton.h" // Подключаем класс скелета

class Coffin
{
	friend class Skeleton;							  // Дружит с классом скелета

private:

	TmxObject coffin;								  // Создаем объект карты гроб
	
	Texture coffinTexture;		                      // Создаём текстуру спрайта

	float hit;										  // Создаем переменную отвечающую за количество ударов

	bool  hited;									  // Создаем переменную отвечающую за удар

	void collisionWithACharacter(Skeleton& skeleton); // Проверка на столкновение с персонажем
	
public:

	Sprite coffinSprite;							  // Создаем спрайт

	void Constructor(TmxLevel& Level, string num);	  // Конструктор объекта

	void update(Skeleton& skeleton);				  // Функция обновления объекта
};