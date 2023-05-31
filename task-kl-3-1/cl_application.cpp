//TODO ����� ������ �������� �������� ����� ���
//TODO ����� ������ �������� � ������������
//TODO ����� ��������� ���������� �������

#include "Cl_application.h"
#include "Cl_branch.h"
#include "Cl_branch_2.h"
#include "Cl_branch_3.h"
#include "Cl_branch_4.h"
#include "Cl_branch_5.h"

Cl_application::Cl_application(Cl_base* parentPtr)
{
	//������������� ������� ������������ ����������� �����
	Cl_base::root->setParent(parentPtr);
	Cl_base::root->setName("root");
	Cl_base::root->setReadiness(1);
}

//�������� ��� ��_3_1
void Cl_application::buildTree()
{
	string parentName, childName;
	int classNumber;

	cin >> parentName;

	// �������� ������
	Cl_base* head = new Cl_base(parentName);
	cin >> parentName;
	while (parentName != "endtree") {

		cin >> childName >> classNumber;

		// �������� ��������� ������� ������������ ������
		// ������������� �������� �������
		switch (classNumber)
		{
		case 2:
		{
			Cl_base* child = new Cl_branch(childName, root->getObjectPtr(parentName));
			break;
		}

		case 3:
		{
			Cl_base* child = new Cl_branch_2(childName, root->getObjectPtr(parentName));
			break;
		}

		case 4:

		{
			Cl_base* child = new Cl_branch_3(childName, root->getObjectPtr(parentName));
			break;
		}

		case 5:
		{
			Cl_base* child = new Cl_branch_4(childName, root->getObjectPtr(parentName));
			break;
		}

		case 6:
		{
			Cl_base* child = new Cl_branch_5(childName, root->getObjectPtr(parentName));
			break;
		}

		}
		cin >> parentName;
	}
}

//������� ������� ����� ����������� ��������
void Cl_application::enterReadiness()
{
	string objectName;
	long long numericReadiness;
	while (cin >> objectName >> numericReadiness)
	{
		(root->getObjectPtr(objectName))->setReadiness(numericReadiness);
	}
}

int Cl_application::execApp()
{
	// ����� ������������ ������;
	cout << "Object tree";
	root->childrenList.at(0)->printTree(false);
	//����� ������ � ����������� ��������
	cout << "\nThe tree of objects and their readiness";
	root->childrenList.at(0)->printTree(true);
	return 0;
}
