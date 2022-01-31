#include <iostream>
#include <map>
#include <set>

using namespace std;

class Guest{
    string name;

public:
    // set
    bool put(const string &named);                                                                  // skontroluje ci meno sa sklada s formatu "Meno Priezvisko" ked na zaciatku alebo na konci su medzery tak odstrani ich

    // get
    string getGuestName() const { return name; };
};

class Reservation {
    Guest name;
    int tableNumber = 0;
    int countOfGuest = 0;                                                                           // pocet hosti
    int orderSum = 0;                                                                               // suma ktoru ma zaplatit stravu guest
    string orderedDishes;                                                                           // vypise jedla ktore boli objednane

public:

    // set
    bool addReservation(const string &name, const int &tableNumber, const int &countOfGuest);       // prida rezervaciu ked meno je dobre
    bool addReservation(Guest name, const int &tableNumber, const int &countOfGuest);               // prida rezervaciu
    string addToOrderDishes(const string &dishes);                                                  // prida ku objednavke dalsie jedlo
    void addOrderSum(const int &sum) { orderSum += sum; };                                          // zvacsi sumu objednavky
    int changeCountOfGuest(const int &countOfGuest);

    // get
    string getGuestName() { return name.getGuestName(); };
    int getTableNumber() const { return tableNumber; };
    int getCountOfGuest() const { return countOfGuest; };
    int getCheck() const { return orderSum; };
    string getOrderedDishes() const { return orderedDishes; };

    // remove
    void removeDishes();                                                                            // odstrani jedla a sumu
};

