# Build instructions

## Prepare environment (Windows)

Install and configure vcpkg. Read fallowing articles

- https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=vs-2019
- https://github.com/microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md

Tip: Select triple for your project - https://github.com/microsoft/vcpkg/blob/master/docs/users/integration.md#triplet-selection


You can get correct path using **"vcpkg integrate install"** command

## Install dependencies

Projects are configured to use gRPC as static library.

```
vcpkg install grpc:x64-windows-static
```

## Issues during build

- proto_utils.h:52
```
Error	C4996	'google::protobuf::MessageLite::ByteSize': Please use ByteSizeLong() instead	**\vcpkg\installed\x86-windows\include\grpcpp\impl\codegen\proto_utils.h	52	
```
Problem is that protobuf have deprecated ByteSize in lieu of ByteSizeLong, but grpc library source taken from vcpkg does not uses old deprecated function.
Better solution will be to ask for fix in grpc. Or find a flag to use deprecated functions.

**My temp solution**: I just replaces ByteSize with ByteSizeLong in proto_utils.h in the line, which is point on in Error List

## VCPKG Usage

```
The package protobuf:x64-windows-static provides CMake targets:

    find_package(protobuf CONFIG REQUIRED)
    target_link_libraries(main PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

The package grpc:x64-windows-static provides CMake targets:

    find_package(gRPC CONFIG REQUIRED)
    # Note: 9 target(s) were omitted.
    target_link_libraries(main PRIVATE gRPC::gpr gRPC::upb gRPC::grpc gRPC::grpc++)
```