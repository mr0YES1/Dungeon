#include "Skeleton.h" // Подключаем класс скелета

void Skeleton::Constructor(TmxLevel& Level_1, float X, float Y) // Конструктор скелета
{
	generalСonstructor(X, Y);												 // Запускаем общий конструктор
	
	solidObject = Level_1.GetAllObjects("solid");							 // Получаем все объекты стены

	skeletonTextures[0].loadFromFile("Images/Skeleton/Skeleton_Idle.png");   // Получаем анимацию пасивности
	skeletonTextures[1].loadFromFile("Images/Skeleton/Skeleton_Walk.png");   // Получаем анимацию прогулки
	skeletonTextures[2].loadFromFile("Images/Skeleton/Skeleton_Attack.png"); // Получаем анимацию атаки 
	skeletonTextures[3].loadFromFile("Images/Skeleton/Skeleton_React.png");  // Получаем анимацию реакции 
	skeletonTextures[4].loadFromFile("Images/Skeleton/Skeleton_Dead.png");   // Получаем анимацию смерти
	skeletonTextures[5].loadFromFile("Images/Skeleton/Skeleton_Hit.png");    // Получаем анимацию удара

	speed = 26;				// Устанавливаем скорость

	state         = stay;   // Устанавливаем стандартный статус -> стойка
	rebirthStatus = alive;  // Устанавливаем стандартный статус перерождения -> жив
	
	skeletonSprite.setPosition(x, y); // Устанавливаем позицию скелета
}

void Skeleton::control() // Контроллер скелета
{
	if ((state != attack) && (rebirthStatus != revive) && (rebirthStatus != dies) && (state != react)  && (state != hit)) // Если игрок не бьет, не умирает/оживает, не реагирует и не ударяется 
	{
		if ((!(Keyboard::isKeyPressed(Keyboard::D))) && (Keyboard::isKeyPressed(Keyboard::A)))	    // Движение влево
		{
			if (rebirthStatus == dead)  // Если игрок мертв
			{
				state         = reborn;	// Статус -> перерождение
				rebirthStatus = revive; // Игрок оживает
				currentFrame  = 15;		// Раскадровщик идет в обратную сторону
			}
			else
			{
				state = left;			// Статус -> движение влево
			}
		}
		else if ((!(Keyboard::isKeyPressed(Keyboard::A))) && (Keyboard::isKeyPressed(Keyboard::D))) // Движение вправо
		{
			if (rebirthStatus == dead)  // Если игрок мертв
			{
				state         = reborn;	// Статус -> перерождение
				rebirthStatus = revive; // Игрок оживает
				currentFrame  = 15;		// Раскадровщик идет в обратную сторону
			}
			else
			{
				state = right;			// Статус -> движение вправо
			}
		}
		else if ((!(Keyboard::isKeyPressed(Keyboard::S))) && (Keyboard::isKeyPressed(Keyboard::W))) // Движение вверх
		{
			if (rebirthStatus == dead)  // Если игрок мертв
			{
				state         = reborn;	// Статус -> перерождение
				rebirthStatus = revive; // Игрок оживает
				currentFrame  = 15;		// Раскадровщик идет в обратную сторону
			}
			else
			{
				state = up;				// Статус -> движение вверх
			}
		}
		else if ((!(Keyboard::isKeyPressed(Keyboard::W))) && (Keyboard::isKeyPressed(Keyboard::S))) // Движение вниз
		{
			if (rebirthStatus == dead)  // Если игрок мертв
			{
				state         = reborn;	// Статус -> перерождение
				rebirthStatus = revive; // Игрок оживает
				currentFrame  = 15;		// Раскадровщик идет в обратную сторону
			}
			else
			{
				state = down;			// Статус -> движение вниз
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Left)) // Нажатие левой кнопки мыши (удар)
		{
			if (rebirthStatus == dead)  // Если игрок мертв
			{
				state         = reborn;	// Статус -> перерождение
				rebirthStatus = revive; // Игрок оживает
				currentFrame  = 15;		// Раскадровщик идет в обратную сторону
			}
			else
			{
				state        = attack;	// Статус -> атака
				currentFrame = 0;		// Обнуляем раскадровщик
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::R)) // Нажатие клавиши R позволяет перерождать персонажа
		{
			if (rebirthStatus == dead)		 // Если игрок мёртв
			{
				rebirthStatus = revive;		 // Оживает
				currentFrame  = 15;			 // Раскадровщик идет в обратную сторону
			}
			else if (rebirthStatus == alive) // Если игрок жив
			{
				rebirthStatus = dies;		 // Умирает
				currentFrame  = 1;			 // Раскадровщик идет сначала
			}

			state = reborn;                  // Статус -> перерождение
		}
		else // В остальных случая проверяем на статику скелета
		{
				if (rebirthStatus == alive) state = stay; // Если персонаж жив, то он стоит на месте
		}
	}
}

