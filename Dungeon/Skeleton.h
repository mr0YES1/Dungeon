#pragma once

#include "Entity.h" // Подключаем общий класс родителя

//////////////////////////////////////////////КЛАСС-СКЕЛЕТА////////////////////////
class Skeleton : public Entity
{
	friend class Bat;														// Дружит с классом летучей мыши
	friend class Coffin;													// Дружит с классом гробом 

private:

	Texture skeletonTextures[6];											// Задаем текстуры спрайту

	enum { stay, left, right, up, down, attack, reborn, react, hit } state; // Перечисляем статусы скелета: стоит, влево, вправо, вверх, вниз, атакует, перерождается, реагирует, ударяется 

	enum { revive, dies, alive, dead } rebirthStatus;						// Перечисляем статусы перерождения: оживает, умирает, жив, мертв

	void control();															// Контроллер персонажа

	void checkCollisionWithMap(float Dx, float Dy);							// Проверка на столкновение

	void cancellationOfActions();											// Метод отмены действия

	void repulsion(FloatRect rect);											// Метод отталкивания

public:
	
	Sprite skeletonSprite;													// Создаем спрайт
	
	void Constructor(TmxLevel& Level_1, float X, float Y);					// Конструктор персонажа

	void update(float time);												// Функция обновления персонажа

	float getPlayerCoordinateX();											// Метод передачи координаты x

	float getPlayerCoordinateY();											// Метод передачи координаты y
};