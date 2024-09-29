# Solioquy

An open source game engine for c++ .


## Authors

- [Tom Knowles](https://www.github.com/gnolley)


## Installation

Build the project using cmake.

### Prerequisites    
LunarG Vulkan SDK

VCPKG

### Visual Studio
Install Dektop Development with C++ Module.
Ensure you have the following Options.
- Windows 10/11 SDK
- Vcpkg package manager
- C++ Cmake tools for Windows
- Test Adapter for Google Test

### Vcpkg
Create a CMakeUserPresets.json file to set vcpkg, or set VCPKG_ROOT as an environment variables

```
{
  "version": 2,
  "configurePresets": [
    {
      "name": "default",
      "inherits": "vcpkg",
      "environment": {
        "VCPKG_ROOT": "C:\\Users\\thoma\\OneDrive\\Documents\\Projects\\vcpkg"
      }
    }
  ]
}
```