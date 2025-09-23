#pragma once
#include "Enemy.h"
#include <vector>

using namespace std;

class EnemyManager
{
public:
	//적 생성(int count)
	//적 전체 제거

	//update 플레이어의 위치에 따른 적 상태 업데이트 (순회<=>추적)
	//set 플레이어가 토큰을 다 먹으면 맵 전체를 추격모드로 변경
	//set 플레이어가 토큰을 먹으면 일정 시간 정지

	//플레이어가 토큰을 다 먹었는지 확인

	//테스트모드: 실시
	//추적 경로, 감지 범위 등 디버그 정보 표시
	//적이 플레이어를 발견했을 때 알림

	//적 리스트 반환(디버깅)
private:
	vector<Enemy*> Enemies;
};

