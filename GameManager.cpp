#include "GameManager.h"
#include <iostream>
#include <algorithm>
using namespace std;

GameManager::GameManager()
    : GameMap(32, 32), IsExitOpen(false), CurrentGameState(GameState::Playing),
    TotalTokens(1), IsDebugMode(false) {}

void GameManager::Run()
{
    Init();

    IsDebugMode = false;

    if (IsDebugMode)
    {
        RunDebugMode();
        return;
    }
    else
    {
        while (CurrentGameState == GameState::Playing)
        {
            Print();
            Update();
        }
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
    ExitPosition = GameMapGenerator.GetExitSpawn();
    GameMap.SetCell(ExitPosition.x, ExitPosition.y, CellType::Exit);

    //���� �� �߽� ��ǥ�� ������ ĳ��
    CashingRoomCentersToEnemy();
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
            cout << "All Tokens Collected! Exit is now open.\n";
            //���� �Լ� �߰� ����
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
    GameEnemy.Update(GamePlayer.GetPosition(), GameMap);

    //���� �浹�ϸ� ���� ����
    if (IsConllisionEnemy())
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

bool GameManager::IsConllisionEnemy()
{
    return GamePlayer.GetPosition() == GameEnemy.GetPosition();
}

void GameManager::CashingRoomCentersToEnemy()
{
	GameEnemy.CashingRoomCenters(GameMap);
}

//���� ���, �� ��� ǥ��
void GameManager::RunDebugMode()
{
    while (CurrentGameState == GameState::Playing)
    {
        cout << "=== Debug Mode Activated ===" << endl;
        PrintForDebug();
        Update();
        PrintGameStateForDebug();
    }

    if (CurrentGameState == GameState::GameOver)
        cout << "Game Over!\n";
    else if (CurrentGameState == GameState::Clear)
        cout << "Congratulations. You Escaped Safely!\n";
}

void GameManager::PrintGameStateForDebug()
{
	cout << "=== Enemy State Debug Info ===" << endl;
    //���� ����
	cout << "Map Size: " << GameMap.GetWidth() << " x " << GameMap.GetHeight() << endl;
	cout << "Total Tokens: " << TotalTokens << endl;
	cout << "Is Exit Open: " << (IsExitOpen ? "Yes" : "No") << endl;
	cout << "Exit Position: (" << ExitPosition.x << ", " << ExitPosition.y << ")" << endl;
	cout << "Total Room: " << GameMap.GetRoomCenters().size() << endl;

    //�÷��̾� ����
	cout << "Player Position: (" << GamePlayer.GetPosition().x << ", " << GamePlayer.GetPosition().y << ")" << endl;
	cout << "Collision with Enemy: " << (IsConllisionEnemy() ? "Yes" : "No") << endl;
	cout << "Collision with Token: " << (GamePlayer.DetectedTokenCollision(GameMap) ? "Yes" : "No") << endl;

    //���� ����
 /*   cout << "Enemy Update Counter: " << GameEnemy.GetPathUpdateCounter() << endl;
    cout << "Enemy Update ThreshHold: " << GameEnemy.GetPathUpdateThreshold() << endl;
    if (GameEnemy.GetPathUpdateCounter() > GameEnemy.GetPathUpdateThreshold())
    {
        cout << "���� ��θ� ��Ž�� �մϴ�." << endl;
    }*/

    //���� ����
	cout << "Current Game State: ";
    cout << (CurrentGameState == GameState::Playing ? "Playing" :
		(CurrentGameState == GameState::GameOver ? "GameOver" : "Clear")) << endl;
	cout << "IsAllTokensCollected: " << (IsAllTokensCollected() ? "Yes" : "No") << endl;

	cout << "ExitPosition == PlayerPosition: "  << (ExitPosition == GamePlayer.GetPosition() ? "Yes" : "No") << endl;
	cout << "==============================" << endl;
}

void GameManager::PrintForDebug()
{
    //system("cls");
    for (int y = 0; y < GameMap.GetHeight(); y++)
    {
        for (int x = 0; x < GameMap.GetWidth(); x++)
        {
            if (GamePlayer.GetPosition().x == x && GamePlayer.GetPosition().y == y)
                {
                cout.width(2);
                cout << "P";
                continue;
            }
            else if (GameEnemy.GetPosition().x == x && GameEnemy.GetPosition().y == y)
            {
                cout.width(2);
                cout << "X";
                continue;
            }
            switch (GameMap.GetCell(x, y))
            {
            case CellType::Wall:
                cout.width(2);
                //cout << "W";
                cout << "��";
                break;
            case CellType::Floor:
                cout.width(2);
                cout << " ";
                break;
            case CellType::Token:
                cout.width(2);
                cout << "T";
                //cout << "��"; 
                break;
            case CellType::Exit:
                cout.width(2);
                cout << "E";
                break;
            case CellType::Start:
                cout.width(2);
                cout << "S";
                break;
            default:break;
            }
        }
        cout << endl;
    }
}

//if (IsPath(x, y))
//{
//    cout.width(2);
//    cout << "!";
//}
//else if (GamePlayer.GetPosition().x == x && GamePlayer.GetPosition().y == y)
//{
//    cout.width(2);
//    cout << "P";
//}
//case CellType::Enemy:
//    cout.width(2);
//    cout << "X";
//    break;

bool GameManager::IsPath(int InX, int InY)
{
	vector<Point> ChasingPath = GameEnemy.GetChasingPath();
	vector<Point> PatrolPath = GameEnemy.GetPatrolPath();
    
    if (ChasingPath.empty() && PatrolPath.empty())
        return false;
    else if (ChasingPath.size() > 0)
    {
        return find(ChasingPath.begin(), ChasingPath.end(), Point(InX, InY)) != ChasingPath.end();
    }
    else if (PatrolPath.size() > 0)
    {
        return find(PatrolPath.begin(), PatrolPath.end(), Point(InX, InY)) != PatrolPath.end();
    }
    else
        return false;
}
