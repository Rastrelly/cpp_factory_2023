#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using std::cout;
using std::cin;
using std::vector;
using std::string;

vector<string>    names = { "John","Jack","Peter","William","Andrey","Jill","Lea","Marge","Tomato" };
vector<string> surnames = { "Stalvern","Gates","Maxton","Bourne","Bond","Asimov","Musk","Valentine","LaCroix" };

string genName()
{
	int i1 = rand() % names.size();
	int i2 = rand() % surnames.size();
	return names[i1] + " " + surnames[i2];
}

enum jobPosition
{
	   jpJanitor,
	   jpPlumber,
	   jpGuard,
	   jpClerk,
	   jpManager,
	   jpDirector
};

jobPosition getRandomJob()
{
	int rj = rand() % 6;
	return (jobPosition)rj;
}

class employee
{
private: 
	string name;
	string position;
	int age;
	int baseSalary;
	int realSalary;	
	void setup(string cName, int cAge, int bSalary)
	{
		name = cName;
		age = cAge;
		baseSalary = bSalary;
		realSalary = 0;
		setMyPosition();
	}
	void setRealSalary()
	{
		realSalary = calcRealSalary();
	}
public:	
	int getBaseSalary() { return baseSalary; };
	int getAge() { return age; };
	string getName() { return name; }
	virtual int calcRealSalary() = 0;
	void setMyPosVar(string mPos) { position = mPos; }
	string getMyPosVar() { return position; }
	virtual void setMyPosition()=0;
	void quickSetup(string cName, int cAge, int bSalary)
	{
		setup(cName, cAge, bSalary);
		setRealSalary();
	}
	void reportMyState()
	{
		cout << getName() << "; " << getAge() << " yo. Position:" << getMyPosVar() << ". Salary: " << realSalary << std::endl;
	}
	static employee * Create(jobPosition jp);
};

class janitor : public employee
{
public:	
	int calcRealSalary()
	{
		return getBaseSalary() * 1.1;
	}
	void setMyPosition()
	{
		setMyPosVar("Janitor");
	}
};

class plumber : public employee
{
public:
	int calcRealSalary()
	{
		return getBaseSalary() * 1.2 + 100;
	}
	void setMyPosition()
	{
		setMyPosVar("Plumber");
	}
};

class guard : public employee
{
public:

	int calcRealSalary()
	{
		return getBaseSalary() * 1.4 + getAge() * 3;
	}
	void setMyPosition()
	{
		setMyPosVar("Guard");
	}
};

class clerk : public employee
{
public:
	int calcRealSalary()
	{
		return getBaseSalary() * 1.7 + getAge() * 4;
	}
	void setMyPosition()
	{
		setMyPosVar("Clerk");
	}
};

class manager : public employee
{
public:
	int calcRealSalary()
	{
		return getBaseSalary() * 2.3 + getAge() * 5;
	}
	void setMyPosition()
	{
		setMyPosVar("Manager");
	}
};

class director : public employee
{
public:
	int calcRealSalary()
	{
		return getBaseSalary() * 4 + getAge() * 7 + 1000;
	}
	void setMyPosition()
	{
		setMyPosVar("Director");
	}
};

employee * employee::Create(jobPosition jp)
{
	switch (jp)
	{
	case jpJanitor:
		return new janitor();
		break;
	case jpPlumber:
		return new plumber();
		break;
	case jpGuard:
		return new guard();
		break;
	case jpClerk:
		return new clerk();
		break;
	case jpManager:
		return new manager();
		break;
	case jpDirector:
		return new director();
		break;
	}
}

class Client
{
private:
	employee *cEmployee;
public:

	Client(jobPosition jp, string name, int age, int baseSalary)
	{
		cEmployee = employee::Create(jp);
		cEmployee->quickSetup(name, age, baseSalary);
	}
	~Client()
	{
		if (cEmployee)
		{
			delete[] cEmployee;
			cEmployee = NULL;
		}
	}
	employee *getEmployee() { return cEmployee; }
};

class StaffManager
{
private:
	vector<Client*> staff; //list of employees
public:
	StaffManager(int nEmps)
	{
		cout << "nEmployees = " << nEmps << std::endl;
		for (int i = 0; i < nEmps; i++)
		{
			staff.push_back(new Client(getRandomJob(), genName(), rand() % 40 + 18, 500));
		}

		for (int i = 0; i < nEmps; i++)
		{
			cout << "Report " << i << ": ";
			staff[i]->getEmployee()->reportMyState();
		}
	}
};



int main()
{
	srand(time(NULL));
	int nEmployees = rand() % 10 + 10;
	StaffManager sMan(nEmployees);
	system("pause");
}
