#include "Cl_application.h"
#include "Cl_branch.h"

Cl_application::Cl_application(Cl_base* parentPtr)
{
	//������������� ������� ������������ ����������� �����
	Cl_base::root->setParent(parentPtr);
	Cl_base::root->setName("root");
}

void Cl_application::buildTree()
{
	string parentName, childName;

	cin >> parentName;

	// �������� ������
	Cl_base* head = new Cl_base(parentName);
	while (true) {

		cin >> parentName >> childName;
		//������� ��������� �����
		if (parentName == childName)
		{
			return;
		}

		// �������� ��������� �������
		Cl_base* child = new Cl_branch(childName, root->getObjectPtr(parentName));
	}
}

int Cl_application::execApp()
{
	//����� ����� ��������� �������
	cout << root->childrenList[0]->getName();
	// ����� ������������ ������
	root->childrenList[0]->printTree();
	return 0;
}