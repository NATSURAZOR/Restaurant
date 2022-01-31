// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "2_Tables.h"

using namespace ::testing;

TEST(TestTable, emptyTable){
    Table t;
    ASSERT_EQ(0,t.getSeats());
    t.setSeats(4);
    ASSERT_EQ(4, t.getSeats());
}

TEST(TestTable, goodTable){
    Table t(5);
    ASSERT_EQ(5, t.getSeats());
}

TEST(TestTable, badTable){
    Table t(25);
    ASSERT_EQ(0,t.getSeats());
}

TEST(TestsTables, emptyTables){
    Tables t;
    ASSERT_EQ(0, t.numberOfTables());
    ASSERT_EQ(0,t.numberOfMaxGuests());
}

TEST(TestsTables, biggerThanMAX){
    Tables t(3333, 5000);
    ASSERT_EQ(0, t.numberOfTables());
    t.addOneTable(4);
    ASSERT_EQ(1, t.numberOfTables());
}

TEST(TestsTables, checkMINandMAX){
    Tables t;
    ASSERT_EQ(-1, t.addTables(-3, 5));
    ASSERT_EQ(-1, t.addTables(15, 8));
    ASSERT_EQ(-1, t.addTables(-3, 8));
    ASSERT_EQ(-1, t.addTables(18, -3));
    ASSERT_EQ(-1, t.addTables(50, 5));
    ASSERT_EQ(-1, t.addTables(0, 0));
}

TEST(TestsTables, defaultTable){
    Tables t;
    t.createDefaultTablse();
    ASSERT_EQ(25, t.numberOfTables());
    ASSERT_EQ(100, t.numberOfMaxGuests());
}

TEST(TestsTables, addTables){
    Table t(4);
    Table t1(3);
    Table t2(6);
    Tables tab;
    tab.addOneTable(t);
    tab.addOneTable(t1);
    tab.addOneTable(t2);
    ASSERT_EQ(3, tab.numberOfTables());
    Table t4(3);
    tab.addOneTable(t4);
    ASSERT_EQ(4, tab.numberOfTables());
}

TEST(TestsTables, inTable){
    Tables t(10, 4);
    ASSERT_EQ(true, t.inTables(5));
    ASSERT_EQ(false, t.inTables(-20));
}

TEST(TestsTables, removeALL){
    Tables t;
    t.createDefaultTablse();
    t.eraseAllTables();
    ASSERT_EQ(0, t.numberOfTables());
    ASSERT_EQ(0, t.numberOfMaxGuests());
}

TEST(TestsTables, removeTable){
    Tables t;
    ASSERT_EQ(false, t.removeTable(2));
    t.addOneTable(4);
    ASSERT_EQ(true, t.removeTable(1));
}

TEST(TestsTables, addTablebyTableNumber){
    Tables t;
    t.addTables(16, 3);
    ASSERT_EQ(true, t.inTables(16));
}

TEST(TestsTables, goodTables){
    Tables t(1, 5);
    ASSERT_EQ(1, t.numberOfTables());
    t.addOneTable(4);
    ASSERT_EQ(2, t.numberOfTables());
    t.addTables(3, 5);
    ASSERT_EQ(24, t.numberOfMaxGuests());
    t.addOneTable(2);
    ASSERT_EQ(2, t.numberOfSeatsAtTheTable(6));
    t.removeTable(6);
    ASSERT_EQ(5, t.numberOfTables());
    t.eraseAllTables();
    ASSERT_EQ(0, t.numberOfTables());
}

