#pragma once

#include "TmxLevel.h" // ���������� ��� ������ ����
#include <vector>     // ���������� �������

using namespace sf;  // ������������� ������������ ���� sf
using namespace std; // ������������� ������������ ���� std

////////////////////////////////////����� �����-��������//////////////////////////
class Entity
{
protected:

	vector <TmxObject> solidObject;			   // ������� ����� ���������� �������� ����� �����

	float dx, dy, x, y, speed;				   // ������� ����� ���������� ����������� �� x, y; � ���-�� ���������� x, y � ��������

	int w, h;								   // ������� ����� ���������� ������ � ������

	void general�onstructor(float X, float Y); // ����������� ������ ������

public:

	float currentFrame;              // ������� ����� ���������� ������������

	bool goingForward;               // ������� ����� ���������� �����������
	
	FloatRect getRect(bool changeTheWidth = false, int X = 0, int W = 0, bool changeTheHeight = false, int Y = 0, int H = 0); // ������� �������� ��������� � �������� �������
};