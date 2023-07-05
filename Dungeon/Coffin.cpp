#include "Coffin.h" // Подключаем класс гроба

void Coffin::Constructor(TmxLevel& Level, string num)			 // Конструктор объекта
{
	coffin = Level.GetFirstObject("coffin_" + num);				 // Получаем с уровня объект пробуждение летучей мыши

	coffinTexture.loadFromFile("Images/Coffin/Coffin.png");		 // Загружаем текстуру гроба

	coffinSprite.setOrigin(Vector2f(2, 16));					 // Задаем координаты отрисовки спрайта гроба
	coffinSprite.setTexture(coffinTexture);						 // Получаем текстуру гроба 

	coffinSprite.setPosition(coffin.rect.left, coffin.rect.top); // Устанавливаем позицию гроба

	hit   = 0;													 // Задаем количество ударов

	hited = false;												 // Задаем удар
}

void Coffin::collisionWithACharacter(Skeleton& skeleton) // Метод проверки столкновения со скелетом	
{
	if (skeleton.getRect().intersects(coffin.rect))		 // Проверяем столкновение
	{
		if (skeleton.state == Skeleton::attack)			 // Если скелет бьет
		{
			if (int(skeleton.currentFrame) == 7) 		 // Проверяем удар
			{
				if (!hited)								 // Если не ударил
				{
					hit += 0.5f;						 // Ударяем один раз
					hited = true;					     // Удар произошёл
				}
				if (int(hit) > 2)						 // Если более 4-x ударов
				{
					hit = 2;							 // То остается 4 удара
				}
			}
			else                                         // Иначе
			{
				hited = false;							 // Это не удар 
			}
		}
		else if ((skeleton.rebirthStatus == Skeleton::revive) || (skeleton.rebirthStatus == Skeleton::dies)) // Если умирает/оживает
		{
			skeleton.cancellationOfActions();			 // То отменяем действия
		}
		else											 // Иначе                                                                            
		{
			skeleton.repulsion(coffin.rect);			 // Иначе отталкиваем от стены		
		}
	}
}

void Coffin::update(Skeleton& skeleton)								// Функция обновления объекта
{	
	coffinSprite.setTextureRect(IntRect(int(hit) * 18, 0, 18, 43)); // Задаём определенную текстуру объекта

	collisionWithACharacter(skeleton);								// Проверяем столкновение со скелетом							
}
