#include <iostream>
#include <iomanip>
#include "lift.hpp"
#include <windows.h>
#include <locale.h>

using namespace std;

void clearScreen() {
	#ifdef _WIN32
		system("cls");
   	#endif
}

void printLiftState(const Lift& lift) {
	cout << "---------------------------------\n";
	cout << "           СТАН ЛIФТА          \n";
	cout << "---------------------------------\n";
	cout << " Загальний стан: " << lift.GetGeneralStateName() << "\n";
	cout << " Стан двигуна: " << lift.GetEngineStateName() << "\n";
	cout << " Стан дверчат: " << lift.GetDoorStateName() << "\n";
	cout << " Поточний поверх: " << lift.GetCurrentFloor() << "\n";
	cout << " Цiльовий поверх: " << lift.GetTargetFloor() << "\n";
	cout << fixed << setprecision(1);
	cout << " Навантаження: " << lift.GetCurrentLoad() << " кг\n";
	cout << "---------------------------------\n\n";
}

void printMenu() {
	cout << "         ПУЛЬТ КЕРУВАННЯ         \n";
	cout << "1. Старт виклику (на поверх)\n";
	cout << "2. Кiнець виклику (прибуття)\n";
	cout << "3. Завантаження кабiни (вказати вагу)\n";
	cout << "4. Запуск (з кабiни на поверх)\n";
	cout << "5. Стоп (прибуття)\n";
	cout << "0. Скинути стан (Reset)\n";
	cout << "q. Вихiд\n\n";
	cout << "Ваш вибiр: ";
}

int main() {
	setlocale(LC_ALL, "Ukrainian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Lift myLift;
	char choice;

	do {
		clearScreen();
		printLiftState(myLift);
		printMenu();

		cin >> choice;

		int floor;
		double load;

		switch (choice) {
			case '1':
				cout << "Введiть цiльовий поверх (1-24): ";
				cin >> floor;
				myLift.StartCall(floor);
				break;
			case '2':
				myLift.EndCall();
				break;
			case '3':
				cout << "Введiть навантаження (кг): ";
				cin >> load;
				myLift.LoadCabin(load);
				break;
			case '4':
				cout << "Введiть цiльовий поверх (1-24): ";
				cin >> floor;
				try {
					myLift.Start(floor);
				}
				catch (const OverloadException& e) {
					cout << "\n**************************************************\n";
					cout << e.what() << endl;
					cout << "Будь ласка, зменшiть вагу в кабiнi (опцiя 3)." << endl;
					cout << "**************************************************\n";
                    cout << "Натиснiть Enter для продовження...";
					cin.clear();
					cin.ignore(10000, '\n');
					cin.get();
				}
				catch (...) {
					cout << "Виникла невiдома помилка!" << endl;
				}
				break;

			case '5':
				myLift.Stop();
				break;
			case '0':
				myLift.Reset();
				break;
			case 'q':
			case 'Q':
				cout << "Завершення роботи.\n";
				break;
			default:
				cout << "Некоректний вибiр. Натиснiть Enter.\n";
				cin.clear();
				cin.ignore(10000, '\n');
				cin.get();
				break;
		}

	} while (choice != 'q' && choice != 'Q');

	cout << "\nНатиснiть Enter для того щоб вийти" << endl;
	cin.clear();
	cin.ignore(10000, '\n');
	cin.get();

	return 0;
}
