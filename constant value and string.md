# const and constexpr
1. on variable value
	- "const" modifies an object or value,which hasn't been changing:RiComputerFill:
	- "constexpr" decorates value of expression which is known at compile-time:RiTimer2Line:
2. on arguments of function
	- "const" function is regarded as constant value at runtime
	- "constexpre" function can't indicate the arguments of function
3. constexpr function([be uesd of in constant expression](https://learncpp.com.cn/cpp-tutorial/constexpr-variables/))
	- it must evaluate the result at compile-time

# std::string & std::string_view
> they aren't basic types, but class types

in C++,we should avoid using C-style string that use strings around double quotation marks 

string is variable-length value, unlike basic types (e.g int,unsigned int) have fixed sizes. so the data that std::string object point to is allocated in the heap, std::string object in the stack
# compile-time optimization
as-if rule
- use "const" keyword to decorate variable always
- the constant value propagation
```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << x << '\n'; //the x can be replaced by 7

	return 0;
}
```
- the constant value folding
```cpp
#include <iostream>

int main()
{
	int x { 7 };
	int y { 3 };
	std::cout << x+y << '\n';
	// x+y will be replaced by 10
	// first: x and y become 7 and 3
	// second: calculate the expression of x+y
	return 0;
}
```