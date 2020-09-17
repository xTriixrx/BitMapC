# BitMapC

A C bitmap structure allowing programming access at the bit level along with a complete example highlighting functionality.

## Description

The BitMap C structure and utility functions were written for extendability and safety in mind. Using the provided functions will prevent bit clearing/setting outside of the allocated structure. The BitMap structure is mainly built upon a Flexible Array Member (FAM) integer array which can set dynamically. The choice for using an integer array (4 bytes per block) v.s. a char array (1 byte per block) was due to optimization considerations that favored the integer array allocation. The BitMap structure also contains 2 integer values: the number of bits in the bitmap, and the number of integer blocks allocated in the bitmap. Please note that these 2 values are rarely parallel to each other; meaning that for a given integer block (32 bits) a user can utilize any number of bits up to the 32 bits. The example program provided shows how this data structure is operated on and the proper way of instantiating the structure. 

To run the executable example, the binary requires 2 command line arguments: the number of bits in the bitmap data structure, and the number of columns the printing function should format to. The bit-ops.c utility file contains all of the code that implements the bitmap and the functions to operate on the bitmap. The lowest level functions: SetBit, ClearBit, and TestBit, all contain range checking in order to prevent bit writing outside of the allocated data structure. I found this structure particularly interesting to implement efforts requiring limited memory usage.

### Tutorial

The example program provided under the bitmap-datatype.c file provides the following options via a REPL loop for experimentation:
1. SetBit - Sets a bit to the "ON" state (1)
2. ClearBit - Sets a bit to the "OFF" state (0)
3. TestBit - Returns 1 if a bit is "ON" and 0 if "OFF"
4. Invert BitMap - Inverts the entire bitmap
5. Invert BitMap Column - Inverts a subset of the bitmap based on the column provided.
6. Invert BitMap Row - Inverts a subset of the bitmap based on the row provided.

Below are simple screenshots of a 100 bit, 10 column example (10x10) bitmap using each of the commands:

![](https://github.com/xTriixrx/BitMapC/blob/master/images/testbit0.png)

![](https://github.com/xTriixrx/BitMapC/blob/master/images/setbit0.png)

![](https://github.com/xTriixrx/BitMapC/blob/master/images/clearbit0.png)

![](https://github.com/xTriixrx/BitMapC/blob/master/images/invertcol5.png)

![](https://github.com/xTriixrx/BitMapC/blob/master/images/invertrow5.png)

![](https://github.com/xTriixrx/BitMapC/blob/master/images/invertmap.png)

### Build Instructions

To build the provided example:

gcc -o BM bitmap-datatype.c

### Questions & Help

If you have any questions please feel free to reach out to me on LinkedIn.