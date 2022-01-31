#include "3_Reservation.h"
#include "const.h"

bool checkSymbol(const char &symbol){
    if ((symbol < 'a' || symbol > 'z') && (symbol < 'A' || symbol > 'Z')){
        return false;
    }

    return true;
}

bool checkFormat(const string &text){
    string word1, word2;
    bool t = false;

    for (char i : text){

        if (i == ' ' && !word1.empty() && word2.empty()){
            t = true;
        }

        else if (i == ' ' && !word2.empty()){
            return false;
        }

        else if (i != ' ' && !t){
            if (!checkSymbol(i)){
                return false;
            }
            word1 += i;
        }

        else if (t){
            if (!checkSymbol(i)) {
                return false;
            }
            word2 += i;
        }
    }

    if (!word1.empty() && !word2.empty()){
        return true;
    }

    return false;
}

bool Guest::put(const string &named) {
    if (this->name == named || !checkFormat(named) || named.size() > 35){
        return false;
    }

    this->name = named;
    return true;
}

bool Reservation::addReservation(const string &name, const int &tableNumber, const int &countOfGuest) {
    Guest n;

    if (!n.put(name) || tableNumber < 1 || tableNumber > 99 || countOfGuest < 1 || countOfGuest > 6){
        return false;
    }

    this->name = n;
    this->countOfGuest = countOfGuest;
    this->tableNumber = tableNumber;
    return true;
}

bool Reservation::addReservation(Guest name, const int &tableNumber, const int &countOfGuest) {
    return this->addReservation(name.getGuestName(), tableNumber, countOfGuest);
}

string Reservation::addToOrderDishes(const string &dishes) {
    if(!this->orderedDishes.empty()){
        this->orderedDishes += "\n" + dishes;
        return this->orderedDishes;
    }

    this->orderedDishes += dishes;
    return this->orderedDishes;
}

int Reservation::changeCountOfGuest(const int &countOfGuest) {
    if (countOfGuest < 1 || countOfGuest > 6){
        return FAILD_INT;
    }

    this->countOfGuest = countOfGuest;
    return this->countOfGuest;
}

void Reservation::removeDishes() {
    orderedDishes = "";
    orderSum = 0;
}