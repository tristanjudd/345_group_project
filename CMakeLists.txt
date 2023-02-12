cmake_minimum_required(VERSION 3.23)
project(Warzone)

set(CMAKE_CXX_STANDARD 20)

add_executable(Warzone main.cpp
        Map/MapDriver.cpp
        Map/Map.cpp
        Map/Map.h
        Map/MapDriver.h
        Card.cpp
        Card.h
        CardsDriver.cpp
        Deck.cpp
        Deck.h
        Hand.cpp
        Hand.h 
        CardsDriver.h 
        Orders.h
        Orders.cpp
        OrdersDriver.h
        OrdersDriver.cpp Player/Player.h Player/Player.cpp Player/PlayerDriver.h Player/PlayerDriver.cpp)

install (TARGETS Warzone DESTINATION "warzone/bin")