cmake_minimum_required(VERSION 3.29)
project(Lab1)

set(CMAKE_CXX_STANDARD 23)

add_executable(Lab1
        main.cpp
        Commands/arrCommands.cpp
        Structures/arr.cpp
        Commands/stackCommands.cpp
        Structures/Stack.cpp
        Commands/queueCommands.cpp
        Structures/MyQueue.cpp
        Structures/list.cpp
        Commands/listCommands.cpp
        Structures/Pair.cpp
        Structures/hashMap.cpp
        Commands/hashCommands.cpp
        helpFuncs.cpp
        Structures/ComplTree.cpp
        Commands/treeCommands.cpp
)
