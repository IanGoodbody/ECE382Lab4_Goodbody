ECE382Lab4_Goodbody
===================

### Prelab

##### Data Types
The following table provides a summary of different data types available in the MSP430 optimized C compiler

|Size|Signed/Unsigned|Min Value|Max Value|
|:-|:-|-:|-:|
|8-bit|Unsigned|Unsigned Char|0|255|
|8-bit|Signed|Signed Char|-128|127|
|16-bit|Unsigned|Unsigned Short|0|65,535|
|16-bit|Signed|Short|-32,768|32,767|
|32-bit|Unsigned|Unsigned Long|0|4,294,967,295|
|32-bit|Signed|Long|-2,147,483,648|2,147,483,647|
|64-bit|Unsigned|Unsigned Long|0|18,446,744,073,709,551,615|
|64-bit|Signed|Unsigned Long|-9,223,372,036,854,775,808|9,223,372,036,854,775,807|

Because the names of these different data types are rather unwieldy, C offers the `typedef` statement to reassign these
type names. A summary is provided below

|Type|Meaning|C typedef declaration|
|:-|:-|:-|
|int8|unsigned 8 bit value|`typedef unsigned char int8`|
|sint8|signed 8 bit value|`typedef signed char sint8`|
|int16|unsigned 16 bit value|`typedef unsigned short int16`|
|sint16|signed 16 bit value|`typedef signed short sint16`|
|int32|unsigned 32 bit value|`typedef unsigned long int32`|
|sint32|signed 32 bit value|`typedef signed long sint32`|
|int64|unsigned 64 bit value|`typedef unsigned long long int64`|
|sint64|signed 64 bit value|`typedef signed long long int64`|

##### Calling/Return Convention

The CSS debuging platform allows the developer to view the different variables, registers, and disassembled code
involved in running a C program on the MSP430. For this section a sample of code labeled simpleLab4.c (shown below) 
was analized.

```objetive-c
#include <msp430g2553.h>

typedef	unsigned short int16;

int16 func(int16 w, int16 x, int16 y, int16 z);

void main() {

	int16	a,b,c,d,e;

	a=1;
	b=2;
	c=3;
	d=4;

	while(1) {

		e = func(a,b,c,d);
		d = e+5;
		c = d+1;
		b = c+1;
		a = b+1;
	}
}

int16 func(int16 w, int16 x, int16 y, int16 z) {

	int16 sum;

	sum = w+x+y+z;
	sum = sum >> 2;

	return(sum);
```
 The program was run for 5 iterations of the while loop. The following table records the progression of the values a, b,
 c, d, and e through those iterations.
 
|Iteration|a|b|c|d|e|
|:-:|:-:|:-:|:-:|:-:|:-:|
|1st|10|9|8|7|10|
|2nd|16|15|14|13|16|
|3rd|22|21|20|19|22|
|4th|28|27|26|25|28|
|5th|34|33|32|31|34|

Finally the Disassembler was used to study the `func()` function in the compiled program. This table shows a summary of 
the different function parameters.

|Parameter|Value Sought|
|:-|:-|
|Starting address of  `func()`|0xC2CC|
|Ending address of  `func()`|0xC2D8|
|Register holding  w|R12|
|Register holding  x|R13|
|Register holding  y|R14|
|Register holding  z|R15|
|Register holding return value|R12|

##### Corss Language Build Constructs

The `extern` directive in a .c file tells the compiler a function name, return type, and parameters of a function located somewhere else in the build path. It is essentially a function protype for things that are outside of .c files.

The `.global` directive tells the assembler to make certain memory labels global so that they can be referenced elsewhere in the build path.  
