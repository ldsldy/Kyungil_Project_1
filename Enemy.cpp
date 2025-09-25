#include "Enemy.h"
#include "Map.h"
#include <set>
#include <map>

vector<Point> Enemy::BFSFindPath(const Point& InStart, const Point& InTarget, Map& InMap)
{
	if (InStart == InTarget)
		return {};

	queue<Point> VisitQueue; 
	set<Point> VisitedSet;			// 방문한 노드
	map<Point, Point> CameFrom; //<현재 노드, 바로 전의 노드> <= backTracking 용

	VisitQueue.push(InStart);
	VisitedSet.insert(InStart);

	//Up, Down, Left, Right
	Point Directions[] = { {0,-1},{0,1},{-1,0},{1,0} };

	//BFS
	while (!VisitQueue.empty())
	{
		Point Current = VisitQueue.front();
		VisitQueue.pop();

		//목적지 도착하면 백트래킹
		if (Current == InTarget)
		{
			vector<Point> Path;
			Point BackStep = InTarget;
			//시작점에 도달할 때까지
			//CameFrom을 통해 바로 전 노드로 이동
			while (!(BackStep == InStart))
			{
				Path.push_back(BackStep);
				BackStep = CameFrom[BackStep]; 
			}
			reverse(Path.begin(), Path.end());
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

void Enemy::Update(const Point& InPlayerPos, Map& InMap)
{
	vector<Point> Path = BFSFindPath(Position, InPlayerPos, InMap);

	if (!Path.empty())
	{
		Position = Path[0];
	}
}
