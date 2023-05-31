#ifndef CL_APPLICATION_H
#define CL_APPLICATION_H

#include  "Cl_base.h"

class Cl_application : public Cl_base {
public:
	//�����������
	Cl_application(Cl_base* parentPtr = nullptr);

	//���������� ������ �������� (����)
	void buildTree();

	//��������� ��������� ���������� ��� ��������
	void enterReadiness();

	//������������� ��������� �� ������ ���� ����� ������ "SET" � "FIND"
	void treeNavigation();

	//"������ ����������"
	int execApp();
	
};

#endif
