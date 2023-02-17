# ImGui Backend

This repository provides an easy solution for using [DearImGui](https://github.com/ocornut/imgui) with CMake. 
The key feature is a simple class that enables you to create an OpenGL context using the GLFW library and initialize
the Dear ImGui library with the created context.

# Status
![linux build](https://github.com/TheKiHub/imGuiBackend/actions/workflows/linux.yml/badge.svg)  
![windows build](https://github.com/TheKiHub/imGuiBackend/actions/workflows/windows.yml/badge.svg)    
![mac build](https://github.com/TheKiHub/imGuiBackend/actions/workflows/mac.yml/badge.svg)

# Usage
### 1. Get the target
To use this repository effectively, it is recommended to use my [cmakeBase](https://github.com/TheKiHub/cmakeBase) in your root CMakeLists.txt file and 
then utilize CPM to handle the remaining processes:

```cmake
CPMAddPackage(
        NAME guiBackend
        URL https://github.com/TheKiHub/imGuiBackend/releases/latest/download/package_files.zip
)
```

If you do not wish to use cmakeBase but still want to utilize fetch, it is important to set 
NO_BASIC_INITIAL_IN_ROOT before:

```cmake
set(NO_BASIC_INITIAL_IN_ROOT ON)    # needed to get cmakeBase repository on its own
FetchContent_Declare(
        guiBackend
        URL https://github.com/TheKiHub/guiBackend/releases/latest/download/package_files.zip
)
FetchContent_MakeAvailable(guiBackend guiBackend)
```
While it's still possible to install this repository using 'find_package', it's no longer the recommended method. 
This is because manual installation can be difficult for users without extensive CMake knowledge. It's important to
note that while the traditional method is still supported, there may be compatibility issues due to lack of
regular maintenance.

### 2. Link the target
Once that is taken care of you can use the target and link it against your project.
``` cmake
target_link_libraries(guiBackendExample
    guiBackend
)
```

### 3. Use it in your code
Inside your C++ Code you can create a window and integrate it with imGui in this manner:

```c
#include "imGuiCustom.h"

int main() {
    imGuiCustom gui;
    
    if (gui.createWindow() != 0) {
    return -1;
    }
    
    while(gui.checkWindow()) {
      imGuiCustom::createFrame();
      showDemo();
      gui.renderFrame();
    }
    
    return 0;
}
```

## Error Handling
The createWindow method returns an error code of 0 if everything went well,
and -1 if an error occurred while creating the window.
