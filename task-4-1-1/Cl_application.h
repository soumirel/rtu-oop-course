#pragma once

#include  "Cl_base.h"

class Cl_application : public Cl_base {
public:
	//�����������
	Cl_application(Cl_base* parentPtr = nullptr);

	//���������� ������ �������� (����)
	void buildTree();

	//"������ ����������"
	int execApp();

};
