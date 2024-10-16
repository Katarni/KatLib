# KatLib

My small sfml library

I update this lib with my practice works

## Docs
[Dependency tree](docs/md/dependency-tree.md) of framework's files  
[Inheritance tree](docs/md/inheritance-tree.md) of framework's classes


## Installation

make 
```
git clone https://github.com/Katarni/KatLib.git
```
or
```
git submodule add https://github.com/Katarni/KatLib.git 
```

and include KatLib in cmake

```cmake
add_subdirectory(KatLibDirectory)
target_link_libraries(ProfectName KatLib)
```

### For Windows users
To use it, u need to change include sfml libs in CMakeLists.txt in lines 37-38.
Replace "path/to/sfml" with your path

## TODO
+ docs
