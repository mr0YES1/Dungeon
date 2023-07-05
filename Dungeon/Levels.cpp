#include "Levels.h" // Подключаем заголовочный файл уровней

Level_1::Level_1() // Конструктор первого уровня
{
	Main_Objects.LoadFromFile("Level_1/Main_Objects.tmx"); // Загружаем -> основные_объекты
	Decorations.LoadFromFile("Level_1/Decorations.tmx");   // Загружаем -> декорации 
	Jug_1.LoadFromFile("Level_1/Jug_1.tmx");		       // Загружаем -> кувшин 1
	Jug_2.LoadFromFile("Level_1/Jug_2.tmx");		       // Загружаем -> кувшин 2
	Jug_3.LoadFromFile("Level_1/Jug_3.tmx");		       // Загружаем -> кувшин 3
	Candle_1.LoadFromFile("Level_1/Candle_1.tmx");	       // Загружаем -> свечи 1
	Candle_2.LoadFromFile("Level_1/Candle_2.tmx");	       // Загружаем -> свечи 2
	Coffin_2.LoadFromFile("Level_1/Coffin_2.tmx");	       // Загружаем -> гроб 2
	Right_Wall.LoadFromFile("Level_1/Right_Wall.tmx");     // Загружаем -> правую стену
	Lower_Wall.LoadFromFile("Level_1/Lower_Wall.tmx");     // Загружаем -> нижнюю стену

	player     = Main_Objects.GetFirstObject("skeleton");  // Получаем с уровня объект игрока
	enemy      = Main_Objects.GetFirstObject("bat");	   // Получаем с уровня объект врага
	exit       = Main_Objects.GetFirstObject("exit");      // Получаем с уровня объект выхода
	
	skeleton.Constructor(Main_Objects, player.rect.left, player.rect.top); // Вызываем конструктор скелета
	bat.Constructor(Main_Objects, enemy.rect.left, enemy.rect.top, "1");   // Вызываем конструктор летучей мыши
	coffin.Constructor(Main_Objects, "1");								   // Вызываем конструктор гроба
}

void Level_1::update(int& level, float time) // Обновление уровня
{
	skeleton.update(time);	    // Обновляем скелета
	bat.update(skeleton, time); // Обновляем летучую мышь
	coffin.update(skeleton);	// Обновляем гроб

	if (skeleton.getRect().intersects(exit.rect)) // Если выходим
	{
		level++;								  // Переходим на следующий уровень
	}
}

void Level_1::orderOfRenderings(RenderWindow& window) // Последовательность отрисовки
{
	characterDrawn = false;										   // Задаем, что персонаж не нарисован
	
	Main_Objects.Draw(window);									   // Рисуем -> основные_объекты
	Decorations.Draw(window);									   // Рисуем -> декорации

	if (bat.state == Bat::dies)									   // Если летучая мышь погибла
	{
		if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 100)  // Если персонаж поверх мертвой летучей мыши
		{
			window.draw(skeleton.skeletonSprite);					    // Рисуем персонажа                    
			characterDrawn = true;									    // Персонаж нарисован
		}
		window.draw(bat.batSprite);									    // Рисуем -> летучую мышь
	}

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 128) // Если персонаж поверх правой стены
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Right_Wall.Draw(window);									   // Рисуем -> правую стену

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 154) // Если персонаж поверх свечи 1
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа 
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Candle_1.Draw(window);										   // Рисуем -> свечи 1

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 165) // Если персонаж поверх гроба 1
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа 
		characterDrawn = true;									   // Персонаж нарисован	
	}

	window.draw(coffin.coffinSprite);							   // Рисуем -> гроб 

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 184) // Если персонаж поверх кувшина 1
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа 
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_1.Draw(window);											   // Рисуем -> кувшин 1										  

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 201) // Если персонаж поверх свечи 2
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа 
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Candle_2.Draw(window);										   // Рисуем -> свечи 2										  

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 202) // Если персонаж поверх кувшина 2
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа 
		characterDrawn = true;									   // Персонаж нарисован	
	}
	
	Jug_2.Draw(window);											   // Рисуем -> кувшин 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 245) // Если персонаж поверх гроба 2
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа 
		characterDrawn = true;									   // Персонаж нарисован
	}

	Coffin_2.Draw(window);										   // Рисуем -> гроб 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 250) // Если персонаж поверх кувшина 3
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа 
		characterDrawn = true;									   // Персонаж нарисован
	}

	Jug_3.Draw(window);											   // Рисуем -> кувшин 3

	if (!characterDrawn)										   // Если персонаж не нарисован
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа
	}

	Lower_Wall.Draw(window);									   // Рисуем -> нижнюю стену

	if (bat.state != Bat::dies)									   // Если летучая мышь не погибла
	{
		window.draw(bat.batSprite);								   // Рисуем летучую мышь
	}
}



