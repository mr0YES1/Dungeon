#pragma once

#include "Entity.h"   // Подключаем общий класс родителя
#include "Skeleton.h" // Подключаем класс скелета

//////////////////////////////////////////////КЛАСС ЛЕТУЧЕЙ МЫШИ////////////////////////
class Bat : public Entity
{
	friend class Skeleton;							  // Дружит с классом скелета
	friend class Level_1;							  // Дружит с классом 1-го уровня
	friend class Level_2;							  // Дружит с классом 2-го уровня

private:

	TmxObject wakeUpTheBat;                           // Создаём пробуждение для летучей мыши

	Texture batTextures[5];		                      // Создаём массив текстур спрайта

	enum { wake, walk, attack, dies, hit } state;	  // Перечисляем статусы летучей мыши: пробуждение, прогулака, атака, смерть, удар 

	int health;										  // Создаём здоровье

	bool sleep;					                      // Создаем переменную, которая отслеживает сон
	bool dead;										  // Создаем переменную, которая отслеживает смерть

	void checkCollisionWithMap();                     // Проверка на столкновение со стенами

	void collisionWithACharacter(Skeleton& skeleton); // Проверка на столкновение с персонажем

public:

	Sprite batSprite;									             // Создаем спрайт

	void Constructor(TmxLevel& Level, float X, float Y, string num); // Конструктор персонажа

	void update(Skeleton& skeleton, float time);		             // Функция обновления персонажа
};
