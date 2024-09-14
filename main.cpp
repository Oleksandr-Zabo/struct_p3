#include "entity.h"


enum UserAction {
    exit_main = 0,
    updateItem,
    viewAllItems,
    findCharac,
};


void showAllEntities(void* entities[], int size, Type_entity* types[]) {
    for (int i = 0; i < size; ++i) {
        cout << "Entity #" << i + 1 << endl;

        if (*types[i] == Type_entity::Bird) {
            static_cast<Entity<double>*>(entities[i])->print_info();
        }
        else if (*types[i] == Type_entity::Human) {
			static_cast<Entity<int>*>(entities[i])->print_info();
		}
		else if (*types[i] == Type_entity::Livestock) {
			static_cast<Entity<bool>*>(entities[i])->print_info();
        }
        else {
            cout << "Unknown entity type" << std::endl;
        }

        cout << endl;
    }
}



template <typename T>

void find_by_charac(void* entities[], int size, T charac) {
	for (int i = 0; i < size; ++i) {
		if (typeid(*static_cast<Entity<T>*>(entities[i])) == typeid(Entity<T>)) {
			if (static_cast<Entity<T>*>(entities[i])->get_charac() == charac) {
				cout << "Entity #" << i + 1 << endl;
				static_cast<Entity<T>*>(entities[i])->print_info();
				cout << endl;
			}
		}
	}
}

void editEntity(void* entities[], int size, Type_entity* types[]) {
    int index;
    do {
        cout << "Enter the index of the entity you want to edit: ";
        cin >> index;
    } while (index < 0 || index >= size);

	//show old entity
	cout << "Old entity:" << endl;
    if (*types[index] == Type_entity::Bird) {
        static_cast<Entity<double>*>(entities[index])->print_info();
    }
    else if (*types[index] == Type_entity::Human) {
        static_cast<Entity<int>*>(entities[index])->print_info();
    }
    else if (*types[index] == Type_entity::Livestock) {
        static_cast<Entity<bool>*>(entities[index])->print_info();
    }
    else {
        cout << "Unknown entity type" << endl;
    }
	cout << endl;

    // Delete old entity
    if (*types[index] == Type_entity::Bird) {
        delete static_cast<Entity<double>*>(entities[index]);
    }
    else if (*types[index] == Type_entity::Human) {
        delete static_cast<Entity<int>*>(entities[index]);
    }
    else if (*types[index] == Type_entity::Livestock) {
        delete static_cast<Entity<bool>*>(entities[index]);
    }
	delete types[index];
    

    // Create new entity
    int move_speed;
    do {
        cout << "Enter move speed: ";
        cin >> move_speed;
    } while (move_speed < 0);

    string color;
    cin.ignore(); // Clear the newline character left in the buffer
    cout << "Enter color: ";
    getline(cin, color); // Use getline to read the entire line

    int num_type;
    do {
        cout << "Enter type of entity (1- bird, 2- livestock, 3- human): ";
        cin >> num_type;
    } while (num_type < 1 || num_type > 3);

    switch (num_type) {
    case 1: {
        double charac;
        do
        {
            cout << "Enter flight speed: ";
            cin >> charac;
        } while (charac < 0);
        entities[index] = new Entity<double>(move_speed, color, charac);
		types[index] = new Type_entity(Bird);

    } break;

    case 2: {
        bool charac;
        cout << "Enter cloven-hoofed (1 - true / 0 - false): ";
        cin >> charac; 
        entities[index] = new Entity<bool>(move_speed, color, charac);
		types[index] = new Type_entity(Livestock);
    } break;

    case 3: {
        int charac;
        do
        {
            cout << "Enter IQ level: ";
            cin >> charac;
        } while (charac < 0);
        entities[index] = new Entity<int>(move_speed, color, charac);
		types[index] = new Type_entity(Human);
    } break;

    default:
        cout << "Unknown entity type" << std::endl;
        break;
    }
}



int main() {
    const int size = 10;
    void* entities[size];
    Type_entity* types[size];//for correct work func showAllEntities
    

    entities[0] = new Entity<int>(4, "white", 100);
	types[0] = new Type_entity(Human);

    entities[1] = new Entity<double>(5, "pink", 10.3);
    types[1] = new Type_entity(Bird);

    entities[2] = new Entity<bool>(4, "red", true);
    types[2] = new Type_entity(Livestock);

    entities[3] = new Entity<int>(4, "black", 120);
    types[3] = new Type_entity(Human);

    entities[4] = new Entity<bool>(5, "green", false);
    types[4] = new Type_entity(Livestock);

    entities[5] = new Entity<double>(5, "pink", 10.3);
    types[5] = new Type_entity(Bird);

    entities[6] = new Entity<int>(4, "yellow", 130);
    types[6] = new Type_entity(Human);

    entities[7] = new Entity<bool>(5, "purple", true);
	types[7] = new Type_entity(Livestock);

    entities[8] = new Entity<double>(4, "orange", 10.3);
	types[8] = new Type_entity(Bird);

    entities[9] = new Entity<bool>(5, "brown", false);
	types[9] = new Type_entity(Livestock);

    std::cout << "Our entities:" << std::endl;
    showAllEntities(entities, size, types);
	system("pause");

    bool main_bool = true;
    do {
        system("cls");

        int action;
        do {
            cout << "Main menu:" << std::endl;
            cout << "0 - Exit" << std::endl;
            cout << "1 - Update(Edit) Item" << std::endl;
            cout << "2 - View All Items" << std::endl;
            cout << "3 - Find Entity With Characteristic" << std::endl;

            cout << "Enter your value: ";
            cin >> action;

        } while (action < 0 || action > 9);

        system("cls");
        switch (action) {
        case exit_main: {
            system("cls");
            main_bool = false;
        } break;

        case updateItem: {
			editEntity(entities, size, types);
            system("pause");
            system("cls");
            showAllEntities(entities, size, types);
            system("pause");
        } break;

        case viewAllItems: {
            showAllEntities(entities, size, types);
            system("pause");
        } break;

        case findCharac: {
            int num_type;
            do
            {
                cout << "Enter type of entity(1- bird, 2- livestock, 3- human): ";
                cin >> num_type;
            } while (num_type < 1 || num_type>3);

            switch (num_type)
            {
			case 1: {
				double charac;
                do
                {
                    cin.ignore();
                    cout << "Enter flight speed: ";
                    cin >> charac;
                } while (charac < 0);
				
				find_by_charac<double>(entities, size, charac);
				system("pause");
			} break;
			case 2: {
				bool charac;
				cin.ignore();
				cout << "Enter cloven-hoofed (true/false): ";
				cin >> charac;
				find_by_charac<bool>(entities, size, charac);
				system("pause");
			} break;
            case 3: {
				int charac;
                do
                {
                    cin.ignore();
                    cout << "Enter IQ level: ";
                    cin >> charac;
                } while (charac < 0);
				
				find_by_charac<int>(entities, size, charac);
				system("pause");
            }
            }
            system("pause");
        } break;

        system("pause");
        }
    } while (main_bool);

    // Clean up
    for (int i = 0; i < size; ++i) {
        if (*types[i] == Type_entity::Bird) {
            delete static_cast<Entity<double>*>(entities[i]);
        }
        else if (*types[i] == Type_entity::Human) {
            delete static_cast<Entity<int>*>(entities[i]);
        }
        else if (*types[i] == Type_entity::Livestock) {
            delete static_cast<Entity<bool>*>(entities[i]);
        }

		delete types[i];
    }

    system("pause");
    return 0;
}
