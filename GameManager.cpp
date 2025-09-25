#include "GameManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

GameManager::GameManager()
    : GameMap(64, 64), IsExitOpen(false), CurrentGameState(GameState::Playing),
    TotalTokens(5) {}

void GameManager::Run()
{
    Init();

    while (CurrentGameState == GameState::Playing)
    {
        Print();
        Update();
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
    GameEnemy.SetPosition(GameMapGenerator.GetEnemySpawn());

    //출구 배치
    Point ExitSpawn = GameMapGenerator.GetExitSpawn();
    GameMap.SetCell(ExitSpawn.x, ExitSpawn.y, CellType::Exit);
}

void GameManager::Update()
{
    Direction MoveDir = GamePlayer.GetInputDirection();

	//플레이어 이동
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
        CheckGameProgress();
	}

    //적 업데이트
    GameEnemy.Update(GamePlayer.GetPosition(), GameMap);

    //적과 충돌하면 게임 오버
    if (IsContactEnemy())
    {
		CurrentGameState = GameState::GameOver;
    }
}

void GameManager::Print()
{
    //적의 위치에 적 표시를 위해 임시로 셀 타입 변경
	Point EnemyPos = GameEnemy.GetPosition();
	CellType StatedCell = GameMap.GetCell(EnemyPos.x, EnemyPos.y);
	GameMap.SetCell(EnemyPos.x, EnemyPos.y, CellType::Enemy);

	GameMap.Print(GamePlayer.GetPosition());

    //프린트 후 원래 셀 타입으로 복원
	GameMap.SetCell(EnemyPos.x, EnemyPos.y, StatedCell);
}

bool GameManager::IsContactEnemy()
{
    return GamePlayer.GetPosition() == GameEnemy.GetPosition();
}

void GameManager::CheckGameProgress()
{
    //모든 토큰을 모으면 출구 오픈
    if (IsAllTokensCollected() && !IsExitOpen)
    {
        IsExitOpen = true;
        cout << "All Tokens Collected! Exit is now open.\n";
        //정지 함수 추가 가능
    }

    //모든 토큰을 모은 상태에서 출구에 도착하면 게임 클리어
    if(IsExitOpen && GamePlayer.GetPosition() == ExitPosition)
    {
        CurrentGameState = GameState::Clear;
	}

    //모든 토큰을 모으지 못한 상태에서 출구에 도착하면 경고 메시지 출력
    if (!IsAllTokensCollected() && GamePlayer.GetPosition() == ExitPosition)
    {
		cout << "The exit is locked. Collect all tokens first!\n";
    }
}
