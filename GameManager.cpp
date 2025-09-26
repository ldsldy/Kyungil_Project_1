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
    //맵 생성
    GameMapGenerator.GenerateMap(GameMap, 10, 5);

    //플레이어 스폰
	Point PlayerSpawn = GameMapGenerator.GetPlayerSpawn();
    GamePlayer.SetPosition(PlayerSpawn);
	GameMap.SetCell(PlayerSpawn.x, PlayerSpawn.y, CellType::Start);

    //토큰 스폰
    TokenPositions = GameMapGenerator.GetTokenSpawns(TotalTokens);
    for (Point TokenPos : TokenPositions)
    {
		GameMap.SetCell(TokenPos.x, TokenPos.y, CellType::Token);
    }

	//적 스폰
    SpawnEnemies();

    //출구 배치
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
            //토큰 충돌 체크
            if (GamePlayer.DetectedTokenCollision(GameMap))
            {
                TotalTokens = TotalTokens - 1;
                cout << "Token Collected! Remaining: " << TotalTokens << endl;

                Point PlayerPos = GamePlayer.GetPosition();
				GameMap.SetCell(PlayerPos.x, PlayerPos.y, CellType::Floor);
            }
        }
        //모든 토큰을 모으면 출구 오픈
        if (IsAllTokensCollected() && !IsExitOpen)
        {
            IsExitOpen = true;
        }

        //모든 토큰을 모은 상태에서 출구에 도착하면 게임 클리어
        if (IsExitOpen && GamePlayer.GetPosition() == ExitPosition)
        {
            cout << "Clear";
            CurrentGameState = GameState::Clear;
        }

        //모든 토큰을 모으지 못한 상태에서 출구에 도착하면 경고 메시지 출력
        if (!IsAllTokensCollected() && GamePlayer.GetPosition() == ExitPosition)
        {
            cout << "The exit is locked. Collect all tokens first!\n";
        }
	}

    //적 업데이트
    for (Enemy& GameEnemy : GameEnemies)
    {
        GameEnemy.Update(GamePlayer.GetPosition(), GameMap);
    }

    //적과 충돌하면 게임 오버
    if (IsConllisionEnemies())
    {
		CurrentGameState = GameState::GameOver;
    }
}

void GameManager::Print()
{
    //적의 위치에 적 표시를 위해 임시로 셀 타입 변경
	map<Point, CellType> EnemyPosMap;
    for (Enemy GameEnemy : GameEnemies)
    {
		Point EnemyPos = GameEnemy.GetPosition();
        EnemyPosMap.insert({ EnemyPos, GameMap.GetCell(EnemyPos.x, EnemyPos.y)});
        GameMap.SetCell(EnemyPos.x, EnemyPos.y, CellType::Enemy);
    }

    GameMap.Print(GamePlayer.GetPosition());
    //GameMap.PrintDarkMode(GamePlayer.GetPosition());

    //프린트 후 원래 셀 타입으로 복원
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

