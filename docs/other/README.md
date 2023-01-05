# BridgeAPI

BridgeAPI is a mechanism for the interaction of components within the operating system. The namespace contains a single `E_Request()` method that takes as arguments a reference to the class of the request receiver and the request itself as a string.

In order for the component to receive and process requests from the BridgeAPI, its class must contain 2 methods - `bool E_Bridge () { retrun true; }` and the `E_BridgeAPI` method, which will accept and process requests.

For example, this system (already at an early stage) was used in a virtual memory module:

```cpp
/* Any.hpp */

#include "__VirtualMemory/VM_Core.hpp"
#include "__Kernel/K_BridgeAPI.hpp"

__VirtualMemory::Core D_VirtualMemoryManager;

__Kernel::E_Request(D_VirtualMemoryManager, "get --0 --0");
```

```cpp
/* VM_Core.hpp */

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

# Universal Template Mechanism (UTM)

This mechanism allows you to compose simple text templates for further use!

```cpp
#include "./__StandardLibrary/SL_Template.hpp"
#include <iostream>

__StandardLibrary::Templater D_Templater;

D_Templater.E_Push("welcome-message", "Welcome!");

std::cout << D_Templater.E_Drop("welcome-message"); // Welcome!
```

# Color tTmplating Mechanism (CTM)

This mechanism works the same as the previous one but with colors.

```cpp
#include "./__StandardLibrary/SL_Colorizer.hpp"
#include <iostream>

__StandardLibrary::ColorTemplater D_ColorTemplater;

/* first argument - template name, second - the color with which the line will start, third - the color at which the line ends */
D_ColorTemplater.E_Push("Greet-Color", D_ColorTemplater.E_GenerateFront(255, 0, 0), D_ColorTemplater.E_GenerateFront(255, 255, 255));
```

If you want to see all Color Templates use `D_ColorTemplater.E_DropTable()` and you can see some like this:

<img src="https://github.com/ruletkasuperstar/NatureOS/blob/main/__Sources/Screenshot_2.png">

# Configuration

This module allows to create and use `.config` files!

```cpp
#include "./__Kernel/K_Configuration.hpp"

__Kernel::CFile D_ConfigManager;
```

Create any cfg file

```txt
// this is your config file
```

Next:

```cpp
D_ConfigManager.E_OpenFile("path/to/any.config");
```

And now you can:

```cpp
D_ConfigManager.E_Push("USE_DEBUG", "true"); // push items
D_ConfigManager.E_Get("USE_DEBUG").E_DropDataByIndex(1); // get item value
D_ConfigManager.E_Set("USE_DEBUG", "false"); // set new value to item

D_ConfigManager.E_DropContent(); // save all to file
```

```txt
// this is your config file
USE_DEBUG=false

```
