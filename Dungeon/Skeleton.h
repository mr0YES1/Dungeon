#pragma once

#include "Entity.h" // ���������� ����� ����� ��������

//////////////////////////////////////////////�����-�������////////////////////////
class Skeleton : public Entity
{
	friend class Bat;														// ������ � ������� ������� ����
	friend class Coffin;													// ������ � ������� ������ 

private:

	Texture skeletonTextures[6];											// ������ �������� �������

	enum { stay, left, right, up, down, attack, reborn, react, hit } state; // ����������� ������� �������: �����, �����, ������, �����, ����, �������, �������������, ���������, ��������� 

	enum { revive, dies, alive, dead } rebirthStatus;						// ����������� ������� ������������: �������, �������, ���, �����

	void control();															// ���������� ���������

	void checkCollisionWithMap(float Dx, float Dy);							// �������� �� ������������

	void cancellationOfActions();											// ����� ������ ��������

	void repulsion(FloatRect rect);											// ����� ������������

public:
	
	Sprite skeletonSprite;													// ������� ������
	
	void Constructor(TmxLevel& Level_1, float X, float Y);					// ����������� ���������

	void update(float time);												// ������� ���������� ���������

	float getPlayerCoordinateX();											// ����� �������� ���������� x

	float getPlayerCoordinateY();											// ����� �������� ���������� y
};