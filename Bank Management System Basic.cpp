#include <iostream>
using namespace std;
#include <string>

class User {
private:
	int total;
	string name;
	string pin;
	string CNIC;
	int electricityBill;
	int gasBill;
	int waterBill;
	bool loanTaken;
public:
	User()
	{
		electricityBill = 0;
		gasBill = 0;
		waterBill = 0;
		loanTaken = 0;
		total = 0;
	}
	User(int total, string name, string pin, string cnic)
	{
		electricityBill = 10000;
		gasBill = 24000;
		waterBill = 5600;
		loanTaken = 0;
		this->total = total;
		this->name = name;
		this->pin = pin;
		this->CNIC = cnic;
	}
	int getTotal()
	{
		return total;
	}
	string getName()
	{
		return name;
	}
	string getpin()
	{
		return pin;
	}
	string getcnic()
	{
		return CNIC;
	}
	void setTotal(int total)
	{
		this->total = total;
	}
	bool getLoan()
	{
		return loanTaken;
	}
	void setLoan()
	{
		loanTaken = true;
	}
};

class Bank {
private:
	int funds;
	User** List;
	int UserCount;
public:
	int getfunds()
	{
		return funds;
	}
	void setfunds(int funds)
	{
		this->funds = funds;
	}
	Bank()
	{
		UserCount = 0;
		funds = 0;
		List = new User * [10];
	}
	void addUser(int total, string name, string pin, string cnic)
	{
		List[UserCount] = new User(total, name, pin, cnic);
		UserCount++;
		funds = funds + total;
	}
	void printUserNames()
	{
		for (int i = 0; i < UserCount; i++)
		{
			cout << List[i]->getName();
			cout << ",";
		}
		cout << endl;
	}
	void printUserDetails(User &u)
	{
		cout << u.getName();
		cout << ",";
		cout << u.getcnic();
		cout << ",";
		cout << endl;
	}
	bool findUser(string CNIC)
	{
		for (int i = 0; i < UserCount; i++)
		{
			if (CNIC == List[i]->getcnic())
				return 1;
		}
		return 0;
	}
	int getuseramount(string CNIC)
	{
		for (int i = 0; i < 10; i++)
		{
			if (CNIC == List[i]->getcnic())
				return List[i]->getTotal();
		}
	}
	void userWithdrawal(string CNIC, int amount)
	{
		for (int i = 0; i < UserCount; i++)
		{
			if (CNIC == List[i]->getcnic())
			{
				List[i]->setTotal(List[i]->getTotal() - amount);
				break;
			}
		}
		funds = funds - amount;
	}
	void userDeposit(string CNIC, int amount)
	{
		for (int i = 0; i < UserCount; i++)
		{
			if (CNIC == List[i]->getcnic())
			{
				List[i]->setTotal(List[i]->getTotal() + amount);
				break;
			}
		}
		funds = funds + amount;
	}
	void printUserDetails(int amt)
	{
		cout << List[amt]->getName();
		cout << ",";
		cout << List[amt]->getcnic();
		cout << ",";
		cout << List[amt]->getTotal();
		cout << endl;
	}
	void applyForLoan(string CNIC)
	{
		int amt = 0;
		for (int i = 0; i < UserCount; i++)
		{
			if (List[i]->getcnic() == CNIC)
			{
				if (List[i]->getLoan() == 1)
				{
					cout << "Loan has already been taken!" << endl;
					return;
				}
				else
				{
					cout << "Kindly enter the loan amount" << endl;
					cin >> amt;
					if (amt > funds)
					{
						cout << "Sorry, a loan of this value cannot be given" << endl;
						return;
					}
					else
					{
						List[i]->setLoan();
						List[i]->setTotal(List[i]->getTotal() + amt);
						cout << "Loan has been granted!" << endl;
						printUserDetails(i);
						return;
					}
				}
			}
		}
	}
};



int main()
{
	int userAmount = 0;
	int amount;
	string CNIC;
	string name;
	string pin;
	int Run = -5;
	Bank B1;
	cout << "Welcome to the Bank Management System!" << endl;
	while (Run != 5)
	{
		cout << "Choose a service" << endl;
		cout << "1.Open an Account" << endl;
		cout << "2.Deposit into an Account" << endl;
		cout << "3.Withdraw from an Account" << endl;
		cout << "4.Request a Loan" << endl;
		cout << "5.Exit the System" << endl;
		cin >> Run;
		if (Run == 1)
		{
			cout << "Enter your name" << endl;
			cin >> name;
			cout << "Enter your CNIC" << endl;
			cin >> CNIC;
			cout << "Create a 4 digit pin" << endl;
			cin >> pin;
			cout << "Enter an amount to be deposited" << endl;
			cin >> amount;
			B1.addUser(amount, name, pin, CNIC);
			B1.printUserDetails(userAmount);
		}
		else if (Run == 2)
		{
			cout << "Enter your CNIC" << endl;
			cin >> CNIC;
			if (B1.findUser(CNIC) == 0)
				cout << "Error. User does not exist. Make sure you have entered proper details" << endl;
			else
			{
				cout << "Enter your 4 digit pin" << endl;
				cin >> pin;
				cout << "Enter the amount to be deposited" << endl;
				cin >> amount;
				B1.userDeposit(CNIC, amount);
			}
			B1.printUserDetails(userAmount);
		}
		else if (Run == 3)
		{
			cout << "Enter your CNIC" << endl;
			cin >> CNIC;
			if (B1.findUser(CNIC) == 0)
				cout << "Error. User does not exist. Make sure you have entered proper details" << endl;
			else
			{
				cout << "Enter your 4 digit pin" << endl;
				cin >> pin;
				cout << "Enter the amount to be withdrawn" << endl;
				cin >> amount;
				if (amount > B1.getuseramount(CNIC))
					cout << "Error, withdrawn amount is greater than total funds" << endl;
				else
				{
					B1.userWithdrawal(CNIC, amount);
				}
			}
			B1.printUserDetails(userAmount);
		}
		else if (Run == 4)
		{
			cout << "Enter your CNIC" << endl;
			cin >> CNIC;
			if (B1.findUser(CNIC) == 0)
				cout << "Error. User does not exist. Make sure you have entered proper details" << endl;
			else if (B1.findUser(CNIC)!=0)
			{
				cout << "Enter your 4 digit pin" << endl;
				cin >> pin;
				B1.applyForLoan(CNIC);
			}
		}
	}
}