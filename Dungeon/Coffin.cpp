#include "Coffin.h" // ���������� ����� �����

void Coffin::Constructor(TmxLevel& Level, string num)			 // ����������� �������
{
	coffin = Level.GetFirstObject("coffin_" + num);				 // �������� � ������ ������ ����������� ������� ����

	coffinTexture.loadFromFile("Images/Coffin/Coffin.png");		 // ��������� �������� �����

	coffinSprite.setOrigin(Vector2f(2, 16));					 // ������ ���������� ��������� ������� �����
	coffinSprite.setTexture(coffinTexture);						 // �������� �������� ����� 

	coffinSprite.setPosition(coffin.rect.left, coffin.rect.top); // ������������� ������� �����

	hit   = 0;													 // ������ ���������� ������

	hited = false;												 // ������ ����
}

void Coffin::collisionWithACharacter(Skeleton& skeleton) // ����� �������� ������������ �� ��������	
{
	if (skeleton.getRect().intersects(coffin.rect))		 // ��������� ������������
	{
		if (skeleton.state == Skeleton::attack)			 // ���� ������ ����
		{
			if (int(skeleton.currentFrame) == 7) 		 // ��������� ����
			{
				if (!hited)								 // ���� �� ������
				{
					hit += 0.5f;						 // ������� ���� ���
					hited = true;					     // ���� ���������
				}
				if (int(hit) > 2)						 // ���� ����� 4-x ������
				{
					hit = 2;							 // �� �������� 4 �����
				}
			}
			else                                         // �����
			{
				hited = false;							 // ��� �� ���� 
			}
		}
		else if ((skeleton.rebirthStatus == Skeleton::revive) || (skeleton.rebirthStatus == Skeleton::dies)) // ���� �������/�������
		{
			skeleton.cancellationOfActions();			 // �� �������� ��������
		}
		else											 // �����                                                                            
		{
			skeleton.repulsion(coffin.rect);			 // ����� ����������� �� �����		
		}
	}
}

void Coffin::update(Skeleton& skeleton)								// ������� ���������� �������
{	
	coffinSprite.setTextureRect(IntRect(int(hit) * 18, 0, 18, 43)); // ����� ������������ �������� �������

	collisionWithACharacter(skeleton);								// ��������� ������������ �� ��������							
}
