#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Windows.h"
#include <ctime>
#include <conio.h>

using namespace std;

string UsersPath = "users.txt";

struct UsersList
{
	string Login;
	unsigned int SaltedHashPassword;
	string Salt;
	unsigned int Role = 0;
	int Access = 0;
};

int Loginning();
bool Registration();
int Authorisation();
string SaltGenerator();
unsigned int HashPassword(string);
string InPass();
vector<UsersList> FileImport();
void FileExport(vector<UsersList>);
void Verification();
void Ban(unsigned int);
void GiveAdmin();

int Loginning()
{
	while (true)
	{
		system("cls");
		cout << "1. Регистрация в программе" << endl;
		cout << "2. Авторизация в программе" << endl;
		cout << "3. Продолжить без авторизации" << endl;
		cout << "4. Выход из программы" << endl;

		char choise;
		cout << "\nВведите номер пункта меню: ";
		cin >> choise;

		switch (choise)
		{
		case '1':
		{
			bool registered = false;
			while (!registered)
			{
				registered = Registration();
			}
			break;
		}
		case '2':
		{
			int TempRole = 0;
			TempRole = Authorisation();

			if (TempRole == -1)
			{
				break;
			}

			return TempRole;
			break;
		}
		case '3':
		{
			int TempRole = 0;
			return TempRole;
			break;
		}
		case '4':
		{
			exit(0);
			break;
		}
		default:
		{
			cout << "Такого пункта меню не существует...\n Повторите ввод" << endl;
			system("pause");
			break;
		}
		}
	}
}

bool Registration()
{
	system("cls");

	vector <UsersList> UserSpis;

	UserSpis = FileImport();

	string TempLogin, TempPassword;
	cout << "Если вы хотите прервать регистрацию, введите '-1'" << endl;

	//Login
	cout << "Введите желаемый логин: ";
	cin >> TempLogin;
	if (TempLogin == "-1")
	{
		cout << "Вы прервали регистрацию.";
		return true;
	}
	else
	{
		for (int i = 0; i < (int)UserSpis.size(); i++)
		{
			if (UserSpis.at(i).Login == TempLogin)
			{
				cout << "Такой логин уже существует. Повторите регистрацию..." << endl;
				system("pause");
				return false;
			}
		}
	}

	//Password
	while (true)
	{
		cout << "Введите желаемый пароль: ";
		TempPassword = InPass();
		if (TempPassword == "-1")
		{
			cout << "Вы прервали регистрацию.";
			return true;
		}
		else
		{
			string Salt, TempPassword2;
			unsigned int HashSaltedPassword;

			cout << "Повторите пароль: ";
			TempPassword2 = InPass();

			if (TempPassword2 != TempPassword)
			{
				cout << "Пароли не совпадают. Повторите ввод..." << endl;
				continue;
			}

			Salt = SaltGenerator();
			HashSaltedPassword = HashPassword(TempPassword + Salt);

			UsersList temp = { TempLogin, HashSaltedPassword, Salt, 1, 0 };

			UserSpis.push_back(temp);

			//сохранение в файл
			FileExport(UserSpis);

			return true;
		}
	}
}

int Authorisation()
{
	system("cls");

	vector <UsersList> UserSpis;

	UserSpis = FileImport();

	string TempLogin, TempPassword;
	int IndexOfRecord = -1;
	cout << "Если Вы хотите прервать авторизацию, введите '-1'" << endl;

	//Login
	cout << "Введите Ваш логин: ";
	cin >> TempLogin;
	if (TempLogin == "-1")
	{
		cout << "Вы прервали авторизацию." << endl;
		system("pause");
		return -1;
	}
	else
	{
		for (int i = 0; i < (int)UserSpis.size(); i++)
		{
			if (UserSpis.at(i).Login == TempLogin)
			{
				if (UserSpis.at(i).Access == -1)
				{
					cout << "Ваш аккаунт заблокирован. Обратитесь к администратору для разблокировки." << endl;
					system("pause");
					return -1;
				}
				
				IndexOfRecord = i;
				break;
			}
		}

		if (IndexOfRecord == -1)
		{
			cout << "Такой логин не найден." << endl;
			system("pause");
			return -1;
		}
	}

	//Password
	int counter = 2;
	while (true)
	{
		cout << "Введите Ваш пароль: ";
		TempPassword = InPass();
		if (TempPassword == "-1")
		{
			cout << "Вы прервали авторизацию." << endl;
			system("pause");
			return -1;
		}
		else
		{
			unsigned int HashSaltedPassword;
			HashSaltedPassword = HashPassword(TempPassword + UserSpis[IndexOfRecord].Salt);

			if (HashSaltedPassword == UserSpis[IndexOfRecord].SaltedHashPassword)
			{

				if (UserSpis.at(IndexOfRecord).Access == 0)
				{
					cout << "Ваш аккаунт ещё не одобрен администратором. Вы продолжите в качестве гостя" << endl;
					system("pause");
					return 0;
				}
				
				return UserSpis[IndexOfRecord].Role;
			}
			else
			{
				if (counter != 0)
				{
					cout << "Введён неверный пароль. После трёх неверных попыток аккаунт будет заблокирован." << endl;
					if (UserSpis[IndexOfRecord].Role == 3)
					{

					}
					else
					{
						counter--;
					}
					continue;
				}
				else
				{
					cout << "Ваш аккаунт заблокирован. Обратитесь к администратору для разблокировки." << endl;
					UserSpis[IndexOfRecord].Access = -1;
					FileExport(UserSpis);
				}

				system("pause");
				return -1;
			}
		}
	}
}

