#include "Skeleton.h" // ���������� ����� �������

void Skeleton::Constructor(TmxLevel& Level_1, float X, float Y) // ����������� �������
{
	general�onstructor(X, Y);												 // ��������� ����� �����������
	
	solidObject = Level_1.GetAllObjects("solid");							 // �������� ��� ������� �����

	skeletonTextures[0].loadFromFile("Images/Skeleton/Skeleton_Idle.png");   // �������� �������� ����������
	skeletonTextures[1].loadFromFile("Images/Skeleton/Skeleton_Walk.png");   // �������� �������� ��������
	skeletonTextures[2].loadFromFile("Images/Skeleton/Skeleton_Attack.png"); // �������� �������� ����� 
	skeletonTextures[3].loadFromFile("Images/Skeleton/Skeleton_React.png");  // �������� �������� ������� 
	skeletonTextures[4].loadFromFile("Images/Skeleton/Skeleton_Dead.png");   // �������� �������� ������
	skeletonTextures[5].loadFromFile("Images/Skeleton/Skeleton_Hit.png");    // �������� �������� �����

	speed = 26;				// ������������� ��������

	state         = stay;   // ������������� ����������� ������ -> ������
	rebirthStatus = alive;  // ������������� ����������� ������ ������������ -> ���
	
	skeletonSprite.setPosition(x, y); // ������������� ������� �������
}

void Skeleton::control() // ���������� �������
{
	if ((state != attack) && (rebirthStatus != revive) && (rebirthStatus != dies) && (state != react)  && (state != hit)) // ���� ����� �� ����, �� �������/�������, �� ��������� � �� ��������� 
	{
		if ((!(Keyboard::isKeyPressed(Keyboard::D))) && (Keyboard::isKeyPressed(Keyboard::A)))	    // �������� �����
		{
			if (rebirthStatus == dead)  // ���� ����� �����
			{
				state         = reborn;	// ������ -> ������������
				rebirthStatus = revive; // ����� �������
				currentFrame  = 15;		// ������������ ���� � �������� �������
			}
			else
			{
				state = left;			// ������ -> �������� �����
			}
		}
		else if ((!(Keyboard::isKeyPressed(Keyboard::A))) && (Keyboard::isKeyPressed(Keyboard::D))) // �������� ������
		{
			if (rebirthStatus == dead)  // ���� ����� �����
			{
				state         = reborn;	// ������ -> ������������
				rebirthStatus = revive; // ����� �������
				currentFrame  = 15;		// ������������ ���� � �������� �������
			}
			else
			{
				state = right;			// ������ -> �������� ������
			}
		}
		else if ((!(Keyboard::isKeyPressed(Keyboard::S))) && (Keyboard::isKeyPressed(Keyboard::W))) // �������� �����
		{
			if (rebirthStatus == dead)  // ���� ����� �����
			{
				state         = reborn;	// ������ -> ������������
				rebirthStatus = revive; // ����� �������
				currentFrame  = 15;		// ������������ ���� � �������� �������
			}
			else
			{
				state = up;				// ������ -> �������� �����
			}
		}
		else if ((!(Keyboard::isKeyPressed(Keyboard::W))) && (Keyboard::isKeyPressed(Keyboard::S))) // �������� ����
		{
			if (rebirthStatus == dead)  // ���� ����� �����
			{
				state         = reborn;	// ������ -> ������������
				rebirthStatus = revive; // ����� �������
				currentFrame  = 15;		// ������������ ���� � �������� �������
			}
			else
			{
				state = down;			// ������ -> �������� ����
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Left)) // ������� ����� ������ ���� (����)
		{
			if (rebirthStatus == dead)  // ���� ����� �����
			{
				state         = reborn;	// ������ -> ������������
				rebirthStatus = revive; // ����� �������
				currentFrame  = 15;		// ������������ ���� � �������� �������
			}
			else
			{
				state        = attack;	// ������ -> �����
				currentFrame = 0;		// �������� ������������
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::R)) // ������� ������� R ��������� ����������� ���������
		{
			if (rebirthStatus == dead)		 // ���� ����� ����
			{
				rebirthStatus = revive;		 // �������
				currentFrame  = 15;			 // ������������ ���� � �������� �������
			}
			else if (rebirthStatus == alive) // ���� ����� ���
			{
				rebirthStatus = dies;		 // �������
				currentFrame  = 1;			 // ������������ ���� �������
			}

			state = reborn;                  // ������ -> ������������
		}
		else // � ��������� ������ ��������� �� ������� �������
		{
				if (rebirthStatus == alive) state = stay; // ���� �������� ���, �� �� ����� �� �����
		}
	}
}

