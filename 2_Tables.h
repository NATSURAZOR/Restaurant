#include <iostream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

class Table{
    int seats = 0;
    bool reserved = false;

public:
    // konstroktor
    Table() = default;
    Table(const int &seatsT);

    // set
    bool setSeats(const int &seatsT);
    bool setReservation(const bool  &statusOfReservation);

    // get
    int getSeats() const { return seats; };
    bool getReservation() const { return reserved; };
};

class Tables{
    map<int, Table> tables;                                                     // pole stolov, ktore 1) nomer stolu 2) pocet miest

public:
    // konstroktors
    Tables();
    Tables(const int &numberOfTables, const int &seats);                        // konstruktor pre konkretny pocet stolov a miest

    // set
    void createDefaultTablse ();                                                // urobi  25 stolov po 4 miesta a tym zaplny maximalny pocet ludi
    bool addOneTable(const int &seats);                                         // prida jeden stol, ked sa to podary vrati true, ked nie vrati false
    void addOneTable(Table table);
    bool addOneTable(const int &tableNumber, const int &seats);
    int addTables(const int &numberOfTables, const int &seats);                 // prida niekolko stolov, vrati pocet pridanych stolov
    bool setReservation(const int &numberOfTable, const bool &statusOfReservation);

    // get
    bool inTables(const int &numberOfTable);                                    // ked je stol s tym cislom tak vrati true ked nie vrati false
    int numberOfTables();                                                       // Vrati pocet stolov
    string getTables();                                                         // puste
    int numberOfSeatsAtTheTable (const int &numberOfTable);                     // Vrati pocet miestenok za danym stolom
    int numberOfMaxGuests ();                                                   // Vrati pocet toho kolko sa da vmestit ludi
    bool getReservationStatus(const int &numberOfTable);

    // remove
    bool removeTable(const int &numberOfTable);                                 // delete 1 stol
    void eraseAllTables(){tables.clear(); };                                    // delete vsetky stoly
};




