#pragma once

#include "Entity.h"   // ���������� ����� ����� ��������
#include "Skeleton.h" // ���������� ����� �������

//////////////////////////////////////////////����� ������� ����////////////////////////
class Bat : public Entity
{
	friend class Skeleton;							  // ������ � ������� �������
	friend class Level_1;							  // ������ � ������� 1-�� ������
	friend class Level_2;							  // ������ � ������� 2-�� ������

private:

	TmxObject wakeUpTheBat;                           // ������ ����������� ��� ������� ����

	Texture batTextures[5];		                      // ������ ������ ������� �������

	enum { wake, walk, attack, dies, hit } state;	  // ����������� ������� ������� ����: �����������, ���������, �����, ������, ���� 

	int health;										  // ������ ��������

	bool sleep;					                      // ������� ����������, ������� ����������� ���
	bool dead;										  // ������� ����������, ������� ����������� ������

	void checkCollisionWithMap();                     // �������� �� ������������ �� �������

	void collisionWithACharacter(Skeleton& skeleton); // �������� �� ������������ � ����������

public:

	Sprite batSprite;									             // ������� ������

	void Constructor(TmxLevel& Level, float X, float Y, string num); // ����������� ���������

	void update(Skeleton& skeleton, float time);		             // ������� ���������� ���������
};
