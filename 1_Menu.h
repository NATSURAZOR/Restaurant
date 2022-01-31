#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>



using namespace std;

class Dish{
    string name;
    string type = "EMPTY";
    int price = 0;

public:
    // konstruktor
    Dish() = default;
    Dish(const string& named, const string &typed, const int &priced);

    // set
    bool changeDish(const string &named, const string &type, const int &price);

    // get
    string getName() const {return name; };
    string getType() const {return type; };
    int getPrice() const {return price; };
    string getDish();                                                              // vrati vo formate <name> : <type> : <price>
};

class Menu {
    map<string, Dish> dishes;                                                      // pole map z jedlami kde 1) nazov jedla 2) object classa dish


public:
    // set
    bool addDish (const string &name, const string &type, const int &price);
    int addFromAnotherMenu(Menu &&menu);                                           // tie ktore ne pozna prida other menu delete a vrati pocet pridanych
    bool addDish(const Dish &dish);

    // get
    string getMenu();
    bool inMenu(const string &name);
    string getDish(const string &name);
    int getDishPrice(const string &name);
    Menu getAllDishesWithType(const string &type);                             // vrati class menu v ktorom su iba jedla jedneho typu

    // remove
    bool removeDish(const string& dishName);
    void eraseAllDishes() {dishes.clear(); };
};


