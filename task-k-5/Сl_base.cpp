
#include "Cl_base.h"
#include "Cl_coffeeMachine.h"
#include "Cl_console.h"
#include "Cl_controller.h"
#include "Cl_cashReceiver.h"
#include "Cl_coinsReturner.h"
#include "Cl_coffeemaker.h"
#include "Cl_screen.h"


//�����������
Cl_base::Cl_base(string objectName, Cl_base* parentPtr)
{
	this->objectName = objectName;
	//���� ��� �� �������� ������
	if (parentPtr)
	{
		setParent(parentPtr);
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

		for (size_t i = 0; i < this->childrenList.size(); i++)
		{
			this->childrenList.at(i)->setReadiness(numericReadiness);
		}
	}
	else
	{
		this->readiness = false;

		for (size_t i = 0; i < this->childrenList.size(); i++)
		{
			this->childrenList.at(i)->setReadiness(numericReadiness);
		}
	}
	return;
}


//���������� �����
void Cl_base::setConnection(TYPE_SIGNAL signalPtr, Cl_base* objectPtr, TYPE_HANDLER handlerPtr)
{
	connectionInfo* tempConnect;

	for (size_t iter = 0; iter < connections.size(); iter++)
	{
		if (connections.at(iter)->signalPtr == signalPtr &&
			connections.at(iter)->objectPtr == objectPtr &&
			connections.at(iter)->handlerPtr == handlerPtr)
		{
			return;
		}
	}

	tempConnect = new connectionInfo();

	tempConnect->signalPtr = signalPtr;
	tempConnect->objectPtr = objectPtr;
	tempConnect->handlerPtr = handlerPtr;

	this->connections.push_back(tempConnect);
}


// ����� ������� �����
void Cl_base::deleteConnection(TYPE_SIGNAL signalPtr, Cl_base* objectPtr, TYPE_HANDLER handlerPtr)
{
	for (size_t iter = 0; iter < connections.size(); iter++)
	{
		if (connections.at(iter)->signalPtr == signalPtr &&
			connections.at(iter)->objectPtr == objectPtr &&
			connections.at(iter)->handlerPtr == handlerPtr)
		{
			this->connections.erase(connections.begin() + iter);
		}
	}
}


// ������ ��������� �������
void Cl_base::emitSignal(TYPE_SIGNAL signalPtr, string& message)
{
	if (this->getReadiness() == false)
	{
		return;
	}
	string absObjPath = this->getAbsPath();
	this->signal_v(absObjPath, message);
	for (size_t iter = 0; iter < this->connections.size(); iter++)
	{
		if (this->connections.at(iter)->objectPtr->getReadiness())
		{
			this->connections.at(iter)->objectPtr->handler_v(this->connections.at(iter)->objectPtr->getAbsPath(), message);
		}
	}
}



//����� �������� (���������)
Cl_base* Cl_base::getParent()
{
	return parentPtr;
}


//����� �����
string Cl_base::getName()
{
	return objectName;
}


//����� ����������
bool Cl_base::getReadiness()
{
	return readiness;
}


//�������� ����� ������
size_t Cl_base::getClassNumber()
{
	return 0;
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
		if (childrenList.at(i)->getObjectByName(objectName)->getName() == objectName)
		{
			return childrenList.at(i)->getObjectByName(objectName);
		}
	}
	return this;
}


//������� ������ - ���. ���������� �������
string Cl_base::getAbsPath()
{
	if (this->getParent() == nullptr)
	{
		return "/";
	}
	else
	{
		string absPath;
		Cl_base* currentObjectPtr = this;

		while (currentObjectPtr != nullptr)
		{
			absPath = '/' + currentObjectPtr->getName() + absPath;
			currentObjectPtr = currentObjectPtr->getParent();
		}

		return absPath;
	}
}


//��������� ��������� �� ������ �� ����
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
		return this->getHeadPtr();
	}

	size_t pathSize = path.size();

	//���� ��������� �� ���������� ��� �� ������ ��������.
	if (path.front() == '/' && path.at(1) == '/')
	{
		if (this->getObjectByName(path.substr(2)) != this->getHeadPtr())
			return (this->getObjectByName(path.substr(2)));
	}

	//��������� ������ �� ����� �������� � �������� ������������ ����
	size_t iter = 0;
	if (path.front() == '/')
	{
		iter = 1;
	}

	Cl_base* currentObject = this;
	size_t currentChildrenListSize = currentObject->childrenList.size();
	string nextObjectName = "";
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


