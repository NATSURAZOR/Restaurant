// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "3_Reservation.h"

using namespace ::testing;

TEST(TestName, emptyName){
    Guest name;
    ASSERT_EQ("", name.getGuestName());
}

TEST(TestName, goodName){
    Guest name;
    name.put("James Adlert");
    ASSERT_EQ("James Adlert", name.getGuestName());
}

TEST(TestName, badName){
    Guest name;
    name.put("NameWithoutsSpaces");
    ASSERT_EQ("", name.getGuestName());
}

TEST(TestName, longName){
    Guest name;
    name.put("VeryVeryVeryVeryVeryVeryVeryVeryBIGGGGGGGGGGGGGGGGGGGGGGGGNAAAAAAAAMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM"
             "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");
    ASSERT_EQ("", name.getGuestName());
}

TEST(TestName, shortName){
    Guest name;
    name.put("James");
    ASSERT_EQ("", name.getGuestName());
}

TEST(TestName, threeWord){
    Guest name;
    name.put("one twoo three");
    ASSERT_EQ("", name.getGuestName());
}

TEST(TestReservation, res){
    Guest name;
    name.put("James Adlert");
    Reservation reservation;
    reservation.addReservation("James Adlert", 4, 5);
    ASSERT_EQ("James Adlert", reservation.getGuestName());
    ASSERT_EQ(5, reservation.getCountOfGuest());
    ASSERT_EQ(4,reservation.getTableNumber());
    ASSERT_EQ(0,reservation.getCheck());
    ASSERT_EQ("", reservation.getOrderedDishes());
}

TEST(TestReservation, res2){
    Reservation reservation;
    reservation.addReservation("James Adlert", 5, 4);
    ASSERT_EQ("James Adlert", reservation.getGuestName());
    ASSERT_EQ(4, reservation.getCountOfGuest());
    ASSERT_EQ(5,reservation.getTableNumber());
    ASSERT_EQ(0,reservation.getCheck());
    ASSERT_EQ("", reservation.getOrderedDishes());
}

TEST(TestReservation, res3){
    Reservation reservation;
    reservation.addReservation("James Adlert", 5, 100);
    ASSERT_EQ("", reservation.getGuestName());
    ASSERT_EQ(0, reservation.getCountOfGuest());
    ASSERT_EQ(0,reservation.getTableNumber());
    ASSERT_EQ(0,reservation.getCheck());
    ASSERT_EQ("", reservation.getOrderedDishes());
}

TEST(TestReservation, res4){
    Reservation reservation;
    reservation.addReservation("James Adlert", 5, 4);
    reservation.addToOrderDishes("YEP you can write everything you want her because it's not controled her");
    ASSERT_EQ("YEP you can write everything you want her because it's not controled her",
              reservation.getOrderedDishes());
}