void Skeleton::checkCollisionWithMap(float Dx, float Dy) // �������� �� ������������ �� ������
{
	for (int i = 0; i < solidObject.size(); i++)		 // �������� �� �������� �����
	{
		if (getRect().intersects(solidObject[i].rect))   // ���� ���������� ������������
		{
			if ((state == attack) || (rebirthStatus == revive) || (rebirthStatus == dies)) // ���� ��������� ��� �������/�������
			{
				cancellationOfActions();												   // �� �������� ��������
			}
			else																		   // �����                                                                            
			{
				repulsion(solidObject[i].rect);											   // ����� ����������� �� �����		
			}
		}
	}
}

void Skeleton::cancellationOfActions()
{
	state         = react; // ������ -> �������
	rebirthStatus = alive; // ����� ��� 
	currentFrame  = 1;	   // �������� ������������

	skeletonSprite.setOrigin(sf::Vector2f(0, 32));  // ������ ���������� ��������� ������� �������
	skeletonSprite.setTexture(skeletonTextures[3]); // ������ �������� �������

	goingForward ? skeletonSprite.setTextureRect(IntRect(0, 0, 22, 32)) :   // ���� �� ����� ��������� �����, �� �������� ����� �������� �����
					skeletonSprite.setTextureRect(IntRect(22, 0, -22, 32)); // ����� �����
}

void Skeleton::repulsion(FloatRect rect)
{
	if (dy > 0) { y = rect.top; dy = 0; }                   // ���� �������� ����
	if (dy < 0) { y = rect.top + rect.height - h; dy = 0; } // ���� �������� �����
	if (dx > 0) { x = rect.left - w; dx = 0; }              // ���� �������� ������
	if (dx < 0) { x = rect.left + rect.width; dx = 0; }     // ���� �������� �����
}