string SaltGenerator()
{
	string Salt = "";

	srand((unsigned int)time(0));
	
	for (int i = 0; i < 8; i++)
	{
		Salt += (char)(97 + rand() % 122);
	}

	return Salt;
}

unsigned int HashPassword(string Password)
{
	unsigned int A = 54059, B = 76963, C = 86969, D = 37;

	unsigned h = D;
	
	for (unsigned int i = 0; i < Password.length(); i++)
	{
		h = (h * A) ^ (Password[i] * B);
	}

	return h % C;
}

vector<UsersList> FileImport()
{
	vector<UsersList> temp;
	fstream file(UsersPath, ios::binary | ios::in);
	
	size_t len, kol;
	file.read((char*)&kol, sizeof(size_t));

	for (unsigned int i = 0; i < kol; i++)
	{
		UsersList tmp;
		char* str;

		file.read((char*)&len, sizeof(size_t));
		str = new char[len + 1];
		file.read(str, len);
		str[len] = '\0';
		tmp.Login = str;

		file.read((char*)&tmp.SaltedHashPassword, sizeof(unsigned int));

		file.read((char*)&len, sizeof(size_t));
		str = new char[len + 1];
		file.read(str, len);
		str[len] = '\0';
		tmp.Salt = str;

		file.read((char*)&tmp.Role, sizeof(unsigned int));

		file.read((char*)&tmp.Access, sizeof(int));

		temp.push_back(tmp);

		delete[]str;
	}

	file.close();
	return temp;
}

void FileExport(vector<UsersList> temp)
{
	fstream file(UsersPath, ios::binary | ios::out | ios::trunc);
	
	size_t len;
	len = temp.size();
	file.write((char*)&len, sizeof(size_t));

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		len = temp[i].Login.length();
		file.write((char*)&len, sizeof(size_t));
		file.write(temp[i].Login.data(), len);

		file.write((char*)&temp[i].SaltedHashPassword, sizeof(unsigned int));

		len = temp[i].Salt.length();
		file.write((char*)&len, sizeof(size_t));
		file.write(temp[i].Salt.data(), len);

		file.write((char*)&temp[i].Role, sizeof(unsigned int));

		file.write((char*)&temp[i].Access, sizeof(int));
	}

	file.close();
}

