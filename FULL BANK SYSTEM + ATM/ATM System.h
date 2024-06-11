#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const string ClientsFileName = "clients.txt";

struct sClients
{
	string AccountNumber;
	string Pincode;
	string FirstName;
	string LastName;
	string Phone;
	double AccountBalance;
	bool Flag = false;
};

sClients Client;

//------------

//Defenasions

void LoginScreen();
void ShowMainMenue();
short ReadChoes();

//-----------

vector<string>FillVectorByData(string line, string sperator = "#//#")
{
	short count = 0;
	int i = 0;
	string temp = "";
	vector <string> result;
	while (count != 7)
	{
		for (; i < line.length(); i++)
		{
			if (line[i] == sperator[0])
			{
				break;
			}
			else
			{
				temp += line[i];
			}
		}
		count++;
		i += sperator.length();
		result.push_back(temp);
		temp = "";
	}

	return result;
}



sClients ConvertLineToRecord(string Line, string sperator = "#//#")
{
	sClients Client;
	vector<string> result = FillVectorByData(Line, sperator);
	Client.AccountNumber = result[3];
	Client.Pincode = result[4];
	Client.FirstName = result[0];
	Client.LastName = result[1];
	Client.Phone = result[2];
	Client.AccountBalance = stod(result[5]);
	return Client;
}


vector<sClients>LoadClientDataFromFile(string ClientsFileName)
{
	vector<sClients>vClients;
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sClients Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}
void GoBackToMenu()
{
	cout << "\nPress Enter To Back to main\n";
	system("pause>0");
	ShowMainMenue();
}
vector<sClients>EditvectorWithdraw(vector<sClients>& vClients, string AccountNumber, double amount)
{
	for (sClients& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.AccountBalance = C.AccountBalance - amount;
		}
	}
	return vClients;
}
double getAccountBalance(vector<sClients>& vClients, string AccountNumber)
{
	for (sClients& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			return C.AccountBalance;
		}
	}
}
string ConvertRecordToLine(sClients client, string sperator = "#//#")
{
	string result = "";
	result += client.FirstName + sperator;
	result += client.LastName + sperator;
	result += client.Phone + sperator;
	result += client.AccountNumber + sperator;
	result += client.Pincode + sperator;
	result += to_string(client.AccountBalance);
	return result;
}
vector<sClients>SaveClientsDataToFile(string ClientsFileName, vector<sClients>vClients)
{
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::out);
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClients& C : vClients)
		{
			if (C.Flag == false)
			{
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

sClients ToEqualClient(sClients& Client, string AccountNumber)
{
	vector< sClients> temp = LoadClientDataFromFile(ClientsFileName);
	for (sClients& C : temp)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
		}
	}
	return Client;
}

bool isAmountBigger(vector<sClients> vClients, string AccountNumber, short amount)
{
	for (sClients& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			if (amount > C.AccountBalance)
			{
				return true;
			}
		}
	}
	return false;
}

void NormalWithdraw(vector<sClients> vClients)
{
	char ch;
	double amount;
	cout << "\nPlease Enter withdraw amnount? ";
	cin >> amount;
	while (isAmountBigger(vClients, Client.AccountNumber, amount))
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << getAccountBalance(vClients, Client.AccountNumber) << endl;
		cout << "Please Enter another amount? ";
		cin >> amount;
	}
	cout << "\nAre You Sure you want perform this transaction? y/n ? ";
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		vClients = EditvectorWithdraw(vClients, Client.AccountNumber, amount);
		SaveClientsDataToFile(ClientsFileName, vClients);
		cout << "\nDone Successfully new balance is: " << getAccountBalance(vClients, Client.AccountNumber) << endl;
	}
}
void NormalWithdrawScreen()
{
	vector<sClients> vClients = LoadClientDataFromFile(ClientsFileName);
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "        Normal Withdraw Screen\n";
	cout << "-----------------------------------\n";
	NormalWithdraw(vClients);
	GoBackToMenu();
}

vector<sClients>EditvectorDepostit(vector<sClients>& vClients, string AccountNumber, double amount)
{
	for (sClients& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.AccountBalance = C.AccountBalance + amount;
		}
	}
	return vClients;
}
void Deposit(vector<sClients>& vClients)
{
	char ch;
	double amount;
	cout << "\nPlease Enter deposit amnount? ";
	cin >> amount;
	cout << "\nAre You Sure you want perform this transaction? y/n ? ";
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		vClients = EditvectorDepostit(vClients, Client.AccountNumber, amount);
		SaveClientsDataToFile(ClientsFileName, vClients);
		cout << "\nDone Successfully new balance is: " << getAccountBalance(vClients, Client.AccountNumber) << endl;
	}
}
void CaseDeposit()
{
	vector<sClients> vClients = LoadClientDataFromFile(ClientsFileName);
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "         Deposit Screen\n";
	cout << "-----------------------------------\n";

	Deposit(vClients);
	GoBackToMenu();
}

