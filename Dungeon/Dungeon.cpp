#include "View.h"   // Подключаем заголовочный файл камеры
#include "Levels.h" // Подключаем заголовочный файл уровней

int main()
{
	RenderWindow window(sf::VideoMode(480, 270), "Dungeon"); // Создаем окно игры
	view.reset(sf::FloatRect(0, 0, 480, 270));				 // Размер "вида" камеры при создании объекта вида камеры

	Level_1 level_1;		 // Создаём первый уровень
	Level_2 level_2;		 // Создаём второй уровень
	Level_3 level_3;		 // Создаём третий уровень

	Clock clock;			 // Создаем время

	int level = 1;			 // Создаем контроллер уровня
 
	while (window.isOpen())								 // Пока окно открыто
	{
		float time = clock.getElapsedTime().asSeconds(); // Передаем в переменную time время в секундах
		clock.restart();							     // Обнуляем время
		
		Event event;									 // Создаём событие

		while (window.pollEvent(event))					 // Срабатываение события	   
		{
			if (event.type == Event::Closed)			 // Если закрываем окно
			{
				window.close();							 // Закрываем окно
			}
		}

		switch (level) // Проверка уровня
		{
		case 1:		   // Уровень 1

			level_1.update(level, time);																						 // Обновляем уровень

			getPlayerCoordinateForView(level, level_1.skeleton.getPlayerCoordinateX(), level_1.skeleton.getPlayerCoordinateY()); // Получаем координаты игрока

			window.setView(view);																								 // Передаём камеру
			window.clear();																										 // Очищаем окно

			level_1.orderOfRenderings(window);																					 // Отрисовываем уровень

			break;																												 // Завершаем проверку

		case 2:		   // Уровень 2

			level_2.update(level, time);																						 // Обновляем уровень

			getPlayerCoordinateForView(level, level_2.skeleton.getPlayerCoordinateX(), level_2.skeleton.getPlayerCoordinateY()); // Получаем координаты игрока

			window.setView(view);																								 // Передаём камеру
			window.clear();																										 // Очищаем окно

			level_2.orderOfRenderings(window);																					 // Отрисовываем уровень
			
			break;																												 // Завершаем проверку

		case 3:		   // Уровень 3

			level_3.update(time);																								 // Обновляем уровень

			getPlayerCoordinateForView(level, level_3.skeleton.getPlayerCoordinateX(), level_3.skeleton.getPlayerCoordinateY()); // Получаем координаты игрока

			window.setView(view);																								 // Передаём камеру
			window.clear();																										 // Очищаем окно

			level_3.orderOfRenderings(window);																					 // Отрисовываем уровень

			break;																												 // Завершаем проверку
		}

		window.display(); // Отрисовываем экран
	}
 
	return 0;			  // Завершаем программу
}