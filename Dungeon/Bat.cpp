#include "Bat.h" // Подключаем класс летучей мыши

void Bat::Constructor(TmxLevel& Level, float X, float Y, string num) // Конструктор персонажа
{
	generalСonstructor(X, Y);								         // Запускаем общий конструктор
	
	solidObject  = Level.GetAllObjects("solid");		             // Получаем все объекты стены
	wakeUpTheBat = Level.GetFirstObject("wakeUpTheBat_" + num);      // Получаем с уровня объект пробуждение летучей мыши
	
	batTextures[0].loadFromFile("Images/Bat/Bat_wake.png");          // Получаем анимацию пробуждения
	batTextures[1].loadFromFile("Images/Bat/Bat_Walk.png");          // Получаем анимацию прогулки
	batTextures[2].loadFromFile("Images/Bat/Bat_Attack.png");        // Получаем анимацию атаки
	batTextures[3].loadFromFile("Images/Bat/Bat_Dead.png");          // Получаем анимацию смерти
	batTextures[4].loadFromFile("Images/Bat/Bat_Hit.png");           // Получаем анимацию удара

	state = wake; // Устанавливаем стандартный статус -> пробуждение

	health = 3;   // Задаём здоровье
	speed = 38;   // Устанавливаем скорость

	sleep = true; // Устанавливаем сон
	dead = false; // Устанавливаем отсутствие смерти

	batSprite.setPosition(x, y); // Устанавливаем позицию игрока
}

void Bat::checkCollisionWithMap() // Проверка на столкновение
{
	for (int i = 0; i < solidObject.size(); i++)									 // Проходим по объектам стены
	{
		if (getRect().intersects(solidObject[i].rect))								 // Если происходит столкновение
		{
			if (goingForward)														 // Если движение вперед
			{
				x            = solidObject[i].rect.left - w;						 // Отодвигаем летучую мышь
				dx           = 0;													 // Останавливаем летучую мышь
				goingForward = false;												 // Меняем направление
			}
			else
			{
				x            = solidObject[i].rect.left + solidObject[i].rect.width; // Отодвигаем летучую мышь
				dx           = 0;													 // Останавливаем летучую мышь
				goingForward = true;												 // Меняем направление
			}
		}
	}
}

void Bat::collisionWithACharacter(Skeleton& skeleton)
{
	if ((skeleton.getRect().intersects(wakeUpTheBat.rect)) // Если скелет разбудил летучую мышь
		&& (sleep)) sleep = false;						   // То она просыпается

	if (state != hit && state != dies)																				 // Если не ударились и не умираем
	{																												
		if ((skeleton.state == Skeleton::attack) && (int(skeleton.currentFrame) == 7) &&							 // Проверка попадания летучей мыши 
			(skeleton.goingForward ? skeleton.getRect(true,  33, 2).intersects(getRect(false, 0, 0, true, 4, -27)) : // В зону нанесения скелетом урона
									 skeleton.getRect(true, -11, 2).intersects(getRect(false, 0, 0, true, 4, -27))))	
		{
				state = hit;		
				currentFrame = 0;
		}
		else if (skeleton.goingForward ? skeleton.getRect(true, 0, 18).intersects(goingForward ? getRect(true, 22, 2, true, 4, -27) : getRect(true, -2, -2, true, 4, -27)) : // Проверяем столкновение скелета и летучей мыши 
										 skeleton.getRect(true, 4, 18).intersects(goingForward ? getRect(true, 22, 2, true, 4, -27) : getRect(true, -2, -2, true, 4, -27)))
		{
			if ((skeleton.state != Skeleton::reborn) || ((skeleton.state == Skeleton::reborn) // Если статус скелета не перерождение
				&& (int(skeleton.currentFrame) >= 0) && (int(skeleton.currentFrame) <= 9)))	  // Или если статус скелета перерождение и он его заканчивает								  
			{
				if (state != attack)														  // Если статус летучей мыши не атакует
				{
					state = attack;															  // Статус летучей мыши -> атака
					currentFrame = 0;														  // Обнуляем раскадровщик летучей мыши
				}
				if ((skeleton.state != Skeleton::hit) && ((int(currentFrame) >= 5) &&		  // Если летучая мыш укусила, то скелет ударяется
					(int(currentFrame) <= 10)))
				{
					skeleton.state = Skeleton::hit;											  // Статус скелета -> удар
					skeleton.currentFrame = 0;												  // Обнуляем раскадровщик скелета
				}
			}
		}
	}
}

