cmake_minimum_required(VERSION 3.21)
project(address_book VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Address Book Library (core) ─────────────────────────────
add_library(ab_model STATIC
    src/model/person.cpp
)

add_library(ab_utils STATIC
    src/utils/validator.cpp
    src/utils/fuzzy_search.cpp
    src/utils/file_io.cpp
)
target_link_libraries(ab_utils PUBLIC ab_model)

add_library(ab_service STATIC
    src/service/address_book_service.cpp
)
target_link_libraries(ab_service PUBLIC ab_utils ab_model)

add_library(ab_ui STATIC
    src/ui/console_view.cpp
)
target_link_libraries(ab_ui PUBLIC ab_service)

# ── CLI Executable ──────────────────────────────────────────
add_executable(address_book
    src/main.cpp
)
target_link_libraries(address_book PRIVATE ab_ui ab_service ab_utils ab_model)

# ── Tests ───────────────────────────────────────────────────
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