// ��������� ��������� ����� ����� ���������
void Cl_base::realizeConnection(Cl_base* firstObjectPtr, Cl_base* secondObjectPtr)
{
	switch (secondObjectPtr->getClassNumber())
	{
	case 1:
		firstObjectPtr->setConnection(SIGNAL(Cl_coffeeMachine::signal_v),
			(Cl_base*)secondObjectPtr, HANDLER(Cl_coffeeMachine::handler_v));
		break;

	case 2:
		firstObjectPtr->setConnection(SIGNAL(Cl_console::signal_v),
			(Cl_console*)secondObjectPtr, HANDLER(Cl_console::handler_v));
		break;

	case 3:
		firstObjectPtr->setConnection(SIGNAL(Cl_controller::signal_v),
			(Cl_controller*)secondObjectPtr, HANDLER(Cl_controller::handler_v));
		break;

	case 4:
		firstObjectPtr->setConnection(SIGNAL(Cl_cashReceiver::signal_v),
			(Cl_cashReceiver*)secondObjectPtr, HANDLER(Cl_cashReceiver::handler_v));
		break;

	case 5:
		firstObjectPtr->setConnection(SIGNAL(Cl_coinsReturner::signal_v),
			(Cl_coinsReturner*)secondObjectPtr, HANDLER(Cl_coinsReturner::handler_v));
		break;

	case 6:
		firstObjectPtr->setConnection(SIGNAL(Cl_coffeemaker::signal_v),
			(Cl_coffeemaker*)secondObjectPtr, HANDLER(Cl_coffeemaker::handler_v));
		break;
	case 7:
		firstObjectPtr->setConnection(SIGNAL(Cl_screen::signal_v),
			(Cl_screen*)secondObjectPtr, HANDLER(Cl_screen::handler_v));
		break;
	}
}


// ��������� ����������� �������
void Cl_base::realizeEmit(string message)
{
	Cl_base* tempObjectPtr = this;

	while (tempObjectPtr->getParent() != nullptr)
	{
		if (tempObjectPtr->getReadiness())
		{
			tempObjectPtr = tempObjectPtr->getParent();
		}
		else
		{
			return;
		}
	}

	switch (this->getClassNumber())
	{
	case 1:
		tempObjectPtr->emitSignal(SIGNAL(Cl_coffeeMachine::signal_v), message);
		break;

	case 2:
		tempObjectPtr->emitSignal(SIGNAL(Cl_console::signal_v), message);
		break;

	case 3:
		tempObjectPtr->emitSignal(SIGNAL(Cl_controller::signal_v), message);
		break;

	case 4:
		tempObjectPtr->emitSignal(SIGNAL(Cl_cashReceiver::signal_v), message);
		break;

	case 5:
		tempObjectPtr->emitSignal(SIGNAL(Cl_coinsReturner::signal_v), message);
		break;

	case 6:
		tempObjectPtr->emitSignal(SIGNAL(Cl_coffeemaker::signal_v), message);
		break;

	case 7:
		tempObjectPtr->emitSignal(SIGNAL(Cl_screen::signal_v), message);
		break;
	}

}


// ��������� �������� �����
void Cl_base::removeConnection(Cl_base* firstObjectPtr, Cl_base* secondObjectPtr)
{
	switch (secondObjectPtr->getClassNumber())
	{
	case 1:
		firstObjectPtr->deleteConnection(SIGNAL(Cl_coffeeMachine::signal_v),
			(Cl_base*)secondObjectPtr, HANDLER(Cl_coffeeMachine::handler_v));
		break;

	case 2:
		firstObjectPtr->deleteConnection(SIGNAL(Cl_console::signal_v),
			(Cl_console*)secondObjectPtr, HANDLER(Cl_console::handler_v));
		break;

	case 3:
		firstObjectPtr->deleteConnection(SIGNAL(Cl_controller::signal_v),
			(Cl_controller*)secondObjectPtr, HANDLER(Cl_controller::handler_v));
		break;

	case 4:
		firstObjectPtr->deleteConnection(SIGNAL(Cl_cashReceiver::signal_v),
			(Cl_cashReceiver*)secondObjectPtr, HANDLER(Cl_cashReceiver::handler_v));
		break;

	case 5:
		firstObjectPtr->deleteConnection(SIGNAL(Cl_coinsReturner::signal_v),
			(Cl_coinsReturner*)secondObjectPtr, HANDLER(Cl_coinsReturner::handler_v));
		break;

	case 6:
		firstObjectPtr->deleteConnection(SIGNAL(Cl_coffeemaker::signal_v),
			(Cl_coffeemaker*)secondObjectPtr, HANDLER(Cl_coffeemaker::handler_v));
		break;
	}
}


// ����� ������ ��������
void Cl_base::printTree(bool isPrintReadiness, unsigned tabLevel)
{
	// ������ ���������� ���������. ������� ������ - ��������� ���.��������
	// ����� ������� ����� �� ����� ������ � �� ����� ������ � ������������
	// ��� �� ���� �������� �������� - ������� �� isPrintReadiness

	
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
		cout << '\n';
		//����������� ����� � ����������� �������� ������ ���������
		childrenList[i]->printTree(isPrintReadiness, tabLevel + 1);
	}
}


void Cl_base::signal_v(string path, string message)
{
	cout << "\nSignal from " << path;
}


void Cl_base::handler_v(string path, string message)
{
	cout << "\nSignal to " << path
		<< " Text: " << message << " (class: 1)";
}


bool Cl_base::getStatusCoffeLoad()
{
	return false;
}


bool Cl_base::getStatusCoinsLoad()
{
	return false;
}


Cl_base* Cl_base::getHeadPtr()
{
	Cl_base* p_tempObject = this;

	while (p_tempObject->getParent() != nullptr)
	{
		p_tempObject = p_tempObject->getParent();
	}

	return p_tempObject;
}


bool Cl_base::isNumber(string str)
{
	return str.find_first_not_of("0123456789") == string::npos;
}