#include "Enemy.h"
#include "Map.h"
#include <set>
#include <map>

vector<Point> Enemy::BFSFindPath(const Point& InStart, const Point& InTarget, Map& InMap)
{
	if (InStart == InTarget)
		return {};

	queue<Point> VisitQueue; 
	set<Point> VisitedSet;			// �湮�� ���
	map<Point, Point> CameFrom; //<���� ���, �ٷ� ���� ���> <= backTracking ��

	VisitQueue.push(InStart);
	VisitedSet.insert(InStart);

	//Up, Down, Left, Right
	Point Directions[] = { {0,-1},{0,1},{-1,0},{1,0} };

	//BFS
	while (!VisitQueue.empty())
	{
		Point Current = VisitQueue.front();
		VisitQueue.pop();

		//������ �����ϸ� ��Ʈ��ŷ
		if (Current == InTarget)
		{
			vector<Point> Path;
			Point BackStep = InTarget;
			//�������� ������ ������
			//CameFrom�� ���� �ٷ� �� ���� �̵�
			while (!(BackStep == InStart))
			{
				Path.push_back(BackStep);
				BackStep = CameFrom[BackStep]; 
			}
			reverse(Path.begin(), Path.end());
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

void Enemy::Update(const Point& InPlayerPos, Map& InMap)
{
	vector<Point> Path = BFSFindPath(Position, InPlayerPos, InMap);

	if (!Path.empty())
	{
		Position = Path[0];
	}
}
