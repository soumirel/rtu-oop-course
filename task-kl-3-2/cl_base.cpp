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
	if (this->parentPtr)
	{
		const size_t size = this->parentPtr->childrenList.size();
		for (size_t i = 0; i < size; i++)
		{
			if (this->parentPtr->childrenList.at(i) == this)
			{
				this->parentPtr->childrenList.erase(this->parentPtr->childrenList.begin() + i);
				break;
			}
		}
	}

	if (parentPtr)
	{
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
Cl_base* Cl_base::getObjectByName(string objectName)
{

	/* �������� ��������� � ������� �������� - �������� �� ���� �������� ��������
	*  ����� �� �������� ���������� ����� ����������� ��� �������� �������
	*  �.� ������ ������� ���.�������� = 0. �������� �������� �� �������� -
	*  ��������� �� ������, ������� ��� ��������� � ������ ��������. */
	for (size_t i = 0; i < childrenList.size(); i++)
	{
		if (childrenList[i]->getObjectByName(objectName)->getName() == objectName)
		{
			return childrenList[i]->getObjectByName(objectName);
		}
	}
	return this;
}

Cl_base* Cl_base::getObjectByPath(string path)
{
	//���� ��������� �� ��������� ������.
	if (path == ".")
	{
		return this;
	}

	//���� ��������� �� �������� ������.
	if (path == "/")
	{
		return root->childrenList.front();
	}

	size_t pathSize = path.size();

	//���� ��������� �� ���������� ��� �� ������ ��������.
	if (path.front() == '/' && path.at(1) == '/')
	{
		return (root->getObjectByName(path.substr(2)));
	}

	//��������� ������ �� ����� ��������

	size_t iter = 0;
	Cl_base* currentObject = this;
	size_t currentChildrenListSize = currentObject->childrenList.size();
	string nextObjectName = "";
	if (path.front() == '/')
	{
		iter = 1;
	}

	bool isFoundNextObject = false;
	for (; iter <= pathSize; iter++)
	{
		if (iter == pathSize || path.at(iter) == '/')
		{
			isFoundNextObject = false;
			currentChildrenListSize = currentObject->childrenList.size();

			for (size_t j = 0; j < currentChildrenListSize; j++)
			{
				if (currentObject->childrenList.at(j)->getName() == nextObjectName)
				{
					currentObject = currentObject->childrenList.at(j);
					isFoundNextObject = true;
					break;
				}
			}

			if (isFoundNextObject == false)
			{
				return nullptr;
			}

			nextObjectName = "";
		}
		else
		{
			nextObjectName += path.at(iter);
		}
	}

	return currentObject;
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