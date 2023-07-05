#pragma once

#include "Bat.h"      // ���������� ����� ������� ����
#include "Coffin.h"   // ���������� ����� �����

class Level_1 // ������ �������
{
private:

	TmxLevel Main_Objects; // ������� -> �������� �������
	TmxLevel Decorations;  // ������� -> ��������� 
	TmxLevel Jug_1;		   // ������� -> ������ 1
	TmxLevel Jug_2;		   // ������� -> ������ 2
	TmxLevel Jug_3;		   // ������� -> ������ 3
	TmxLevel Candle_1;	   // ������� -> ����� 1
	TmxLevel Candle_2;	   // ������� -> ����� 2
	TmxLevel Coffin_2;	   // ������� -> ���� 2
	TmxLevel Right_Wall;   // ������� -> ������ �����
	TmxLevel Lower_Wall;   // ������� -> ������ �����

	TmxObject player;	   // ������ ������
	TmxObject enemy;	   // ������ �����
	TmxObject exit;		   // ������ �����

	bool characterDrawn;   // ��������� ���������   

public:

	Skeleton skeleton;							  // ������� �������
	Bat bat;									  // ������� ������� ����
	Coffin coffin;								  // ������� ����

	Level_1();                                    // ����������� ������� ������

	void update(int& level, float time);          // ���������� ������

	void orderOfRenderings(RenderWindow& window); // ������������������ ���������
};

class Level_2 // ������ �������
{
private:

	TmxLevel Main_Objects; // ������� -> �������� �������
	TmxLevel Decorations;  // ������� -> ���������
	TmxLevel Arches;	   // ������� -> ����
	TmxLevel Jug_1;		   // ������� -> ������ 1
	TmxLevel Jug_2;		   // ������� -> ������ 2
	TmxLevel Jug_3;		   // ������� -> ������ 3
	TmxLevel Jug_4;		   // ������� -> ������ 4
	TmxLevel Jug_5;		   // ������� -> ������ 5
	TmxLevel Jug_6;		   // ������� -> ������ 6
	TmxLevel Jug_7;		   // ������� -> ������ 7
	TmxLevel Jug_8;		   // ������� -> ������ 8
	TmxLevel Jug_9;		   // ������� -> ������ 9
	TmxLevel Jug_10;	   // ������� -> ������ 10
	TmxLevel Candle_1;	   // ������� -> ����� 1
	TmxLevel Candle_2;	   // ������� -> ����� 2
	TmxLevel Candle_3;	   // ������� -> ����� 3
	TmxLevel Candle_4;	   // ������� -> ����� 4
	TmxLevel Coffin_1;	   // ������� -> ���� 1
	TmxLevel Coffin_2;	   // ������� -> ���� 2
	TmxLevel Chests;	   // ������� -> �����
	TmxLevel Lower_Wall;   // ������� -> ������ �����

	TmxObject player;	   // ������ ������
	TmxObject enemy_1;	   // ������ ����� 1 
	TmxObject enemy_2;	   // ������ ����� 2
	TmxObject exit;		   // ������ �����

	bool characterDrawn;   // ��������� ���������   

public:

	Skeleton skeleton;							  // ������� �������
	Bat bat_1;									  // ������� ������� ���� 1
	Bat bat_2;									  // ������� ������� ���� 2 

	Level_2();									  // ����������� ������� ������

	void update(int& level, float time);		  // ���������� ������

	void orderOfRenderings(RenderWindow& window); // ������������������ ���������
};

class Level_3 // ������ �������
{
private:

	TmxLevel Main_Objects;     // ������� -> �������� �������
	TmxLevel Decorations;      // ������� -> ���������
	TmxLevel Skeletal_�orpses; // ������� -> ����� ��������
	TmxLevel Jug_1;			   // ������� -> ������ 1
	TmxLevel Jug_2;			   // ������� -> ������ 2
	TmxLevel Jug_3;			   // ������� -> ������ 3
	TmxLevel Jug_4;			   // ������� -> ������ 4
	TmxLevel Jug_5;			   // ������� -> ������ 5
	TmxLevel Jug_6;			   // ������� -> ������ 6
	TmxLevel Jug_7;			   // ������� -> ������ 7
	TmxLevel Candle_1;		   // ������� -> ����� 1
	TmxLevel Candle_2;		   // ������� -> ����� 2
	TmxLevel Candle_3;		   // ������� -> ����� 3
	TmxLevel Chests_1;		   // ������� -> ����� 1
	TmxLevel Chests_2;		   // ������� -> ����� 2
	TmxLevel Wooden_Beams_1;   // ������� -> ���������� ����� 1
	TmxLevel Wooden_Beams_2;   // ������� -> ���������� ����� 2
	TmxLevel Lower_Wall;       // ������� -> ������ �����

	TmxObject player;          // ������ ������

	bool characterDrawn;	   // ��������� ���������   

public:

	Skeleton skeleton;							  // ������� �������

	Level_3();		 				              // ����������� �������� ������

	void update(float time);					  // ���������� ������

	void orderOfRenderings(RenderWindow& window); // ������������������ ���������
};
