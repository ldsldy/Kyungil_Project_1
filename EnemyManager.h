#pragma once
#include "Enemy.h"
#include <vector>

using namespace std;

class EnemyManager
{
public:
	//�� ����(int count)
	//�� ��ü ����

	//update �÷��̾��� ��ġ�� ���� �� ���� ������Ʈ (��ȸ<=>����)
	//set �÷��̾ ��ū�� �� ������ �� ��ü�� �߰ݸ��� ����
	//set �÷��̾ ��ū�� ������ ���� �ð� ����

	//�÷��̾ ��ū�� �� �Ծ����� Ȯ��

	//�׽�Ʈ���: �ǽ�
	//���� ���, ���� ���� �� ����� ���� ǥ��
	//���� �÷��̾ �߰����� �� �˸�

	//�� ����Ʈ ��ȯ(�����)
private:
	vector<Enemy*> Enemies;
};

