#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "auth.h"
#include "Windows.h"

using namespace std;

struct Routes
{
	string RouteNumber;
	string BusType;
	string Destination;
	string Date;
	string DepTime;
	string ArrTime;
	double Price;
	unsigned int TicketsLeft;
	unsigned int TicketsSold;
};

string RoutesPath = "routes.txt";

void ShowMainMenu(int);
void RoutesExport(vector<Routes>);
vector<Routes> RoutesImport();
void AdminPanel(int);
void RoutesEditor();
void RouteCreate();
void RouteDelete();
vector<Routes> RouteSortByTime(vector<Routes>);
vector<Routes> RouteSort(vector<Routes>);
void ShowAllRoutes();

void ShowMainMenu(int Role)
{
	switch (Role)
	{
	case 0:
	{
		while (true)
		{
			bool changeing = false;
			system("cls");
			cout << "1. ����� �����" << endl;
			cout << "2. �������� ���� ������" << endl;
			cout << "3. ����� ������������" << endl;
			cout << "4. ����� �� ���������" << endl;

			char choise;
			cout << "\n������� ����� ������ ����: ";
			cin >> choise;

			switch (choise)
			{
			case '1':
			{
				system("cls");
				cout << "1. ����� �����" << endl;
				break;
			}
			case '2':
			{
				ShowAllRoutes();
				break;
			}
			case '3':
			{
				system("cls");
				changeing = true;
				break;
			}
			case '4':
			{
				exit(0);
				break;
			}
			default:
			{
				cout << "������ ������ ���� �� ����������...\n ��������� ����" << endl;
				system("pause");
				break;
			}
			}

			if (changeing == true)
			{
				break;
			}
		}
		break;
	}
	case 1:
	{
		while (true)
		{
			bool changeing = false;
			system("cls");
			cout << "1. ����� �����" << endl;
			cout << "2. �������� ���� ������" << endl;
			cout << "3. ������� �������" << endl;
			cout << "4. ����� ������������" << endl;
			cout << "5. ����� �� ���������" << endl;

			char choise;
			cout << "\n������� ����� ������ ����: ";
			cin >> choise;

			switch (choise)
			{
			case '1':
			{
				system("cls");
				cout << "1. ����� �����" << endl;
				break;
			}
			case '2':
			{
				ShowAllRoutes();
				break;
			}
			case '3':
			{
				system("cls");
				cout << "3. ������� �������" << endl;
				break;
			}
			case '4':
			{
				system("cls");
				changeing = true;
				break;
			}
			case '5':
			{
				exit(0);
				break;
			}
			default:
			{
				cout << "������ ������ ���� �� ����������...\n ��������� ����" << endl;
				system("pause");
				break;
			}
			}

			if (changeing == true)
			{
				break;
			}
		}
		break;
	}
	case 2: case 3:
	{
		while (true)
		{
			bool changeing = false;
			system("cls");
			cout << "0. �����-������" << endl;
			cout << "1. ����� �����" << endl;
			cout << "2. �������� ���� ������" << endl;
			cout << "3. ������� �������" << endl;
			cout << "4. ����� ������������" << endl;
			cout << "5. ����� �� ���������" << endl;

			char choise;
			cout << "\n������� ����� ������ ����: ";
			cin >> choise;

			switch (choise)
			{
			case '0':
			{
				AdminPanel(Role);
				break;
			}
			case '1':
			{
				system("cls");
				cout << "1. ����� �����" << endl;
				break;
			}
			case '2':
			{
				ShowAllRoutes();
				break;
			}
			case '3':
			{
				system("cls");
				cout << "3. ������� �������" << endl;
				break;
			}
			case '4':
			{
				system("cls");
				changeing = true;
				break;
			}
			case '5':
			{
				exit(0);
				break;
			}
			default:
			{
				cout << "������ ������ ���� �� ����������...\n ��������� ����" << endl;
				system("pause");
				break;
			}
			}

			if (changeing == true)
			{
				break;
			}
		}
		break;
	}
	}
}

