cmake_minimum_required(VERSION 3.19)
project(zClipboard)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Gui Core Network)
find_package(PkgConfig REQUIRED)

if(LINUX)
    pkg_check_modules(LIBNOTIFY REQUIRED IMPORTED_TARGET libnotify)
endif()

if(NOT WIN32)
    pkg_check_modules(SODIUM REQUIRED IMPORTED_TARGET libsodium)
endif()

set(CXX_SOURCE)
set(CXX_HEADER)
set(ASSETS resources.qrc)

file(GLOB_RECURSE SOURCES_CXX "Source/*.cc")
file(GLOB_RECURSE SOURCES_C "Source/*.c")
file(GLOB_RECURSE HEADER_SOURCES "Source/*.h" "Source/*.hpp")

qt_add_executable(${PROJECT_NAME} ${SOURCES_CXX} ${SOURCES_C} ${HEADER_SOURCES} ${ASSETS})

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE Qt6::Widgets
    PRIVATE Qt6::Sql
    PRIVATE Qt6::Core
    PRIVATE Qt6::Gui
    PRIVATE Qt6::Network
)
if(Z_DEBUG)
    add_compile_definitions(${PROJECT_NAME} PRIVATE Z_DEBUG)
endif()

if(NOT WIN32) 
    target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SODIUM)
endif()

if(WIN32)
    find_package(unofficial-sodium CONFIG REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE unofficial-sodium::sodium)
endif()

if(LINUX)
    target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::LIBNOTIFY)
endif()


# We suggest use Clang for compiler.
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CXX_COMPILER_ID:Clang>:-fno-direct-access-external-data>")
    # Warning:
    # Only enable when use
    # -DZ_DEBUG=1.
    # We will disable it in default, for ABI mismatch reason.
    if(Z_DEBUG)
        add_compile_options(-stdlib=libc++)
        target_link_libraries(${PROJECT_NAME} PRIVATE -lc++ -lc++abi)
    endif()
endif()

message(STATUS "Current C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Current C++ Compiler: ${CMAKE_CXX_COMPILER}")

install(TARGETS ${PROJECT_NAME} DESTINATION bin)