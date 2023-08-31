cmake_minimum_required(VERSION 3.25)
project(ImageRec)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


find_package(ROOT REQUIRED)

include_directories(    include ${PROJECT_SOURCE_DIR}/header                               )


include(${ROOT_USE_FILE})
include_directories((${ROOT_INCLUDE_DIRS}))
link_directories(${ROOT_LIBRARY_DIR})

set(CMAKE_CXX_FLAGS "${ROOT_CXX_FLAGS}")

find_package(pybind11 CONFIG REQUIRED)


LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../Dep/root/lib/)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}../Dep/root/include/)



file(GLOB src_files
      "src/*.cpp"
        )


add_executable(ImageRec helloworld.cpp ${src_files} ${ROOT_LIBRARIES})
target_link_libraries(ImageRec PUBLIC ${ROOT_LIBRARIES})

