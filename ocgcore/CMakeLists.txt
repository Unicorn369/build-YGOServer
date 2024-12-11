project (ocgcore)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_OCGCORE)

#include_directories ( ../lua )

add_library (ocgcore STATIC ${SRC_OCGCORE})

target_link_libraries (ocgcore lua)
target_include_directories(ocgcore PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
