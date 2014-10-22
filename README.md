ECE382Lab4_Goodbody
===================

### Prelab

##### Data Types
The following table provides a summary of different data types available in the MSP430 optimized C compiler

|Size|Signed/Unsigned|Type|Min Value|Max Value|
|:--|:--|:--|--:|--:|
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
|:--|:--|:--|
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

``` c
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
 The program was run for 5 iterations of the while loop. The following table records the progression of the values a, 
 b, c, d, and e through those iterations.
 
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
|:--|:--|
|Starting address of  `func()`|0xC2CC|
|Ending address of  `func()`|0xC2D8|
|Register holding  w|R12|
|Register holding  x|R13|
|Register holding  y|R14|
|Register holding  z|R15|
|Register holding return value|R12|

##### Corss Language Build Constructs

The `extern` directive in a .c file tells the compiler a function name, return type, and parameters of a function
located somewhere else in the build path. It is essentially a function protype for things that are outside of .c files.

The `.global` directive tells the assembler to make certain memory labels global so that they can be referenced 
elsewhere in the build path.  

### Required Functionality

The required functionality was implemented based off of the lab4.c and nokia.asm files provided. The nokia.asm file 
was modified so that the `drawBlock` function took a write byte as the parameter which would allows either writing
a `0xFF` for a solid block or a `0x00` to clear the block. In order to save the data on the screen the `clearDisplay()`
function was not called at the end of each loop. Pressing the auxillary button inverted the color parameter so that 
writing could clear the old bits.

The functionality was tested by by writing and clearing with the cursor. In this regard testing was fairly trivial.

### B Functionality

The B functionality required that a block/ball bounce around a screen, changing direction whenever it came into 
contact with the edge of the screen.

The B functionality utalized the assembly driver from Lab 3 which was implemented to move any a set pattern around by 
one pixel per button press. The nokia_bounce.asm file was stripped of the main function and supporting functionality 
code leaving only the writing methods. The byte arrays that defined the different images that could be written to the 
screen were moved to `#define` statements in the header file along with an additional `#define` parameter which 
specified the length of that byte array. The origional subroutine took in a pointer to the pattern array being used as
well as the length as parameters and thus required little modification. Finally, a wait function was added in the 
assembly file to add a delay process for a specified number of iterations.

The assembly was implemented in c code which handled the ball physics and defined which pattern was drawn to the LCD.
Because the wait function took in a unsigned 16-bit number as an input, its maximum value was only 65,535 which did not
produce a suitable delay. This problem was circumvented by calling the `wait()` function inside of a while loop that
counted by some scale factor i wich specified the number of times the maxed out `wait()` function would be called.

It is worth noting that the `drawPattern()` function has an unusal parameter convention where it places y value in the
parameter list before the x value. Changing this to a more intuitive convention would have required chaning already 
functioning and difficult to modify code, so I decided to just switch the parameters and not break anything.

While the core B functionality required that a 8x8 box move 8 pixels per jump, additional functionality gave the 
option of using different patterns for the block as well as using fine movement (moving 1 pixel per cycle). This
addional functionality was a more general case of the required specifications and were implemented. The program can 
be modified do emulate the required functionality by setting |xVel|=|yVel|=8, multiplying the current scale factor i by
8, and by loading the `BLOCK` and `BLOCK_WD` pattern parmeters into the various calls of the .c file. (Find and replace
works exceptionally well here).
