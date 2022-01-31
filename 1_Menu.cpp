#include "1_Menu.h"
#include "const.h"
Dish::Dish(const string& named, const string &typed, const int &priced) {
    if (named.size() > MAX_SIZE_NAME || priced > MAX_PRICE || priced < 1 || named.empty() || typed.empty()){
        return;
    }

    for (auto &item : dishType){
        if (item == typed){
            this->name = named;
            this->type = typed;
            this->price = priced;
            return;
        }
    }
}

string Dish::getDish() {
    if (name.empty() || type.empty()){
        return EMTY_STRING;
    }

    ostringstream writeDish;
    writeDish << '<' << name << '>' << ':' << '<' << type << '>' << ':' << '<' << price << '>';
    return writeDish.str();
}

bool Dish::changeDish(const string &named, const string &typed, const int &priced) {
    if (named.size() > MAX_SIZE_NAME || price > MAX_PRICE || price < 1){
        return false;
    }
    if (this->name == named && this->type == typed && this->price == priced){
        return false;
    }
    this->name = named;
    this->type = typed;
    this->price = priced;
    return true;
}

bool Menu::addDish(const string &name, const string &type, const int &price) {
    if (dishes.find(name) != dishes.end()){
        bool tryChange = dishes.find(name)->second.changeDish(name,  type, price);
        return tryChange;
    }
    Dish dish(name, type, price);
    if (dish.getName().empty()){
        return false;
    }
    dishes.emplace(name, dish);
    return true;
}

int Menu::addFromAnotherMenu(Menu &&menu) {
    int countOfAddedDishes = 0;
    for (auto & dish : menu.dishes){
        if (!this->inMenu(dish.first)){
            this->addDish(dish.second.getName(), dish.second.getType(), dish.second.getPrice());
            countOfAddedDishes ++;
        }
    }

    menu.dishes.clear();
    return countOfAddedDishes;
}

bool Menu::addDish(const Dish &dish) {
    return this->addDish(dish.getName(), dish.getType(), dish.getPrice());
}

string Menu::getMenu() {
    string menu;

    for (auto &item : dishes){
        menu += item.second.getDish() + '\n';
    }

    if (menu.empty()){
        return "";
    }

    return menu.substr(0, menu.size()-1);
}

bool Menu::inMenu(const string &name) {
    if (dishes.find(name) != dishes.end()){
        return true;
    }

    return false;
}

string Menu::getDish(const string &name) {
    if (inMenu(name)){
        return dishes.find(name)->second.getDish();
    }

    return FAILD_STRING;
}

Menu Menu::getAllDishesWithType(const string &type) {
    Menu m;

    for (auto &item : this->dishes){
        if (item.second.getType() == type){
            m.addDish(item.second);
        }
    }

    return m;
}

int Menu::getDishPrice(const string &name) {
    if (inMenu(name)){
        return dishes.find(name)->second.getPrice();
    }

    return FAILD_INT;
}


bool Menu::removeDish(const string& dishName) {
    if (inMenu(dishName)){
        dishes.erase(dishName);
        return true;
    }

    return false;
}
