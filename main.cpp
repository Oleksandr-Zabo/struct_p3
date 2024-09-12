#include <iostream>
#include <string>
using namespace std;

enum UserAction
{
	exit_main = 0,
	updateItem,
	viewAllItems,
	findCarNumber

};

struct Car {
private:
	string _color;
	string _model;
	int* _number;

public:
	Car() {
		_color = "no-model";
		_model = "no-model";
		_number = nullptr;
	}
	Car(string color) : Car() {
		setColor(color);
	}
	Car(string color, string model) : Car(color) {
		setModel(model);
	}
	Car(string color, string model, int number) : Car(color, model) {
		setNumber(number);
	}

	//del number
	void del_num() {
		delete _number;
		_number = nullptr;
	}


	//print info
	void printInfo() {
		cout << "Color: " << getColor() << endl;
		cout << "Model: " << getModel() << endl;
		cout << "Number: " << getNumber() << endl;
	}

	//setters
	void setColor(string color) {
		this->_color = color;
	}
	void setModel(string model) {
		this->_model = model;
	}
	void setNumber(int number) {
		if (_number == nullptr) {
			_number = new int(number);
		}
		else {
			*_number = number;
		}
	}

	//getters
	string getColor() {
		return _color;
	}
	string getModel() {
		return _model;
	}

	int getNumber() {
		return (_number == nullptr) ? 10000 : *_number;
	}
};


struct User
{
private:
	Car* cars = nullptr;
	int allocated_memory = 10;
	int size = 0;

public:
	//Constructors and destructors
	User()
	{
		cars = new Car[allocated_memory];
	}

	~User()
	{
		for (int i = 0; i < size; i++) {
			cars[i].del_num();
			
		}
		delete[] cars;
		allocated_memory = 10;
	}



	//push back
	void push_back(Car car) {

		cars[size] = car;
		size++;
	};

	//push by index
	void push_by_index(int index, Car car) {
		if (index < 0 || index >= size) {
			cout << "Index out of range" << endl;
			return;
		}
		for (int i = size; i > index; i--) {
			cars[i] = cars[i - 1];
		}
		cars[index] = car;
		size++;
	};

	//remove by index
	void remove_by_index(int index) {
		if (index < 0 || index >= size) {
			cout << "Index out of range" << endl;
			return;
		}
		for (int i = index; i < size - 1; i++) {
			cars[i] = cars[i + 1];
		}
		size--;
	};

	//print
	void print_all_items() {
		for (int i = 0; i < size; i++) {
			cout << "Car number: " << i + 1 << endl;
			cars[i].printInfo();
		}
	};

	//find number
	void find_number(int number) {
		bool is_found = false;
		for (int i = 0; i < size; i++) {
			if (cars[i].getNumber() == number) {
				cout << "Car number: " << i + 1 << endl;
				cars[i].printInfo();
				is_found = true;
			}
		}
		if (!is_found) {
			cout << "Car not found" << endl;
		}
	};

	//edit car
	void edit_car(int number, string color, string model, int car_number) {
		for (int i = 0; i < size; i++) {
			if (cars[i].getNumber() == number) {
				if (color != "") {
					cars[i].setColor(color);
				}
				if (model != "") {
					cars[i].setModel(model);
				}
				if (car_number != 0) {
					cars[i].setNumber(car_number);
				}
			}
		}
	};

};


int main()
{
	User* user = new User();

	//create start cars
	Car car1("red", "bmw", 12345);
	Car car2("yellow", "audi", 54321);
	Car car3("green", "mercedes", 67890);
	Car car4("blue", "volvo", 98765);
	Car car5("black", "toyota", 45678);
	Car car6("white", "nissan", 34567);
	Car car7("orange", "mazda", 23456);
	Car car8("purple", "honda", 15345);
	Car car9("pink", "ford", 18765);
	Car car10("brown", "chevrolet", 19876);

	//push cars to user
	user->push_back(car1);
	user->push_back(car2);
	user->push_back(car3);
	user->push_back(car4);
	user->push_back(car5);
	user->push_back(car6);
	user->push_back(car7);
	user->push_back(car8);
	user->push_back(car9);
	user->push_back(car10);

	//show user cars
	cout << "All cars: " << endl;
	user->print_all_items();
	system("pause");

	bool main_bool = true;
	do
	{
		system("cls");

		int action;
		do
		{
			cout << "Main menu:" << endl;
			cout << "0 - Exit" << endl;
			cout << "1 - Edit car" << endl;
			cout << "2 - View All Items" << endl;
			cout << "3 - Search for a car by number" << endl;

			cout << "Enter your value: ";
			cin >> action;

		} while (action < 0 || action > 3);

		system("cls");
		switch (action)
		{
		case exit_main:
		{
			system("cls");
			main_bool = false;
		}break;

		case updateItem:
		{
			int index;

			do
			{
				cout << "Enter index of car to update (from 1-10): ";
				cin >> index;
			} while (index < 0 || index > 10);
			index--;
			user->remove_by_index(index);

			Car car;

			string color;
			cin.ignore();
			cout << "Enter car color: ";
			cin >> color;
			car.setColor(color);

			string model;
			cout << "Enter car model: ";
			cin >> model;
			car.setModel(model);

			int number;
			cout << "Enter car number: ";
			cin >> number;
			car.setNumber(number);

			user->push_by_index(index, car);

			system("pause");

			system("cls");
			user->print_all_items();
			system("pause");

		}break;


		case viewAllItems:
		{
			user->print_all_items();
			system("pause");
		}break;

		case findCarNumber:
		{
			int number;
			cout << "Enter car number: ";
			cin >> number;
			user->find_number(number);
			system("pause");
		}break;

		}
	} while (main_bool);

	delete user; // Delete the user object

	system("pause");
	return 0;
}