#include "Cl_coffeeMachine.h"

int main()
{
	Cl_coffeeMachine machineObject;

	//���������� ������� ��������
	machineObject.buildTree();

	return machineObject.runMachine();
}