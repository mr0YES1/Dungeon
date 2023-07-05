#include "Levels.h" // ���������� ������������ ���� �������

Level_1::Level_1() // ����������� ������� ������
{
	Main_Objects.LoadFromFile("Level_1/Main_Objects.tmx"); // ��������� -> ��������_�������
	Decorations.LoadFromFile("Level_1/Decorations.tmx");   // ��������� -> ��������� 
	Jug_1.LoadFromFile("Level_1/Jug_1.tmx");		       // ��������� -> ������ 1
	Jug_2.LoadFromFile("Level_1/Jug_2.tmx");		       // ��������� -> ������ 2
	Jug_3.LoadFromFile("Level_1/Jug_3.tmx");		       // ��������� -> ������ 3
	Candle_1.LoadFromFile("Level_1/Candle_1.tmx");	       // ��������� -> ����� 1
	Candle_2.LoadFromFile("Level_1/Candle_2.tmx");	       // ��������� -> ����� 2
	Coffin_2.LoadFromFile("Level_1/Coffin_2.tmx");	       // ��������� -> ���� 2
	Right_Wall.LoadFromFile("Level_1/Right_Wall.tmx");     // ��������� -> ������ �����
	Lower_Wall.LoadFromFile("Level_1/Lower_Wall.tmx");     // ��������� -> ������ �����

	player     = Main_Objects.GetFirstObject("skeleton");  // �������� � ������ ������ ������
	enemy      = Main_Objects.GetFirstObject("bat");	   // �������� � ������ ������ �����
	exit       = Main_Objects.GetFirstObject("exit");      // �������� � ������ ������ ������
	
	skeleton.Constructor(Main_Objects, player.rect.left, player.rect.top); // �������� ����������� �������
	bat.Constructor(Main_Objects, enemy.rect.left, enemy.rect.top, "1");   // �������� ����������� ������� ����
	coffin.Constructor(Main_Objects, "1");								   // �������� ����������� �����
}

void Level_1::update(int& level, float time) // ���������� ������
{
	skeleton.update(time);	    // ��������� �������
	bat.update(skeleton, time); // ��������� ������� ����
	coffin.update(skeleton);	// ��������� ����

	if (skeleton.getRect().intersects(exit.rect)) // ���� �������
	{
		level++;								  // ��������� �� ��������� �������
	}
}

void Level_1::orderOfRenderings(RenderWindow& window) // ������������������ ���������
{
	characterDrawn = false;										   // ������, ��� �������� �� ���������
	
	Main_Objects.Draw(window);									   // ������ -> ��������_�������
	Decorations.Draw(window);									   // ������ -> ���������

	if (bat.state == Bat::dies)									   // ���� ������� ���� �������
	{
		if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 100)  // ���� �������� ������ ������� ������� ����
		{
			window.draw(skeleton.skeletonSprite);					    // ������ ���������                    
			characterDrawn = true;									    // �������� ���������
		}
		window.draw(bat.batSprite);									    // ������ -> ������� ����
	}

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 128) // ���� �������� ������ ������ �����
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Right_Wall.Draw(window);									   // ������ -> ������ �����

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 154) // ���� �������� ������ ����� 1
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ��������� 
		characterDrawn = true;									   // �������� ���������	
	}

	Candle_1.Draw(window);										   // ������ -> ����� 1

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 165) // ���� �������� ������ ����� 1
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ��������� 
		characterDrawn = true;									   // �������� ���������	
	}

	window.draw(coffin.coffinSprite);							   // ������ -> ���� 

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 184) // ���� �������� ������ ������� 1
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ��������� 
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_1.Draw(window);											   // ������ -> ������ 1										  

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 201) // ���� �������� ������ ����� 2
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ��������� 
		characterDrawn = true;									   // �������� ���������	
	}

	Candle_2.Draw(window);										   // ������ -> ����� 2										  

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 202) // ���� �������� ������ ������� 2
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ��������� 
		characterDrawn = true;									   // �������� ���������	
	}
	
	Jug_2.Draw(window);											   // ������ -> ������ 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 245) // ���� �������� ������ ����� 2
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ��������� 
		characterDrawn = true;									   // �������� ���������
	}

	Coffin_2.Draw(window);										   // ������ -> ���� 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 250) // ���� �������� ������ ������� 3
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ��������� 
		characterDrawn = true;									   // �������� ���������
	}

	Jug_3.Draw(window);											   // ������ -> ������ 3

	if (!characterDrawn)										   // ���� �������� �� ���������
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������
	}

	Lower_Wall.Draw(window);									   // ������ -> ������ �����

	if (bat.state != Bat::dies)									   // ���� ������� ���� �� �������
	{
		window.draw(bat.batSprite);								   // ������ ������� ����
	}
}



