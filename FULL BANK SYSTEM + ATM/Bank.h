#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <string>
using namespace std;

const string ClientsFileName = "clients.txt";
const string UsersFileName = "users.txt";

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
struct sUsers
{
	string Username;
	int Password;
	short Permissions;
	bool Flag = false;
};

sUsers User;

vector<string>FillVectorByData(string line, string sperator = "#//#")
{
	short count = 0;
	int i = 0;
	string temp = "";
	vector <string> result;
	while (count != 6)
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
void AddDataLineToFile(string FileName, string  stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{

		MyFile << stDataLine << endl;

		MyFile.close();
	}

}
//--------------------
void PrintCLient_WithAccountNumber(vector<sClients> vClients, string AccountNumber)
{
	for (sClients& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			cout << "\nThe Following are the client detalis:\n";
			cout << "\nAccount Number: " << Client.AccountNumber;
			cout << "\nPin Code: " << Client.Pincode;
			cout << "\nName: " << Client.FirstName + " " + Client.LastName;
			cout << "\nPhone: " << Client.Phone;
			cout << "\nAccount Balance: " << Client.AccountBalance << endl;
		}
	}
}
void PrintClientRecord(sClients Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.Pincode;
	cout << "| " << setw(40) << left << Client.FirstName + " " + Client.LastName;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintAllClientsData()
{
	vector <sClients> vClients = LoadClientDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (sClients Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}
//--------------
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
void AddFile(string Client, string FileName)
{
	fstream clients;
	clients.open(ClientsFileName, ios::out | ios::app);
	if (clients.is_open())
	{
		clients << Client << endl;
		clients.close();
	}
}
void AddNewClient()
{
	sClients client;
	cout << "Enter Account Number: ";
	getline(cin >> ws, client.AccountNumber);
	cout << "Enter PinCode: ";
	getline(cin, client.Pincode);
	cout << "Enter First Name: ";
	getline(cin, client.FirstName);
	cout << "Enter Last Name: ";
	getline(cin, client.LastName);
	cout << "Enter Phone: ";
	getline(cin, client.Phone);
	cout << "Enter AccountBalance: ";
	cin >> client.AccountBalance;
	string result = ConvertRecordToLine(client);
	AddFile(result, ClientsFileName);
}
void AddClients()
{
	char ch = 'Y';
	do
	{
		cout << "Adding New Client:\n\n";

		AddNewClient();

		cout << "Client Add Successfully, do you want to add more clients? y/n ? ";
		cin >> ch;
	} while (toupper(ch) == 'Y');
}
//-------------
bool MarkForDelete(vector<sClients>& vClients, string AccountNumber)
{
	for (sClients& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.Flag = true;
			return true;
		}
	}
	return false;
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
void DeleteClient(vector<sClients>& vClients, string AccountNumber)
{
	char ch;
	cout << "\nAre You Sure you want delete this client? y/n ? ";
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		MarkForDelete(vClients, AccountNumber);
		SaveClientsDataToFile(ClientsFileName, vClients);
		vClients = LoadClientDataFromFile(ClientsFileName);
		cout << "\nClient Deleted Successfully.\n";
	}
}
//-----------------
bool isClientFound(vector<sClients> vClients, string AccountNumber)
{
	for (sClients& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			return true;
		}
	}
	return false;
}
void SearchClient(vector<sClients> vClients, string AccountNumber)
{

	if (isClientFound(vClients, AccountNumber))
	{
		PrintCLient_WithAccountNumber(vClients, AccountNumber);
	}
	else
	{
		cout << "\nClient With Account Number (" << AccountNumber << ") Not Found!\n";
	}

}
vector<sClients>EditVectorForUpdate(vector<sClients>& vClients, string AccountNumber, string nPinCode, string firstname, string lastname, string nPhone, double nAccountBalance)
{
	for (sClients& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.Pincode = nPinCode;
			C.FirstName = firstname;
			C.LastName = lastname;
			C.Phone = nPhone;
			C.AccountBalance = nAccountBalance;
		}
	}
	return vClients;
}
void UpdateClient(vector<sClients>& vClients, string AccountNumber)
{
	char ch;
	string nPinCode, firstname, lastname, nPhone;
	double nAccountBalance;
	cout << "\nAre You Sure you want update this client? y/n ? ";
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		cout << "Enter PinCode: ";
		getline(cin >> ws, nPinCode);
		cout << "Enter First Name: ";
		getline(cin, firstname);
		cout << "Enter Last Name: ";
		getline(cin, lastname);
		cout << "Enter Phone: ";
		getline(cin, nPhone);
		cout << "Enter AccountBalance: ";
		cin >> nAccountBalance;
		vClients = EditVectorForUpdate(vClients, AccountNumber, nPinCode, firstname, lastname, nPhone, nAccountBalance);
		SaveClientsDataToFile(ClientsFileName, vClients);
		cout << "\nClient Updated Successfully.\n";
	}
}
//------------------
enum getPermissions
{
	enumShowClientList = 1, enumAddNewClient = 2, enumDeleteClient = 4, enumUpdateClient = 8,
	enumFindClient = 16, enummTransactions = 32, enummManageUsers = 64
};