void Bat::update(Skeleton& skeleton, float time) // Функция обновления персонажа
{
	switch (state) // Перебираем статусы
	{
	case wake:	   // Если просыпается

		batSprite.setOrigin(sf::Vector2f(22, 53)); // Задаем координаты отрисовки спрайта летучей мыши
		batSprite.setTexture(batTextures[0]);	   // Задаем анимацию пробуждения 
		
		if (sleep)			  // Если спит
		{
			currentFrame = 0; // Задаём значение раскадровщику
		}
		else				  // Иначе
		{
			currentFrame += 10 * time; // Скорость анимации 10 кадров в секунду 
			if (currentFrame > 8)	   // Если доходим до конца анимации
			{
				state = walk;		   // Статус -> прогулка
			}
		}

		goingForward ? batSprite.setTextureRect(IntRect(int(currentFrame) * 64, 0, 64, 64)) :		// Если до этого двигались прямо, то персонаж будет смотреть прямо
						batSprite.setTextureRect(IntRect(int(currentFrame) * 64 + 64, 0, -64, 64)); // Иначе назад

		w  = 20; // Задаем ширину
		h  = -2; // Задаем высоту
		dx =  0; // Задаём скорость

		break;   // Завершаем проверку

	case walk:     // Если гуляет

		batSprite.setOrigin(sf::Vector2f(22, 69)); // Задаем координаты отрисовки спрайта летучей мыши
		batSprite.setTexture(batTextures[1]);	   // Задаем анимацию прогулки 

		currentFrame += 10 * time;																	// Скорость анимации 10 кадров в секунду
		if (currentFrame > 6) currentFrame = 0;														// Обнуляем раскадровщик при окончании анимации
		goingForward ? batSprite.setTextureRect(IntRect(int(currentFrame) * 64, 0, 64, 64)) :		// Если до этого двигались прямо, то персонаж будет смотреть прямо
						batSprite.setTextureRect(IntRect(int(currentFrame) * 64 + 64, 0, -64, 64)); // Иначе назад

		w = 20;									 // Задаем ширину
		h = -2;									 // Задаем высоту
		goingForward ? dx = speed : dx = -speed; // Задаем скорость по x

		break;									 // Завершаем проверку
	
	case attack:   // Если атакует

		batSprite.setOrigin(sf::Vector2f(22, 69)); // Задаем координаты отрисовки спрайта летучей мыши
		batSprite.setTexture(batTextures[2]);	   // Задаем анимацию прогулки

		currentFrame += 12 * time; // Скорость анимации 12 кадров в секунду
		if (currentFrame > 12)	   // Если доходим до конца анимации
		{
			currentFrame = 0;	   // Обнуляем раскадровщик при окончании анимации
			state        = walk;   // Статус -> прогулка 
		}

		goingForward ? batSprite.setTextureRect(IntRect(int(currentFrame) * 64, 0, 64, 64)) :		// Если до этого двигались прямо, то персонаж будет смотреть прямо
						batSprite.setTextureRect(IntRect(int(currentFrame) * 64 + 64, 0, -64, 64)); // Иначе назад

		w = 20;			                                 // Задаем ширину
		h = -2;								             // Задаем высоту
		goingForward ? dx = speed / 2 : dx = -speed / 2; // Задаем скорость по x

		break;									         // Завершаем проверку
	
	case hit:      // Если ударяется
	
		batSprite.setOrigin(sf::Vector2f(22, 69)); // Задаем координаты отрисовки спрайта летучей мыши
		batSprite.setTexture(batTextures[4]);	   // Задаем анимацию прогулки

		currentFrame += 8 * time; // Скорость анимации 8 кадров в секунду
		if (currentFrame > 6)	  // Если доходим до конца анимации
		{
			health--;			  // Убираем здоровье
			currentFrame = 0;	  // Обнуляем раскадровщик при окончании анимации
			
			if (health == 0)	  // Если закончились жизни
			{
				state = dies;	  // Статус -> смерть 
			}
			else				  // Иначе
			{
				state = walk;     // Статус -> прогулка 
			}
		}

		goingForward ? batSprite.setTextureRect(IntRect(int(currentFrame) * 64, 0, 64, 64)) :		// Если до этого двигались прямо, то персонаж будет смотреть прямо
						batSprite.setTextureRect(IntRect(int(currentFrame) * 64 + 64, 0, -64, 64)); // Иначе назад

		w  = 0; // Задаем ширину
		h  = 0; // Задаем высоту
		dx = 0; // Задаём скорость

		break;  // Завершаем проверку

	case dies:

		batSprite.setOrigin(sf::Vector2f(22, 69)); // Задаем координаты отрисовки спрайта летучей мыши
		batSprite.setTexture(batTextures[3]);	   // Задаем анимацию смерти 

		if (dead)			  // Если погиб
		{
			currentFrame = 6; // Задаём значение раскадровщику
		}
		else				  // Иначе
		{
			currentFrame += 10 * time; // Скорость анимации 10 кадров в секунду 
			if (currentFrame > 6)	   // Если доходим до конца анимации
			{
				dead = true;		   // Летучая мышь мертва		
			}
		}

		goingForward ? batSprite.setTextureRect(IntRect(int(currentFrame) * 64, 0, 64, 64)) :		// Если до этого двигались прямо, то персонаж будет смотреть прямо
						batSprite.setTextureRect(IntRect(int(currentFrame) * 64 + 64, 0, -64, 64)); // Иначе назад

		w  = 0; // Задаем ширину
		h  = 0; // Задаем высоту
		dx = 0; // Задаём скорость

		break;  // Завершаем проверку
	}
	
	if (!dead)							   // Если летучая мышь жива
	{
		collisionWithACharacter(skeleton); // Проверяем столкновение со скелетом
		
		x += dx * time;				       // Задаем координаты x
		y += dy * time;
		checkCollisionWithMap();		   // Проверяем столкновение со стеной

		batSprite.setPosition(x, y);       // Задаем позицию летучей мыши
	}
}