Level_2::Level_2()
{
	Main_Objects.LoadFromFile("Level_2/Main_Objects.tmx"); // ��������� -> ��������_�������
	Decorations.LoadFromFile("Level_2/Decorations.tmx");   // ��������� -> ���������
	Arches.LoadFromFile("Level_2/Arches.tmx");			   // ��������� -> ����
	Jug_1.LoadFromFile("Level_2/Jug_1.tmx");			   // ��������� -> ������ 1
	Jug_2.LoadFromFile("Level_2/Jug_2.tmx");			   // ��������� -> ������ 2
	Jug_3.LoadFromFile("Level_2/Jug_3.tmx");			   // ��������� -> ������ 3
	Jug_4.LoadFromFile("Level_2/Jug_4.tmx");			   // ��������� -> ������ 4
	Jug_5.LoadFromFile("Level_2/Jug_5.tmx");			   // ��������� -> ������ 5
	Jug_6.LoadFromFile("Level_2/Jug_6.tmx");			   // ��������� -> ������ 6
	Jug_7.LoadFromFile("Level_2/Jug_7.tmx");			   // ��������� -> ������ 7
	Jug_8.LoadFromFile("Level_2/Jug_8.tmx");			   // ��������� -> ������ 8
	Jug_9.LoadFromFile("Level_2/Jug_9.tmx");			   // ��������� -> ������ 9
	Jug_10.LoadFromFile("Level_2/Jug_10.tmx");			   // ��������� -> ������ 10
	Candle_1.LoadFromFile("Level_2/Candle_1.tmx");		   // ��������� -> ����� 1
	Candle_2.LoadFromFile("Level_2/Candle_2.tmx");		   // ��������� -> ����� 2
	Candle_3.LoadFromFile("Level_2/Candle_3.tmx");		   // ��������� -> ����� 3
	Candle_4.LoadFromFile("Level_2/Candle_4.tmx");		   // ��������� -> ����� 4
	Coffin_1.LoadFromFile("Level_2/Coffin_1.tmx");		   // ��������� -> ���� 1
	Coffin_2.LoadFromFile("Level_2/Coffin_2.tmx");		   // ��������� -> ���� 2
	Chests.LoadFromFile("Level_2/Chests.tmx");			   // ��������� -> �����
	Lower_Wall.LoadFromFile("Level_2/Lower_Wall.tmx");     // ��������� -> ������ �����

	player  = Main_Objects.GetFirstObject("skeleton");	   // �������� � ������ ������ ������
	enemy_1 = Main_Objects.GetFirstObject("bat_1");		   // �������� � ������ ������ ����� 1
	enemy_2 = Main_Objects.GetFirstObject("bat_2");		   // �������� � ������ ������ ����� 2
	exit    = Main_Objects.GetFirstObject("exit");         // �������� � ������ ������ ������

	skeleton.Constructor(Main_Objects, player.rect.left, player.rect.top);		// �������� ����������� �������
	bat_1.Constructor(Main_Objects, enemy_1.rect.left, enemy_1.rect.top, "1");	// �������� ����������� ������� ���� 1
	bat_2.Constructor(Main_Objects, enemy_2.rect.left, enemy_2.rect.top, "2");	// �������� ����������� ������� ���� 2
}

void Level_2::update(int& level, float time)
{
	skeleton.update(time);	      // ��������� �������
	bat_1.update(skeleton, time); // ��������� ������� ���� 1
	bat_2.update(skeleton, time); // ��������� ������� ���� 2

	if (skeleton.getRect().intersects(exit.rect)) // ���� �������
	{
		level++;								  // ��������� �� ��������� �������
	}
}

