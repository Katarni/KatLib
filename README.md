# KatLib

My small sfml library

## FOR WINDOWS USERS
To use it, u need to change include sfml libs in CMakeLists.txt in lines 37-39.

Set it like this
```cmake
set(SFML_INCLUDE_DIRS "C:/path/to/sfml/include")
set(SFML_DIR "C:/path/to/sfml/lib/cmake/SFML")
include_directories(${SFML_INCLUDE_DIRS})
find_package(SFML 2.6.1 COMPONENTS system window graphics network audio CONFIG REQUIRED)
target_link_libraries(KatLib INTERFACE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
```

## FOR UNIX SYSTEM
U can ujust clone it and use ( if u have installed sfml)

## TODO
+ docs
