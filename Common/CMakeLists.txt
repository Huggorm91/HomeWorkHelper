cmake_minimum_required(VERSION 4.0)

set(LOCAL_SOURCES
        Math/Vec2.cpp
        Math/Solvers/Add.cpp
        Math/Solvers/Subtract.cpp
        Math/Solvers/Multiply.cpp
        Math/Solvers/Divide.cpp
        Math/MathGenerator.cpp
        Math/Solvers/SolverBase.cpp
)
set(PUBLIC_HEADERS
        Math/Solvers/Add.h
        Math/Solvers/Subtract.h
        Math/Solvers/Multiply.h
        Math/Solvers/Divide.h
        Math/MathGenerator.h
        Math/Solvers/SolverBase.h
)

add_library(HH_Common ${LOCAL_SOURCES})