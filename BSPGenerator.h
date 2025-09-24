#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "Map.h"
#include "Point.h"
using namespace std;

// map -> bsp -> mapmanager -> game manager
Map InMap; //���� ����

struct Room
{
	int x, y;
	int Width, Height;
	int RegionX, RegionY;

	Room() = default;
	Room(int x, int y, int width, int height, int regX=255, int regY=255)
		:x(x), y(y), Width(width), Height(height), RegionX(regX), RegionY(regY) {}

	//���� �߽� ��ǥ ��ȯ
	inline Point GetCenter() const
	{
		return Point(x + Width / 2, y + Height / 2);
	}

	//�� �ȿ� ��ǥ�� ���ԵǴ��� �˻�
	inline bool IsInside(int px, int py) const
	{
		return px >= x && px < x + Width && py >= y && py < y + Height;
	}
};

//BSP��� - �ε��� ��� ���� ���� 
struct BSPNode
{
public:
	int x, y, Width, Height; //�� ��ǥ, ũ��
	int regionX, regionY; // 5*5 ���� �ȿ����� ��ǥ
	int LeftChild;	//���� �ε��� -1�̸� null
	int RightChild; //���� �ε��� -1�̸� null
	int RoomCount; //�� ��尡 �����ϴ� ���� ����

	BSPNode() :LeftChild(-1), RightChild(-1), RoomCount(0) {}
	BSPNode(int x, int y, int width, int height)
		:x(x), y(y), Width(width), Height(height), LeftChild(-1), RightChild(-1), RoomCount(0) {
	}

	//�ʹ� �۾Ƽ� �ɰ� �� ������ �˻�
	inline bool CanSplit() const
	{
		return Width >= 10 || Height >= 10;
	}
	//���� ������� �˻�
	inline bool IsLeaf() const
	{
		return LeftChild == -1 && RightChild == -1;
	}
};

class BSPGenerator
{
private:
	vector<BSPNode> Nodes;
	vector<Room> Rooms;
	int rngState; //���� ���� ������ ���� ���� ����

	int MapSize;
	int RegionSize;
	int NumRegions;
	int MaxTotalRooms;
	int MaxBSPNodes;

	//���� ���� ���� �Լ�(LCG)
	inline int FastRandom()
	{
		rngState = rngState * 1664525U + 1013904223U;
		return rngState;
	}

	//0���� max-1������ ���� ���� ��ȯ
	inline int FastRandomRange(int max)
	{
		return FastRandom() % max;
	}

	//�� ��� �Ҵ�
	inline int AllocateNode(int x, int y, int w, int h)
	{
		//�� ��� ����
		Nodes.emplace_back(x, y, w, h);
		return static_cast<int>(Nodes.size() - 1);
	}

	//�� �� �Ҵ�
	inline void AllocateRoom(int x, int y, int w, int h, int regX, int regY)
	{
		Rooms.emplace_back(x, y, w, h, regX, regY);
	}

	/// <summary>
	/// �� ���� - ��� ���� �� ������ ���� �� ���� �õ�
	/// </summary>
	/// <param name="NodeIndex"></param>
	void CreateRoomsInNode(int NodeIndex);

	/// <summary>
	/// Ư�� ������ �� ����
	/// �� ũ��� ��ġ�� ���� ������ ���� ����
	/// </summary>
	/// <param name="node">����	�� �Ǵ� BSP���</param>
	/// <param name="regX">�� ��° ����</param>
	/// <param name="regY">�� ��° ����</param>
	void CreateRoomInRegion(const BSPNode& node, int regX, int regY);

	/// <summary>
	/// BSP Ʈ�� ����
	/// </summary>
	/// <param name="RegX"></param>
	/// <param name="RegY"></param>
	/// <returns></returns>
	const Room* FindRoomInRegion(int RegX, int RegY) const;

	/// <summary>
	/// �� ���� �����ϴ� ��� ����
	/// </summary>
	/// <param name="InMap">������ ����� ��</param>
	/// <param name="InRoom1">������ �� 1</param>
	/// <param name="InRoom2">����� �� 2</param>
	void ConnectRooms(Map& InMap, const Room& InRoom1, const Room& InRoom2);

	/// <summary>
	/// �� ��ǥ�� �����ϴ� ��� ����
	/// </summary>
	/// <param name="InMap">��θ� ������ ��</param>
	/// <param name="x1">��ǥ1�� x��</param>
	/// <param name="y1">��ǥ1�� y��</param>
	/// <param name="x2">��ǥ2�� x��</param>
	/// <param name="y2">��ǥ2�� y��</param>
	void CreateCorridors(Map& InMap, int x1, int y1, int x2, int y2);

	/// <summary>
	/// �� ���� ĳ��
	/// </summary>
	/// <param name="InMap">������ �޾ƿ� ��</param>
	void CacheMapInfo(const Map& InMap);

	//void DrawRooms(Map& map) const;

public:
	/// <summary>
	/// �� �� ������ �Ÿ� ��� �Լ�
	/// </summary>
	float GetDistanceBetweenRooms(const Room& room1, const Room& room2) const;

	/// <summary>
	/// ��� ���� �߽��� ��ǥ�� ���� ���·� ��ȯ
	/// </summary>
	vector<Point> GetAllRoomCenters() const;

};
