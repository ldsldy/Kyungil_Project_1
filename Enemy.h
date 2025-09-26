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

	int PathUpdateCounter;
	const int PathUpdateThreshold;
	
	EnemyState CurrentState; //���� ����: ����, ����, �޽�
	vector<Point> ChasingPath;	//�÷��̾� ���� ��� ����
	vector<Point> PatrolPath;	//���� �� �߽� ��ǥ�� �̵� ��� ����
	vector<Point> RoomCenters;

	mt19937 rng;
public:
	Enemy() :Position(0, 0), PathUpdateCounter(0), PathUpdateThreshold(3), rng(random_device{}()){}

	//���� ������ ��ų� ����
	inline const Point GetPosition() const { return Position; }
	inline void SetPosition(const Point& InPos) { Position = InPos; }
	inline const EnemyState GetCurrentState() const { return CurrentState; }

	//�÷��̾� ��ġ�� �޾Ƽ� ��� Ž�� �� �̵�
	void Update(const Point& InPlayerPos, Map& InMap);

	//���� �� �߽ɵ��� ��ǥ�� �޾� ĳ��
	void CashingRoomCenters(Map& InMap);
	
	//��� ���� ���(������)
	inline const vector<Point> GetChasingPath() const { return ChasingPath; }
	inline const vector<Point> GetPatrolPath() const { return PatrolPath; }

	//���� ��� ��Ž�� ���� ���� ���(������)
	inline const int GetPathUpdateCounter() const { return PathUpdateCounter; }
	inline const int GetPathUpdateThreshold() const { return PathUpdateThreshold; }

	

private:
	/// <summary>
	/// Ÿ���� ��ġ������ ��θ� BFS�� Ž��
	/// </summary>
	/// <param name="InStart">�ڽ��� ��ġ</param>
	/// <param name="InTarget">Ÿ���� ��ġ</param>
	/// <param name="InMap">��θ� Ž���� ��</param>
	/// <returns>��ǥ���� �ڽű����� ����� ��ǥ ����</returns>
	vector<Point> BFSFindPath(const Point& InStart, const Point& InTarget, Map& InMap);

	void InActionPatrol(Map& InMap);
	void InActionChasing(const Point& InPlayerPos, Map& InMap);
	void InActionReposing();

	/// <summary>
	/// �÷��̾ ���� ���� �ȿ� �ִ��� Ȯ���ϴ� �Լ�
	/// </summary>
	/// <param name="InPlayerPos">�÷��̾��� ��ġ</param>
	/// <param name="InMap"></param>
	/// <returns></returns>
	bool IsFindPlayer(const Point& InPlayerPos, const int InDetectionRange);
};

//���� ����(�⺻, ��ū�� �� ������� �� ��ü) <= �߰� 
//�÷��̾�� �޸��Ⱑ ���Ƽ� �ѹ� �����ϸ� ��� �����ϴ� ���� ���� �����̸� ��� �޽�	<= �߰�
//�� �߰�(�÷��̾ ������ ������ ������? ��� ��)�� ���� �̵�(�÷��̾� ��ġ)
//ĭ���� �����ϸ� �ʹ� �δ�Ǵ� �÷��̾ ���� ���� �ȿ� �ִ����� üũ�ϰ�

