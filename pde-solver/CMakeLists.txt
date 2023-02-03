cmake_minimum_required(VERSION 3.5)

project(pde-solver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3")

add_executable(pde-solver main.cpp ioutils.cpp matrixutils.cpp solver.cpp ioutils.h matrixutils.h solver.h)

install(TARGETS pde-solver
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

set(CPM_DOWNLOAD_VERSION 0.36.0) # download CPM version

if(CPM_SOURCE_CACHE)
  set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
elseif(DEFINED ENV{CPM_SOURCE_CACHE})
  set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
else()
  set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif()

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
  message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
  file(DOWNLOAD
       https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
       ${CPM_DOWNLOAD_LOCATION}
  )
endif()

include(${CPM_DOWNLOAD_LOCATION}) #include CPM itself

option(CPM_USE_LOCAL_PACKAGES "Try `find_package` before downloading dependencies" ON)

CPMAddPackage(
    NAME matplotplusplus
    GITHUB_REPOSITORY alandefreitas/matplotplusplus
    GIT_TAG origin/master # or whatever tag you want
)

CPMAddPackage("gh:catchorg/Catch2@2.13.9")

# ---- Create binary ----

target_link_libraries(pde-solver matplot Catch2)
target_compile_features(pde-solver PRIVATE cxx_std_17)


# -----


add_executable(pde-solver-test test.cpp ioutils.cpp matrixutils.cpp solver.cpp ioutils.h matrixutils.h solver.h)

install(TARGETS pde-solver-test
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

# ---- Create binary ----

target_link_libraries(pde-solver-test matplot Catch2)
target_compile_features(pde-solver-test PRIVATE cxx_std_17)

# ---- Enable testing ----

enable_testing()
add_test(mytest pde-solver-test)

