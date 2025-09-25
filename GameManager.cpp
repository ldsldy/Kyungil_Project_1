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
    GameEnemy.SetPosition(GameMapGenerator.GetEnemySpawn());

    //�ⱸ ��ġ
    Point ExitSpawn = GameMapGenerator.GetExitSpawn();
    GameMap.SetCell(ExitSpawn.x, ExitSpawn.y, CellType::Exit);
}

void GameManager::Update()
{
    Direction MoveDir = GamePlayer.GetInputDirection();

	//�÷��̾� �̵�
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
        CheckGameProgress();
	}

    //�� ������Ʈ
    GameEnemy.Update(GamePlayer.GetPosition(), GameMap);

    //���� �浹�ϸ� ���� ����
    if (IsContactEnemy())
    {
		CurrentGameState = GameState::GameOver;
    }
}

void GameManager::Print()
{
    //���� ��ġ�� �� ǥ�ø� ���� �ӽ÷� �� Ÿ�� ����
	Point EnemyPos = GameEnemy.GetPosition();
	CellType StatedCell = GameMap.GetCell(EnemyPos.x, EnemyPos.y);
	GameMap.SetCell(EnemyPos.x, EnemyPos.y, CellType::Enemy);

	GameMap.Print(GamePlayer.GetPosition());

    //����Ʈ �� ���� �� Ÿ������ ����
	GameMap.SetCell(EnemyPos.x, EnemyPos.y, StatedCell);
}

bool GameManager::IsContactEnemy()
{
    return GamePlayer.GetPosition() == GameEnemy.GetPosition();
}

void GameManager::CheckGameProgress()
{
    //��� ��ū�� ������ �ⱸ ����
    if (IsAllTokensCollected() && !IsExitOpen)
    {
        IsExitOpen = true;
        cout << "All Tokens Collected! Exit is now open.\n";
        //���� �Լ� �߰� ����
    }

    //��� ��ū�� ���� ���¿��� �ⱸ�� �����ϸ� ���� Ŭ����
    if(IsExitOpen && GamePlayer.GetPosition() == ExitPosition)
    {
        CurrentGameState = GameState::Clear;
	}

    //��� ��ū�� ������ ���� ���¿��� �ⱸ�� �����ϸ� ��� �޽��� ���
    if (!IsAllTokensCollected() && GamePlayer.GetPosition() == ExitPosition)
    {
		cout << "The exit is locked. Collect all tokens first!\n";
    }
}