void Level_2::orderOfRenderings(RenderWindow& window)
{
	characterDrawn = false;									       // ������, ��� �������� �� ���������
	
	Main_Objects.Draw(window);									   // ������ -> ��������_�������
	Decorations.Draw(window);									   // ������ -> ���������

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 69)  // ���� �������� ������ ������
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Chests.Draw(window);										   // ������ -> �����

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 92)  // ���� �������� ������ ����� 1
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Candle_1.Draw(window);										   // ������ -> ����� 1

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 105) // ���� �������� ������ ����� 2
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Candle_2.Draw(window);										   // ������ -> ����� 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 106) // ���� �������� ������ ������� 1
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_1.Draw(window);											   // ������ -> ������ 1

	if (bat_1.state == Bat::dies)									   // ���� ������� ���� �������
	{
		if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 118) // ���� �������� ������ ������� ������� ����
		{
			window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
			characterDrawn = true;									   // �������� ���������
		}
		window.draw(bat_1.batSprite);							   	   // ������ -> ������� ����
	}

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 121) // ���� �������� ������ ����� 3
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Candle_3.Draw(window);										   // ������ -> ����� 3

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 124) // ���� �������� ������ ����� 4
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Candle_4.Draw(window);										   // ������ -> ����� 4

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 170) // ���� �������� ������ ������� 2
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_2.Draw(window);											   // ������ -> ������ 2
	
	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 232) // ���� �������� ������ ������� 3
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_3.Draw(window);											   // ������ -> ������ 3

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 234) // ���� �������� ������ ������� 4
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_4.Draw(window);											   // ������ -> ������ 4

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 245) // ���� �������� ������ ����� 1
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Coffin_1.Draw(window);										   // ������ -> ���� 1

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 250) // ���� �������� ������ ������� 5
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_5.Draw(window);											   // ������ -> ������ 5
	
	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 256) // ���� �������� ������ ����
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Arches.Draw(window);										   // ������ -> ����

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 341) // ���� �������� ������ ����� 2
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Coffin_2.Draw(window);										   // ������ -> ���� 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 346) // ���� �������� ������ ������� 6
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_6.Draw(window);											   // ������ -> ������ 6

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 360) // ���� �������� ������ ������� 7
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_7.Draw(window);											   // ������ -> ������ 7

	if (bat_2.state == Bat::dies)									   // ���� ������� ���� �������
	{
		if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 420) // ���� �������� ������ ������� ������� ����
		{
			window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
			characterDrawn = true;									   // �������� ���������
		}
		window.draw(bat_2.batSprite);								   // ������ -> ������� ����
	}

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 456) // ���� �������� ������ ������� 8
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_8.Draw(window);											   // ������ -> ������ 8

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 458) // ���� �������� ������ ������� 9
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_9.Draw(window);											   // ������ -> ������ 9

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 474) // ���� �������� ������ ������� 10
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_10.Draw(window);										   // ������ -> ������ 10

	if (!characterDrawn)										   // ���� �������� �� ���������
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������
	}

	Lower_Wall.Draw(window);									   // ������ -> ������ �����

	if (bat_1.state != Bat::dies)								   // ���� ������� ���� �� �������
	{
		window.draw(bat_1.batSprite);							   // ������ ������� ����
	}

	if (bat_2.state != Bat::dies)								   // ���� ������� ���� �� �������
	{
		window.draw(bat_2.batSprite);							   // ������ ������� ����
	}
}



