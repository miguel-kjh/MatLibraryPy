cmake_minimum_required(VERSION 2.8.3)

# Find python and Boost - both are required dependencies
find_package(PythonLibs 3 REQUIRED)
find_package(Boost COMPONENTS python REQUIRED)

# Without this, any build libraries automatically have names "lib{x}.so"
set(CMAKE_SHARED_MODULE_PREFIX "")

# Add a shared module - modules are intended to be imported at runtime.
# - This is where you add the source files
add_library(MatLibraryPy MODULE MatLibraryPy.cpp)

# Set up the libraries and header search paths for this target
target_link_libraries(MatLibraryPy ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
target_include_directories(MatLibraryPy PRIVATE ${PYTHON_INCLUDE_DIRS})