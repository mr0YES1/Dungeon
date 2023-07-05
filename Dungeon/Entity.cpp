#include "Entity.h" // ���������� ����� ����� ��������

void Entity::general�onstructor(float X, float Y) // ����������� ������ ������
{
	dx    = 0;			  // ������ ����������� �� x
	dy    = 0;			  // ������ ����������� �� y
	x     = X;            // ������ ���������� x
	y     = Y;            // ������ ���������� y
	speed = 0;		      // ������ ��������

	currentFrame = 0;     // ������ �������� �������������

	w = 1;				  // ������ ������
	h = 1;				  // ������ ������

	goingForward = true;  // ������ ����������� ��������
}

FloatRect Entity::getRect(bool changeTheWidth, int X, int W, bool changeTheHeight, int Y, int H)  // ������� �������� ��������� � �������� �������
{
	if (changeTheWidth && changeTheHeight)    // ���� �������� ������ � ������
	{
		return FloatRect(x + X, y + Y, W, H); // ���������� ���������� � ������� �������
	}
	else if (changeTheWidth)				  // ���� �������� ������
	{
		return FloatRect(x + X, y, W, h);	  // ���������� ���������� � ������� �������
	}
	else if (changeTheHeight)				  // ���� �������� ������					
	{
		return FloatRect(x, y + Y, w, H);	  // ���������� ���������� � ������� �������
	}
	else									  // ���� ������ �� ��������
	{
		return FloatRect(x, y, w, h);		  // ���������� ���������� � ������� �������
	}
}