#include "Cl_base.h"

// �������� �������-�����������
Cl_base* Cl_base::root = new Cl_base();

//�����������
Cl_base::Cl_base(string objectName, Cl_base* parentPtr)
{
	this->objectName = objectName;
	//���� ��� �� �������� ������
	if (parentPtr)
	{
		setParent(parentPtr);
	}
	else
	{
		//����������� ������ ��� �������� (�������� ������ �����������)
		setParent(root);
	}
}

//����� �����
void Cl_base::setName(string objectName)
{
	this->objectName = objectName;
}

//����� ��������
void Cl_base::setParent(Cl_base* parentPtr)
{	
	/*�������� ������ � ������, ���� ��������� �������� �� null,
	* �.� ���� ����� ������ � �� ��������� ������� */
	if (parentPtr)
	{
		const size_t size = parentPtr->childrenList.size();
		/*����, ������� �������� �� ������ ����� ������������� �������
		* � ������� �� ����� ������ ������, ������� �������� ����������� ������������� */
		for (size_t i = 0; i < size; i++)
		{
			if (parentPtr->childrenList[i] == this)
			{
				parentPtr->childrenList.erase(parentPtr->childrenList.begin() + i);
				break;
			}
		}
		//���������� � ������������ ������ ����� ��������� �� �����.������
		parentPtr->childrenList.push_back(this);
	}
	this->parentPtr = parentPtr;
}

//����� �������� (���������)
Cl_base* Cl_base::getParent() {
	return parentPtr;
}

//����� �����
string Cl_base::getName() {
	return objectName;
}

//�������� ��������� �� ������ �� �����
Cl_base* Cl_base::getObjectPtr(string objectName)
{
	/* �������� ��������� � ������� �������� - �������� �� ���� �������� ��������
	*  ����� �� �������� ���������� ����� ����������� ��� �������� �������
	*  �.� ������ ������� ���.�������� = 0. �������� �������� �� �������� -
	*  ��������� �� ������, ������� ��� ��������� � ������ ��������. */
	for (size_t i = 0; i < childrenList.size(); i++)
	{
		if (childrenList[i]->getObjectPtr(objectName)->getName() == objectName)
		{
			return childrenList[i]->getObjectPtr(objectName);
		}
	}

	return this;
}

//����� ������ ��������
void Cl_base::printTree() {
	//������ ���������� ���������. ������� ������ - ��������� ���.��������

	//������� ������ �� ��������
	if (childrenList.size() == 0)
	{
		return;
	}

	//����� �������-�����������
	cout << endl << this->getName();

	//����� ���������� ��������
	for (size_t i = 0; i < childrenList.size(); i++)
	{
		cout << "  " << childrenList[i]->getName();
	}

	//���� � �������� ��� ������� ��������� �������
	for (size_t i = 0; i < childrenList.size(); i++)
	{
		childrenList[i]->printTree();
	}
}