Level_2::Level_2()
{
	Main_Objects.LoadFromFile("Level_2/Main_Objects.tmx"); // Загружаем -> основные_объекты
	Decorations.LoadFromFile("Level_2/Decorations.tmx");   // Загружаем -> декорации
	Arches.LoadFromFile("Level_2/Arches.tmx");			   // Загружаем -> арку
	Jug_1.LoadFromFile("Level_2/Jug_1.tmx");			   // Загружаем -> кувшин 1
	Jug_2.LoadFromFile("Level_2/Jug_2.tmx");			   // Загружаем -> кувшин 2
	Jug_3.LoadFromFile("Level_2/Jug_3.tmx");			   // Загружаем -> кувшин 3
	Jug_4.LoadFromFile("Level_2/Jug_4.tmx");			   // Загружаем -> кувшин 4
	Jug_5.LoadFromFile("Level_2/Jug_5.tmx");			   // Загружаем -> кувшин 5
	Jug_6.LoadFromFile("Level_2/Jug_6.tmx");			   // Загружаем -> кувшин 6
	Jug_7.LoadFromFile("Level_2/Jug_7.tmx");			   // Загружаем -> кувшин 7
	Jug_8.LoadFromFile("Level_2/Jug_8.tmx");			   // Загружаем -> кувшин 8
	Jug_9.LoadFromFile("Level_2/Jug_9.tmx");			   // Загружаем -> кувшин 9
	Jug_10.LoadFromFile("Level_2/Jug_10.tmx");			   // Загружаем -> кувшин 10
	Candle_1.LoadFromFile("Level_2/Candle_1.tmx");		   // Загружаем -> свечи 1
	Candle_2.LoadFromFile("Level_2/Candle_2.tmx");		   // Загружаем -> свечи 2
	Candle_3.LoadFromFile("Level_2/Candle_3.tmx");		   // Загружаем -> свечи 3
	Candle_4.LoadFromFile("Level_2/Candle_4.tmx");		   // Загружаем -> свечи 4
	Coffin_1.LoadFromFile("Level_2/Coffin_1.tmx");		   // Загружаем -> гроб 1
	Coffin_2.LoadFromFile("Level_2/Coffin_2.tmx");		   // Загружаем -> гроб 2
	Chests.LoadFromFile("Level_2/Chests.tmx");			   // Загружаем -> ящики
	Lower_Wall.LoadFromFile("Level_2/Lower_Wall.tmx");     // Загружаем -> нижнюю стену

	player  = Main_Objects.GetFirstObject("skeleton");	   // Получаем с уровня объект игрока
	enemy_1 = Main_Objects.GetFirstObject("bat_1");		   // Получаем с уровня объект врага 1
	enemy_2 = Main_Objects.GetFirstObject("bat_2");		   // Получаем с уровня объект врага 2
	exit    = Main_Objects.GetFirstObject("exit");         // Получаем с уровня объект выхода

	skeleton.Constructor(Main_Objects, player.rect.left, player.rect.top);		// Вызываем конструктор скелета
	bat_1.Constructor(Main_Objects, enemy_1.rect.left, enemy_1.rect.top, "1");	// Вызываем конструктор летучей мыши 1
	bat_2.Constructor(Main_Objects, enemy_2.rect.left, enemy_2.rect.top, "2");	// Вызываем конструктор летучей мыши 2
}

void Level_2::update(int& level, float time)
{
	skeleton.update(time);	      // Обновляем скелета
	bat_1.update(skeleton, time); // Обновляем летучую мышь 1
	bat_2.update(skeleton, time); // Обновляем летучую мышь 2

	if (skeleton.getRect().intersects(exit.rect)) // Если выходим
	{
		level++;								  // Переходим на следующий уровень
	}
}

