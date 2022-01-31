#include <iostream>

#include "gtest/gtest.h"
#include "4_Restaurant.h"

using namespace ::testing;

TEST(TestRestaurant, konstruktor1){
    Restaurant restaurant;
    ASSERT_EQ("No_Name", restaurant.getRestaurntName());
    ASSERT_EQ("",restaurant.getTables());
    ASSERT_EQ("", restaurant.getMenu());
    ASSERT_EQ("", restaurant.getAllReservations());
}

TEST(TestRestaurant, konstruktor2){
    Tables tables(3, 4);
    Menu m;
    m.addDish("espresso", "COFFE", 1);
    m.addDish("capucino", "COFFE", 2);
    m.addDish("latte", "COFFE", 2);
    m.addDish("FISH", "FISH_FOOD", 8);
    m.addDish("FISH2", "FISH_FOOD", 12);
    m.addDish("quatro-Formagi", "PIZZA", 6);
    Restaurant restaurant("PIZZA BUNNY", tables, m);
    ASSERT_EQ("PIZZA BUNNY", restaurant.getRestaurntName());
    ASSERT_EQ("<FISH>:<FISH_FOOD>:<8>\n"
              "<FISH2>:<FISH_FOOD>:<12>\n"
              "<capucino>:<COFFE>:<2>\n"
              "<espresso>:<COFFE>:<1>\n"
              "<latte>:<COFFE>:<2>\n"
              "<quatro-Formagi>:<PIZZA>:<6>", restaurant.getMenu());
    ASSERT_EQ("1,2,3", restaurant.getTables());
}

TEST(TestRestaurant, konstruktor3AddReservation) {
    Tables tables(-3, 2);
    Restaurant restaurant("YukiFish", tables);
    ASSERT_EQ("YukiFish", restaurant.getRestaurntName());
    ASSERT_EQ("", restaurant.getTables());
    ASSERT_EQ("", restaurant.getMenu());
    restaurant.createReservationOnFreeTable("Laver Arnold", 5);
    ASSERT_EQ("", restaurant.getAllReservations());
    ASSERT_EQ("There no reservation on name: Laver Arnold", restaurant.getReservationByName("Laver Arnold"));
}

TEST(TestRestaurant, testTables){
    Table table(4);
    Table table1(6);
    Tables tables1(3, 4);
    Restaurant restaurant("YukiFish");
    restaurant.addTable(table);
    restaurant.addTablesR(tables1);
    ASSERT_EQ("1,2,3", restaurant.getTables());
    Tables tables2;
    tables2.addOneTable(5, 4);
    tables2.addOneTable(9, 2);
    restaurant.addTablesR(tables2);
    ASSERT_EQ("1,2,3,5,9", restaurant.getTables());
    restaurant.removeTable(3);
    restaurant.removeTable(5);
    ASSERT_EQ("1,2,9", restaurant.getTables());
    ASSERT_EQ("Table: 9 changed status to reserved",restaurant.createReservation("Marli Vanos", 2, 9));
    ASSERT_EQ( "Reservation id: 1, Table: 9, count of guest: 2\n"
               "Ordered dishes:\n",restaurant.getReservationByName("Marli Vanos"));
    ASSERT_EQ(false,restaurant.removeTable(9));
    ASSERT_EQ("9",restaurant.removeAllTables());
}

