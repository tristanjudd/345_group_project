cmake_minimum_required(VERSION 3.23)
project(Warzone)

set(CMAKE_CXX_STANDARD 20)

add_executable(Warzone main.cpp
        Map/MapDriver.cpp
        Map/Map.cpp
        Map/Map.h
        Map/MapDriver.h
        Cards/CardsDriver.cpp
        Cards/CardsDriver.h
        Cards/Cards.cpp
        Cards/Cards.h
        Orders/Orders.h
        Orders/Orders.cpp
        Orders/OrdersDriver.h

        Orders/OrdersDriver.cpp Player/Player.h Player/Player.cpp Player/PlayerDriver.h Player/PlayerDriver.cpp GameEngine/GameEngine.cpp GameEngine/GameEngineDriver.cpp GameEngine/GameEngine.h GameEngine/GameEngineDriver.h GameLog/LoggingObserver.h GameLog/LoggingObserver.cpp CommandProcessing/CommandProcessing.h CommandProcessing/CommandProcessing.cpp GameLog/LoggingDriver.cpp GameLog/LoggingDriver.h PlayerStrategies/PlayerStrategies.h PlayerStrategies/PlayerStrategies.cpp PlayerStrategies/NeutralDriver.h PlayerStrategies/NeutralDriver.cpp PlayerStrategies/CheaterDriver.cpp PlayerStrategies/CheaterDriver.h)


install (TARGETS Warzone DESTINATION "warzone/bin")