void AdminPanel(int Role)
{
	while (true)
	{
		bool returning = false;
		system("cls");
		cout << "0. ��������� ��������������" << endl;
		cout << "1. ����������� ��������" << endl;
		cout << "2. ��� ��������" << endl;
		cout << "3. ������ ��������" << endl;
		cout << "4. ���� ���������" << endl;
		cout << "5. ��������� � ������� ����" << endl;

		char choise;
		cout << "\n������� ����� ������ ����: ";
		cin >> choise;

		switch (choise)
		{
		case '0':
		{
			if (Role == 3)
			{
				GiveAdmin();
			}
			else
			{
				cout << "�� ������ ������������� ������� �������������� ��� ������� � ������� �������." << endl;
				system("pause");
			}
			break;
		}
		case '1':
		{
			Verification();
			break;
		}
		case '2':
		{
			Ban(1);
			break;
		}
		case '3':
		{
			Ban(2);
			break;
		}
		case '4':
		{
			if (Role == 3)
			{
				RoutesEditor();
			}
			else
			{
				cout << "�� ������ ������������� ������� �������������� ��� ������� � ������� �������." << endl;
				system("pause");
			}
			break;
		}
		case '5':
		{
			returning = true;
			break;
		}
		default:
		{
			cout << "������ ������ ���� �� ����������...\n ��������� ����" << endl;
			system("pause");
			break;
		}
		}

		if (returning == true)
		{
			break;
		}
	}
}

void RoutesEditor()
{
	while (true)
	{
		bool returning = false;
		system("cls");
		cout << "1. ������� ����" << endl;
		cout << "2. ������� ����" << endl;
		cout << "3. ��������/��������� ���������� ��������� ���� �� �����" << endl;
		cout << "4. ��������� �����" << endl;

		char choise;
		cout << "\n������� ����� ������ ����: ";
		cin >> choise;

		switch (choise)
		{
		case '1':
		{
			RouteCreate();
			break;
		}
		case '2':
		{
			RouteDelete();
			break;
		}
		case '3':
		{

			break;
		}
		case '4':
		{
			returning = true;
			break;
		}
		default:
		{
			cout << "������ ������ ���� �� ����������...\n ��������� ����" << endl;
			system("pause");
			break;
		}
		}

		if (returning == true)
		{
			break;
		}
	}
}

void RouteCreate()
{
	system("cls");

	vector <Routes> RouteSpis;

	Routes temp;

	cout << "���� �� ������ �������� �������� �����, ������� '-1'" << endl;

	cout << "������� ����� ��������: ";
	cin >> temp.RouteNumber;
	if (temp.RouteNumber == "-1")
	{
		cout << "\n�� �������� ������� �������� �����." << endl;
		system("pause");
		return;
	}

	cout << "������� ��� ��������: ";
	cin >> temp.BusType;
	if (temp.BusType == "-1")
	{
		cout << "\n�� �������� ������� �������� �����." << endl;
		system("pause");
		return;
	}

	cout << "������� ����� ����������: ";
	cin >> temp.Destination;
	if (temp.Destination == "-1")
	{
		cout << "\n�� �������� ������� �������� �����." << endl;
		system("pause");
		return;
	}

	cout << "������� ���� ����������� (� ������� DD.MM.YYYY): ";
	cin >> temp.Date;
	if (temp.Date == "-1")
	{
		cout << "\n�� �������� ������� �������� �����." << endl;
		system("pause");
		return;
	}

	cout << "������� ����� ����������� (� ������� HH:MM): ";
	cin >> temp.DepTime;
	if (temp.DepTime == "-1")
	{
		cout << "\n�� �������� ������� �������� �����." << endl;
		system("pause");
		return;
	}

	cout << "������� ����� �������� (� ������� HH:MM): ";
	cin >> temp.ArrTime;
	if (temp.ArrTime == "-1")
	{
		cout << "\n�� �������� ������� �������� �����." << endl;
		system("pause");
		return;
	}

	cout << "������� ���� ������ �����: ";
	cin >> temp.Price;
	if (temp.Price == -1)
	{
		cout << "\n�� �������� ������� �������� �����." << endl;
		system("pause");
		return;
	}

	cout << "������� ���������� ������� ��� ����������: ";
	cin >> temp.TicketsLeft;
	
	temp.TicketsSold = 0;

	RouteSpis = RoutesImport();
	RouteSpis.push_back(temp);
	RouteSpis = RouteSort(RouteSpis);
	RoutesExport(RouteSpis);
}

void RouteDelete()
{

}

