# Build instructions

## Prepare environment (Windows)

Install and configure vcpkg. Read fallowing articles

- https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=vs-2019
- https://github.com/microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md

Set environment variable CMAKE_TOOLCHAIN_FILE to point to vcpkg cmake toolchain script. For example,

```
CMAKE_TOOLCHAIN_FILE=%USERPROFILE%\tools\vcpkg\scripts\buildsystems\vcpkg.cmake
```

You can get correct path using **"vcpkg integrate install"** command

Set environment variable CMAKE_TOOLCHAIN_INSTALLED_ROOT, which  points to the root
of all vcpkg installed packages. For example,

```
CMAKE_TOOLCHAIN_INSTALLED_ROOT=%USERPROFILE%\tools\vcpkg\installed\x64-windows
```

## Fetch dependencies for GrpcHelper project first

```bash
git clone --recurse-submodules <greenlight-url>
```

or

```bash
git clone <greenlight-url>
cd <greenlight-dir>
git submodule update --init --recursive
```
or

```bash
git clone <greenlight-url>
git submodule update --init
cd lib/grpc
git submodule update --init
```

## Issues during build

Sometimes you want to remove **out\build** and bootstrap CMake build directory from scratch

Visual Studio CMake Targets View (in Solution Explorer use Switch Views button) have
commands in contextual menu for CMake projects: **Delete Cache** and **Generate Cache**

## VCPKG Usage

```
The package grpc:x86-windows provides CMake targets:

    find_package(gRPC CONFIG REQUIRED)
    # Note: 9 target(s) were omitted.
    target_link_libraries(main PRIVATE gRPC::gpr gRPC::upb gRPC::grpc gRPC::grpc++)
```