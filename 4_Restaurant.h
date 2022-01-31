#include <iostream>
#include <map>
#include <set>

#include "2_Tables.h"
#include "1_Menu.h"
#include "3_Reservation.h"



using namespace std;

class Restaurant{
    string name;                                                                         // nazov restauracie
    Tables tables;                                                                       // vsetky stoly
    Menu menu;                                                                           // cele menu
    map<int, Reservation> reservation;                                                   // mapa reservacii, 1) id reservacie 2) class reservacii
    int restaurantEarnings = 0;                                                          // zarobok restauracie

public:
    // konstruktors
    Restaurant(const string &nameR = "No_Name");
    Restaurant(const string &nameR, const Tables& tablesR, const Menu& menu);
    Restaurant(const string &nameR, const Tables &tablesR);
    Restaurant(const string &nameR, const Menu &menu);

    // get
    string getAllReservations();                                                        // vrati vsetky reservacie: id reservace, table numbber, count of guest, objednavku, a sumu objednavky
    string getReservationByName(const string &name);                                    // vrati reservacie na toto meno, aj ked jeden clovek ma viac ako jeden stol tak vrati reservaciu na kazdom stole
    string getResrvationByTableNumber(const int &tableNumber);                          // vrti reservaciu na dany stol: meno, pocet hosti a objednavku
    string getTables() { return tables.getTables(); };                                  // vrati stoly: 1,2,3,4,20
    string getMenu() { return menu.getMenu(); };                                        // vrati menu: je mozne ze bude rozdele aj po typoch jedl, ako v zivote
    string getRestaurntName() { return name; };                                         // vrati meno restauracie
    int getRestaurantEarnings() const { return restaurantEarnings; };

    // set
    bool changeRestaurantName(const string &name);                                       // smeni meno a vrati true, ked zadane meno je prazdne alebo sa rovna terajsemu menu tak urobi nic a vrati false
    int addTablesR(Tables tablesR);                                                      // Prida stoly z hotoveho objektu stoly
    bool addTable(Table tableR);                                                         // prida stol
    int addMenu(const Menu &menuR);                                                      // prida menu do restauracie
    bool addDish(const Dish& dishR);                                                     // prida jedlo
    string createReservationOnFreeTable(const string &guestName, const int &countGuest);                    // urobi rezervaciu na volny stol, ked je volny stol a vrati stringom ci sa mu to podarilo ci nie
    string createReservation(const string &guestName, const int &countGuest, const int &tableNumber);       // skusi urobit rezervaciu na zadany stol, ked sa podari tak vypise to ked nie tak vypise ze sa nepodarila operacia
    string addOrderToReservedTable(const string &guestName, const int &tableNumber, const string &dishes);  // ked existuje rezervacia na meno a stol, tak prida k nemu jelda
    string payForOrder(const string &guestName, const int &tableNumber);                                    // ked existuje rezervacia na meno a stol, tak uvolni stol, a prida sumu ovjednavky ku restaurant earnings

    // remove
    bool removeTable(const int &tableNumber);                                             // skontroluje ci stol nie je rezervovany, ked je tak vrati false a urobi nic, ked nie je rezervovani tak odstrani stol
    string removeAllTables();                                                             // podobne ako remove table, lenze odstrani volne stoly a vypise tie ktore sa nepodarilo odstranit
    bool removeDish(const string &dishName);                                              // odstrani jedlo
    void removeMenu();                                                                    // odtrani Menu
    bool removeReservation(const string &guestName, const int &tableNumber);              // odstrani reservaciu iba v rom pripade ked tam nie je objednvka na jedlo
    string removeAllReservations();                                                       // robi to iste co aj remove reservation, a vrati ti reservacie ktore sa nedalo odstranit
    bool removeAll();                                                                     // odstrni vsetko
};

