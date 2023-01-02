## Namespaces

All `namespaces` should have `__` prefix. Example:

```cpp
namespace __BetaAlphaGamma {}
```

> Desirable: description after close bracket.

***It's better not to use using***

## Classes

`Class` should have unique name and first letter in ***upper case***:

```cpp
class FooBar {};
```

> Desirable: description before class initialization.

## Structs

`Struct` should have `_` prefix. Example:

```cpp
struct _User {};
```

> Desirable: description before structure initialization.

## Variables

All `variables` should be divided into two groups: **Static** and **Dynamic**:

```cpp
/* Static variable (constant) */
const std::string S_Username = "Alice";

/* Dynamic variable */
std::string D_Username = "Alice";
```

> Desirable: add **D** prefix to Dynamic variables or **S** to Static.

If the `variable` is an internal field of a `class` or `structure`, `this->...` is **required**