Level_3::Level_3()
{
	Main_Objects.LoadFromFile("Level_3/Main_Objects.tmx");		   // ��������� -> �������� �������
	Decorations.LoadFromFile("Level_3/Decorations.tmx");		   // ��������� -> ���������
	Skeletal_�orpses.LoadFromFile("Level_3/Skeletal_�orpses.tmx"); // ��������� -> ����� ��������
	Jug_1.LoadFromFile("Level_3/Jug_1.tmx");					   // ��������� -> ������ 1
	Jug_2.LoadFromFile("Level_3/Jug_2.tmx");				       // ��������� -> ������ 2
	Jug_3.LoadFromFile("Level_3/Jug_3.tmx");					   // ��������� -> ������ 3
	Jug_4.LoadFromFile("Level_3/Jug_4.tmx");					   // ��������� -> ������ 4
	Jug_5.LoadFromFile("Level_3/Jug_5.tmx");					   // ��������� -> ������ 5
	Jug_6.LoadFromFile("Level_3/Jug_6.tmx");					   // ��������� -> ������ 6
	Jug_7.LoadFromFile("Level_3/Jug_7.tmx");					   // ��������� -> ������ 7
	Candle_1.LoadFromFile("Level_3/Candle_1.tmx");				   // ��������� -> ����� 1
	Candle_2.LoadFromFile("Level_3/Candle_2.tmx");				   // ��������� -> ����� 2
	Candle_3.LoadFromFile("Level_3/Candle_3.tmx");				   // ��������� -> ����� 3
	Chests_1.LoadFromFile("Level_3/Chests_1.tmx");				   // ��������� -> ����� 1
	Chests_2.LoadFromFile("Level_3/Chests_2.tmx");				   // ��������� -> ����� 2
	Wooden_Beams_1.LoadFromFile("Level_3/Wooden_Beams_1.tmx");     // ��������� -> ���������� ����� 1
	Wooden_Beams_2.LoadFromFile("Level_3/Wooden_Beams_2.tmx");     // ��������� -> ���������� ����� 2
	Lower_Wall.LoadFromFile("Level_3/Lower_Wall.tmx");			   // ��������� -> ������ �����

	player = Main_Objects.GetFirstObject("skeleton");			   // �������� � ������ ������ ������

	skeleton.Constructor(Main_Objects, player.rect.left, player.rect.top);		// �������� ����������� �������
}

void Level_3::update(float time)
{
	skeleton.update(time); // ��������� �������
}

void Level_3::orderOfRenderings(RenderWindow& window)
{
	characterDrawn = false;									       // ������, ��� �������� �� ���������

	Main_Objects.Draw(window);									   // ������ -> ��������_�������
	Decorations.Draw(window);									   // ������ -> ���������
	Skeletal_�orpses.Draw(window);								   // ������ -> ����� ��������

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 137) // ���� �������� ������ ����� 1
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Candle_1.Draw(window);										   // ������ -> ����� 1

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 165) // ���� �������� ������ ������ 1
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Chests_1.Draw(window);										   // ������ -> ����� 1

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 216) // ���� �������� ������ ������� 1
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_1.Draw(window);											   // ������ -> ������ 1

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 218) // ���� �������� ������ ������� 2
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_2.Draw(window);											   // ������ -> ������ 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 234) // ���� �������� ������ ������� 3
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_3.Draw(window);											   // ������ -> ������ 3

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 266) // ���� �������� ������ ���������� ����� 1
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Wooden_Beams_1.Draw(window);								   // ������ -> ���������� ����� 1

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 362) // ���� �������� ������ ���������� ����� 2
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Wooden_Beams_2.Draw(window);								   // ������ -> ���������� ����� 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 410) // ���� �������� ������ ������� 4
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_4.Draw(window);											   // ������ -> ������ 4

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 469) // ���� �������� ������ ������ 2
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Chests_2.Draw(window);										   // ������ -> ����� 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 490) // ���� �������� ������ ������� 5
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_5.Draw(window);											   // ������ -> ������ 5

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 504) // ���� �������� ������ ������� 6
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_6.Draw(window);											   // ������ -> ������ 6

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 505) // ���� �������� ������ ����� 2
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Candle_2.Draw(window);										   // ������ -> ����� 2

	if (!characterDrawn && skeleton.getPlayerCoordinateY() <= 506) // ���� �������� ������ ������� 7
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������                    
		characterDrawn = true;									   // �������� ���������	
	}

	Jug_7.Draw(window);											   // ������ -> ������ 7
	Candle_3.Draw(window);										   // ������ -> ����� 3

	if (!characterDrawn)										   // ���� �������� �� ���������
	{
		window.draw(skeleton.skeletonSprite);					   // ������ ���������
	}
	
	Lower_Wall.Draw(window);									   // ������ -> ������ �����
}