void Level_2::orderOfRenderings(RenderWindow& window)
{
	characterDrawn = false;									       // Задаем, что персонаж не нарисован
	
	Main_Objects.Draw(window);									   // Рисуем -> основные_объекты
	Decorations.Draw(window);									   // Рисуем -> декорации

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 69)  // Если персонаж поверх ящиков
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Chests.Draw(window);										   // Рисуем -> ящики

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 92)  // Если персонаж поверх свечи 1
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Candle_1.Draw(window);										   // Рисуем -> свечи 1

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 105) // Если персонаж поверх свечи 2
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Candle_2.Draw(window);										   // Рисуем -> свечи 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 106) // Если персонаж поверх кувшина 1
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_1.Draw(window);											   // Рисуем -> кувшин 1

	if (bat_1.state == Bat::dies)									   // Если летучая мышь погибла
	{
		if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 118) // Если персонаж поверх мертвой летучей мыши
		{
			window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
			characterDrawn = true;									   // Персонаж нарисован
		}
		window.draw(bat_1.batSprite);							   	   // Рисуем -> летучую мышь
	}

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 121) // Если персонаж поверх свечи 3
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Candle_3.Draw(window);										   // Рисуем -> свечи 3

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 124) // Если персонаж поверх свечи 4
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Candle_4.Draw(window);										   // Рисуем -> свечи 4

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 170) // Если персонаж поверх кувшина 2
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_2.Draw(window);											   // Рисуем -> кувшин 2
	
	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 232) // Если персонаж поверх кувшина 3
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_3.Draw(window);											   // Рисуем -> кувшин 3

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 234) // Если персонаж поверх кувшина 4
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_4.Draw(window);											   // Рисуем -> кувшин 4

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 245) // Если персонаж поверх гроба 1
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Coffin_1.Draw(window);										   // Рисуем -> гроб 1

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 250) // Если персонаж поверх кувшина 5
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_5.Draw(window);											   // Рисуем -> кувшин 5
	
	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 256) // Если персонаж поверх арки
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Arches.Draw(window);										   // Рисуем -> арку

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 341) // Если персонаж поверх гроба 2
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Coffin_2.Draw(window);										   // Рисуем -> гроб 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 346) // Если персонаж поверх кувшина 6
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_6.Draw(window);											   // Рисуем -> кувшин 6

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 360) // Если персонаж поверх кувшина 7
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_7.Draw(window);											   // Рисуем -> кувшин 7

	if (bat_2.state == Bat::dies)									   // Если летучая мышь погибла
	{
		if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 420) // Если персонаж поверх мертвой летучей мыши
		{
			window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
			characterDrawn = true;									   // Персонаж нарисован
		}
		window.draw(bat_2.batSprite);								   // Рисуем -> летучую мышь
	}

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 456) // Если персонаж поверх кувшина 8
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_8.Draw(window);											   // Рисуем -> кувшин 8

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 458) // Если персонаж поверх кувшина 9
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_9.Draw(window);											   // Рисуем -> кувшин 9

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 474) // Если персонаж поверх кувшина 10
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_10.Draw(window);										   // Рисуем -> кувшин 10

	if (!characterDrawn)										   // Если персонаж не нарисован
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа
	}

	Lower_Wall.Draw(window);									   // Рисуем -> нижнюю стену

	if (bat_1.state != Bat::dies)								   // Если летучая мышь не погибла
	{
		window.draw(bat_1.batSprite);							   // Рисуем летучую мышь
	}

	if (bat_2.state != Bat::dies)								   // Если летучая мышь не погибла
	{
		window.draw(bat_2.batSprite);							   // Рисуем летучую мышь
	}
}



