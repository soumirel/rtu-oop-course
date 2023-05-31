#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cl_base {
private:
	// ��� �������
	string objectName = "";
	// ��������� �� �������� �������
	Cl_base* parentPtr;

public:
	//������ root - "��������" ���� ��������
	static Cl_base* root;
	//������ ���������� �������� ��������
	vector<Cl_base*> childrenList;

	//������������
	Cl_base() { parentPtr = nullptr; };
	Cl_base(string objectName, Cl_base* parentPtr = nullptr);

	//������
	void setName(string objectName);
	void setParent(Cl_base* parentPtr);

	//������
	Cl_base* getParent();
	string getName();

	//��������� ��������� �� ������ ����� ��� ���
	Cl_base* getObjectPtr(string name);

	//����� ������ ��������
	void printTree();
};
