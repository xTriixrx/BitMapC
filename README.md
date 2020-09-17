# BitMapC
A C bitmap structure allowing programming access at the bit level along with a complete example highlighting functionality.

### Tutorial

The example program provided under the bitmap-datatype.c file provides the following options via a REPL loop for experimentation:
1. SetBit - Sets a bit to the "ON" state (1)
2. ClearBit - Sets a bit to the "OFF" state (0)
3. TestBit - Returns 1 if a bit is "ON" and 0 if "OFF"
4. Invert BitMap - Inverts the entire bitmap
5. Invert BitMap Column - Inverts a subset of the bitmap based on the column provided.
6. Invert BitMap Row - Inverts a subset of the bitmap based on the row provided.

Below are simple screenshots of a 10x10 example bitmap using each of the commands:

![](https://github.com/xTriixrx/BitMapC/blob/master/images/testbit0.png)

![](https://github.com/xTriixrx/BitMapC/blob/master/images/setbit0.png)

![](https://github.com/xTriixrx/BitMapC/blob/master/images/clearbit0.png)

![](https://github.com/xTriixrx/BitMapC/blob/master/images/invertcol5.png)

![](https://github.com/xTriixrx/BitMapC/blob/master/images/invertrow5.png)

![](https://github.com/xTriixrx/BitMapC/blob/master/images/invertmap.png)

### Build Instructions

To build the provided example:
gcc -o BM bitmap-datatype.c