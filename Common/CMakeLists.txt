cmake_minimum_required(VERSION 4.0)

set(COMMON_LOCAL_SOURCES
        Math/Vec2.cpp
        Math/Vec4.cpp
        Math/Solvers/Add.cpp
        Math/Solvers/Subtract.cpp
        Math/Solvers/Multiply.cpp
        Math/Solvers/Divide.cpp
        Math/MathGenerator.cpp
        Math/Solvers/SolverBase.cpp
)
set(COMMON_PUBLIC_HEADERS
        Math/Vec2.h
        Math/Vec4.h
        Math/Solvers/Add.h
        Math/Solvers/Subtract.h
        Math/Solvers/Multiply.h
        Math/Solvers/Divide.h
        Math/MathGenerator.h
        Math/Solvers/SolverBase.h
)

add_library(HH_Common ${COMMON_LOCAL_SOURCES})