TEST(TestRestaurant, makeOrder){
    Tables tables;
    tables.createDefaultTablse();
    Menu m;
    m.addDish("espresso", "COFFE", 1);
    m.addDish("capucino", "COFFE", 2);
    m.addDish("latte", "COFFE", 2);
    m.addDish("Coke", "NOT_ALKOHOL", 2);
    m.addDish("FISHPizza", "PIZZA", 8);
    m.addDish("FISH2Pizza", "PIZZA", 12);
    m.addDish("quatro-Formagi", "PIZZA", 6);
    Restaurant restaurant("PIZZA BUNNY", tables, m);
    restaurant.createReservationOnFreeTable("Freddy Bear", 4);
    ASSERT_EQ("For your order added: <FISHPizza>:<PIZZA>:<8>\n"
              "<espresso>:<COFFE>:<1>\n"
              "<Coke>:<NOT_ALKOHOL>:<2>\n"
              "<quatro-Formagi>:<PIZZA>:<6>\n"
              "for sum: 17 eur",
              restaurant.addOrderToReservedTable("Freddy Bear", 1,
                                                 "FISHPizza,espresso,Coke,quatro-Formagi"));
    ASSERT_EQ("Your order:"
              "<FISHPizza>:<PIZZA>:<8>\n"
              "<espresso>:<COFFE>:<1>\n"
              "<Coke>:<NOT_ALKOHOL>:<2>\n"
              "<quatro-Formagi>:<PIZZA>:<6>\n"
              "The sum of order is: 17eur\n"
              "THANKS\n"
              "SEE YOU NEXT TIME",restaurant.payForOrder("Freddy Bear", 1));
    ASSERT_EQ(17, restaurant.getRestaurantEarnings());
}

TEST(TestRestaurant, createReservationInRestaurantWithoutTables){
    Restaurant restaurant;
    ASSERT_EQ("There aren`t tables on restaurant",restaurant.createReservationOnFreeTable("Arnold Dark", 5));
}

TEST(TestRestaurant, Orders){
    Tables tables;
    tables.createDefaultTablse();
    Menu m;
    m.addDish("espresso", "COFFE", 1);
    m.addDish("capucino", "COFFE", 2);
    m.addDish("latte", "COFFE", 2);
    m.addDish("Coke", "NOT_ALKOHOL", 2);
    m.addDish("FISHPizza", "PIZZA", 8);
    m.addDish("FISH2Pizza", "PIZZA", 12);
    m.addDish("quatro-Formagi", "PIZZA", 6);
    Restaurant restaurant("PIZZA BUNNY", tables, m);
    restaurant.createReservationOnFreeTable("Freddy Bear", 4);
    ASSERT_EQ("For your order added: <quatro-Formagi>:<PIZZA>:<6>\n"
              "for sum: 6 eur",
              restaurant.addOrderToReservedTable("Freddy Bear", 1,
                                                 "FISHP,eso,Ball,quatro-Formagi"));
    ASSERT_EQ("Reservation id: 1, Table: 1, count of guest: 4\n"
              "Ordered dishes:\n"
              "<quatro-Formagi>:<PIZZA>:<6>",
              restaurant.getReservationByName("Freddy Bear"));
    restaurant.addOrderToReservedTable("Freddy Bear", 1, "quatro-Formagi,quatro-Formagi,"
                                                         "coke,capucino");
    ASSERT_EQ("Reservation id: 1, Table: 1, count of guest: 4\n"
              "Ordered dishes:\n"
              "<quatro-Formagi>:<PIZZA>:<6>\n"
              "<quatro-Formagi>:<PIZZA>:<6>\n"
              "<quatro-Formagi>:<PIZZA>:<6>\n"
              "<capucino>:<COFFE>:<2>",
              restaurant.getReservationByName("Freddy Bear"));

    ASSERT_EQ(false, restaurant.removeAll());
    ASSERT_EQ("Your order:"
              "<quatro-Formagi>:<PIZZA>:<6>\n"
              "<quatro-Formagi>:<PIZZA>:<6>\n"
              "<quatro-Formagi>:<PIZZA>:<6>\n"
              "<capucino>:<COFFE>:<2>\n"
              "The sum of order is: 20eur\n"
              "THANKS\n"
              "SEE YOU NEXT TIME", restaurant.payForOrder("Freddy Bear", 1));
    ASSERT_EQ(true, restaurant.removeAll());
}
//TEST(TestRestaurant, ){}
// TEST(TestRestaurant, ){}
// TEST(TestRestaurant, ){}