string InPass()
{
	string TempPassword = "";
	int ch = 0;
	while (ch != 13)
	{
		ch = _getch();

		if (ch == 224 || ch == 0)
		{
			ch = _getch();
			continue;
		}

		if (ch == 8 && TempPassword.length() != 0)
		{
			TempPassword.erase(TempPassword.length() - 1, 1);
			cout << "\b \b";
			continue;
		}

		if ((ch >= 48 && ch <= 57) || ch == 45 || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
		{
			cout << "#";
			TempPassword += ch;
		}
	}
	cout << endl;
	return TempPassword;
}

void Verification()
{
	system("cls");

	vector <UsersList> UserSpis;

	UserSpis = FileImport();
	
	cout << "Список аккаунтов, ожидающих верификации: " << endl;
	for (unsigned int i = 0; i < UserSpis.size(); i++)
	{
		if (UserSpis[i].Access == 0)
		{
			cout << UserSpis[i].Login << endl;
		}
	}

	cout << "\nЕсли Вы хотите прервать процесс верификации аккаунта, введите '-1'" << endl;
	cout << "\nЕсли Вы хотите верифицировать все аккаунты, введите '-2'" << endl;

	while (true)
	{
		string TempLogin;
		cout << "Введите логин аккаунта для верификации: ";
		cin >> TempLogin;

		if (TempLogin == "-1")
		{
			cout << "Вы вышли из меню верификации аккаунтов" << endl;
			system("pause");
			return;
		}

		if (TempLogin == "-2")
		{
			for (unsigned int i = 0; i < UserSpis.size(); i++)
			{
				if (UserSpis[i].Access == 0)
				{
					UserSpis[i].Access = 1;
				}
			}

			cout << "Все аккаунты были верифицированы." << endl;
			FileExport(UserSpis);
			system("pause");
			return;
		}

		for (unsigned int i = 0; i < UserSpis.size(); i++)
		{
			if (UserSpis[i].Login == TempLogin)
			{
				if (UserSpis[i].Access == 1)
				{
					cout << "Аккаунт с логином " << UserSpis[i].Login << " не нужнается в верификации." << endl;
					system("pause");
					return;
				}

				UserSpis[i].Access = 1;

				cout << "Аккаунт с логином " << UserSpis[i].Login << " был верифицирован." << endl;
				FileExport(UserSpis);
				system("pause");
				return;
			}
		}

		cout << "Аккаунт с данным логином не был найден. Повторите попытку..." << endl;
		system("pause");
	}
}

void Ban(unsigned int action)
{
	system("cls");

	vector <UsersList> UserSpis;

	UserSpis = FileImport();

	switch (action)
	{
	case 1:
	{
		cout << "\nЕсли Вы хотите прервать процесс блокировки аккаунта, введите '-1'" << endl;
		while (true)
		{
			string TempLogin;
			cout << "Введите логин аккаунта для блокировки: ";
			cin >> TempLogin;

			if (TempLogin == "-1")
			{
				cout << "Вы вышли из меню блокировки аккаунтов" << endl;
				system("pause");
				return;
			}

			for (unsigned int i = 0; i < UserSpis.size(); i++)
			{
				if (UserSpis[i].Login == TempLogin)
				{
					UserSpis[i].Access = -1;
					UserSpis[i].Role = 1;
					cout << "Аккаунт с логином " << UserSpis[i].Login << " был заблокирован." << endl;
					FileExport(UserSpis);
					system("pause");
					return;
				}
			}

			cout << "Аккаунт с данным логином не был найден. Повторите попытку..." << endl;
			system("pause");
		}
	}
	case 2:
	{
		cout << "Список аккаунтов, находящихся в блокировке: " << endl;
		for (unsigned int i = 0; i < UserSpis.size(); i++)
		{
			if (UserSpis[i].Access == -1)
			{
				cout << UserSpis[i].Login << endl;
			}
		}

		cout << "\nЕсли Вы хотите прервать процесс разблокировки аккаунта, введите '-1'" << endl;
		cout << "\nЕсли Вы хотите разлокировать все аккаунты, введите '-2'" << endl;

		while (true)
		{
			string TempLogin;
			cout << "Введите логин аккаунта для разблокировки: ";
			cin >> TempLogin;

			if (TempLogin == "-1")
			{
				cout << "Вы вышли из меню верификации аккаунтов" << endl;
				system("pause");
				return;
			}

			if (TempLogin == "-2")
			{
				for (unsigned int i = 0; i < UserSpis.size(); i++)
				{
					if (UserSpis[i].Access == -1)
					{
						UserSpis[i].Access = 1;
					}
				}

				cout << "Все аккаунты были разблокированы." << endl;
				FileExport(UserSpis);
				system("pause");
				return;
			}

			for (unsigned int i = 0; i < UserSpis.size(); i++)
			{
				if (UserSpis[i].Login == TempLogin)
				{
					if (UserSpis[i].Access == 1)
					{
						cout << "Аккаунт с логином " << UserSpis[i].Login << " не находится в блокировке." << endl;
						system("pause");
						return;
					}

					UserSpis[i].Access = 1;

					cout << "Аккаунт с логином " << UserSpis[i].Login << " был разблокирован." << endl;
					FileExport(UserSpis);
					system("pause");
					return;
				}
			}

			cout << "Аккаунт с данным логином не был найден. Повторите попытку..." << endl;
			system("pause");
		}
	}
	}
}

void GiveAdmin()
{
	system("cls");

	vector <UsersList> UserSpis;

	UserSpis = FileImport();

	cout << "Если Вы хотите прервать процесс верификации аккаунта, введите '-1'" << endl;

	while (true)
	{
		string TempLogin;
		cout << "Введите логин аккаунта для выдачи админ-прав: ";
		cin >> TempLogin;

		if (TempLogin == "-1")
		{
			cout << "Вы вышли из меню выдачи админ-прав." << endl;
			system("pause");
			return;
		}

		for (unsigned int i = 0; i < UserSpis.size(); i++)
		{
			if (UserSpis[i].Login == TempLogin)
			{
				if (UserSpis[i].Role == 2 || UserSpis[i].Role == 3)
				{
					cout << "Аккаунт с логином " << UserSpis[i].Login << " уже является администратором." << endl;
					system("pause");
					return;
				}

				UserSpis[i].Access = 1;
				UserSpis[i].Role = 2;

				cout << "Аккаунту с логином " << UserSpis[i].Login << " были выданы админ-права." << endl;
				FileExport(UserSpis);
				system("pause");
				return;
			}
		}

		cout << "Аккаунт с данным логином не был найден. Повторите попытку..." << endl;
		system("pause");
	}
}
