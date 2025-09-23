#include "BSPGenerator.h"

void BSPGenerator::CreateRoomsInNode(int NodeIndex)
{
	const BSPNode& node = Nodes[NodeIndex];

	int NumRegionsX = node.Width / RegionSize;	//��� �� ���� ���� ����
	int NumRegionsY = node.Height / RegionSize; //��� �� ���� ���� ����
	
	//�� ������ 70% Ȯ���� �� ����
	for (int regY = 0; regY < NumRegionsY; regY++)
	{
		for (int regX = 0; regX < NumRegionsX; regX++)
		{
			if (FastRandomRange(100) < 70)
			{
				CreateRoomInRegion(node, regX, regY);
			}
		}
	}

}

void BSPGenerator::CreateRoomInRegion(const BSPNode& Node, int RegX, int RegY)
{
	int RegionStartX = Node.x + RegX * RegionSize;	//���� ���� ��ǥ
	int RegionStartY = Node.y + RegY * RegionSize;

	//���� ������ �� ũ�� ���� ����(2*2 ~ 3*3)
	int RoomWidth = 2 + FastRandomRange(2);
	int RoomHeight = 2 + FastRandomRange(2);
	
	//���� ������ �� ��ġ ���� ����
	int MaxPosX = RegionStartX + RegionSize - RoomWidth - 1; //-1�� �� ������ ����
	int MaxPosY = RegionStartY + RegionSize - RoomHeight-1;
	int MinPosX = RegionStartX + 1;	//+1�� �� ������ ����
	int MinPosY = RegionStartY + 1;

	//���� ���� ���� �� �� �ִ��� �˻�
	if (MaxPosX >= MinPosX && MaxPosY >= MinPosY)
	{
		//�� ��ġ ���� ����
		int RoomX = MinPosX + FastRandomRange(MaxPosX - MinPosX + 1); //���� ũ�⸸ŭ ���� ��ġ(+1�� �ִ밪 ������ ����)
		int RoomY = MinPosY + FastRandomRange(MaxPosY - MinPosY + 1);
		//�� �Ҵ�
		// RegionStartX/RegionSize, RegionStartY/RegionSize �� �� ��° �������� ��Ÿ��
		AllocateRoom(RoomX, RoomY, RoomWidth, RoomHeight, RegionStartX/RegionSize, RegionStartY/RegionSize);
	}
}

const Room* BSPGenerator::FindRoomInRegion(int RegX, int RegY) const
{
	//���ٽİ� find_if�� �̿��� Ư�� ������ ���ϴ� �� Ž��
	auto it = find_if(Rooms.begin(), Rooms.end(),
		// ĸó ����Ʈ�� RegX, RegY�� �־� ���ٽ� ���ο��� ��� ����
		[RegX, RegY](const Room& room)
		{
			//���� room�� ������ ã���� �ϴ� (RegX, RegY)�� ���� �� true ��ȯ
			int RoomRegX = room.RegionX;
			int RoomRegY = room.RegionY;
			return RoomRegX == RegX && RoomRegY == RegY;
		});
	//ã������ ������ ��ȯ, �� ã������ nullptr ��ȯ
	return (it != Rooms.end()) ? &(*it) : nullptr;
}