Level_3::Level_3()
{
	Main_Objects.LoadFromFile("Level_3/Main_Objects.tmx");		   // Загружаем -> основные объекты
	Decorations.LoadFromFile("Level_3/Decorations.tmx");		   // Загружаем -> декорации
	Skeletal_Сorpses.LoadFromFile("Level_3/Skeletal_Сorpses.tmx"); // Загружаем -> трупы скелетов
	Jug_1.LoadFromFile("Level_3/Jug_1.tmx");					   // Загружаем -> кувшин 1
	Jug_2.LoadFromFile("Level_3/Jug_2.tmx");				       // Загружаем -> кувшин 2
	Jug_3.LoadFromFile("Level_3/Jug_3.tmx");					   // Загружаем -> кувшин 3
	Jug_4.LoadFromFile("Level_3/Jug_4.tmx");					   // Загружаем -> кувшин 4
	Jug_5.LoadFromFile("Level_3/Jug_5.tmx");					   // Загружаем -> кувшин 5
	Jug_6.LoadFromFile("Level_3/Jug_6.tmx");					   // Загружаем -> кувшин 6
	Jug_7.LoadFromFile("Level_3/Jug_7.tmx");					   // Загружаем -> кувшин 7
	Candle_1.LoadFromFile("Level_3/Candle_1.tmx");				   // Загружаем -> свечи 1
	Candle_2.LoadFromFile("Level_3/Candle_2.tmx");				   // Загружаем -> свечи 2
	Candle_3.LoadFromFile("Level_3/Candle_3.tmx");				   // Загружаем -> свечи 3
	Chests_1.LoadFromFile("Level_3/Chests_1.tmx");				   // Загружаем -> ящики 1
	Chests_2.LoadFromFile("Level_3/Chests_2.tmx");				   // Загружаем -> ящики 2
	Wooden_Beams_1.LoadFromFile("Level_3/Wooden_Beams_1.tmx");     // Загружаем -> деревянные балки 1
	Wooden_Beams_2.LoadFromFile("Level_3/Wooden_Beams_2.tmx");     // Загружаем -> деревянные балки 2
	Lower_Wall.LoadFromFile("Level_3/Lower_Wall.tmx");			   // Загружаем -> нижнюю стену

	player = Main_Objects.GetFirstObject("skeleton");			   // Получаем с уровня объект игрока

	skeleton.Constructor(Main_Objects, player.rect.left, player.rect.top);		// Вызываем конструктор скелета
}

void Level_3::update(float time)
{
	skeleton.update(time); // Обновляем скелета
}

void Level_3::orderOfRenderings(RenderWindow& window)
{
	characterDrawn = false;									       // Задаем, что персонаж не нарисован

	Main_Objects.Draw(window);									   // Рисуем -> основные_объекты
	Decorations.Draw(window);									   // Рисуем -> декорации
	Skeletal_Сorpses.Draw(window);								   // Рисуем -> трупы скелетов

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 137) // Если персонаж поверх свечи 1
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Candle_1.Draw(window);										   // Рисуем -> свечи 1

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 165) // Если персонаж поверх ящиков 1
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Chests_1.Draw(window);										   // Рисуем -> ящики 1

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 216) // Если персонаж поверх кувшина 1
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_1.Draw(window);											   // Рисуем -> кувшин 1

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 218) // Если персонаж поверх кувшина 2
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_2.Draw(window);											   // Рисуем -> кувшин 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 234) // Если персонаж поверх кувшина 3
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_3.Draw(window);											   // Рисуем -> кувшин 3

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 266) // Если персонаж поверх деревянных балок 1
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Wooden_Beams_1.Draw(window);								   // Рисуем -> деревянные балки 1

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 362) // Если персонаж поверх деревянных балок 2
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Wooden_Beams_2.Draw(window);								   // Рисуем -> деревянные балки 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 410) // Если персонаж поверх кувшина 4
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_4.Draw(window);											   // Рисуем -> кувшин 4

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 469) // Если персонаж поверх ящиков 2
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Chests_2.Draw(window);										   // Рисуем -> ящики 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 490) // Если персонаж поверх кувшина 5
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_5.Draw(window);											   // Рисуем -> кувшин 5

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 504) // Если персонаж поверх кувшина 6
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_6.Draw(window);											   // Рисуем -> кувшин 6

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 505) // Если персонаж поверх свечи 2
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Candle_2.Draw(window);										   // Рисуем -> свечи 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 506) // Если персонаж поверх кувшина 7
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа                    
		characterDrawn = true;									   // Персонаж нарисован	
	}

	Jug_7.Draw(window);											   // Рисуем -> кувшин 7
	Candle_3.Draw(window);										   // Рисуем -> свечи 3

	if (!characterDrawn)										   // Если персонаж не нарисован
	{
		window.draw(skeleton.skeletonSprite);					   // Рисуем персонажа
	}
	
	Lower_Wall.Draw(window);									   // Рисуем -> нижнюю стену
}