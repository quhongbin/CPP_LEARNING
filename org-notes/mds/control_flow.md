---
title: test
---

# control workflow

> normally, a program execute sequentially

## Constexpr if statement(C++17) {#a75306e6-72ea-4142-9285-80f737bc3f0b roam_aliases="constexpr-if"}

``` {.cpp results="output"}
#include <iostream>
int main()
{
    constexpr double gravity{ 9.8 };

    if constexpr (gravity == 9.8) // now using constexpr if
        std::cout << "Gravity is normal.\n";
    else
        std::cout << "We are not on Earth.\n";

    return 0;
}
```

## Switch statement {#b37951c4-6f9b-486e-9f9e-777fd8380580 roam_aliases="switch case"}

``` {.cpp results="switch_output"}
#include <iostream>
void printDigitName(int x)
{
    switch (x)
    {
    case 1:
        std::cout << "One";
        return;
    case 2:
        std::cout << "Two";
        return;
    case 3:
        std::cout << "Three";
        return;
    default:
        std::cout << "Unknown";
        return;
    }
}

int main()
{
    printDigitName(2);
    std::cout << '\n';

    return 0;
}
```

-   evaluation statement type must be a int or enum class
    -   only types of int or enum class
-   
