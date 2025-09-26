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
    ExitPosition = GameMapGenerator.GetExitSpawn();
    GameMap.SetCell(ExitPosition.x, ExitPosition.y, CellType::Exit);

    //맵의 방 중심 좌표를 적에게 캐싱
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
            cout << "All Tokens Collected! Exit is now open.\n";
            //정지 함수 추가 가능
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
    GameEnemy.Update(GamePlayer.GetPosition(), GameMap);

    //적과 충돌하면 게임 오버
    if (IsConllisionEnemy())
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

bool GameManager::IsConllisionEnemy()
{
    return GamePlayer.GetPosition() == GameEnemy.GetPosition();
}

void GameManager::CashingRoomCentersToEnemy()
{
	GameEnemy.CashingRoomCenters(GameMap);
}

//정보 출력, 적 경로 표시
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
    //맵의 정보
	cout << "Map Size: " << GameMap.GetWidth() << " x " << GameMap.GetHeight() << endl;
	cout << "Total Tokens: " << TotalTokens << endl;
	cout << "Is Exit Open: " << (IsExitOpen ? "Yes" : "No") << endl;
	cout << "Exit Position: (" << ExitPosition.x << ", " << ExitPosition.y << ")" << endl;
	cout << "Total Room: " << GameMap.GetRoomCenters().size() << endl;

    //플레이어 정보
	cout << "Player Position: (" << GamePlayer.GetPosition().x << ", " << GamePlayer.GetPosition().y << ")" << endl;
	cout << "Collision with Enemy: " << (IsConllisionEnemy() ? "Yes" : "No") << endl;
	cout << "Collision with Token: " << (GamePlayer.DetectedTokenCollision(GameMap) ? "Yes" : "No") << endl;

    //적의 정보
 /*   cout << "Enemy Update Counter: " << GameEnemy.GetPathUpdateCounter() << endl;
    cout << "Enemy Update ThreshHold: " << GameEnemy.GetPathUpdateThreshold() << endl;
    if (GameEnemy.GetPathUpdateCounter() > GameEnemy.GetPathUpdateThreshold())
    {
        cout << "적이 경로를 재탐색 합니다." << endl;
    }*/

    //게임 상태
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
                cout << "■";
                break;
            case CellType::Floor:
                cout.width(2);
                cout << " ";
                break;
            case CellType::Token:
                cout.width(2);
                cout << "T";
                //cout << "★"; 
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
