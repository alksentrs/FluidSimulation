cmake_minimum_required(VERSION 3.10)
project(FluidSimulation)

set(CMAKE_CXX_STANDARD 17)

# Flags úteis de compilação
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# Encontrar SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Incluir o diretório raiz do src para que #include funcione direto
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    src/business
    src/business/engine
    src/business/particleSystem
    src/business/particleSystem/quadTree
    src/application
    src/util
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/business/*.cpp
    src/util/*.cpp
    src/presentation/*.cpp
)

add_executable(${PROJECT_NAME}
    src/application/main.cpp
    ${SOURCES}
)

# Linkar SFML
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

# Agora sim: encontrar e linkar OpenMP (após add_executable)
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
endif()
