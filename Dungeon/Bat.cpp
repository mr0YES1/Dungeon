#include "Bat.h" // ���������� ����� ������� ����

void Bat::Constructor(TmxLevel& Level, float X, float Y, string num) // ����������� ���������
{
	general�onstructor(X, Y);								         // ��������� ����� �����������
	
	solidObject  = Level.GetAllObjects("solid");		             // �������� ��� ������� �����
	wakeUpTheBat = Level.GetFirstObject("wakeUpTheBat_" + num);      // �������� � ������ ������ ����������� ������� ����
	
	batTextures[0].loadFromFile("Images/Bat/Bat_wake.png");          // �������� �������� �����������
	batTextures[1].loadFromFile("Images/Bat/Bat_Walk.png");          // �������� �������� ��������
	batTextures[2].loadFromFile("Images/Bat/Bat_Attack.png");        // �������� �������� �����
	batTextures[3].loadFromFile("Images/Bat/Bat_Dead.png");          // �������� �������� ������
	batTextures[4].loadFromFile("Images/Bat/Bat_Hit.png");           // �������� �������� �����

	state = wake; // ������������� ����������� ������ -> �����������

	health = 3;   // ����� ��������
	speed = 38;   // ������������� ��������

	sleep = true; // ������������� ���
	dead = false; // ������������� ���������� ������

	batSprite.setPosition(x, y); // ������������� ������� ������
}

void Bat::checkCollisionWithMap() // �������� �� ������������
{
	for (int i = 0; i < solidObject.size(); i++)									 // �������� �� �������� �����
	{
		if (getRect().intersects(solidObject[i].rect))								 // ���� ���������� ������������
		{
			if (goingForward)														 // ���� �������� ������
			{
				x            = solidObject[i].rect.left - w;						 // ���������� ������� ����
				dx           = 0;													 // ������������� ������� ����
				goingForward = false;												 // ������ �����������
			}
			else
			{
				x            = solidObject[i].rect.left + solidObject[i].rect.width; // ���������� ������� ����
				dx           = 0;													 // ������������� ������� ����
				goingForward = true;												 // ������ �����������
			}
		}
	}
}

void Bat::collisionWithACharacter(Skeleton& skeleton)
{
	if ((skeleton.getRect().intersects(wakeUpTheBat.rect)) // ���� ������ �������� ������� ����
		&& (sleep)) sleep = false;						   // �� ��� �����������

	if (state != hit && state != dies)																				 // ���� �� ��������� � �� �������
	{																												
		if ((skeleton.state == Skeleton::attack) && (int(skeleton.currentFrame) == 7) &&							 // �������� ��������� ������� ���� 
			(skeleton.goingForward ? skeleton.getRect(true,  33, 2).intersects(getRect(false, 0, 0, true, 4, -27)) : // � ���� ��������� �������� �����
									 skeleton.getRect(true, -11, 2).intersects(getRect(false, 0, 0, true, 4, -27))))	
		{
				state = hit;		
				currentFrame = 0;
		}
		else if (skeleton.goingForward ? skeleton.getRect(true, 0, 18).intersects(goingForward ? getRect(true, 22, 2, true, 4, -27) : getRect(true, -2, -2, true, 4, -27)) : // ��������� ������������ ������� � ������� ���� 
										 skeleton.getRect(true, 4, 18).intersects(goingForward ? getRect(true, 22, 2, true, 4, -27) : getRect(true, -2, -2, true, 4, -27)))
		{
			if ((skeleton.state != Skeleton::reborn) || ((skeleton.state == Skeleton::reborn) // ���� ������ ������� �� ������������
				&& (int(skeleton.currentFrame) >= 0) && (int(skeleton.currentFrame) <= 9)))	  // ��� ���� ������ ������� ������������ � �� ��� �����������								  
			{
				if (state != attack)														  // ���� ������ ������� ���� �� �������
				{
					state = attack;															  // ������ ������� ���� -> �����
					currentFrame = 0;														  // �������� ������������ ������� ����
				}
				if ((skeleton.state != Skeleton::hit) && ((int(currentFrame) >= 5) &&		  // ���� ������� ��� �������, �� ������ ���������
					(int(currentFrame) <= 10)))
				{
					skeleton.state = Skeleton::hit;											  // ������ ������� -> ����
					skeleton.currentFrame = 0;												  // �������� ������������ �������
				}
			}
		}
	}
}