void Skeleton::checkCollisionWithMap(float Dx, float Dy) // Проверка на столкновение со стеной
{
	for (int i = 0; i < solidObject.size(); i++)		 // Проходим по объектам стены
	{
		if (getRect().intersects(solidObject[i].rect))   // Если происходит столкновение
		{
			if ((state == attack) || (rebirthStatus == revive) || (rebirthStatus == dies)) // Если сражается или умирает/оживает
			{
				cancellationOfActions();												   // То отменяем действия
			}
			else																		   // Иначе                                                                            
			{
				repulsion(solidObject[i].rect);											   // Иначе отталкиваем от стены		
			}
		}
	}
}

void Skeleton::cancellationOfActions()
{
	state         = react; // Статус -> реакция
	rebirthStatus = alive; // Игрок жив 
	currentFrame  = 1;	   // Обнуляем раскадровщик

	skeletonSprite.setOrigin(sf::Vector2f(0, 32));  // Задаем координаты отрисовки спрайта скелета
	skeletonSprite.setTexture(skeletonTextures[3]); // Задаем анимацию реакции

	goingForward ? skeletonSprite.setTextureRect(IntRect(0, 0, 22, 32)) :   // Если до этого двигались прямо, то персонаж будет смотреть прямо
					skeletonSprite.setTextureRect(IntRect(22, 0, -22, 32)); // Иначе назад
}

void Skeleton::repulsion(FloatRect rect)
{
	if (dy > 0) { y = rect.top; dy = 0; }                   // Если движение вниз
	if (dy < 0) { y = rect.top + rect.height - h; dy = 0; } // Если движение вверх
	if (dx > 0) { x = rect.left - w; dx = 0; }              // Если движение вправо
	if (dx < 0) { x = rect.left + rect.width; dx = 0; }     // Если движение влево
}

