#ifndef CL_BASE_H
#define CL_BASE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cl_base 
{
private:
	// ��� �������
	string objectName = "";

	// ��������� �� �������� �������
	Cl_base* parentPtr = nullptr;

	//��������� ���������� �������
	bool readiness = false;
	

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
	void setReadiness(long long numericReadiness);

	//������
	Cl_base* getParent();
	string getName();
	bool getReadiness();

	//��������� ��������� �� ������ ����� ��� ���
	Cl_base* getObjectByName(string name);

	//��������� ��������� �� ������ ����� �������� ����
	Cl_base* getObjectByPath(string path);

	//����� ������ ��������
	void printTree(bool isPrintReadiness, unsigned tabLevel = 0);
};

#endif