void Bat::update(Skeleton& skeleton, float time) // ������� ���������� ���������
{
	switch (state) // ���������� �������
	{
	case wake:	   // ���� �����������

		batSprite.setOrigin(sf::Vector2f(22, 53)); // ������ ���������� ��������� ������� ������� ����
		batSprite.setTexture(batTextures[0]);	   // ������ �������� ����������� 
		
		if (sleep)			  // ���� ����
		{
			currentFrame = 0; // ����� �������� �������������
		}
		else				  // �����
		{
			currentFrame += 10 * time; // �������� �������� 10 ������ � ������� 
			if (currentFrame > 8)	   // ���� ������� �� ����� ��������
			{
				state = walk;		   // ������ -> ��������
			}
		}

		goingForward ? batSprite.setTextureRect(IntRect(int(currentFrame) * 64, 0, 64, 64)) :		// ���� �� ����� ��������� �����, �� �������� ����� �������� �����
						batSprite.setTextureRect(IntRect(int(currentFrame) * 64 + 64, 0, -64, 64)); // ����� �����

		w  = 20; // ������ ������
		h  = -2; // ������ ������
		dx =  0; // ����� ��������

		break;   // ��������� ��������

	case walk:     // ���� ������

		batSprite.setOrigin(sf::Vector2f(22, 69)); // ������ ���������� ��������� ������� ������� ����
		batSprite.setTexture(batTextures[1]);	   // ������ �������� �������� 

		currentFrame += 10 * time;																	// �������� �������� 10 ������ � �������
		if (currentFrame > 6) currentFrame = 0;														// �������� ������������ ��� ��������� ��������
		goingForward ? batSprite.setTextureRect(IntRect(int(currentFrame) * 64, 0, 64, 64)) :		// ���� �� ����� ��������� �����, �� �������� ����� �������� �����
						batSprite.setTextureRect(IntRect(int(currentFrame) * 64 + 64, 0, -64, 64)); // ����� �����

		w = 20;									 // ������ ������
		h = -2;									 // ������ ������
		goingForward ? dx = speed : dx = -speed; // ������ �������� �� x

		break;									 // ��������� ��������
	
	case attack:   // ���� �������

		batSprite.setOrigin(sf::Vector2f(22, 69)); // ������ ���������� ��������� ������� ������� ����
		batSprite.setTexture(batTextures[2]);	   // ������ �������� ��������

		currentFrame += 12 * time; // �������� �������� 12 ������ � �������
		if (currentFrame > 12)	   // ���� ������� �� ����� ��������
		{
			currentFrame = 0;	   // �������� ������������ ��� ��������� ��������
			state        = walk;   // ������ -> �������� 
		}

		goingForward ? batSprite.setTextureRect(IntRect(int(currentFrame) * 64, 0, 64, 64)) :		// ���� �� ����� ��������� �����, �� �������� ����� �������� �����
						batSprite.setTextureRect(IntRect(int(currentFrame) * 64 + 64, 0, -64, 64)); // ����� �����

		w = 20;			                                 // ������ ������
		h = -2;								             // ������ ������
		goingForward ? dx = speed / 2 : dx = -speed / 2; // ������ �������� �� x

		break;									         // ��������� ��������
	
	case hit:      // ���� ���������
	
		batSprite.setOrigin(sf::Vector2f(22, 69)); // ������ ���������� ��������� ������� ������� ����
		batSprite.setTexture(batTextures[4]);	   // ������ �������� ��������

		currentFrame += 8 * time; // �������� �������� 8 ������ � �������
		if (currentFrame > 6)	  // ���� ������� �� ����� ��������
		{
			health--;			  // ������� ��������
			currentFrame = 0;	  // �������� ������������ ��� ��������� ��������
			
			if (health == 0)	  // ���� ����������� �����
			{
				state = dies;	  // ������ -> ������ 
			}
			else				  // �����
			{
				state = walk;     // ������ -> �������� 
			}
		}

		goingForward ? batSprite.setTextureRect(IntRect(int(currentFrame) * 64, 0, 64, 64)) :		// ���� �� ����� ��������� �����, �� �������� ����� �������� �����
						batSprite.setTextureRect(IntRect(int(currentFrame) * 64 + 64, 0, -64, 64)); // ����� �����

		w  = 0; // ������ ������
		h  = 0; // ������ ������
		dx = 0; // ����� ��������

		break;  // ��������� ��������

	case dies:

		batSprite.setOrigin(sf::Vector2f(22, 69)); // ������ ���������� ��������� ������� ������� ����
		batSprite.setTexture(batTextures[3]);	   // ������ �������� ������ 

		if (dead)			  // ���� �����
		{
			currentFrame = 6; // ����� �������� �������������
		}
		else				  // �����
		{
			currentFrame += 10 * time; // �������� �������� 10 ������ � ������� 
			if (currentFrame > 6)	   // ���� ������� �� ����� ��������
			{
				dead = true;		   // ������� ���� ������		
			}
		}

		goingForward ? batSprite.setTextureRect(IntRect(int(currentFrame) * 64, 0, 64, 64)) :		// ���� �� ����� ��������� �����, �� �������� ����� �������� �����
						batSprite.setTextureRect(IntRect(int(currentFrame) * 64 + 64, 0, -64, 64)); // ����� �����

		w  = 0; // ������ ������
		h  = 0; // ������ ������
		dx = 0; // ����� ��������

		break;  // ��������� ��������
	}
	
	if (!dead)							   // ���� ������� ���� ����
	{
		collisionWithACharacter(skeleton); // ��������� ������������ �� ��������
		
		x += dx * time;				       // ������ ���������� x
		y += dy * time;
		checkCollisionWithMap();		   // ��������� ������������ �� ������

		batSprite.setPosition(x, y);       // ������ ������� ������� ����
	}
}
