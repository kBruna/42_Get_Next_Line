# 42_Get_Next_Line
42's Project Get Next Line

Write a function that returns a line read from a file descriptor.

Prototype:

	char *get_next_line(int fd);


## Notes

### Static Variables

Static Variables have the property of retaining their value between multiple function calls. It is initialized only once and is not destroyed when the function returns a value. It extends the lifetime of the variable till the end of the program.

Syntax:

	static datatype var_name;
	
Static Variables can be used inside a function and outside, as a static global variable. If they are a global, then it will be visible inside the same file only. On the other hand, the static variables declared inside a function will be visible inside de the function only.

Static Variables are stored in the data segment of memory, not on the stack, so they survive function returns.
	
### Macro

In C programming, a macro is a symbolic name or constant that represents a value, expression, or code snippet. They are defined using the `#define` directivem and when encountered, the preprocessor substitutes it with its defined content.

Syntax:

	#define MACRO_NAME value

	
Macros actually doesn't need to be all uppercase, however is a convention that makes it easily recognizable.

#### Types of Macros

#####  Object-Like Macros

The simplest type of macros. They replace the macro name with a defined value or expression. There are used for constant or simple values.

Syntax:

	#define MACRO_NAME value


##### Chain Macros

These macros involve chaining multiple macros together. This can be done by combining different macros in a single macro definition, allowing for complex operations. In chain macros the first of all parent macro is expanded then the child macro is expanded.

Syntax:

	#define MACRO_PARENT MACRO_CHILD
	#define MACRO_CHILD 12

##### Multi-line Macros

These macros span multiple lines for readability and organization. They are often used when you need a more complex expression or code block. To create a multi-line macro you have to use backlash `\`.

Syntax:

	#define LINE 	1, \
			2, \
			3
			
##### Function-like Macros

These macros take parameters and behavi like functions, allowing you to define reusable logic for common operators. They are expanded at compile time. A function-like macro is only lengthened of and only its name appears with a pair of parentheses after it. If we don't do this, the function pointer will get the address of the real function and lead to syntax error.

According to the Norm, these are not allowed.
