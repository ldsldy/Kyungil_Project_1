#pragma once
#include "Point.h"
#include "EnumClass.h"
#include <vector>
#include <random>

using namespace std;

class Map;

class Enemy
{
private:
	Point Position;

	int PathUpdateCounter;			//경로 재탐색을 위한 카운터(임계치를 넘으면 실시)
	const int PathUpdateThreshold;	//경로 재탐색하기까지의 시간
	int ExhaustedCount;				//플레이어를 추적하다 지침을 나타내기 위한 카운터
	int ExhaustedThreshold;			//지침 카운터가 이 값을 넘으면 잠시 휴식
	int RestTime;					//여기서는 회복까지 걸리는 시간 //탐색 범위와 같게 혹은 +1
	int DetectionRange;				//적의 탐색 범위
	

	EnemyState CurrentState;	//현재 상태: 순찰, 추적, 휴식
	vector<Point> ChasingPath;	//플레이어 추적 경로 저장
	vector<Point> PatrolPath;	//다음 방 중심 좌표로 이동 경로 저장
	vector<Point> RoomCenters;

	mt19937 rng;
public:
	Enemy() :Position(0, 0), PathUpdateCounter(0), PathUpdateThreshold(3), ExhaustedCount(0), ExhaustedThreshold(8),
		RestTime(6), DetectionRange(6), rng(random_device{}()), CurrentState(EnemyState::Patrol){}

	//적의 정보를 얻거나 설정
	inline const Point GetPosition() const { return Position; }
	inline void SetPosition(const Point& InPos) { Position = InPos; }
	inline const EnemyState GetCurrentState() const { return CurrentState; }

	//플레이어 위치를 받아서 경로 탐색 후 이동
	void Update(const Point& InPlayerPos, Map& InMap);

	//맵의 방 중심들의 좌표를 받아 캐싱
	void CashingRoomCenters(Map& InMap);
	
	//경로 정보 얻기(디버깅용)
	inline const vector<Point> GetChasingPath() const { return ChasingPath; }
	inline const vector<Point> GetPatrolPath() const { return PatrolPath; }

	//추적 경로 재탐색 관련 정보 얻기(디버깅용)
	inline const int GetPathUpdateCounter() const { return PathUpdateCounter; }
	inline const int GetPathUpdateThreshold() const { return PathUpdateThreshold; }

	

private:
	/// <summary>
	/// 타겟의 위치까지의 경로를 BFS로 탐색
	/// </summary>
	/// <param name="InStart">자신의 위치</param>
	/// <param name="InTarget">타겟의 위치</param>
	/// <param name="InMap">경로를 탐색할 맵</param>
	/// <returns>목표에서 자신까지의 경로의 좌표 벡터</returns>
	vector<Point> BFSFindPath(const Point& InStart, const Point& InTarget, Map& InMap);

	//순찰상태(방과 방 사이를 돌아다닌다)
	void InActionPatrol(Map& InMap);
	//추적상태(플레이어 위치로 이동)
	void InActionChasing(const Point& InPlayerPos, Map& InMap);

	/// <summary>
	/// 플레이어가 일정 범위 안에 있는지 확인하는 함수
	/// </summary>
	/// <param name="InPlayerPos">플레이어의 위치</param>
	/// <param name="InMap"></param>
	/// <returns></returns>
	bool IsFindPlayer(const Point& InPlayerPos, const int InDetectionRange);
};

//추적 범위(기본, 토큰이 다 사라지면 맵 전체)
//플레이어와 달리기가 같아서 한번 추적하면 계속 추적하니 일정 셀을 움직이면 잠시 휴식
//적 발견시 추적 이동(플레이어 위치)