void Skeleton::update(float time) // Функция обновления персонажа
{
	control();     // Просматриваем статусы скелета

	switch (state) // Перебираем статусы
	{
	case left:     // Если двигаемся влево

		skeletonSprite.setOrigin(sf::Vector2f(0, 33));  // Задаем координаты отрисовки спрайта скелета
		skeletonSprite.setTexture(skeletonTextures[1]); // Задаем анимацию ходьбы 

		currentFrame += 13 * time;                                                       // Скорость анимации 13 кадров в секунду
		if (currentFrame > 13) currentFrame = 0;                                         // Обнуляем раскадровщик при окончании анимации 
		skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22 + 22, 0, -22, 33)); // Отрисовывем персонажа

		w  = 22;     // Задаем ширину
		h  = -2;     // Задаем высоту
		dx = -speed; // Задаем скорость по x 
		dy = 0;      // Задаем скорость по y

		goingForward = false; // Направление назад

		break;                // Завершаем проверку

	case right:    // Если двигаемся вправо

		skeletonSprite.setOrigin(sf::Vector2f(0, 33));  // Задаем координаты отрисовки спрайта скелета
		skeletonSprite.setTexture(skeletonTextures[1]); // Задаем анимацию ходьбы  

		currentFrame += 13 * time;												   // Скорость анимации 13 кадров в секунду
		if (currentFrame > 13) currentFrame = 0;                                   // Обнуляем раскадровщик при окончании анимации
		skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22, 0, 22, 33)); // Отрисовывем персонажа

		w  = 22;    // Задаем ширину
		h  = -2;    // Задаем высоту 
		dx = speed; // Задаем скорость по x
		dy = 0;     // Задаем скорость по y

		goingForward = true; // Направление вперед

		break;               // Завершаем проверку

	case up:       // Если двигаемся вверх

		skeletonSprite.setOrigin(sf::Vector2f(0, 33));  // Задаем координаты отрисовки спрайта скелета
		skeletonSprite.setTexture(skeletonTextures[1]); // Задаем анимацию ходьбы 

		currentFrame += 13 * time;																		 // Скорость анимации 13 кадров в секунду
		if (currentFrame > 13) currentFrame = 0;														 // Обнуляем раскадровщик при окончании анимации
		goingForward ? skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22, 0, 22, 33)) :       // Если до этого двигались прямо, то персонаж будет смотреть прямо
						skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22 + 22, 0, -22, 33)); // Иначе назад

		w  = 22;     // Задаем ширину
		h  = -2;     // Задаем высоту
		dx = 0;      // Задаем скорость по x
		dy = -speed; // Задаем скорость по y

		break;      // Завершаем проверку

	case down:     // Если двигаемся вниз

		skeletonSprite.setOrigin(sf::Vector2f(0, 33));  // Задаем координаты отрисовки спрайта скелета
		skeletonSprite.setTexture(skeletonTextures[1]); // Задаем анимацию ходьбы 

		currentFrame += 13 * time;																		 // Скорость анимации 13 кадров в секунду
		if (currentFrame > 13) currentFrame = 0;														 // Обнуляем раскадровщик при окончании анимации
		goingForward ? skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22, 0, 22, 33)) :       // Если до этого двигались прямо, то персонаж будет смотреть прямо
						skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22 + 22, 0, -22, 33)); // Иначе назад

		w  = 22;    // Задаем ширину
		h  = -2;    // Задаем высоту
		dx = 0;     // Задаем скорость по x
		dy = speed; // Задаем скорость по y

		break;      // Завершаем проверку

	case attack:   // Если атакуем

		goingForward ? skeletonSprite.setOrigin(sf::Vector2f(3, 37)) : // Задаем координаты отрисовки спрайта скелета
			skeletonSprite.setOrigin(sf::Vector2f(18, 37));

		skeletonSprite.setTexture(skeletonTextures[2]);				   // Задаем анимацию удара 

		currentFrame += 18 * time; // Скорость анимации 18 кадров в секунду

		if (currentFrame > 18)     // Если доходим до конца анимации
		{
			currentFrame = 0;      // Обнуляем раскадровщик
			state = stay;		   // Устанавливаем стандартный статус -> стойка
		}

		goingForward ? skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 43, 0, 43, 37)) :       // Если до этого двигались прямо, то персонаж будет смотреть прямо
						skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 43 + 43, 0, -43, 37)); // Иначе назад

		goingForward ? w = 40 : w = -18; // Задаем ширину
		h  = -2;                         // Задаем высоту
		dx = 0;                          // Задаем скорость по x
		dy = 0;                          // Задаем скорость по y

		break;                           // Завершаем проверку

	case reborn:   // Если перерождается

		goingForward ? skeletonSprite.setOrigin(sf::Vector2f(11, 32)) : // Задаем координаты отрисовки спрайта скелета
			skeletonSprite.setOrigin(sf::Vector2f(0, 32));

		skeletonSprite.setTexture(skeletonTextures[4]);					// Задаем анимацию перерождения

		if (rebirthStatus == dies)         // Если статус возрождения -> умирает
		{
			currentFrame += 15 * time;     // Скорость анимации 15 кадров в секунду

			if (currentFrame > 15)         // Если доходим до конца анимации
			{
				currentFrame = 14;	       // Ставим последний возможный кадр раскадровщика
				rebirthStatus = dead;	   // Cтатус возрождения -> мертв 
			}
		}
		else if (rebirthStatus == revive)  // Если статус возрождения -> возрождается
		{
			currentFrame -= 15 * time;	   // Скорость анимации 15 кадров в секунду

			if (currentFrame < 1)		   // Если доходим до конца анимации
			{
				currentFrame = 1;		   // Ставим последний возможный кадр раскадровщик 
				rebirthStatus = alive;     // Cтатус возрождения -> жив
			}
		}
		else if (rebirthStatus == dead)    // Иначе если он просто мертв
		{
			currentFrame = 14;			   // Раскадровщик не изменяется
		}

		goingForward ? skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 33, 0, 33, 32)) :		 // Если до этого двигались прямо, то персонаж будет смотреть прямо
						skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 33 + 33, 0, -33, 32)); // Иначе назад 

		goingForward ? w = -11 : w = 33; // Задаем ширину
		h  = -2;						 // Задаем высоту
		dx = 0;							 // Задаем скорость по x
		dy = 0;							 // Задаем скорость по y

		break;							 // Завершаем проверку 

	case react:    // Если реагирует

		currentFrame += 8 * time; // Скорость анимации 8 кадров в секунду 
		if (currentFrame > 4)     // Если доходим до конца анимации
		{
			currentFrame = 0;	  // Обнуляем раскадровщик
			state = stay;		  // Устанавливаем стандартный статус -> стойка 
		}
		goingForward ? skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22, 0, 22, 32)) :       // Если до этого двигались прямо, то персонаж будет смотреть прямо
						skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22 + 22, 0, -22, 32)); // Иначе назад  

		w  = 22;  // Задаем ширину
		h  = -2; // Задаем высоту
		dx = 0;  // Задаем скорость по x
		dy = 0;  // Задаем скорость по y

		break;   // Завершаем проверку

	case hit:

		goingForward ? skeletonSprite.setOrigin(sf::Vector2f(6, 32)) : // Задаем координаты отрисовки спрайта скелета
						skeletonSprite.setOrigin(sf::Vector2f(2, 32));

		skeletonSprite.setTexture(skeletonTextures[5]);				   // Задаем анимацию удара 

		currentFrame += 12 * time;  // Скорость анимации 12 кадров в секунду
		if (currentFrame > 8)	   // Если доходим до конца анимации
		{
			state         = stay;  // Устанавливаем стандартный статус -> стойка
			rebirthStatus = alive; // Cтатус возрождения -> жив
			currentFrame  = 0;     // Обнуляем раскадровщик
		}
		goingForward ? skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 30, 0, 30, 32)) :		 // Если до этого двигались прямо, то персонаж будет смотреть прямо
						skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 30 + 30, 0, -30, 32)); // Иначе назад 

		w  = 0; // Задаем ширину
		h  = 0; // Задаем высоту
		dx = 0; // Задаем скорость по x
		dy = 0; // Задаем скорость по y

		break;  // Завершаем проверку 
	
	case stay:     // Если стоит

		goingForward ? skeletonSprite.setOrigin(sf::Vector2f(0, 32)) : // Задаем координаты отрисовки спрайта скелета
						skeletonSprite.setOrigin(sf::Vector2f(2, 32));

		skeletonSprite.setTexture(skeletonTextures[0]);				   // Задаем анимацию стойки 

		currentFrame += 11 * time;																		 // Скорость анимации 11 кадров в секунду
		if (currentFrame > 11) currentFrame = 0;														 // Обнуляем раскадровщик при окончании анимации
		goingForward ? skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 24, 0, 24, 32)) :		 // Если до этого двигались прямо, то персонаж будет смотреть прямо
						skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 24 + 24, 0, -24, 32)); // Иначе назад 

		w  = 22; // Задаем ширину
		h  = -2; // Задаем высоту
		dx = 0;  // Задаем скорость по x
		dy = 0;  // Задаем скорость по y

		break;   // Завершаем проверку
	}

	x += dx * time;					  // Задаем координаты x
	y += dy * time;					  // Задаем координаты y

	checkCollisionWithMap(dx, dy);    // Проверяем столкновение

	skeletonSprite.setPosition(x, y); // Задаем позицию скелета
}
 
float Skeleton::getPlayerCoordinateX() // Метод передачи координаты x
{
	return x; // Передаем x
}

float Skeleton::getPlayerCoordinateY() // Метод передачи координаты y
{
	return y; // Передаем y
}
