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
vector<Routes> RouteSortByRouteNumber(vector<Routes>);
vector<Routes> RouteSort(vector<Routes>);
void ShowAllRoutes();
void RouteFind();
void SellTickets();

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
			cout << "1. Поиск рейса" << endl;
			cout << "2. Просмотр всех рейсов" << endl;
			cout << "3. Смена пользователя" << endl;
			cout << "4. Выход из программы" << endl;

			char choise;
			cout << "\nВведите номер пункта меню: ";
			cin >> choise;

			switch (choise)
			{
			case '1':
			{
				RouteFind();
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
				cout << "Такого пункта меню не существует...\n Повторите ввод" << endl;
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
			cout << "1. Поиск рейса" << endl;
			cout << "2. Просмотр всех рейсов" << endl;
			cout << "3. Покупка билетов" << endl;
			cout << "4. Смена пользователя" << endl;
			cout << "5. Выход из программы" << endl;

			char choise;
			cout << "\nВведите номер пункта меню: ";
			cin >> choise;

			switch (choise)
			{
			case '1':
			{
				RouteFind();
				break;
			}
			case '2':
			{
				ShowAllRoutes();
				break;
			}
			case '3':
			{
				SellTickets();
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
				cout << "Такого пункта меню не существует...\n Повторите ввод" << endl;
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
			cout << "0. Админ-панель" << endl;
			cout << "1. Поиск рейса" << endl;
			cout << "2. Просмотр всех рейсов" << endl;
			cout << "3. Покупка билетов" << endl;
			cout << "4. Смена пользователя" << endl;
			cout << "5. Выход из программы" << endl;

			char choise;
			cout << "\nВведите номер пункта меню: ";
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
				RouteFind();
				break;
			}
			case '2':
			{
				ShowAllRoutes();
				break;
			}
			case '3':
			{
				SellTickets();
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
				cout << "Такого пункта меню не существует...\n Повторите ввод" << endl;
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
		cout << "0. Назначить администратора" << endl;
		cout << "1. Верификация аккаунта" << endl;
		cout << "2. Бан аккаунта" << endl;
		cout << "3. Разбан аккаунта" << endl;
		cout << "4. Меню маршрутов" << endl;
		cout << "5. Показать всех администраторов" << endl;
		cout << "6. Показать всех пользователей" << endl;
		cout << "7. Снять администратора" << endl;
		cout << "8. Удалить аккаунт" << endl;
		cout << "9. Вернуться в главное меню" << endl;

		char choise;
		cout << "\nВведите номер пункта меню: ";
		cin >> choise;

		switch (choise)
		{
		case '0':
		{
			if (Role == 3)
			{
				GiveAdmin(1);
			}
			else
			{
				cout << "Вы имеете недостаточный уровень администратора для доступа к данному разделу." << endl;
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
				cout << "Вы имеете недостаточный уровень администратора для доступа к данному разделу." << endl;
				system("pause");
			}
			break;
		}
		case '5':
		{
			ShowAdmins();
			break;
		}
		case '6':
		{
			ShowUsers();
			break;
		}
		case '7':
		{
			if (Role == 3)
			{
				GiveAdmin(2);
			}
			else
			{
				cout << "Вы имеете недостаточный уровень администратора для доступа к данному разделу." << endl;
				system("pause");
			}
			break;
		}
		case '8':
		{
			if (Role == 3)
			{
				DeleteAccount();
			}
			else
			{
				cout << "Вы имеете недостаточный уровень администратора для доступа к данному разделу." << endl;
				system("pause");
			}
			break;
		}
		case '9':
		{
			returning = true;
			break;
		}
		default:
		{
			cout << "Такого пункта меню не существует...\n Повторите ввод" << endl;
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
		cout << "1. Создать рейс" << endl;
		cout << "2. Удалить рейс" << endl;
		cout << "3. Редактировать рейс" << endl;
		cout << "4. Вернуться назад" << endl;

		char choise;
		cout << "\nВведите номер пункта меню: ";
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
			cout << "Такого пункта меню не существует...\n Повторите ввод" << endl;
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

	cout << "Если вы хотите прервать создание рейса, введите '-1'" << endl;

	cout << "Введите номер маршрута: ";
	cin >> temp.RouteNumber;
	if (temp.RouteNumber == "-1")
	{
		cout << "\nВы прервали процесс создания рейса." << endl;
		system("pause");
		return;
	}

	cout << "Введите тип автобуса: ";
	cin >> temp.BusType;
	if (temp.BusType == "-1")
	{
		cout << "\nВы прервали процесс создания рейса." << endl;
		system("pause");
		return;
	}

	cout << "Введите пункт назначения: ";
	cin >> temp.Destination;
	if (temp.Destination == "-1")
	{
		cout << "\nВы прервали процесс создания рейса." << endl;
		system("pause");
		return;
	}

	cout << "Введите дату отправления (в формате DD.MM.YYYY): ";
	cin >> temp.Date;
	if (temp.Date == "-1")
	{
		cout << "\nВы прервали процесс создания рейса." << endl;
		system("pause");
		return;
	}

	cout << "Введите время отправления (в формате HH:MM): ";
	cin >> temp.DepTime;
	if (temp.DepTime == "-1")
	{
		cout << "\nВы прервали процесс создания рейса." << endl;
		system("pause");
		return;
	}

	cout << "Введите время прибытия (в формате HH:MM): ";
	cin >> temp.ArrTime;
	if (temp.ArrTime == "-1")
	{
		cout << "\nВы прервали процесс создания рейса." << endl;
		system("pause");
		return;
	}

	cout << "Введите цену одного места: ";
	cin >> temp.Price;
	if (temp.Price == -1)
	{
		cout << "\nВы прервали процесс создания рейса." << endl;
		system("pause");
		return;
	}

	cout << "Введите количество билетов для реализации: ";
	cin >> temp.TicketsLeft;
	
	temp.TicketsSold = 0;

	RouteSpis = RoutesImport();
	RouteSpis.push_back(temp);
	RouteSpis = RouteSort(RouteSpis);
	RoutesExport(RouteSpis);
}

void RouteDelete()
{
	system("cls");

	vector<Routes> RoutesList;
	RoutesList = RoutesImport();

	cout << "Вы попали в меню удаления маршрутов" << endl;
	cout << "Если вы хотите прервать операцию удаления, введите '-1'" << endl;
	
	string TRouteNumber;
	cout << "Введите номер маршрута: ";
	cin >> TRouteNumber;
	if (TRouteNumber == "-1")
	{
		cout << "Вы прервали процесс удаления маршрута" << endl;
		system("pause");
		return;
	}
	else
	{
		int kol = -1;
		for (unsigned int i = 0; i < RoutesList.size(); i++)
		{
			if (RoutesList[i].RouteNumber == TRouteNumber)
			{
				kol++;
			}
		}

		if (kol == -1)
		{
			cout << "Такого маршрута не существует." << endl;
			system("pause");
			return;
		}
		if (kol == 0)
		{
			for (unsigned int i = 0; i < RoutesList.size(); i++)
			{
				if (RoutesList[i].RouteNumber == TRouteNumber)
				{
					kol = i;
					break;
				}
			}

			cout << "Введите 1, если вы действительно хотите удалить этот маршрут: ";
			cin >> TRouteNumber;
			if (TRouteNumber == "1")
			{
				RoutesList.erase(RoutesList.begin() + kol);
				RoutesExport(RoutesList);
				cout << "Маршрут успешно удалён." << endl;
				system("pause");
				return;
			}
			else
			{
				cout << "Вы прервали процесс удаления маршрута" << endl;
				system("pause");
				return;
			}
		}
	}

	string TDate;
	cout << "Введите дату отправления: ";
	cin >> TDate;
	if (TDate == "-1")
	{
		cout << "Вы прервали процесс удаления маршрута" << endl;
		system("pause");
		return;
	}
	else
	{
		int kol = -1;
		for (unsigned int i = 0; i < RoutesList.size(); i++)
		{
			if ((RoutesList[i].RouteNumber == TRouteNumber) && (RoutesList[i].Date == TDate))
			{
				kol++;
			}
		}

		if (kol == -1)
		{
			cout << "Такого маршрута не существует." << endl;
			system("pause");
			return;
		}
		if (kol == 0)
		{
			for (unsigned int i = 0; i < RoutesList.size(); i++)
			{
				if ((RoutesList[i].RouteNumber == TRouteNumber) && (RoutesList[i].Date == TDate))
				{
					kol = i;
					break;
				}
			}

			cout << "Введите 1, если вы действительно хотите удалить этот маршрут: ";
			cin >> TDate;
			if (TDate == "1")
			{
				RoutesList.erase(RoutesList.begin() + kol);
				RoutesExport(RoutesList);
				cout << "Маршрут успешно удалён." << endl;
				system("pause");
				return;
			}
			else
			{
				cout << "Вы прервали процесс удаления маршрута" << endl;
				system("pause");
				return;
			}
		}
	}

	string TDepTime;
	cout << "Введите время отправления: ";
	cin >> TDepTime;
	if (TDepTime == "-1")
	{
		cout << "Вы прервали процесс удаления маршрута" << endl;
		system("pause");
		return;
	}
	else
	{
		int kol = -1;
		for (unsigned int i = 0; i < RoutesList.size(); i++)
		{
			if ((RoutesList[i].RouteNumber == TRouteNumber) && (RoutesList[i].Date == TDate) && (RoutesList[i].DepTime == TDepTime))
			{
				kol++;
			}
		}

		if (kol == -1)
		{
			cout << "Такого маршрута не существует." << endl;
			system("pause");
			return;
		}
		if (kol == 0)
		{
			for (unsigned int i = 0; i < RoutesList.size(); i++)
			{
				if ((RoutesList[i].RouteNumber == TRouteNumber) && (RoutesList[i].Date == TDate) && (RoutesList[i].DepTime == TDepTime))
				{
					kol = i;
					break;
				}
			}

			cout << "Введите 1, если вы действительно хотите удалить этот маршрут: ";
			cin >> TDepTime;
			if (TDepTime == "1")
			{
				RoutesList.erase(RoutesList.begin() + kol);
				RoutesExport(RoutesList);
				cout << "Маршрут успешно удалён." << endl;
				system("pause");
				return;
			}
			else
			{
				cout << "Вы прервали процесс удаления маршрута" << endl;
				system("pause");
				return;
			}
		}
	}
}

void ShowAllRoutes()
{
	while (true)
	{
		bool returning = false;
		system("cls");
		cout << "1. Сортировка по времени отправления" << endl;
		cout << "2. Сортировка по пункту назначения" << endl;
		cout << "3. Сортировка по номеру маршрута" << endl;
		cout << "4. Вернуться назад" << endl;

		char choise;
		cout << "\nВведите номер пункта меню: ";
		cin >> choise;

		switch (choise)
		{
		case '1':
		{
			system("cls");
			vector<Routes> RouteSpis;
			RouteSpis = RoutesImport();
			RouteSpis = RouteSortByTime(RouteSpis);
			
			cout << "№Марш.\tТип Т/С\tПункт назначения\tДата\tОтпр.\tПриб.\tЦена\tСвоб.\tПрод." << endl;
			cout << "=========================================================================" << endl;
			for (unsigned int i = 0; i < RouteSpis.size(); i++)
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

			cout << "№Марш.\tТип Т/С\tПункт назначения\tДата\tОтпр.\tПриб.\tЦена\tСвоб.\tПрод." << endl;
			cout << "=========================================================================" << endl;
			for (unsigned int i = 0; i < RouteSpis.size(); i++)
			{
				cout << RouteSpis[i].RouteNumber << "\t" << RouteSpis[i].BusType << "\t" << RouteSpis[i].Destination << "\t\t" << RouteSpis[i].Date << "\t" << RouteSpis[i].DepTime << "\t" << RouteSpis[i].ArrTime << "\t" << RouteSpis[i].Price << "\t" << RouteSpis[i].TicketsLeft << "\t" << RouteSpis[i].TicketsSold << endl;
			}
			cout << endl;
			system("pause");
			break;
		}
		case '3':
		{
			system("cls");
			vector<Routes> RouteSpis;
			RouteSpis = RoutesImport();
			RouteSpis = RouteSortByRouteNumber(RouteSpis);

			cout << "№Марш.\tТип Т/С\tПункт назначения\tДата\tОтпр.\tПриб.\tЦена\tСвоб.\tПрод." << endl;
			cout << "=========================================================================" << endl;
			for (unsigned int i = 0; i < RouteSpis.size(); i++)
			{
				cout << RouteSpis[i].RouteNumber << "\t" << RouteSpis[i].BusType << "\t" << RouteSpis[i].Destination << "\t\t" << RouteSpis[i].Date << "\t" << RouteSpis[i].DepTime << "\t" << RouteSpis[i].ArrTime << "\t" << RouteSpis[i].Price << "\t" << RouteSpis[i].TicketsLeft << "\t" << RouteSpis[i].TicketsSold << endl;
			}
			cout << endl;
			system("pause");
			break;
		}
		case '4':
		{
			returning = true;
			break;
		}
		default:
		{
			cout << "Такого пункта меню не существует...\n Повторите ввод" << endl;
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

void RouteFind()
{
	system("cls");

	vector<Routes> RoutesList;
	RoutesList = RoutesImport();
	RoutesList = RouteSort(RoutesList);

	string TDestination;
	cout << "Введите пункт назначения: ";
	cin >> TDestination;
	int kol = 0;
	for (unsigned int i = 0; i < RoutesList.size(); i++)
	{
		if (RoutesList[i].Destination == TDestination)
		{
			kol++;
		}
	}

	if (kol == 0)
	{
		cout << "Такого маршрута не существует." << endl;
		system("pause");
		return;
	}

	string TDate;
	cout << "Введите дату отправления: ";
	cin >> TDate;

	kol = 0;
	for (unsigned int i = 0; i < RoutesList.size(); i++)
	{
		if ((RoutesList[i].Destination == TDestination) && (RoutesList[i].Date == TDate))
		{
			kol++;
		}
	}
	if (kol == 0)
	{
		cout << "В этот день нет рейсов в заданный пункт назначения." << endl;
		system("pause");
		return;
	}
	else
	{
		system("cls");
		cout << "№Марш.\tТип Т/С\tПункт назначения\tДата\tОтпр.\tПриб.\tЦена\tСвоб.\tПрод." << endl;
		cout << "=========================================================================" << endl;
		for (unsigned int i = 0; i < RoutesList.size(); i++)
		{
			if ((RoutesList[i].Destination == TDestination) && (RoutesList[i].Date == TDate))
			{
				cout << RoutesList[i].RouteNumber << "\t" << RoutesList[i].BusType << "\t" << RoutesList[i].Destination << "\t\t" << RoutesList[i].Date << "\t" << RoutesList[i].DepTime << "\t" << RoutesList[i].ArrTime << "\t" << RoutesList[i].Price << "\t" << RoutesList[i].TicketsLeft << "\t" << RoutesList[i].TicketsSold << endl;
			}
		}
		cout << endl;
		system("pause");
		return;
	}
}

void SellTickets()
{
	system("cls");

	vector<Routes> RoutesList;
	RoutesList = RoutesImport();
	RoutesList = RouteSort(RoutesList);

	string TDestination;
	cout << "Введите пункт назначения: ";
	cin >> TDestination;
	int kol = 0;
	for (unsigned int i = 0; i < RoutesList.size(); i++)
	{
		if (RoutesList[i].Destination == TDestination)
		{
			kol++;
		}
	}

	if (kol == 0)
	{
		cout << "Такого маршрута не существует." << endl;
		system("pause");
		return;
	}

	string TDate;
	cout << "Введите дату отправления: ";
	cin >> TDate;

	kol = 0;
	for (unsigned int i = 0; i < RoutesList.size(); i++)
	{
		if ((RoutesList[i].Destination == TDestination) && (RoutesList[i].Date == TDate))
		{
			kol++;
		}
	}
	if (kol == 0)
	{
		cout << "В этот день нет рейсов в заданный пункт назначения." << endl;
		system("pause");
		return;
	}
	else
	{
		int ind = 0, chosen = 0;
		system("cls");
		cout << "П/п№\t№Марш.\tТип Т/С\tПункт назначения\tДата\tОтпр.\tПриб.\tЦена\tСвоб.\tПрод." << endl;
		cout << "=========================================================================" << endl;
		for (unsigned int i = 0; i < RoutesList.size(); i++)
		{
			if ((RoutesList[i].Destination == TDestination) && (RoutesList[i].Date == TDate))
			{
				cout << ind << "\t" << RoutesList[i].RouteNumber << "\t" << RoutesList[i].BusType << "\t" << RoutesList[i].Destination << "\t\t" << RoutesList[i].Date << "\t" << RoutesList[i].DepTime << "\t" << RoutesList[i].ArrTime << "\t" << RoutesList[i].Price << "\t" << RoutesList[i].TicketsLeft << "\t" << RoutesList[i].TicketsSold << endl;
				ind++;
			}
		}
		cout << endl;
		
		cout << "Введите порядковый номер рейса, на который вы хотите приобрести билет: ";
		cin >> chosen;

		system("cls");

		if ((chosen >= ind) or (chosen < 0))
		{
			cout << "Вы ввели неправильный порядковый номер." << endl;
			system("pause");
			return;
		}
		
		ind = -1;
		for (unsigned int i = 0; i < RoutesList.size(); i++)
		{
			if ((RoutesList[i].Destination == TDestination) && (RoutesList[i].Date == TDate) && (ind + 1 == chosen))
			{
				int kolplace;
				cout << "Доступно для покупки " << RoutesList[i].TicketsLeft << " мест." << endl;
				
				while (true)
				{
					cout << "Введите количество мест для покупки: ";
					cin >> kolplace;
					if (kolplace == 0)
					{
						cout << "Вы прервали процесс покупки билета." << endl;
						system("pause");
						return;
					}

					if ((kolplace < 0) || ((unsigned int)kolplace > RoutesList[i].TicketsLeft))
					{
						cout << "Вы ввели неверное количество. Повторите попытку." << endl;
						system("pause");
						continue;
					}

					break;
				}

				RoutesList[i].TicketsLeft -= kolplace;
				RoutesList[i].TicketsSold += kolplace;
				RoutesExport(RoutesList);
				fstream TicketFile("ticket.txt", ios::out | ios::trunc);

				for (int j = 0; j < kolplace; j++)
				{
					TicketFile << "Филиал Витебскоблавтотранс" << endl;
					TicketFile << "Автовокзал г.Новополоцка" << endl;
					TicketFile << "--------------------------" << endl;
					TicketFile << "Номер маршрута: " << RoutesList[i].RouteNumber << endl;
					TicketFile << "Пункт назначения: " << RoutesList[i].Destination << endl;
					TicketFile << "Тип автобуса: " << RoutesList[i].BusType << endl;
					TicketFile << "Дата отправления: " << RoutesList[i].Date << endl;
					TicketFile << "Время отправления: " << RoutesList[i].DepTime << endl;
					TicketFile << "Время прибытия: " << RoutesList[i].ArrTime << endl;
					TicketFile << "Цена билета: " << RoutesList[i].Price << endl;
					TicketFile << "--------------------------" << endl;
					TicketFile << "Перевозчик: АТП №6 г.Новополоцка" << endl;
					TicketFile << "==========================" << endl;
				}

				TicketFile.close();
				cout << "Билет(ы) успешно приобретены" << endl;
				system("pause");
			}

			if ((RoutesList[i].Destination == TDestination) && (RoutesList[i].Date == TDate))
			{
				ind++;
			}
		}
	}
}

vector<Routes> RouteSortByTime(vector<Routes> temp)
{
	//sort by Date
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		for (unsigned int j = 1; j < temp.size(); j++)
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
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		for (unsigned int j = 1; j < temp.size(); j++)
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

vector<Routes> RouteSortByRouteNumber(vector<Routes> temp)
{
	//sort by RouteNumber
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		for (unsigned int j = 1; j < temp.size(); j++)
		{
			if (temp[j].RouteNumber != temp[j].RouteNumber)
			{
				string s1 = "", s2 = "";

				for (int k = temp[j].RouteNumber.length(); k >= 0; k--)
				{
					s1 += temp[j].RouteNumber[k];
				}

				for (int k = temp[j-1].RouteNumber.length(); k >= 0; k--)
				{
					s1 += temp[j-1].RouteNumber[k];
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
	
	//sort by Destination
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		for (unsigned int j = 1; j < temp.size(); j++)
		{
			if ((temp[j].RouteNumber == temp[j].RouteNumber) && (temp[j].Destination < temp[j - 1].Destination))
			{
				Routes t;
				t = temp[j];
				temp[j] = temp[j - 1];
				temp[j - 1] = t;
			}
		}
	}

	//sort by Date
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		for (unsigned int j = 1; j < temp.size(); j++)
		{
			if ((temp[j].RouteNumber == temp[j].RouteNumber) && (temp[j].Destination == temp[j - 1].Destination) && (temp[j].Date != temp[j - 1].Date))
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
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		for (unsigned int j = 1; j < temp.size(); j++)
		{
			if ((temp[j].RouteNumber == temp[j].RouteNumber) && (temp[j].Destination == temp[j - 1].Destination) && (temp[j].Date == temp[j - 1].Date))
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
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		for (unsigned int j = 1; j < temp.size(); j++)
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
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		for (unsigned int j = 1; j < temp.size(); j++)
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
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		for (unsigned int j = 1; j < temp.size(); j++)
		{
			if ((temp[j].Destination == temp[j - 1].Destination) && (temp[j].Date == temp[j - 1].Date))
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
