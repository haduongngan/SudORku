cmake_minimum_required(VERSION 3.15)
project(sudoku)

set(CMAKE_CXX_STANDARD 14)

add_executable(sudoku
        main.cpp
#        1sol.cpp
        )


include_directories(/Applications/CPLEX_Studio1210/cplex/include)
include_directories(/Applications/CPLEX_Studio1210/concert/include)

find_library(CPLEX cplex /Applications/CPLEX_Studio1210/cplex/lib/x86-64_osx/static_pic)
target_link_libraries(sudoku LINK_PUBLIC ${CPLEX})

find_library(ILOCPLEX ilocplex /Applications/CPLEX_Studio1210/cplex/lib/x86-64_osx/static_pic)
target_link_libraries(sudoku LINK_PUBLIC ${ILOCPLEX})

find_library(CONCERT concert /Applications/CPLEX_Studio1210/concert/lib/x86-64_osx/static_pic)
target_link_libraries(sudoku LINK_PUBLIC ${CONCERT})