void Skeleton::update(float time) // ������� ���������� ���������
{
	control();     // ������������� ������� �������

	switch (state) // ���������� �������
	{
	case left:     // ���� ��������� �����

		skeletonSprite.setOrigin(sf::Vector2f(0, 33));  // ������ ���������� ��������� ������� �������
		skeletonSprite.setTexture(skeletonTextures[1]); // ������ �������� ������ 

		currentFrame += 13 * time;                                                       // �������� �������� 13 ������ � �������
		if (currentFrame > 13) currentFrame = 0;                                         // �������� ������������ ��� ��������� �������� 
		skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22 + 22, 0, -22, 33)); // ����������� ���������

		w  = 22;     // ������ ������
		h  = -2;     // ������ ������
		dx = -speed; // ������ �������� �� x 
		dy = 0;      // ������ �������� �� y

		goingForward = false; // ����������� �����

		break;                // ��������� ��������

	case right:    // ���� ��������� ������

		skeletonSprite.setOrigin(sf::Vector2f(0, 33));  // ������ ���������� ��������� ������� �������
		skeletonSprite.setTexture(skeletonTextures[1]); // ������ �������� ������  

		currentFrame += 13 * time;												   // �������� �������� 13 ������ � �������
		if (currentFrame > 13) currentFrame = 0;                                   // �������� ������������ ��� ��������� ��������
		skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22, 0, 22, 33)); // ����������� ���������

		w  = 22;    // ������ ������
		h  = -2;    // ������ ������ 
		dx = speed; // ������ �������� �� x
		dy = 0;     // ������ �������� �� y

		goingForward = true; // ����������� ������

		break;               // ��������� ��������

	case up:       // ���� ��������� �����

		skeletonSprite.setOrigin(sf::Vector2f(0, 33));  // ������ ���������� ��������� ������� �������
		skeletonSprite.setTexture(skeletonTextures[1]); // ������ �������� ������ 

		currentFrame += 13 * time;																		 // �������� �������� 13 ������ � �������
		if (currentFrame > 13) currentFrame = 0;														 // �������� ������������ ��� ��������� ��������
		goingForward ? skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22, 0, 22, 33)) :       // ���� �� ����� ��������� �����, �� �������� ����� �������� �����
						skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22 + 22, 0, -22, 33)); // ����� �����

		w  = 22;     // ������ ������
		h  = -2;     // ������ ������
		dx = 0;      // ������ �������� �� x
		dy = -speed; // ������ �������� �� y

		break;      // ��������� ��������

	case down:     // ���� ��������� ����

		skeletonSprite.setOrigin(sf::Vector2f(0, 33));  // ������ ���������� ��������� ������� �������
		skeletonSprite.setTexture(skeletonTextures[1]); // ������ �������� ������ 

		currentFrame += 13 * time;																		 // �������� �������� 13 ������ � �������
		if (currentFrame > 13) currentFrame = 0;														 // �������� ������������ ��� ��������� ��������
		goingForward ? skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22, 0, 22, 33)) :       // ���� �� ����� ��������� �����, �� �������� ����� �������� �����
						skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22 + 22, 0, -22, 33)); // ����� �����

		w  = 22;    // ������ ������
		h  = -2;    // ������ ������
		dx = 0;     // ������ �������� �� x
		dy = speed; // ������ �������� �� y

		break;      // ��������� ��������

	case attack:   // ���� �������

		goingForward ? skeletonSprite.setOrigin(sf::Vector2f(3, 37)) : // ������ ���������� ��������� ������� �������
			skeletonSprite.setOrigin(sf::Vector2f(18, 37));

		skeletonSprite.setTexture(skeletonTextures[2]);				   // ������ �������� ����� 

		currentFrame += 18 * time; // �������� �������� 18 ������ � �������

		if (currentFrame > 18)     // ���� ������� �� ����� ��������
		{
			currentFrame = 0;      // �������� ������������
			state = stay;		   // ������������� ����������� ������ -> ������
		}

		goingForward ? skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 43, 0, 43, 37)) :       // ���� �� ����� ��������� �����, �� �������� ����� �������� �����
						skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 43 + 43, 0, -43, 37)); // ����� �����

		goingForward ? w = 40 : w = -18; // ������ ������
		h  = -2;                         // ������ ������
		dx = 0;                          // ������ �������� �� x
		dy = 0;                          // ������ �������� �� y

		break;                           // ��������� ��������

	case reborn:   // ���� �������������

		goingForward ? skeletonSprite.setOrigin(sf::Vector2f(11, 32)) : // ������ ���������� ��������� ������� �������
			skeletonSprite.setOrigin(sf::Vector2f(0, 32));

		skeletonSprite.setTexture(skeletonTextures[4]);					// ������ �������� ������������

		if (rebirthStatus == dies)         // ���� ������ ����������� -> �������
		{
			currentFrame += 15 * time;     // �������� �������� 15 ������ � �������

			if (currentFrame > 15)         // ���� ������� �� ����� ��������
			{
				currentFrame = 14;	       // ������ ��������� ��������� ���� �������������
				rebirthStatus = dead;	   // C����� ����������� -> ����� 
			}
		}
		else if (rebirthStatus == revive)  // ���� ������ ����������� -> ������������
		{
			currentFrame -= 15 * time;	   // �������� �������� 15 ������ � �������

			if (currentFrame < 1)		   // ���� ������� �� ����� ��������
			{
				currentFrame = 1;		   // ������ ��������� ��������� ���� ������������ 
				rebirthStatus = alive;     // C����� ����������� -> ���
			}
		}
		else if (rebirthStatus == dead)    // ����� ���� �� ������ �����
		{
			currentFrame = 14;			   // ������������ �� ����������
		}

		goingForward ? skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 33, 0, 33, 32)) :		 // ���� �� ����� ��������� �����, �� �������� ����� �������� �����
						skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 33 + 33, 0, -33, 32)); // ����� ����� 

		goingForward ? w = -11 : w = 33; // ������ ������
		h  = -2;						 // ������ ������
		dx = 0;							 // ������ �������� �� x
		dy = 0;							 // ������ �������� �� y

		break;							 // ��������� �������� 

	case react:    // ���� ���������

		currentFrame += 8 * time; // �������� �������� 8 ������ � ������� 
		if (currentFrame > 4)     // ���� ������� �� ����� ��������
		{
			currentFrame = 0;	  // �������� ������������
			state = stay;		  // ������������� ����������� ������ -> ������ 
		}
		goingForward ? skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22, 0, 22, 32)) :       // ���� �� ����� ��������� �����, �� �������� ����� �������� �����
						skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 22 + 22, 0, -22, 32)); // ����� �����  

		w  = 22;  // ������ ������
		h  = -2; // ������ ������
		dx = 0;  // ������ �������� �� x
		dy = 0;  // ������ �������� �� y

		break;   // ��������� ��������

	case hit:

		goingForward ? skeletonSprite.setOrigin(sf::Vector2f(6, 32)) : // ������ ���������� ��������� ������� �������
						skeletonSprite.setOrigin(sf::Vector2f(2, 32));

		skeletonSprite.setTexture(skeletonTextures[5]);				   // ������ �������� ����� 

		currentFrame += 12 * time;  // �������� �������� 12 ������ � �������
		if (currentFrame > 8)	   // ���� ������� �� ����� ��������
		{
			state         = stay;  // ������������� ����������� ������ -> ������
			rebirthStatus = alive; // C����� ����������� -> ���
			currentFrame  = 0;     // �������� ������������
		}
		goingForward ? skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 30, 0, 30, 32)) :		 // ���� �� ����� ��������� �����, �� �������� ����� �������� �����
						skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 30 + 30, 0, -30, 32)); // ����� ����� 

		w  = 0; // ������ ������
		h  = 0; // ������ ������
		dx = 0; // ������ �������� �� x
		dy = 0; // ������ �������� �� y

		break;  // ��������� �������� 
	
	case stay:     // ���� �����

		goingForward ? skeletonSprite.setOrigin(sf::Vector2f(0, 32)) : // ������ ���������� ��������� ������� �������
						skeletonSprite.setOrigin(sf::Vector2f(2, 32));

		skeletonSprite.setTexture(skeletonTextures[0]);				   // ������ �������� ������ 

		currentFrame += 11 * time;																		 // �������� �������� 11 ������ � �������
		if (currentFrame > 11) currentFrame = 0;														 // �������� ������������ ��� ��������� ��������
		goingForward ? skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 24, 0, 24, 32)) :		 // ���� �� ����� ��������� �����, �� �������� ����� �������� �����
						skeletonSprite.setTextureRect(IntRect(int(currentFrame) * 24 + 24, 0, -24, 32)); // ����� ����� 

		w  = 22; // ������ ������
		h  = -2; // ������ ������
		dx = 0;  // ������ �������� �� x
		dy = 0;  // ������ �������� �� y

		break;   // ��������� ��������
	}

	x += dx * time;					  // ������ ���������� x
	y += dy * time;					  // ������ ���������� y

	checkCollisionWithMap(dx, dy);    // ��������� ������������

	skeletonSprite.setPosition(x, y); // ������ ������� �������
}
 
float Skeleton::getPlayerCoordinateX() // ����� �������� ���������� x
{
	return x; // �������� x
}

float Skeleton::getPlayerCoordinateY() // ����� �������� ���������� y
{
	return y; // �������� y
}
