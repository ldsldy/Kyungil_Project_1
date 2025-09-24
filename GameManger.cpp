#include "GameManager.h"
#include "Player.h"
#include "MapManager.h"
#include "EnemyManager.h"
#include "ItemManager.h"

GameManager::GameManager()
{
	UserPlayer = new Player;
	CurrentMapManager = new MapManager;
	CurrentEnemyManager = new EnemyManager;
	CurrentItemManager = new ItemManager;
}
GameManager::~GameManager()
{
	delete UserPlayer;
	delete CurrentMapManager;
	delete CurrentEnemyManager;
	delete CurrentItemManager;
}

void GameManager::Run()
{
	Update();
}

bool GameManager::CanPlayerMove()
{
	// �÷��̾ ���� ���� ��ǥ�� �̸� Ȯ���� ��ǥ ����
	Point PrecUserPos = UserPos;
	if (UserDirection == Direction::Up)
	{
		PrecUserPos.y = UserPos.y - 1;
	}
	if (UserDirection == Direction::Down)
	{
		PrecUserPos.y = UserPos.y + 1;
	}
	if (UserDirection == Direction::Left)
	{
		PrecUserPos.x = UserPos.x - 1;
	}
	if (UserDirection == Direction::Right)
	{
		PrecUserPos.x = UserPos.x + 1;
	}
	
	// �÷��̾ ���� ���� ��ǥ�� ���̳� ������ ���� ���̶�� false
	if (CurrentMapManager->GetMap()->IsWall(PrecUserPos.x, PrecUserPos.y)
		|| !(CurrentMapManager->GetMap()->IsValidPosition(PrecUserPos.x, PrecUserPos.y)))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void GameManager::Update()
{
	UserDirection = UserPlayer->GetMoveDirection();
	UserPos = UserPlayer->GetPlayerPose();
}