//------------------

// Defenations

void ShowMainMenue();
void GoBackToMenu();
void GoBackToTrans();
void HeadManageUsersScreen();
void LoginScreen();
short ReadChoes();
void NoAccess();
bool CheackAccessPermissions(getPermissions Permission);

//-----------------
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
void Deposit(vector<sClients>& vClients, string AccountNumber)
{
	char ch;
	double amount;
	cout << "\nPlease Enter deposit amnount? ";
	cin >> amount;
	cout << "\nAre You Sure you want perform this transaction? y/n ? ";
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		vClients = EditvectorDepostit(vClients, AccountNumber, amount);
		SaveClientsDataToFile(ClientsFileName, vClients);
		cout << "\nDone Successfully new balance is: " << getAccountBalance(vClients, AccountNumber) << endl;
	}
}
void CaseDeposit()
{
	vector<sClients> vClients = LoadClientDataFromFile(ClientsFileName);
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "         Deposit Screen\n";
	cout << "-----------------------------------\n";
	string AccountNumber;
	cout << "Please Enter Account Number? ";
	getline(cin >> ws, AccountNumber);
	SearchClient(vClients, AccountNumber);
	if (isClientFound(vClients, AccountNumber))
	{
		Deposit(vClients, AccountNumber);
	}
	GoBackToTrans();
}
//------------
bool isAmountBigger(vector<sClients>& vClients, string AccountNumber, double amount)
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
void Withdraw(vector<sClients>& vClients, string AccountNumber)
{
	char ch;
	double amount;
	cout << "\nPlease Enter withdraw amnount? ";
	cin >> amount;
	while (isAmountBigger(vClients, AccountNumber, amount))
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << getAccountBalance(vClients, AccountNumber) << endl;
		cout << "Please Enter another amount? ";
		cin >> amount;
	}
	cout << "\nAre You Sure you want perform this transaction? y/n ? ";
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		vClients = EditvectorWithdraw(vClients, AccountNumber, amount);
		SaveClientsDataToFile(ClientsFileName, vClients);
		cout << "\nDone Successfully new balance is: " << getAccountBalance(vClients, AccountNumber) << endl;
	}

}
void CaseWithdraw()
{
	vector<sClients> vClients = LoadClientDataFromFile(ClientsFileName);
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "         Withdraw Screen\n";
	cout << "-----------------------------------\n";
	string AccountNumber;
	cout << "Please Enter Account Number? ";
	getline(cin >> ws, AccountNumber);
	SearchClient(vClients, AccountNumber);
	if (isClientFound(vClients, AccountNumber))
	{
		Withdraw(vClients, AccountNumber);
	}
	GoBackToTrans();
}
//------------
double getTotalAcountBalance(vector<sClients>& vClients)
{
	double result = 0;
	for (sClients& C : vClients)
	{
		result += C.AccountBalance;
	}
	return result;
}
void PrintrecordForTotalBalance(sClients Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.FirstName + " " + Client.LastName;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void CaseTotalBalance()
{
	system("cls");
	vector <sClients> vClients = LoadClientDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (sClients Client : vClients)
	{
		PrintrecordForTotalBalance(Client);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "                                       Total Balance : " << getTotalAcountBalance(vClients) << "\n\n";
	GoBackToTrans();
}
//------------
enum ChoesTrans
{
	enumDepsit = 1, enumWithdraw = 2, enumTotalBalance = 3, MainMenue = 4
};
void StatmentsTrans(ChoesTrans ChoesTransactions)
{
	switch (ChoesTransactions)
	{
	case enumDepsit:
		CaseDeposit();
		break;
	case enumWithdraw:
		CaseWithdraw();
		break;
	case enumTotalBalance:
		CaseTotalBalance();
		break;
	case MainMenue:
		ShowMainMenue();
		break;
	default:
		break;
	}
}
void TransactionsMenueScreen()
{
	if (!CheackAccessPermissions(getPermissions::enummTransactions))
	{
		NoAccess();
		GoBackToMenu();
		return;
	}
	system("cls");
	cout << "\n==================================\n";
	cout << "      Transactions Menue Screen\n";
	cout << "==================================\n";
	cout << "       [1] Deposit.\n" <<
		"       [2] Withdraw.\n" <<
		"       [3] Total Balances.\n" <<
		"       [4] Main Menue.\n";
	cout << "==================================" << endl;
	cout << "Choose what do you want to do? [1 to 4]? ";
	StatmentsTrans((ChoesTrans)ReadChoes());
}
void GoBackToTrans()
{
	cout << "\nPress Enter To Back to Transactions Menue\n";
	system("pause>0");
	TransactionsMenueScreen();
}
//------------------
void PrintrecordForUsers(sUsers User)
{
	cout << "| " << setw(15) << left << User.Username;
	cout << "| " << setw(20) << left << User.Password;
	cout << "| " << setw(12) << left << User.Permissions;
}
sUsers ConvertLineToRecordUser(string Line, string sperator = "#//#")
{
	sUsers User;
	vector<string> result = FillVectorByData(Line, sperator);
	User.Username = result[0];
	User.Password = stoi(result[1]);
	User.Permissions = stoi(result[2]);
	return User;
}
vector<sUsers>LoadUserDataFromFile(string UsersFileName)
{
	vector<sUsers>vUsers;
	fstream MyFile;
	MyFile.open(UsersFileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sUsers Users;
		while (getline(MyFile, Line))
		{
			Users = ConvertLineToRecordUser(Line);
			vUsers.push_back(Users);
		}
		MyFile.close();
	}
	return vUsers;
}
bool FindUsernameAndPassword(string username, int password, sUsers& User)
{
	vector<sUsers> Users = LoadUserDataFromFile(UsersFileName);
	for (sUsers& U : Users)
	{
		if (username == U.Username)
		{
			if (password == U.Password)
			{
				User = U;
				return true;
			}
		}
	}
	return false;
}
void PrintUsersList()
{
	system("cls");
	vector <sUsers> vUsers = LoadUserDataFromFile(UsersFileName);
	cout << "\n\t\t\t\t\tClient List (" << vUsers.size() << ") Client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(20) << "Password";
	cout << "| " << left << setw(12) << "Permissions";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (sUsers& User : vUsers)
	{
		PrintrecordForUsers(User);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}
//****
//-----
void NoAccess()
{
	system("cls");
	cout << "\n_______________________________________\n";
	cout << "Access Denied,\n";
	cout << "You Dont have premissions To Do this,\n";
	cout << "Please Conact Your Admin.\n";
	cout << "\n_______________________________________\n";
}

//-----
int Permissions()
{
	char Answer;
	int premissions = 0;
	cout << "\nDo You want to give full access? y/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		return -1;
	}
	cout << "\nDo you Want to give access to:\n";
	cout << "\nShow Client List? y/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		premissions += getPermissions::enumShowClientList;
	}
	cout << "\nAdd New Client? y/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		premissions += getPermissions::enumAddNewClient;
	}
	cout << "\nDelete Client? y/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		premissions += getPermissions::enumDeleteClient;
	}
	cout << "\nUpdate Client? y/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		premissions += getPermissions::enumUpdateClient;
	}
	cout << "\nFind Client? y/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		premissions += getPermissions::enumFindClient;
	}
	cout << "\nTransactions? y/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		premissions += getPermissions::enummTransactions;
	}
	cout << "\nManage Users? y/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		premissions += getPermissions::enummManageUsers;
	}
	return premissions;
}
bool CheackAccessPermissions(getPermissions Permission)
{
	if (User.Permissions == -1)
		return true;
	if ((Permission & User.Permissions) == Permission)
		return true;
	return false;
}
void GoBackManageUser()
{
	cout << "\nPress Enter To Back to Manage Screen\n";
	system("pause>0");
	HeadManageUsersScreen();
}
string ConvertRecordToLineUser(sUsers User, string sperator = "#//#")
{
	string result = "";
	result += User.Username + sperator;
	result += to_string(User.Password) + sperator;
	result += to_string(User.Permissions);
	return result;
}
void AddFileUser(string User, string FileName)
{
	fstream user;
	user.open(FileName, ios::out | ios::app);
	if (user.is_open())
	{
		user << User << endl;
		user.close();
	}
}
bool isFoundUser(string username)
{
	vector<sUsers> User = LoadUserDataFromFile(UsersFileName);
	for (sUsers& U : User)
	{
		if (U.Username == username)
			return true;
	}
	return false;
}
void AddNewUser()
{
	sUsers User;
	cout << "Enter Username: ";
	getline(cin >> ws, User.Username);
	while (isFoundUser(User.Username))
	{
		cout << "User With [" << User.Username << "] already exists, Enter another Username? ";
		getline(cin >> ws, User.Username);
	}
	cout << "Enter Password: ";
	cin >> User.Password;
	User.Permissions = Permissions();
	AddDataLineToFile(UsersFileName, ConvertRecordToLineUser(User));
}
void AddUsers()
{
	char ch = 'Y';
	do
	{
		cout << "Adding New User:\n\n";

		AddNewUser();

		cout << "User Add Successfully, do you want to add more users? y/n ? ";
		cin >> ch;
	} while (toupper(ch) == 'Y');
}
void AddUserScreen()
{
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "         Add New User Screen\n";
	cout << "-----------------------------------\n";
	AddUsers();
	GoBackManageUser();
}
//****
//------------------
short ReadChoes()
{
	short ch;
	cin >> ch;
	return ch;
}
enum Choes
{
	enumShow = 1, enumAdd = 2, enumDelete = 3, enumUpdate = 4, enumFind = 5, enumTransactions = 6,
	enumManageUsers = 7
	, enumLogOut = 8
};
void GoBackToMenu()
{
	cout << "\nPress Enter To Back to main\n";
	system("pause>0");
	ShowMainMenue();
}
void Case1()
{
	if (!CheackAccessPermissions(getPermissions::enumShowClientList))
	{
		NoAccess();
		GoBackToMenu();
		return;
	}
	system("cls");
	PrintAllClientsData();
	GoBackToMenu();
}
void Case2()
{
	if (!CheackAccessPermissions(getPermissions::enumAddNewClient))
	{
		NoAccess();
		GoBackToMenu();
		return;
	}
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "         Add New Client Screen\n";
	cout << "-----------------------------------\n";
	AddClients();
	GoBackToMenu();
}
void Case3()
{
	if (!CheackAccessPermissions(getPermissions::enumDeleteClient))
	{
		NoAccess();
		GoBackToMenu();
		return;
	}
	vector<sClients> vClients = LoadClientDataFromFile(ClientsFileName);
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "         Delete Client Screen\n";
	cout << "-----------------------------------\n";
	string AccountNumber;
	cout << "Please Enter Account Number? ";
	getline(cin >> ws, AccountNumber);
	SearchClient(vClients, AccountNumber);
	if (isClientFound(vClients, AccountNumber))
	{
		DeleteClient(vClients, AccountNumber);
	}
	GoBackToMenu();
}
void case4()
{
	if (!CheackAccessPermissions(getPermissions::enumUpdateClient))
	{
		NoAccess();
		GoBackToMenu();
		return;
	}
	vector<sClients> vClients = LoadClientDataFromFile(ClientsFileName);
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "         Update Client Screen\n";
	cout << "-----------------------------------\n";
	string AccountNumber;
	cout << "Please Enter Account Number? ";
	getline(cin >> ws, AccountNumber);
	SearchClient(vClients, AccountNumber);
	if (isClientFound(vClients, AccountNumber))
	{
		UpdateClient(vClients, AccountNumber);
	}
	GoBackToMenu();
}
void Case5()
{
	if (!CheackAccessPermissions(getPermissions::enumFindClient))
	{
		NoAccess();
		GoBackToMenu();
		return;
	}
	vector<sClients> vClients = LoadClientDataFromFile(ClientsFileName);
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "         Find Client Screen\n";
	cout << "-----------------------------------\n";
	cout << "Please Enter AcoountNumber? ";
	string AccountNumber;
	getline(cin >> ws, AccountNumber);
	SearchClient(vClients, AccountNumber);
	GoBackToMenu();
}
void Case7()
{
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "         Program Ends :-)\n";
	cout << "-----------------------------------\n";
	system("pause>0");
}
void Statments(Choes ch)
{
	switch (ch)
	{
	case Choes::enumShow:
		Case1();
		break;
	case Choes::enumAdd:
		Case2();
		break;
	case  Choes::enumDelete:
		Case3();
		break;
	case  Choes::enumUpdate:
		case4();
		break;
	case  Choes::enumFind:
		Case5();
		break;
	case Choes::enumTransactions:
		TransactionsMenueScreen();
		break;
	case  Choes::enumManageUsers:
		HeadManageUsersScreen();
		break;
	case Choes::enumLogOut:
		LoginScreen();
		break;
	}
}
void ShowMainMenue()
{
	system("cls");
	cout << "\n==================================\n";
	cout << "           Main Menu Screen\n";
	cout << "==================================\n";
	cout << "       [1] Show Client List.\n" <<
		"       [2] Add New Client.\n" <<
		"       [3] Delete Client.\n" <<
		"       [4] Update Clien Info.\n" <<
		"       [5] Find Client.\n" <<
		"       [6] Transactions.\n" <<
		"       [7] Manage Users.\n" <<
		"       [8] LogOut.\n";
	cout << "==================================" << endl;
	cout << "Choose what do you want to do? [1 to 7]? ";
	Statments((Choes)ReadChoes());
}
//---------------------
void PrintUser_WithAccountNumber(vector<sUsers> vUsers, string Username)
{
	for (sUsers& User : vUsers)
	{
		if (User.Username == Username)
		{
			cout << "\nThe Following are the User detalis:\n";
			cout << "\nUsername: " << User.Username;
			cout << "\nPassword: " << User.Password;
			cout << "\nPermissions: " << User.Permissions << endl;
		}
	}
}
bool isUserFound(vector<sUsers> vUsers, string Username)
{
	for (sUsers& User : vUsers)
	{
		if (User.Username == Username)
		{
			return true;
		}
	}
	return false;
}
void SearchUser(vector<sUsers> vUsers, string Username)
{

	if (isUserFound(vUsers, Username))
	{
		PrintUser_WithAccountNumber(vUsers, Username);
	}
	else
	{
		cout << "\nUser With Username (" << Username << ") Not Found!\n";
	}

}
bool MarkForDeleteUser(vector<sUsers>& vUsers, string Username)
{
	for (sUsers& C : vUsers)
	{
		if (C.Username == Username)
		{
			C.Flag = true;
			return true;
		}
	}
	return false;
}
vector<sUsers>SaveUsersDataToFile(string UsersFileName, vector<sUsers> vUsers)
{
	fstream MyFile;
	MyFile.open(UsersFileName, ios::out);
	string DataLine;
	if (MyFile.is_open())
	{
		for (sUsers& C : vUsers)
		{
			if (C.Flag == false)
			{
				DataLine = ConvertRecordToLineUser(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vUsers;
}
void DeleteUser(vector<sUsers>& vUsers, string Username)
{

	char ch;
	cout << "\nAre You Sure you want delete this User? y/n ? ";
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		MarkForDeleteUser(vUsers, Username);
		SaveUsersDataToFile(UsersFileName, vUsers);
		vUsers = LoadUserDataFromFile(UsersFileName);
		cout << "\nUser Deleted Successfully.\n";
	}

}
void DeleteScreen()
{
	vector<sUsers> vUsers = LoadUserDataFromFile(UsersFileName);
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "         Delete User Screen\n";
	cout << "-----------------------------------\n";
	string Username;
	cout << "Please Enter Username? ";
	getline(cin >> ws, Username);
	if (Username == "Admin")
	{
		cout << "\nYou Cannot Delete This User\n";
	}
	else
	{
		SearchUser(vUsers, Username);
		if (isUserFound(vUsers, Username))
		{
			DeleteUser(vUsers, Username);
		}
	}
	GoBackManageUser();
}
//---------
vector<sUsers>EditVectorForUpdateUsers(vector<sUsers>& vUsers, string Username, int nPassword, int nPermissions)
{
	for (sUsers& C : vUsers)
	{
		if (C.Username == Username)
		{
			C.Password = nPassword;
			C.Permissions = nPermissions;
		}
	}
	return vUsers;
}
void UpdateUser(vector<sUsers>& vUsers, string Username)
{
	char ch;
	int Password = 0;
	int Permissons = 0;;
	cout << "\nAre You Sure you want update this user? y/n ? ";
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		cout << "Enter Password: ";
		cin >> Password;
		Permissons = Permissions();
		vUsers = EditVectorForUpdateUsers(vUsers, Username, Password, Permissons);
		SaveUsersDataToFile(UsersFileName, vUsers);
		cout << "\nUser Updated Successfully.\n";
	}
}
void UpdateScreen()
{
	vector<sUsers> vUsers = LoadUserDataFromFile(UsersFileName);
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "         Update User Screen\n";
	cout << "-----------------------------------\n";
	string Username;
	cout << "Please Enter Username? ";
	getline(cin >> ws, Username);
	SearchUser(vUsers, Username);
	if (isUserFound(vUsers, Username))
	{
		UpdateUser(vUsers, Username);
	}
	GoBackManageUser();
}
//---------
void FindScreen()
{
	vector<sUsers> vUsers = LoadUserDataFromFile(UsersFileName);
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "         Find Client Screen\n";
	cout << "-----------------------------------\n";
	cout << "Please Enter Username? ";
	string Username;
	getline(cin >> ws, Username);
	if (Username == "Admin")
	{
		cout << "\nYou Connot Show This User.!\n";
	}
	else
	{
		SearchUser(vUsers, Username);
	}
	GoBackManageUser();
}
//---------
enum ChoesUs
{
	enumListUsers = 1, enumAddNewUser = 2, enumDeleteUser = 3, enumUpdateUser = 4,
	enumFindUser = 5, enumMainMenue = 6
};
void StatmentsUsers(ChoesUs Us)
{
	switch (Us)
	{
	case enumListUsers:
		PrintUsersList();
		GoBackManageUser();
		break;
	case enumAddNewUser:
		AddUserScreen();
		break;
	case enumDeleteUser:
		DeleteScreen();
		break;
	case enumUpdateUser:
		UpdateScreen();
		break;
	case enumFindUser:
		FindScreen();
		break;
	case enumMainMenue:
		ShowMainMenue();
		break;
	default:
		break;
	}
}
void HeadManageUsersScreen()
{
	if (!CheackAccessPermissions(getPermissions::enummManageUsers))
	{
		NoAccess();
		GoBackToMenu();
		return;
	}
	system("cls");
	cout << "\n==================================\n";
	cout << "     Manage Users Menue Screen\n";
	cout << "==================================\n";
	cout << "       [1] List Users.\n" <<
		"       [2] Add New User.\n" <<
		"       [3] Delete User.\n" <<
		"       [4] Update User.\n" <<
		"       [5] Find User.\n" <<
		"       [6] Main Menue.\n";
	cout << "==================================" << endl;
	cout << "Choose what do you want to do? [1 to 6]? ";
	StatmentsUsers((ChoesUs)ReadChoes());
}
//---------------------
void HeadLoginScreen()
{
	system("cls");
	cout << "\n==================================\n";
	cout << "           Login Screen\n";
	cout << "==================================\n";
}
void Login(string username, int password, sUsers& User)
{
	if (FindUsernameAndPassword(username, password, User))
	{
		ShowMainMenue();
	}
	else
	{
		HeadLoginScreen();
		cout << "Invalied Username/Password\n";
		cout << "Enter Username? ";
		getline(cin >> ws, username);
		cout << "Enter Password? ";
		cin >> password;
		Login(username, password, User);
	}
}
void LoginScreen()
{
	HeadLoginScreen();
	string username;
	int password;
	cout << "Enter Username? ";
	getline(cin >> ws, username);
	cout << "Enter Password? ";
	cin >> password;
	Login(username, password, User);
}