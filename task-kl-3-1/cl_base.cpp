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
	if (parentPtr)
	{
		const size_t size = parentPtr->childrenList.size();
		for (size_t i = 0; i < size; i++)
		{
			if (parentPtr->childrenList[i] == this)
			{
				parentPtr->childrenList.erase(parentPtr->childrenList.begin() + i);
				break;
			}
		}

		parentPtr->childrenList.push_back(this);
	}
	this->parentPtr = parentPtr;
}

// ������ ��� ���� readines
// ������������� ���������� � ������������ � ��������
void Cl_base::setReadiness(long long numericReadiness) 
{
	if (numericReadiness)
	{
		Cl_base* tempParentPtr = this->parentPtr;
		while (tempParentPtr)
		{
			if (!(tempParentPtr->getReadiness()))
			{
				return;
			}
			tempParentPtr = tempParentPtr->getParent();
		}
		this->readiness = true;
	}
	return;
}

//����� �������� (���������)
Cl_base* Cl_base::getParent() {
	return parentPtr;
}

//����� �����
string Cl_base::getName() {
	return objectName;
}

//����� ����������
bool Cl_base::getReadiness()
{
	return readiness;
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


void Cl_base::printTree(bool isPrintReadiness, unsigned tabLevel) {
	// ������ ���������� ���������. ������� ������ - ��������� ���.��������
	// ����� ������� ����� �� ����� ������ � �� ����� ������ � ������������
	// ��� �� ���� �������� �������� - ������� �� isPrintReadiness

	cout << '\n';
	//�� ����� ��������� � �� ������ �������� �������� tabLevel
	for (unsigned i = 0; i < tabLevel; i++)
	{
		cout << "    ";
	}
	cout << this->getName() << (isPrintReadiness ? (this->getReadiness() ? " is ready" : " is not ready") : "");


	//������� ������ �� ��������
	if (childrenList.empty())
	{
		return;
	}

	for (size_t i = 0; i < childrenList.size(); i++)
	{
		//����������� ����� � ����������� �������� ������ ���������
		childrenList[i]->printTree(isPrintReadiness, tabLevel + 1);
	}
}