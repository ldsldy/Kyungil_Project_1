#include "Enemy.h"
#include "Map.h"
#include <set>
#include <map>
#include <queue>
#include <cmath>

//BFS는 목표에서 현재위치까지의 경로 탐색 => back으로 이동할 위치를 얻으면 무조건! pop으로 제거

void Enemy::CashingRoomCenters(Map& InMap)
{
	RoomCenters = InMap.GetRoomCenters();
}

vector<Point> Enemy::BFSFindPath(const Point& InStart, const Point& InTarget, Map& InMap)
{
	if (InStart == InTarget)
		return {};

	queue<Point> VisitQueue;
	set<Point> VisitedSet;			// 방문한 노드
	map<Point, Point> CameFrom;		//<현재 노드, 바로 전의 노드> <= backTracking 용

	VisitQueue.push(InStart);
	VisitedSet.insert(InStart);

	//Up, Down, Left, Right
	Point Directions[] = { {0,-1},{0,1},{-1,0},{1,0} };

	//BFS
	while (!VisitQueue.empty())
	{
		Point Current = VisitQueue.front();
		VisitQueue.pop();


		if (Current == InTarget)
		{
			//목적지 도착하면 백트래킹
			vector<Point> Path;
			Point BackStep = InTarget;
			//시작점에 도달할 때까지
			//CameFrom을 통해 바로 전 노드로 이동
			while (!(BackStep == InStart))
			{
				Path.push_back(BackStep);
				BackStep = CameFrom[BackStep];
			}
			/*reverse(Path.begin(), Path.end());*/
			return Path;
		}

		//목적지가 아니면 주변 탐색
		for (Point Dir : Directions)
		{
			Point Next = Current + Dir;

			//갈 수 있고 방문한 적이 없다
			if (InMap.IsWalkable(Next.x, Next.y)
				&& VisitedSet.find(Next) == VisitedSet.end())
			{
				VisitedSet.insert(Next);
				CameFrom[Next] = Current; //<다음노드, 현재노드(다음노드가 직전에 들른곳)>
				VisitQueue.push(Next);
			}
		}
	}
	//모든 곳을 다 돌아도 못 찾음
	return {};
}

void Enemy::InActionPatrol(Map& InMap)
{
	if (PatrolPath.empty())
	{
		PatrolPath = BFSFindPath(Position, RoomCenters[rng() % RoomCenters.size()], InMap);
	}
	else
	{
		Position = PatrolPath.back();
		PatrolPath.pop_back();
	}
}

void Enemy::InActionChasing(const Point& InPlayerPos, Map& InMap)
{
	//일정 횟수마다 경로 재탐색
	if (PathUpdateCounter > PathUpdateThreshold)
	{
		ChasingPath = BFSFindPath(Position, InPlayerPos, InMap);
		PathUpdateCounter = 0;
	}

	if (!ChasingPath.empty())
	{
		Position = ChasingPath.back();
		ChasingPath.pop_back();
	}
	PathUpdateCounter++;
}

//void Enemy::InActionReposing()
//{
//	//지침 카운트가 일정 이상 차오르면 플레이어가 도망가도록 정지
//}

bool Enemy::IsFindPlayer(const Point& InPlayerPos, const int InDetectionRange)
{
	int DistX = abs(Position.x - InPlayerPos.x);
	int DistY = abs(Position.y - InPlayerPos.y);

	bool InRange = (DistX * DistX + DistY * DistY) <= InDetectionRange * InDetectionRange;
	if (InRange)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::Update(const Point& InPlayerPos, Map& InMap)
{
	// 플레이어를 발견하면 추적 모드로 전환하며 순찰 가던 경로를 초기화
	if (IsFindPlayer(InPlayerPos, 6))
	{
		PatrolPath.clear();	// 순찰 경로 초기화
		CurrentState = EnemyState::Chasing;
	}
	else
	{
		CurrentState = EnemyState::Patrol;
	}

	// 추적 중이라면 추적이 최우선 =>
	// 추적 중이 아니지만 추적 경로가 남아있다면 처리=>
	// 추적 중이 아니고 추적 경로도 없다면 순찰
	if (CurrentState == EnemyState::Chasing)
	{
		InActionChasing(InPlayerPos, InMap);
	}
	else if (CurrentState == EnemyState::Patrol && !ChasingPath.empty()) 
	{
		Position = ChasingPath[PathUpdateCounter];
		PathUpdateCounter++;
	}
	else 
	{
		InActionPatrol(InMap);
	}
}


