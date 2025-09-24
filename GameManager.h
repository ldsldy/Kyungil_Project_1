#pragma once
#include"EnumClass.h"
#include"Point.h"

extern class Player;
extern class MapManager;
extern class EnemyManager;
extern class ItemManager;

class GameManager
{
public:
	GameManager();
	~GameManager();

	//�ٸ� Ŭ������ �����ؾ��ϴ� ���� ��� ������Ʈ
	void Update();
	//���� ���� �Լ�
	void Run();

	bool CanPlayerMove();
private:
	Direction UserDirection = Direction::Default;
	Point UserPos = 0;
	//��ū�� ������ �ʸŴ����� ���� �޾Ƽ� ����
	//�÷��̾ ��ū �浹�� �˸��� ����=>�ʸŴ������� �˸�
	//��ū�� 0�� �Ǹ� ���Ŵ������� �� ��ü�� �����϶�� �˸�

	//�÷��̾ ������ ȹ���� �˸� => ȹ���� �����ۿ� ���� �� �Ŵ������� �˸�
	//                            => �ʸŴ������� �˸�(������ ��ġ ����)
	Player* UserPlayer;
	MapManager* CurrentMapManager;
	EnemyManager* CurrentEnemyManager;
	ItemManager* CurrentItemManager;
};