void ShowAllRoutes()
{
	while (true)
	{
		bool returning = false;
		system("cls");
		cout << "1. ���������� �� ������� �����������" << endl;
		cout << "2. ���������� �� ������ ����������" << endl;
		cout << "3. ��������� �����" << endl;

		char choise;
		cout << "\n������� ����� ������ ����: ";
		cin >> choise;

		switch (choise)
		{
		case '1':
		{
			system("cls");
			vector<Routes> RouteSpis;
			RouteSpis = RoutesImport();
			RouteSpis = RouteSortByTime(RouteSpis);
			
			cout << "�����.\t��� �/�\t����� ����������\t����\t����.\t����.\t����\t����.\t����." << endl;
			cout << "=========================================================================" << endl;
			for (int i = 0; i < RouteSpis.size(); i++)
			{
				cout << RouteSpis[i].RouteNumber << "\t" << RouteSpis[i].BusType << "\t" << RouteSpis[i].Destination << "\t\t" << RouteSpis[i].Date << "\t" << RouteSpis[i].DepTime << "\t" << RouteSpis[i].ArrTime << "\t" << RouteSpis[i].Price << "\t" << RouteSpis[i].TicketsLeft << "\t" << RouteSpis[i].TicketsSold << endl;
			}
			cout << endl;
			system("pause");
			break;
		}
		case '2':
		{
			system("cls");
			vector<Routes> RouteSpis;
			RouteSpis = RoutesImport();
			RouteSpis = RouteSort(RouteSpis);

			cout << "�����.\t��� �/�\t����� ����������\t����\t����.\t����.\t����\t����.\t����." << endl;
			cout << "=========================================================================" << endl;
			for (int i = 0; i < RouteSpis.size(); i++)
			{
				cout << RouteSpis[i].RouteNumber << "\t" << RouteSpis[i].BusType << "\t" << RouteSpis[i].Destination << "\t\t" << RouteSpis[i].Date << "\t" << RouteSpis[i].DepTime << "\t" << RouteSpis[i].ArrTime << "\t" << RouteSpis[i].Price << "\t" << RouteSpis[i].TicketsLeft << "\t" << RouteSpis[i].TicketsSold << endl;
			}
			cout << endl;
			system("pause");
			break;
		}
		case '3':
		{
			returning = true;
			break;
		}
		default:
		{
			cout << "������ ������ ���� �� ����������...\n ��������� ����" << endl;
			system("pause");
			break;
		}
		}

		if (returning == true)
		{
			break;
		}
	}
}

vector<Routes> RouteSortByTime(vector<Routes> temp)
{
	//sort by Date
	for (int i = 0; i < temp.size(); i++)
	{
		for (int j = 1; j < temp.size(); j++)
		{
			if (temp[j].Date != temp[j - 1].Date)
			{
				string s1 = "", s2 = "";
				for (int k = 9; k >= 0; k--)
				{
					s1 += temp[j].Date[k];
					s2 += temp[j - 1].Date[k];
				}

				if (s1 < s2)
				{
					Routes t;
					t = temp[j];
					temp[j] = temp[j - 1];
					temp[j - 1] = t;
				}
			}
		}
	}

	//sort by DepTime
	for (int i = 0; i < temp.size(); i++)
	{
		for (int j = 1; j < temp.size(); j++)
		{
			if (temp[j].Date == temp[j - 1].Date)
			{
				string s1 = "", s2 = "";
				s1.assign(temp[j].DepTime, 0, 2);
				s2.assign(temp[j - 1].DepTime, 0, 2);
				if (stoi(s1) < stoi(s2))
				{
					Routes t;
					t = temp[j];
					temp[j] = temp[j - 1];
					temp[j - 1] = t;
					continue;
				}

				if (stoi(s1) == stoi(s2))
				{
					string s3 = "", s4 = "";
					s3.assign(temp[j].DepTime, 3, 2);
					s4.assign(temp[j - 1].DepTime, 3, 2);
					if (stoi(s3) < stoi(s4))
					{
						Routes t;
						t = temp[j];
						temp[j] = temp[j - 1];
						temp[j - 1] = t;
						continue;
					}
				}
			}
		}
	}

	return temp;
}

