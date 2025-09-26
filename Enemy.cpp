#include "Enemy.h"
#include "Map.h"
#include <set>
#include <map>
#include <queue>
#include <cmath>

//BFS�� ��ǥ���� ������ġ������ ��� Ž�� => back���� �̵��� ��ġ�� ������ ������! pop���� ����

void Enemy::CashingRoomCenters(Map& InMap)
{
	RoomCenters = InMap.GetRoomCenters();
}

vector<Point> Enemy::BFSFindPath(const Point& InStart, const Point& InTarget, Map& InMap)
{
	if (InStart == InTarget)
		return {};

	queue<Point> VisitQueue;
	set<Point> VisitedSet;			// �湮�� ���
	map<Point, Point> CameFrom;		//<���� ���, �ٷ� ���� ���> <= backTracking ��

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
			//������ �����ϸ� ��Ʈ��ŷ
			vector<Point> Path;
			Point BackStep = InTarget;
			//�������� ������ ������
			//CameFrom�� ���� �ٷ� �� ���� �̵�
			while (!(BackStep == InStart))
			{
				Path.push_back(BackStep);
				BackStep = CameFrom[BackStep];
			}
			/*reverse(Path.begin(), Path.end());*/
			return Path;
		}

		//�������� �ƴϸ� �ֺ� Ž��
		for (Point Dir : Directions)
		{
			Point Next = Current + Dir;

			//�� �� �ְ� �湮�� ���� ����
			if (InMap.IsWalkable(Next.x, Next.y)
				&& VisitedSet.find(Next) == VisitedSet.end())
			{
				VisitedSet.insert(Next);
				CameFrom[Next] = Current; //<�������, ������(������尡 ������ �鸥��)>
				VisitQueue.push(Next);
			}
		}
	}
	//��� ���� �� ���Ƶ� �� ã��
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
	//���� Ƚ������ ��� ��Ž��
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
//	//��ħ ī��Ʈ�� ���� �̻� �������� �÷��̾ ���������� ����
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
	// �÷��̾ �߰��ϸ� ���� ���� ��ȯ�ϸ� ���� ���� ��θ� �ʱ�ȭ
	if (IsFindPlayer(InPlayerPos, 6))
	{
		PatrolPath.clear();	// ���� ��� �ʱ�ȭ
		CurrentState = EnemyState::Chasing;
	}
	else
	{
		CurrentState = EnemyState::Patrol;
	}

	// ���� ���̶�� ������ �ֿ켱 =>
	// ���� ���� �ƴ����� ���� ��ΰ� �����ִٸ� ó��=>
	// ���� ���� �ƴϰ� ���� ��ε� ���ٸ� ����
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


