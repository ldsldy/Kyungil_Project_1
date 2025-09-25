#include "GameManager.h"
#include "Player.h"
#include "MapManager.h"
#include "EnemyManager.h"

class GameManager;

GameManager::GameManager()
{
	CurrentPlayer = new Player;
	CurrentMapManager = new MapManager;
	CurrentEnemyManager = new EnemyManager;
}
GameManager::~GameManager()
{
	delete CurrentPlayer;
	delete CurrentMapManager;
	delete CurrentEnemyManager;
}

void GameManager::Run()
{
	InitGame();

	while (true) 
	{
		CurrentMapManager->PrintMap();
		PlayerMove();
	}
}

void GameManager::InitGame()
{
	CurrentPlayer->SetPosition(GetPlayerSpawnFromMM());
}

Point GameManager::GetPlayerSpawnFromMM() const
{
	return CurrentMapManager->GetPlayerSpawnFromBSP();
}

Point GameManager::GetCurrentPlayerPos() const
{
	cout << "PlayerPos: (" << endl;
	return CurrentPlayer->GetPlayerPose();
}

bool GameManager::CanPlayerMove(Direction InDirection)
{
	// �÷��̾ ���� ���� ��ǥ�� �̸� Ȯ���� ��ǥ ����
	Point PrecPlayerPos = CurrentPlayer->GetPlayerPose();
	if (InDirection == Direction::Up)
	{
		PrecPlayerPos.y = PrecPlayerPos.y - 1;
	}
	if (InDirection == Direction::Down)
	{
		PrecPlayerPos.y = PrecPlayerPos.y + 1;
	}
	if (InDirection == Direction::Left)
	{
		PrecPlayerPos.x = PrecPlayerPos.x - 1;
	}
	if (InDirection == Direction::Right)
	{
		PrecPlayerPos.x = PrecPlayerPos.x + 1;
	}
	
	// �÷��̾ ���� ���� ��ǥ�� ���̳� ������ ���� ���̶�� false
	if (CurrentMapManager->GetMap()->IsWall(PrecPlayerPos.x, PrecPlayerPos.y)
		|| !(CurrentMapManager->GetMap()->IsValidPosition(PrecPlayerPos.x, PrecPlayerPos.y)))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void GameManager::PlayerMove()
{
	UserDirection = CurrentPlayer->GetMoveDirection();

	if (CanPlayerMove(UserDirection))
	{
		//�÷��̾� ��ü�� ��ġ�� ����
		switch (UserDirection)
		{
		case Direction::Up:
			CurrentPlayer->SetPositionY(CurrentPlayerPos.y - 1);
			break;
		case Direction::Down:
			CurrentPlayer->SetPositionY(CurrentPlayerPos.y + 1);
			break;
		case Direction::Left:
			CurrentPlayer->SetPositionX(CurrentPlayerPos.x - 1);
			break;
		case Direction::Right:
			CurrentPlayer->SetPositionY(CurrentPlayerPos.x + 1);
			break;
		case Direction::Default:
			break;
		}
	}
}




//void GameManager::InitGame()
//{
//	UserPlayer->SetPosition(CurrentMapManager->)
//	UserPos
//}

void GameManager::Update()
{
	CurrentPlayerPos = CurrentPlayer->GetPlayerPose();
}

