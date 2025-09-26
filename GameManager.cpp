#include "GameManager.h"
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

GameManager::GameManager()
    : GameMap(MapWidth, MapHeighth), IsExitOpen(false), CurrentGameState(GameState::Playing),
    TotalTokens(4), IsDebugMode(false) {}

void GameManager::Run()
{
    Init();

    while (CurrentGameState == GameState::Playing)
    {
        Print();
        Update();
        system("cls");
		cout << "Tokens Remaining: " << TotalTokens << endl;
        if(IsExitOpen)
            cout << "Exit is Open!\n";
    }
    
    if (CurrentGameState == GameState::GameOver)
       cout << "Game Over!\n";
    else if (CurrentGameState == GameState::Clear)
        cout << "Congratulations. You Escaped Safely!\n";
}

void GameManager::Init()
{
    //�� ����
    GameMapGenerator.GenerateMap(GameMap, 10, 5);

    //�÷��̾� ����
	Point PlayerSpawn = GameMapGenerator.GetPlayerSpawn();
    GamePlayer.SetPosition(PlayerSpawn);
	GameMap.SetCell(PlayerSpawn.x, PlayerSpawn.y, CellType::Start);

    //��ū ����
    TokenPositions = GameMapGenerator.GetTokenSpawns(TotalTokens);
    for (Point TokenPos : TokenPositions)
    {
		GameMap.SetCell(TokenPos.x, TokenPos.y, CellType::Token);
    }

	//�� ����
    SpawnEnemies();

    //�ⱸ ��ġ
    ExitPosition = GameMapGenerator.GetExitSpawn();
    GameMap.SetCell(ExitPosition.x, ExitPosition.y, CellType::Exit);
}

void GameManager::Update()
{
    Direction MoveDir = GamePlayer.GetInputDirection();

    if(MoveDir != Direction::None)
    {
        bool IsMoved = GamePlayer.Move(MoveDir, GameMap);
        if (IsMoved)
        {
            //��ū �浹 üũ
            if (GamePlayer.DetectedTokenCollision(GameMap))
            {
                TotalTokens = TotalTokens - 1;
                cout << "Token Collected! Remaining: " << TotalTokens << endl;

                Point PlayerPos = GamePlayer.GetPosition();
				GameMap.SetCell(PlayerPos.x, PlayerPos.y, CellType::Floor);
            }
        }
        //��� ��ū�� ������ �ⱸ ����
        if (IsAllTokensCollected() && !IsExitOpen)
        {
            IsExitOpen = true;
        }

        //��� ��ū�� ���� ���¿��� �ⱸ�� �����ϸ� ���� Ŭ����
        if (IsExitOpen && GamePlayer.GetPosition() == ExitPosition)
        {
            cout << "Clear";
            CurrentGameState = GameState::Clear;
        }

        //��� ��ū�� ������ ���� ���¿��� �ⱸ�� �����ϸ� ��� �޽��� ���
        if (!IsAllTokensCollected() && GamePlayer.GetPosition() == ExitPosition)
        {
            cout << "The exit is locked. Collect all tokens first!\n";
        }
	}

    //�� ������Ʈ
    for (Enemy& GameEnemy : GameEnemies)
    {
        GameEnemy.Update(GamePlayer.GetPosition(), GameMap);
    }

    //���� �浹�ϸ� ���� ����
    if (IsConllisionEnemies())
    {
		CurrentGameState = GameState::GameOver;
    }
}

void GameManager::Print()
{
    //���� ��ġ�� �� ǥ�ø� ���� �ӽ÷� �� Ÿ�� ����
	map<Point, CellType> EnemyPosMap;
    for (Enemy GameEnemy : GameEnemies)
    {
		Point EnemyPos = GameEnemy.GetPosition();
        EnemyPosMap.insert({ EnemyPos, GameMap.GetCell(EnemyPos.x, EnemyPos.y)});
        GameMap.SetCell(EnemyPos.x, EnemyPos.y, CellType::Enemy);
    }

    GameMap.Print(GamePlayer.GetPosition());
    //GameMap.PrintDarkMode(GamePlayer.GetPosition());

    //����Ʈ �� ���� �� Ÿ������ ����
    for(auto iter = EnemyPosMap.begin(); iter != EnemyPosMap.end(); ++iter)
    {
        Point EnemyPos = iter->first;
        CellType OriginCell = iter->second;
        GameMap.SetCell(EnemyPos.x, EnemyPos.y, OriginCell);
	}
}

void GameManager::SpawnEnemies()
{
	vector<Point> EnemiesSpawns = GameMapGenerator.GetEnemiesSpawn(MaxEnemies);
    for (int i = 0; i < EnemiesSpawns.size(); i++)
    {
        Enemy NewEnemy;
        NewEnemy.CashingRoomCenters(GameMap);
        NewEnemy.SetPosition(EnemiesSpawns[i]);
		GameEnemies.push_back(NewEnemy);
    }
}

bool GameManager::IsConllisionEnemies()
{
    for (Enemy GameEnemy : GameEnemies)
    {
        if (GameEnemy.GetPosition() == GamePlayer.GetPosition())
            return true;
    }
    return false;
}

void GameManager::CashingRoomCentersToEnemy(Enemy& InEnemy)
{
	InEnemy.CashingRoomCenters(GameMap);
}

