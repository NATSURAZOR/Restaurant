#include "4_Restaurant.h"
#include "const.h"

Restaurant::Restaurant(const string &name) : name(name){}

Restaurant::Restaurant(const string &nameR, const Tables& tablesR, const Menu& menu) : name(nameR), tables(tablesR),
                                                                                       menu(menu){}

Restaurant::Restaurant(const string &nameR, const Tables &tablesR) : name(nameR), tables(tablesR) {}

Restaurant::Restaurant(const string &nameR, const Menu &menu) : name(nameR), menu(menu){}

string Restaurant::getAllReservations() {
    ostringstream allReservations;

    for(auto &item : reservation){
        allReservations << "ID: " << item.first << ", Guest name: " << item.second.getGuestName()
        << ", reserved for: " << item.second.getCountOfGuest() << " on table number: " << item.second.getTableNumber()
        << "\n";
    }

    string strReservations = allReservations.str();
    return strReservations.substr(0, strReservations.size()-1);
}

string Restaurant::getReservationByName(const string &name) {
    string reservOnName;

    for (auto &item : reservation){
        if(item.second.getGuestName() == name){
            ostringstream res;
            res << "Reservation id: " << item.first << ", Table: " << item.second.getTableNumber()
            << ", count of guest: " << item.second.getCountOfGuest() << "\nOrdered dishes:\n"
            << item.second.getOrderedDishes();
            reservOnName += res.str();
        }
    }

    if (reservOnName.empty()){
        return "There no reservation on name: " + name;
    }

    return reservOnName;
}

string Restaurant::getResrvationByTableNumber(const int &tableNumber) {
    string reservOnName;

    for (auto &item : reservation){
        if(item.second.getTableNumber() == tableNumber){
            ostringstream res;
            res << "Reservation id: " << item.first << ", Table: " << item.second.getTableNumber()
                << ", count of guest: " << item.second.getCountOfGuest() << "\nOrdered dishes: \n"
                << item.second.getOrderedDishes();
            return res.str();
        }
    }

    return "There no reservation on Table number " + to_string(tableNumber);
}

bool Restaurant::changeRestaurantName(const string &name) {
    if(name.empty() || name == this->name){
        return false;
    }

    this->name = name;
    return true;
}

int Restaurant::addTablesR(Tables tablesR) {
    stringstream allTables(tablesR.getTables());
    string substr;
    int countOfAdded = 0;

    while (getline(allTables, substr, ',')){
        int number = atoi(substr.c_str());
        bool checkAds = tables.addOneTable(number, tablesR.numberOfSeatsAtTheTable(number));

        if (checkAds){
            countOfAdded++;
        }
    }

    return countOfAdded;
}


bool Restaurant::addTable(Table tableR) {
    if (tableR.getSeats() + tables.numberOfMaxGuests()  > 100 || tableR.getReservation()){
        return false;
    }

    tables.addOneTable(tableR);
    return true;
}

int Restaurant::addMenu(const Menu &menuR) {
    return menu.addFromAnotherMenu((Menu &&) menuR);
}

bool Restaurant::addDish(const Dish& dishR) {
    if (menu.inMenu(dishR.getName())){
        return false;
    }

    return true;
}

string Restaurant::createReservationOnFreeTable(const string &guestName, const int &countGuest) {
    string numberOfTable;
    string allTables = tables.getTables();

    if (allTables.empty()){
        return "There aren`t tables on restaurant";
    }

    for (int i = 0; i < allTables.size(); ++i){
        if(allTables[i] == ','){
            int number = atoi(numberOfTable.c_str());

            if (!tables.getReservationStatus(number)){
                break;
            }

            numberOfTable = "";
        }

        else {
            numberOfTable += allTables[i];
        }
    }

    int number = atoi(numberOfTable.c_str());

    if (!tables.getReservationStatus(number)) {
        Reservation res;

        if (res.addReservation(guestName, number, countGuest)) {
            auto it = reservation.emplace(reservation.size() + 1, res);
            tables.setReservation(number, true);
            return "Table: " + to_string(number) + " changed status to reserved";
        }

        return "Table: " + to_string(number) + " can`t be reserved check name or count of guest";
    }

    return "Reservation faild, there aren`t free tables";
}

