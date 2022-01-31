#include "2_Tables.h"
#include "const.h"
Table::Table(const int &seatsT) {
    if (seatsT > MAX_PEOPLE_ON_ONE_TABLE || seatsT < MIN_PEOPLE_ON_ONE_TABLE){
        return;
    }

    this->seats = seatsT;
}

bool Table::setSeats(const int &seatsT) {
    if (seatsT > MAX_PEOPLE_ON_ONE_TABLE || seatsT < MIN_PEOPLE_ON_ONE_TABLE){
        return false;
    }

    this->seats = seatsT;
    return true;
}

bool Table::setReservation(const bool &statusOfReservation) {
    if (statusOfReservation == this->reserved){
        return false;
    }

    this->reserved = statusOfReservation;
    return true;
}

Tables::Tables() = default;

Tables::Tables(const int &numberOfTables, const int &seats){
    addTables(numberOfTables, seats);
};

void Tables::createDefaultTablse (){
    eraseAllTables();
    addTables(25, 4);
}

bool Tables::addOneTable(const int &seats){
    if (seats > MAX_PEOPLE_ON_ONE_TABLE || this->numberOfMaxGuests() + seats > MAX_PEOPLE
        || seats < MIN_PEOPLE_ON_ONE_TABLE){
        return false;
    }

    Table table(seats);
    tables.emplace(this->numberOfTables()+1, table);
    return true;
}

void Tables::addOneTable(Table table) {
    if (table.getSeats() < 1 || table.getReservation()){
        return;
    }

    tables.emplace(this->numberOfTables()+1, table);
}

bool Tables::addOneTable(const int &tableNumber, const int &seats) {
    if (inTables(tableNumber)) {
        if (tables.find(tableNumber)->second.getSeats() == seats ||
            this->numberOfMaxGuests() - tables.find(tableNumber)->second.getSeats() + seats > MAX_PEOPLE
            || (inTables(tableNumber) && getReservationStatus(tableNumber))) {
            return false;
        }

        tables.find(tableNumber)->second.setSeats(seats);
        return true;
    }

    if (this->numberOfMaxGuests() + seats > MAX_PEOPLE){
        return false;
    }

    tables.emplace(tableNumber, seats);
    return true;
}

int Tables::addTables(const int &numberOfTables, const int &seats) {
    if (numberOfTables < 1 || seats < MIN_PEOPLE_ON_ONE_TABLE || seats > MAX_PEOPLE_ON_ONE_TABLE ){
        return FAILD_INT;
    }

    int countOfAdd = 0;
    int start = this->numberOfTables();
    int end = numberOfTables + this->numberOfTables();

    for (int i = start; i < end; ++i){
        bool control = addOneTable(seats);

        if (numberOfMaxGuests() + seats > MAX_PEOPLE){
            return FAILD_INT;
        }

        if (control){
            countOfAdd ++;
        }
    }

    return countOfAdd;
}

bool Tables::setReservation(const int &numberOfTable, const bool &statusOfReservation) {
    auto t = getTables();

    if (inTables(numberOfTable)){
        if (tables.find(numberOfTable)->second.getReservation() != statusOfReservation){
            tables.find(numberOfTable)->second.setReservation(statusOfReservation);
            return true;
        }
    }

    return false;
}

bool Tables::inTables(const int &numberOfTable) {
    if (tables.find(numberOfTable) != tables.end()){
        return true;
    }

    return false;
}

int Tables::numberOfTables() {
    return tables.size();
}

string Tables::getTables() {
    string tablesstr;

    for (auto &item : tables){
        tablesstr += to_string(item.first) + ",";
    }

    return tablesstr.substr(0, tablesstr.size()-1);
}

int Tables::numberOfSeatsAtTheTable (const int &numberOfTable){
    if (tables.find(numberOfTable) != tables.end()){
        auto it = tables.find(numberOfTable);
        return it->second.getSeats();
    }

    return FAILD_INT;
}

int Tables::numberOfMaxGuests (){
    int countOfGuests = 0;

    for (auto &item : tables){
        countOfGuests += item.second.getSeats();
    }

    return countOfGuests;
}

bool Tables::getReservationStatus(const int &numberOfTable) {
    if (inTables(numberOfTable)){
        return tables.find(numberOfTable)->second.getReservation();
    }

    return false;
}

bool Tables::removeTable(const int &numberOfTable){
    if (tables.find(numberOfTable) != tables.end()){
        tables.erase(numberOfTable);
        return true;
    }

    return false;
}

