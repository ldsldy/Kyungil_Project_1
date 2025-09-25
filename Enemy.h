#pragma once
#include "Point.h"
#include <vector>
#include <queue>

using namespace std;

class Map;

class Enemy
{
private:
	Point Position;

	vector<Point> BFSFindPath(const Point& InStart, const Point& InTarget, Map& InMap);
	

public:
	Enemy() :Position(0, 0) {}

	inline Point GetPosition() const { return Position; } const
	inline void SetPosition(const Point& InPos) { Position = InPos; }

	void Update(const Point& InPlayerPos, Map& InMap);
};

//추적 범위(기본, 토큰이 다 사라지면 맵 전체) <= 추가 
//플레이어와 달리기가 같아서 한번 추적하면 계속 추적하니 일정 셀을 움직이면 잠시 휴식	<= 추가
//적 발견(플레이어가 범위를 가진게 좋은가? 고민 좀)시 추적 이동(플레이어 위치)
//칸마다 추적하면 너무 부담되니 플레이어가 일정 범위 안에 있는지만 체크하고
//일정 시간마다 다시 업데이트

//경로 표시 디버깅 모드
