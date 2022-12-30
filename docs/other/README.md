BridgeAPI is a mechanism for the interaction of components within the operating system. The namespace contains a single `E_Request()` method that takes as arguments a reference to the class of the request receiver and the request itself as a string.

In order for the component to receive and process requests from the BridgeAPI, its class must contain 2 methods - `bool E_Bridge () { retrun true; }` and the `E_BridgeAPI` method, which will accept and process requests.

For example, this system (already at an early stage) was used in a virtual memory module:

```cpp
/* Any.hpp */

#include "__VirtualMemory/VM_Core.hpp"
#include "__Kernel/K_BridgeAPI.hpp"

__VirtualMemory::Core D_VirtualMemoryManager;

E_Request(D_VirtualMemoryManager, "get --0 --0");
```

```cpp
/* VM_Core.cpp */

//...

bool E_Bridge () {
    return true;
}

__StandardLibrary::Situate E_BridgeAPI (std::string D_RequestHeader, __StandardLibrary::Composition D_RequestBody) {
  /* code... */
}

//..
```

`D_RequestHeader` and `D_RequestBody` are the received data

```cpp
std::cout << D_RequestHeader; // "get"

for (std::vector<std::string> D_RequestBodyElement : D_RequestBody) {
  std::cout << D_RequestBodyElement.at(0) + ": " + D_RequestBodyElement.at(1)) << std::endl; // "argument: 0 argument: 0"
}
```
