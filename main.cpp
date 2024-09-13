#include "entity.h"


enum UserAction {
    exit_main = 0,
    updateItem,
    viewAllItems,
    findCharac,
};


void showAllEntities(void* entities[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << "Entity #" << i + 1 << endl;

        if (typeid(static_cast<Entity<double>*>(entities[i])->get_charac()).name() == typeid(double).name()) {
            static_cast<Entity<double>*>(entities[i])->print_info();
        }
        else if (typeid(static_cast<Entity<int>*>(entities[i])->get_charac()).name() == typeid(int).name()) {
            static_cast<Entity<int>*>(entities[i])->print_info();
        }
        else if (typeid(static_cast<Entity<bool>*>(entities[i])->get_charac()).name() == typeid(bool).name()) {
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

void editEntity(void* entities[], int size) {
    int index;
    do {
        std::cout << "Enter the index of the entity you want to edit: ";
        std::cin >> index;
    } while (index < 0 || index >= size);

    // Delete old entity
    if (typeid(*static_cast<Entity<int>*>(entities[index])) == typeid(Entity<int>)) {
        delete static_cast<Entity<int>*>(entities[index]);
    }
    else if (typeid(*static_cast<Entity<double>*>(entities[index])) == typeid(Entity<double>)) {
        delete static_cast<Entity<double>*>(entities[index]);
    }
    else if (typeid(*static_cast<Entity<bool>*>(entities[index])) == typeid(Entity<bool>)) {
        delete static_cast<Entity<bool>*>(entities[index]);
    }

    // Create new entity
    int move_speed;
    do {
        std::cout << "Enter move speed: ";
        std::cin >> move_speed;
    } while (move_speed < 0);

    std::string color;
    std::cin.ignore();
    std::cout << "Enter color: ";
    std::cin >> color;

    int num_type;
    do {
        std::cout << "Enter type of entity (1- bird, 2- livestock, 3- human): ";
        std::cin >> num_type;
    } while (num_type < 1 || num_type > 3);

    switch (num_type) {
    case 1: {
        double charac;
        std::cout << "Enter flight speed: ";
        std::cin >> charac;
        entities[index] = new Entity<double>(move_speed, color, charac);
    } break;

    case 2: {
        bool charac;
        std::cout << "Enter cloven-hoofed (true/false): ";
        std::cin >> charac;
        entities[index] = new Entity<bool>(move_speed, color, charac);
    } break;

    case 3: {
        int charac;
        std::cout << "Enter IQ level: ";
        std::cin >> charac;
        entities[index] = new Entity<int>(move_speed, color, charac);
    } break;

    default:
        std::cout << "Unknown entity type" << std::endl;
        break;
    }
}


int main() {
    const int size = 10;
    void* entities[size];

    entities[0] = new Entity<int>(4, "white", 100);
    entities[1] = new Entity<double>(5, "pink", 10.3);
    entities[2] = new Entity<bool>(4, "red", true);
    entities[3] = new Entity<int>(4, "black", 120);
    entities[4] = new Entity<bool>(5, "green", false);
    entities[5] = new Entity<double>(5, "pink", 10.3);
    entities[6] = new Entity<int>(4, "yellow", 130);
    entities[7] = new Entity<bool>(5, "purple", true);
    entities[8] = new Entity<double>(4, "orange", 10.3);
    entities[9] = new Entity<bool>(5, "brown", false);

    std::cout << "Our entities:" << std::endl;

    bool main_bool = true;
    do {
        system("cls");

        int action;
        do {
            std::cout << "Main menu:" << std::endl;
            std::cout << "0 - Exit" << std::endl;
            std::cout << "1 - Update(Edit) Item" << std::endl;
            std::cout << "2 - View All Items" << std::endl;
            std::cout << "3 - Find Entity With Characteristic" << std::endl;

            std::cout << "Enter your value: ";
            std::cin >> action;

        } while (action < 0 || action > 9);

        system("cls");
        switch (action) {
        case exit_main: {
            system("cls");
            main_bool = false;
        } break;

        case updateItem: {
			editEntity(entities, size);
            system("pause");
            system("cls");
            showAllEntities(entities, size);
            system("pause");
        } break;

        case viewAllItems: {
            showAllEntities(entities, size);
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
				std::cin.ignore();
				std::cout << "Enter characteristic: ";
				std::cin >> charac;
				find_by_charac<double>(entities, size, charac);
				system("pause");
			} break;
			case 2: {
				bool charac;
				std::cin.ignore();
				std::cout << "Enter characteristic: ";
				std::cin >> charac;
				find_by_charac<bool>(entities, size, charac);
				system("pause");
			} break;
            case 3: {
				int charac;
				std::cin.ignore();
				std::cout << "Enter characteristic: ";
				std::cin >> charac;
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
        if (typeid(*static_cast<Entity<int>*>(entities[i])) == typeid(Entity<int>)) {
            delete static_cast<Entity<int>*>(entities[i]);
        }
        else if (typeid(*static_cast<Entity<double>*>(entities[i])) == typeid(Entity<double>)) {
            delete static_cast<Entity<double>*>(entities[i]);
        }
        else if (typeid(*static_cast<Entity<bool>*>(entities[i])) == typeid(Entity<bool>)) {
            delete static_cast<Entity<bool>*>(entities[i]);
        }
    }

    system("pause");
    return 0;
}
