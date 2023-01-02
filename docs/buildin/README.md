# SL_Colorizer.hpp

- Simple module for colorize text output!

### __StandardLibrary::E_ColorizeFront(std::string, int, int, int)

- Colorize font with RGB model.

```cpp
__StandardLibrary::E_ColorizeFront("My simple text", 255 /* Red */, 0 /* Green */, 0 /* Blue */);
```

### __StandardLibrary::E_ColorizeBack(std::string, int, int, int)

- Colorize background with RGB model.

```cpp
__StandardLibrary::E_ColorizeBack("This is Green background", 0 /* Red */, 255 /* Green */, 0 /* Blue */);
```

## __StandardLibrary::ColorTemplater

- A class that stores your color schemes.

### __StandardLibrary::ColorTemplater::E_Push(std::string, std::string, std::string)

```cpp
__StandardLibrary::ColorTemplater::E_Push("First", __StandardLibrary::ColorTemplater::E_GenerateFront(255, 0, 0), __StandardLibrary::ColorTemplater::GenerateFront(255, 255, 255));
```

### __StandardLibrary::ColorTemplater::E_Wrap(std::string, std::string)

```cpp
__StandardLibrary::ColorTemplater::E_Wrap("Hello, World!", "First").E_GetDetails().at(0); // First - name of template
```

### __StandardLibrary::ColorTemplater::E_DropTable()

- This method show all your templates with names (if you forgot)

### __StandardLibrary::ColorTemplater::E_GenereateFront(const ::size_t, const ::size_t, const ::size_t)

```
std::cout << __StandardLibrary::ColorTemplater::E_GenereateFront(255, 0, 0) << " My red text" << std::endl;
```

### __StandardLibrary::ColorTemplater::E_GenereateBack(const ::size_t, const ::size_t, const ::size_t)

```
std::cout << __StandardLibrary::ColorTemplater::E_GenereateBack(255, 0, 0) << " My red background for text" << std::endl;
```

# SL_Screen.hpp

- Screen Manager

### __StandardLibrary::E_Output(std::string)

```cpp
__StandardLibrary::E_Output("Hello, World!");
```

### __StandardLibrary::E_Input(std::string&)

```cpp
std::string D_UserInput;

__StandardLibrary::E_Input(D_UserInput);
```

# SL_Timer.hpp

- Get Time and Date

### __StandardLibrary::E_GetDateAndTime()

```cpp
std::cout << __StandardLibrary::E_GetDateAndTime(); 02.01.2023
```
