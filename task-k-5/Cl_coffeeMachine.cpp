
#include "Cl_coffeeMachine.h"
#include "Cl_console.h"
#include "Cl_controller.h"
#include "Cl_cashReceiver.h"
#include "Cl_coinsReturner.h"
#include "Cl_coffeemaker.h"
#include "Cl_screen.h"


bool Cl_coffeeMachine::getStatusCoffeLoad()
{
	return statusCoffeLoad;
}

bool Cl_coffeeMachine::getStatusCoinsLoad()
{
	return statusCoinsLoad;
}

void Cl_coffeeMachine::setStatusCoffeLoad(bool status)
{
	this->statusCoffeLoad = status;
}

void Cl_coffeeMachine::setStatusCoinsLoad(bool status)
{
	this->statusCoinsLoad = status;
}

//������ ����� ����� ��� ���������� ������
void Cl_coffeeMachine::buildTree()
{
	//�������������� ��������-����������� ����������
	Cl_base* p_consoleObject = new Cl_console("consoleObject", this);

	Cl_base* p_controllerObject = new Cl_controller("controllerObject", this);

	Cl_base* p_cashReceiverObject = new Cl_cashReceiver("cashReceiverObject", this);

	Cl_base* p_coinsReturner = new Cl_coinsReturner("coinsReturner", this);

	Cl_base* p_coffemakerObject = new Cl_coffeemaker("coffemakerObject", this);

	Cl_base* p_screenObject = new Cl_screen("screenObject", this);

	//������ ������� � �������-����������� ���������� ������
	this->realizeConnection(this, p_consoleObject);

	//��������� ������ �����������-���������� ����� ���������
	for (size_t i = 1; i < this->childrenList.size() - 1; i++)
	{
		p_consoleObject->realizeConnection(
			p_consoleObject , this->childrenList.at(i));
	}

	//������ ���� �������� � ������� ��� ������ ���������
	for (size_t i = 0; i < this->childrenList.size() - 1; i++)
	{
		this->childrenList.at(i)->realizeConnection(
			this->childrenList.at(i), p_screenObject);
	}

	//���������� ��������� ��������� ��������
	p_controllerObject->realizeConnection(p_controllerObject, p_coinsReturner);

	p_controllerObject->realizeConnection(p_controllerObject, p_coffemakerObject);

	p_cashReceiverObject->realizeConnection(p_cashReceiverObject, p_screenObject);

	p_cashReceiverObject->realizeConnection(p_cashReceiverObject, p_coinsReturner);

	p_coinsReturner->realizeConnection(p_coinsReturner, p_cashReceiverObject);

	p_coinsReturner->realizeConnection(p_coinsReturner, p_controllerObject);

	p_coffemakerObject->realizeConnection(p_coffemakerObject, p_coinsReturner);

	p_coffemakerObject->realizeConnection(p_coffemakerObject, p_controllerObject);

	return;
}


//������ ����� ����� ��� ��������� ����������� ��������
void Cl_coffeeMachine::enterReadiness()
{
	string objectName;
	long long numericReadiness;
	while (cin >> objectName >> numericReadiness)
	{
		(this->getObjectByName(objectName))->setReadiness(numericReadiness);
	}
}


//������ ����� ����� ��� ��������� ������ ����� ���������
void Cl_coffeeMachine::enterConnections()
{
	string signalPath, handlerPath;
	cin >> signalPath;
	while (signalPath != "end_of_connections")
	{
		cin >> handlerPath;

		Cl_base* firstObjectPtr = this->getObjectByPath(signalPath);
		Cl_base* secondObjectPtr = this->getObjectByPath(handlerPath);

		firstObjectPtr->realizeConnection(firstObjectPtr, secondObjectPtr);

		cin >> signalPath;
	}
}


//������ ����� ����� ��� ������������� ����������� ��� ��������� ��� ������ ������
void Cl_coffeeMachine::enterCommands()
{
	Cl_base* setedObjectPtr = this;
	Cl_base* objectFromPath;

	string command, path;

	cin >> command;

	while (command != "END")
	{
		cin >> path;

		objectFromPath = setedObjectPtr->getObjectByPath(path);

		// ��������� ������� ��������� �������� �������
		if (command == "SET")
		{
			if (objectFromPath)
			{
				setedObjectPtr = objectFromPath;
				cout << "Object is set: " << setedObjectPtr->getName();
			}
			else
			{
				cout << "Object is not found: " << setedObjectPtr->getName() << " " << path;
			}
		}

		// ��������� ������� ������ ������� �� ����������
		if (command == "FIND")
		{
			if (objectFromPath)
			{
				cout << path << "     Object name: " << objectFromPath->getName();
			}
			else
			{
				cout << path << "     Object is not found";
			}
		}

		// ��������� ������� �������� ������
		if (command == "EMIT")
		{
			string message;
			getline(cin, message);

			if (objectFromPath)
			{
				objectFromPath->realizeEmit(message);
			}
			else
			{
				cout << '\n' << "Object " << path << " not found";
			}
		}

		// ��������� ������� ��������� �������� �������
		if (command == "SET_CONDITION")
		{
			int condition;
			cin >> condition;

			Cl_base* tempObjectPtr;
			tempObjectPtr = this->getObjectByPath(path);

			if (tempObjectPtr)
			{
				tempObjectPtr->setReadiness(condition);
			}
			else
			{
				cout << endl << "Object " << path << " not found";
			}
		}

		// ��������� ������ ��������� � ������� ����� ����� ���������
		if (command == "SET_CONNECT" || command == "DELETE_CONNECT")
		{
			string connectPath;
			cin >> connectPath;

			Cl_base* tempObjectPtr;
			tempObjectPtr = this->getObjectByPath(connectPath);

			//�������� �� ������������� �������� �� �����������
			if (objectFromPath == nullptr || tempObjectPtr == nullptr)
			{
				if (objectFromPath == nullptr)
				{
					cout << endl << "Object " << path << " not found";
				}
				if (tempObjectPtr == nullptr)
				{
					cout << endl << "Handler object " << connectPath << " not found";
				}
			}
			else
			{
				if (command == "SET_CONNECT")
				{
					objectFromPath->realizeConnection(objectFromPath, tempObjectPtr);
				}
				else
				{
					objectFromPath->removeConnection(objectFromPath, tempObjectPtr);
				}
			}
		}

		cin >> command;
	}
}


void Cl_coffeeMachine::signal_v(string path, string message)
{
	return;
}


void Cl_coffeeMachine::handler_v(string path, string message)
{
	return;
}

size_t Cl_coffeeMachine::getClassNumber()
{
	return 1;
}


//������ ������� ����������
int Cl_coffeeMachine::runMachine()
{
	this->setReadiness(1);

	this->realizeEmit("MACHINE:CONSOLE_START");

	return 0;
}

