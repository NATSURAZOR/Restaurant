// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "1_Menu.h"

using namespace ::testing;

TEST(TestDish, createDish){
    Dish t("Paperoni", "PASTA", 5);
    ASSERT_EQ("PASTA", t.getType());
    ASSERT_EQ("Paperoni",t.getName());
    ASSERT_EQ(5, t.getPrice());
}

TEST(TestDish, badDish){
    Dish t("", "PASTA", 5);
    ASSERT_EQ("", t.getName());
    ASSERT_EQ("EMPTY", t.getType());
    ASSERT_EQ(0, t.getPrice());
    Dish m("Hawaii", "PIZZA", 120);
    ASSERT_EQ("", t.getName());
}

TEST(TestDish, changeDish){
    Dish t("Paperoni", "PIZZA", 5);
    t.changeDish("Hawaii", "PIZZA", 5);
    ASSERT_EQ("<Hawaii>:<PIZZA>:<5>",t.getDish());
    ASSERT_EQ(false, t.changeDish("Hawaii", "PIZZA", 5));
}

TEST(TestMenu, createMenu){
    Menu m;
    m.addDish("quatro-Formagi", "PIZZA", 6);
    ASSERT_EQ("<quatro-Formagi>:<PIZZA>:<6>" ,m.getDish("quatro-Formagi"));
    Dish pizza("Prosciutto", "PIZZA", 5);
    m.addDish(pizza);
    ASSERT_EQ("<Prosciutto>:<PIZZA>:<5>\n"
              "<quatro-Formagi>:<PIZZA>:<6>", m.getMenu());
}

TEST(TestMenu, deleting){
    Menu m;
    m.addDish("espresso", "COFFE", 1);
    m.addDish("capucino", "COFFE", 2);
    ASSERT_EQ("<capucino>:<COFFE>:<2>\n<espresso>:<COFFE>:<1>",m.getMenu());
    m.removeDish("capucino");
    ASSERT_EQ("<espresso>:<COFFE>:<1>",m.getMenu());
    ASSERT_EQ(false, m.inMenu("capucino"));
}

TEST(TestMenu, addFromAnotherMenu){
    Menu m;
    m.addDish("espresso", "COFFE", 1);
    m.addDish("capucino", "COFFE", 2);
    m.addDish("latte", "COFFE", 2);
    Menu m2;
    m2.addFromAnotherMenu(move(m));
    ASSERT_EQ("<capucino>:<COFFE>:<2>\n"
              "<espresso>:<COFFE>:<1>\n"
              "<latte>:<COFFE>:<2>", m2.getMenu());
    ASSERT_EQ("", m.getMenu());
}

TEST(TestMenu, badMenu){
    Menu m;
    m.addDish("fungi", "PASTA", 5);
    m.addDish("fish", "PASTA", 120);
    ASSERT_EQ("ERROR", m.getDish("fish"));
    Dish pizza("Hawaii", "PIZZA", 99999);
    m.addDish(pizza);
    ASSERT_EQ("ERROR", m.getDish("Hawaii"));
}

TEST(TestMenu, removeOneFromMenu){
    Menu m;
    m.addDish("espresso", "COFFE", 1);
    m.addDish("capucino", "COFFE", 2);
    m.addDish("latte", "COFFE", 2);
    ASSERT_EQ("<espresso>:<COFFE>:<1>", m.getDish("espresso"));
    m.removeDish("espresso");
    cout << m.getDish("espresso");
    ASSERT_EQ("ERROR", m.getDish("espresso"));
    ASSERT_EQ(false, m.removeDish("espresso"));
    m.eraseAllDishes();
    ASSERT_EQ("", m.getMenu());
}

TEST(TestMenu, oneType){
    Menu m;
    m.addDish("espresso", "COFFE", 1);
    m.addDish("capucino", "COFFE", 2);
    m.addDish("latte", "COFFE", 2);
    m.addDish("FISH", "FISH_FOOD", 8);
    m.addDish("FISH2", "FISH_FOOD", 12);
    m.addDish("quatro-Formagi", "PIZZA", 6);
    Dish pizza("Prosciutto", "PIZZA", 5);
    m.addDish(pizza);
    Menu m2 = m.getAllDishesWithType("PIZZA");
    ASSERT_EQ("<Prosciutto>:<PIZZA>:<5>\n"
              "<quatro-Formagi>:<PIZZA>:<6>", m2.getMenu());
    Menu m3 = m.getAllDishesWithType("FISH_FOOD");
    ASSERT_EQ("<FISH>:<FISH_FOOD>:<8>\n"
              "<FISH2>:<FISH_FOOD>:<12>", m3.getMenu());
    Menu m4 = m.getAllDishesWithType("DESERTS");
    ASSERT_EQ("", m4.getMenu());
}