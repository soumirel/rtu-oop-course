#ifndef CL_COFFEMACHINE_H
#define CL_COFFEMACHINE_H

#include  "Cl_base.h"

class Cl_coffeeMachine : 
	public Cl_base 
{
private:
	//����-������� �������� � ������� ���� � �����
	bool statusCoffeLoad = false;
	bool statusCoinsLoad = false;

public:
	//�����������
	Cl_coffeeMachine(string objectName = "coffeMachineObject", Cl_base* parentPtr = nullptr) :
		Cl_base(objectName, parentPtr) {};

	//������� � ������� �������� �������� ����� � ����
	bool getStatusCoffeLoad() override;
	bool getStatusCoinsLoad() override;
	void setStatusCoffeLoad(bool status) override;
	void setStatusCoinsLoad(bool status) override;

	//������ � ����������
	void signal_v(string path, string message) override;

	void handler_v(string path, string message) override;

	size_t getClassNumber() override;

	//������ ����� ����� ��� ���������� ������
	void buildTree();

	//������ ����� ����� ��� ��������� ����������� ��������
	void enterReadiness();

	//������ ����� ����� ��� ��������� ������ ����� ���������
	void enterConnections();

	//������ ����� ����� ��� ������������� ����������� ��� ��������� ��� ������ ������
	void enterCommands();

	//������ ������� ����������
	int runMachine();

};

#endif