vector<Routes> RouteSort(vector<Routes> temp)
{
	//sort by Destination
	for (int i = 0; i < temp.size(); i++)
	{
		for (int j = 1; j < temp.size(); j++)
		{
			if (temp[j].Destination < temp[j - 1].Destination)
			{
				Routes t;
				t = temp[j];
				temp[j] = temp[j - 1];
				temp[j - 1] = t;
			}
		}
	}

	//sort by Date
	for (int i = 0; i < temp.size(); i++)
	{
		for (int j = 1; j < temp.size(); j++)
		{
			if ((temp[j].Destination == temp[j - 1].Destination) && (temp[j].Date != temp[j - 1].Date))
			{
				string s1 = "", s2 = "";
				for (int k = 9; k >= 0; k--)
				{
					s1 += temp[j].Date[k];
					s2 += temp[j - 1].Date[k];
				}

				if (s1 < s2)
				{
					Routes t;
					t = temp[j];
					temp[j] = temp[j - 1];
					temp[j - 1] = t;
				}
			}
		}
	}

	//sort by DepTime
	for (int i = 0; i < temp.size(); i++)
	{
		for (int j = 1; j < temp.size(); j++)
		{
			if (temp[j].Date == temp[j - 1].Date)
			{
				string s1 = "", s2 = "";
				s1.assign(temp[j].DepTime, 0, 2);
				s2.assign(temp[j - 1].DepTime, 0, 2);
				if (stoi(s1) < stoi(s2))
				{
					Routes t;
					t = temp[j];
					temp[j] = temp[j - 1];
					temp[j - 1] = t;
					continue;
				}

				if (stoi(s1) == stoi(s2))
				{
					string s3 = "", s4 = "";
					s3.assign(temp[j].DepTime, 3, 2);
					s4.assign(temp[j - 1].DepTime, 3, 2);
					if (stoi(s3) < stoi(s4))
					{
						Routes t;
						t = temp[j];
						temp[j] = temp[j - 1];
						temp[j - 1] = t;
						continue;
					}
				}
			}
		}
	}

	return temp;
}

void RoutesExport(vector<Routes> temp)
{
	fstream file(RoutesPath, ios::binary | ios::out | ios::trunc);

	size_t len;
	len = temp.size();
	file.write((char*)&len, sizeof(size_t));

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		len = temp[i].RouteNumber.length();
		file.write((char*)&len, sizeof(size_t));
		file.write(temp[i].RouteNumber.data(), len);

		len = temp[i].BusType.length();
		file.write((char*)&len, sizeof(size_t));
		file.write(temp[i].BusType.data(), len);

		len = temp[i].Destination.length();
		file.write((char*)&len, sizeof(size_t));
		file.write(temp[i].Destination.data(), len);

		len = temp[i].Date.length();
		file.write((char*)&len, sizeof(size_t));
		file.write(temp[i].Date.data(), len);

		len = temp[i].DepTime.length();
		file.write((char*)&len, sizeof(size_t));
		file.write(temp[i].DepTime.data(), len);

		len = temp[i].ArrTime.length();
		file.write((char*)&len, sizeof(size_t));
		file.write(temp[i].ArrTime.data(), len);

		file.write((char*)&temp[i].Price, sizeof(double));

		file.write((char*)&temp[i].TicketsLeft, sizeof(unsigned int));

		file.write((char*)&temp[i].TicketsSold, sizeof(unsigned int));
	}

	file.close();
}

vector<Routes> RoutesImport()
{
	vector<Routes> temp;
	fstream file(RoutesPath, ios::binary | ios::in);

	size_t len, kol;
	file.read((char*)&kol, sizeof(size_t));

	for (unsigned int i = 0; i < kol; i++)
	{
		Routes tmp;
		char* str;

		file.read((char*)&len, sizeof(size_t));
		str = new char[len + 1];
		file.read(str, len);
		str[len] = '\0';
		tmp.RouteNumber = str;

		file.read((char*)&len, sizeof(size_t));
		str = new char[len + 1];
		file.read(str, len);
		str[len] = '\0';
		tmp.BusType = str;

		file.read((char*)&len, sizeof(size_t));
		str = new char[len + 1];
		file.read(str, len);
		str[len] = '\0';
		tmp.Destination = str;

		file.read((char*)&len, sizeof(size_t));
		str = new char[len + 1];
		file.read(str, len);
		str[len] = '\0';
		tmp.Date = str;

		file.read((char*)&len, sizeof(size_t));
		str = new char[len + 1];
		file.read(str, len);
		str[len] = '\0';
		tmp.DepTime = str;

		file.read((char*)&len, sizeof(size_t));
		str = new char[len + 1];
		file.read(str, len);
		str[len] = '\0';
		tmp.ArrTime = str;

		file.read((char*)&tmp.Price, sizeof(double));

		file.read((char*)&tmp.TicketsLeft, sizeof(unsigned int));

		file.read((char*)&tmp.TicketsSold, sizeof(unsigned int));

		temp.push_back(tmp);

		delete[]str;
	}

	file.close();
	return temp;
}
