#include "library.h"

enum Type_entity {
	Bird,
	Livestock,
	Human,
	None

};



template <typename T>

struct Entity {
private:
	int* _move_speed;
	Type_entity _type;
	string _color;
	T* _charac;

public:
	//constructors
	Entity() {
		this->_move_speed = nullptr;
		this->_type = Type_entity::None;
		this->_color = "no color";
		this->_charac = nullptr;
	}

	Entity(int move_speed): Entity() {
		set_move_speed(move_speed);
	}

	Entity(int move_speed, string color) : Entity(move_speed) {
		set_color(color);
	}

	Entity(int move_speed, string color, T charac) : Entity(move_speed, color) {
		set_charac(charac);

		if (typeid(get_charac()).name() == typeid(int).name()) {
			set_type(Type_entity::Human);
		}
		else if (typeid(get_charac()).name() == typeid(double).name()) {
			set_type(Type_entity::Bird);
		}
		else if (typeid(get_charac()).name() == typeid(bool).name()) {
			set_type(Type_entity::Livestock);
		}
		else {
			set_type(Type_entity::None);
		}
		
	}

	//destructor
	~Entity() {
		delete _move_speed;
		_move_speed = nullptr;
		delete _charac;
		_charac = nullptr;
	}

	//getters
	

	int get_move_speed() {
		return (this->_move_speed == nullptr) ? 0: *this->_move_speed;
	}

	Type_entity get_type() {
		return _type;
	}

	string get_color() {
		return (this->_color.empty()) ? "No color": this->_color;
	}

	T get_charac() {
		return (this->_charac == nullptr) ? 0: *this->_charac;
	}

	//setters
	void set_move_speed(int move_speed) {
		this->_move_speed = (this->_move_speed == nullptr) ? new int(move_speed) : &move_speed;
	}
	void set_type(Type_entity type) {
		_type = type;
	}
	void set_color(string color) {
		_color = color;
	}
	void set_charac(T charac) {
		this->_charac = (this->_charac == nullptr) ? new T(charac) : &charac;
	}

	//print	info
	void print_info() {
		cout << "Move speed: " << get_move_speed() << endl;
		
		

		switch (get_type())
		{
			case Bird: {
				cout << "Type: Bird" << endl;
				cout << "Color: " << get_color() << endl;
				cout << "Bird flight speed: " << get_charac() << endl;
				break;
			}


			case Livestock: {
				cout << "Type: Livestock" << endl;
				cout << "Color: " << get_color() << endl;
				string answer = (get_charac()) ? "yes" : "no";
				cout << "Livestock: " << answer << endl;
				break;
			}
			
			case Human: {
				cout << "Type: Human" << endl;
				cout << "Color: " << get_color() << endl;
				cout << "Human IQ: " << get_charac() << endl;
				break;
			}
			case None: {
				cout << "Type: None" << endl;
				cout << "Color: " << get_color() << endl;
				cout << "No character" << endl;
				break;
			}

		}
		
	}
	
};