void Withdraw(short amount)
{
	vector<sClients> vClients = LoadClientDataFromFile(ClientsFileName);
	char ch;
	if (isAmountBigger(vClients, Client.AccountNumber, amount))
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << getAccountBalance(vClients, Client.AccountNumber) << endl;
		GoBackToMenu();
	}
	else
	{
		cout << "\nAre You Sure you want perform this transaction? y/n ? ";
		cin >> ch;
		if (ch == 'Y' || ch == 'y')
		{
			vClients = EditvectorWithdraw(vClients, Client.AccountNumber, amount);
			SaveClientsDataToFile(ClientsFileName, vClients);
			cout << "\nDone Successfully new balance is: " << getAccountBalance(vClients, Client.AccountNumber) << endl;
		}
	}
}
enum ChoesQuickWithdraw
{
	enum20 = 1, enum50 = 2, enum100 = 3, enum200 = 4, enum400 = 5, enum600 = 6,
	enum800 = 7, enum1000 = 8, enumExit = 9
};
void Statment_QuickWithdraw(ChoesQuickWithdraw ch)
{
	switch (ch)
	{
	case enum20:
		Withdraw(20);
		break;
	case enum50:
		Withdraw(50);
		break;
	case enum100:
		Withdraw(100);
		break;
	case enum200:
		Withdraw(200);
		break;
	case enum400:
		Withdraw(400);
		break;
	case enum600:
		Withdraw(600);
		break;
	case enum800:
		Withdraw(800);
		break;
	case enum1000:
		Withdraw(1000);
		break;
	case enumExit:
		GoBackToMenu();
		break;
	default:
		break;
	}
}
void QuickWithdraw()
{
	vector<sClients> vClients = LoadClientDataFromFile(ClientsFileName);
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "         Quick Withdraw Screen\n";
	cout << "-----------------------------------\n";
	cout << "\t[1] 20\t\t[2] 50\n";
	cout << "\t[3] 100\t\t[4] 200\n";
	cout << "\t[5] 400\t\t[6] 600\n";
	cout << "\t[7] 800\t\t[8] 1000\n";
	cout << "\t[9] Exit\n";
	cout << "-----------------------------------\n";
	cout << "Your Balance is: " << getAccountBalance(vClients, Client.AccountNumber) << endl;
	cout << "Choose what to Withdraw From [1 to 8]? ";
	Statment_QuickWithdraw((ChoesQuickWithdraw)ReadChoes());
	GoBackToMenu();
}
//--------------
void CheackBalance()
{
	vector<sClients> vClients = LoadClientDataFromFile(ClientsFileName);
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "         Cheack Balance Screen\n";
	cout << "-----------------------------------\n";
	cout << "Your Balance is: " << getAccountBalance(vClients, Client.AccountNumber) << endl;
	GoBackToMenu();
}
short ReadChoes()
{
	short ch;
	cin >> ch;
	return ch;
}
enum Choes
{
	enumQuickWithdraw = 1, enumNormalWithdraw = 2, enumDeposit = 3, enumCheckBalance = 4, enumLogOut = 5
};
void Statments(Choes ch)
{
	switch (ch)
	{
	case enumQuickWithdraw:
		QuickWithdraw();
		break;
	case enumNormalWithdraw:
		NormalWithdrawScreen();
		break;
	case enumDeposit:
		CaseDeposit();
		break;
	case enumCheckBalance:
		CheackBalance();
		break;
	case enumLogOut:
		LoginScreen();
		break;
	default:
		break;
	}
}
void ShowMainMenue()
{
	system("cls");
	cout << "\n==================================\n";
	cout << "         ATM Main Menu Screen\n";
	cout << "==================================\n";
	cout << "       [1] Quick Withdraw.\n" <<
		"       [2] Normal Withdraw.\n" <<
		"       [3] Deposit.\n" <<
		"       [4] Check Balance.\n" <<
		"       [5] LogOut.\n";
	cout << "==================================" << endl;
	cout << "Choose what do you want to do? [1 to 5? ";
	Statments((Choes)ReadChoes());
}
bool FindUsernameAndPassword(string AccountNumber, int Pincode, sClients& Client)
{
	vector<sClients> vClients = LoadClientDataFromFile(ClientsFileName);
	for (sClients& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			if (stoi(C.Pincode) == Pincode)
			{
				return true;
			}
		}
	}
	return false;
}
void HeadLoginScreen()
{
	system("cls");
	cout << "\n==================================\n";
	cout << "           Login Screen\n";
	cout << "==================================\n";
}
void Login(string AccountNumber, int Pincode, sClients& Client)
{
	if (FindUsernameAndPassword(AccountNumber, Pincode, Client))
	{
		ToEqualClient(Client, AccountNumber);
		ShowMainMenue();
	}
	else
	{
		HeadLoginScreen();
		cout << "Invalied AccountNumber/Pincode!\n";
		cout << "Enter AccountNumber? ";
		getline(cin >> ws, AccountNumber);
		cout << "Enter Pincode? ";
		cin >> Pincode;
		Login(AccountNumber, Pincode, Client);
	}
}
void LoginScreen()
{
	HeadLoginScreen();
	string AccountNumber;
	int Pincode;
	cout << "Enter AcountNumber? ";
	getline(cin >> ws, AccountNumber);
	cout << "Enter Password? ";
	cin >> Pincode;
	Login(AccountNumber, Pincode, Client);
}