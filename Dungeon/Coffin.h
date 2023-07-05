#pragma once

#include "Skeleton.h" // ���������� ����� �������

class Coffin
{
	friend class Skeleton;							  // ������ � ������� �������

private:

	TmxObject coffin;								  // ������� ������ ����� ����
	
	Texture coffinTexture;		                      // ������ �������� �������

	float hit;										  // ������� ���������� ���������� �� ���������� ������

	bool  hited;									  // ������� ���������� ���������� �� ����

	void collisionWithACharacter(Skeleton& skeleton); // �������� �� ������������ � ����������
	
public:

	Sprite coffinSprite;							  // ������� ������

	void Constructor(TmxLevel& Level, string num);	  // ����������� �������

	void update(Skeleton& skeleton);				  // ������� ���������� �������
};