string Restaurant::createReservation(const string &guestName, const int &countGuest, const int &tableNumber) {
    Guest nameG;

    if (!nameG.put(guestName) || !tables.inTables(tableNumber) || countGuest < 1 || countGuest > 6 ||
            tables.numberOfSeatsAtTheTable(tableNumber) < countGuest || tables.getReservationStatus(tableNumber)){
        return "Can`t create reservation on table: " + to_string(tableNumber);
    }

    Reservation res;
    bool checkAdd = res.addReservation(nameG, tableNumber, countGuest);

    if (checkAdd){
        reservation.emplace(reservation.size()+1, res);
        tables.setReservation(tableNumber, true);
        return "Table: " + to_string(tableNumber) + " changed status to reserved";
    }

    return "Can`t create reservation on table: " + to_string(tableNumber);
}

string Restaurant::addOrderToReservedTable(const string &guestName, const int &tableNumber, const string &dishes) {
    string orderForTable;
    string oneDish;
    stringstream allDishes(dishes);
    int price = 0;

    while (getline(allDishes, oneDish, ',')){
        if(menu.inMenu(oneDish)){
            orderForTable += menu.getDish(oneDish) + "\n";
            price += menu.getDishPrice(oneDish);
        }
    }

    if(!orderForTable.empty()){
        orderForTable = orderForTable.substr(0, orderForTable.size()-1);
    }

    for (auto &item : reservation){

        if (item.second.getTableNumber() == tableNumber && item.second.getGuestName() != guestName){
            return "We can`t edit your order, because tableNumber not reserved on this name";
        }

        if (item.second.getTableNumber() != tableNumber && item.second.getGuestName() == guestName){
            return "We can`t edit your order, because you aren`t reserved this table";
        }

        if (item.second.getTableNumber() == tableNumber && item.second.getGuestName() == guestName){
            item.second.addToOrderDishes(orderForTable);
            item.second.addOrderSum(price);
            return "For your order added: " + orderForTable + "\nfor sum: " + to_string(price) + " eur";
        }
    }

    return "We can`t edit your order, we can`t fint table nubmber and guest name";
}

string Restaurant::payForOrder(const string &guestName, const int &tableNumber) {
    for (auto &item : reservation){

        if (item.second.getTableNumber() == tableNumber && item.second.getGuestName() != guestName){
            return "We can`t edit your order, because tableNumber not reserved on this name";
        }

        if (item.second.getTableNumber() != tableNumber && item.second.getGuestName() == guestName){
            return "We can`t edit your order, because you aren`t reserved this table";
        }

        if (item.second.getTableNumber() == tableNumber && item.second.getGuestName() == guestName){
            string chek = "Your order:" + item.second.getOrderedDishes() + "\nThe sum of order is: " +
                            to_string(item.second.getCheck()) + "eur\nTHANKS\nSEE YOU NEXT TIME";
            restaurantEarnings += item.second.getCheck();
            item.second.removeDishes();
            tables.setReservation(item.second.getTableNumber(), false);
            removeReservation(guestName, tableNumber);
            return chek;
        }
    }

    return "We can`t edit your order, we can`t fint table nubmber and guest name";
}

bool Restaurant::removeTable(const int &tableNumber) {
    if(tables.getReservationStatus(tableNumber)){
        return false;
    }

    tables.removeTable(tableNumber);
    return true;
}

string Restaurant::removeAllTables() {
    stringstream allTables(tables.getTables());
    string substr;
    string cantDelete;

    while (getline(allTables, substr, ',')){
        bool tryDelete = removeTable(atoi(substr.c_str()));

        if (!tryDelete){

            if (cantDelete.size())
                cantDelete += ",";
            cantDelete += substr;
        }
    }

    return cantDelete;
}

bool Restaurant::removeDish(const string &dishName) {
    return menu.removeDish(dishName);
}

void Restaurant::removeMenu() {
    menu.eraseAllDishes();
}

bool Restaurant::removeReservation(const string &guestName, const int &tableNumber) {
    for (auto &item : reservation){

        if (item.second.getTableNumber() == tableNumber && item.second.getGuestName() == guestName){

            if(item.second.getCheck() == 0){
                reservation.erase(item.first);
                return true;
            }

            return false;
        }
    }

    return false;
}

string Restaurant::removeAllReservations() {
    string nonDeletetReserves;

    for(auto &item : reservation){
        if(!removeReservation(item.second.getGuestName(), item.second.getTableNumber())){
            nonDeletetReserves += to_string(item.first) + ",";
        }
    }

    if(nonDeletetReserves.empty()){
        return "SUCCES";
    }

    return nonDeletetReserves.substr(0, nonDeletetReserves.size()-1);
}

bool Restaurant::removeAll() {
    if (removeAllReservations() == "SUCCES"){
        removeAllTables();
        removeMenu();
        this->name = "NO Name";
        return true;
    }

    return false;
}