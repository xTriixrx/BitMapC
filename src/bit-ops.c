#include <math.h>
#include <string.h>

#define INT_BITS 32

#define SetBit(A,k,b)     ((k < b) ? A[(k/32)] |= (1 << (k%32)) : -1)
#define ClearBit(A,k,b)   ((k < b) ? A[(k/32)] &= ~(1 << (k%32)) : -1)
#define TestBit(A,k,b)    ((k < b) ? A[(k/32)] & (1 << (k%32)) : -1)

/**
 * The BitMap structure contains size variables and a Flexible Array Member (FAM)
 * variable to allocate and store a bitmap within a contiguous block of integer sized
 * memory blocks. The allocation of the map member is done during the createBitMap function
 * and should be used with extreme care as improper use of dynamic memory allocation can
 * cause crashes. An example of a bitmap structs allocation and instantiation is the following:
 * struct BitMap *bm = createBitMap(bm, 2, 25); 2 represents the number of integer blocks
 * and 25 represents the number of bits that will be addressable within the 2 integer blocks.
 * Therefore this example above creates a bitmap containing at most, 64 bits but only has 25 bits
 * addressable.
 */
struct BitMap {
    int bit_size;
    int int_size;
    int map[];
};

/**
 * Allocates memory for a BitMap structure, sets the size of the BitMap struct
 * and zeros out the bitmap.
 *
 * @param *bm
 * @param arrSize
 * @return BitMap
 */
struct BitMap *createBitMap(struct BitMap *bm, int arrSize, int bitSize)
{
  // Allocating bitmap
  bm = malloc(sizeof(*bm) + sizeof(int) * arrSize);

  // bit_size is the number of addressable bits.
  bm->bit_size = bitSize;

  // int_size is the number of int blocks allocated in bitmap
  bm->int_size = arrSize;

  // Zero out bitmap
  memset(bm->map, 0, bm->int_size);

  return bm;
}

/**
 * Accepts the number of desired bits within the bitmap and calculates the number
 * of int sized blocks it would take to create such a bitmap. Will return this value
 * of int sized blocks to the callee.
 *
 * @param bits
 * @return void
 */
int determineBitMapSize(int bits)
{
  int size = 0;
  while (bits > (++size * INT_BITS)) {}
  return size;
}

/**
 * Inverts the entire bitmap by iterating over each bit in the bit map and utilizing
 * the SetBit or ClearBit macros on the appropriate bits to invert them.
 *
 * @param *A
 * @return void
 */
void invertBitMap(int *A, int bitSize)
{
  int validBit;

  for (int i = 0; i < bitSize; i++)
  {
    if ((validBit = TestBit(A, i, bitSize)) == 0) // Bit was not set
      SetBit(A, i, bitSize);
    else // Bit was set
      ClearBit(A, i, bitSize);
  }
}

/**
 * If colNum is a valid column choice, this function will stride over the bitmap
 * over chunks the size of the given colTotal size and invert each bit.
 *
 * @param *A
 * @param bitSize
 * @param colTotal
 * @param colNum
 * @return void
 */
 void invertBitMapColumn(int *A, int bitSize, int colTotal, int colNum)
 {
   int validBit;

   if (colNum > colTotal || colNum < 1)
   {
     printf("Column selection must be between %d-%d.\n", 1, colTotal);
     return;
   }

   for (int i = colNum - 1; i < bitSize; i += colTotal)
   {
     if ((validBit = TestBit(A, i, bitSize)) == 0) // Bit was not set
       SetBit(A, i, bitSize);
     else // Bit was set
       ClearBit(A, i, bitSize);
   }
 }

/**
 * If rowNum is a valid row choice, this function will iterate through the valid row
 * inverting the bits in that row until the terminating condition is met; which is when
 * the total column count has been counted up to.
 *
 * @param *A
 * @param bitSize
 * @param colTotal
 * @param rowNum
 * @return void
 */
void invertBitMapRow(int *A, int bitSize, int colTotal, int rowNum)
{
    int validBit, colCnt = 1, rowCnt = 1;
    int maxRow = (int) ceil(bitSize / (colTotal * 1.0));

    if (rowNum > maxRow || rowNum < 1)
    {
      printf("Row selection must be between %d-%d.\n", 1, maxRow);
      return;
    }

    for (int i = (colTotal * rowNum) - colTotal; colCnt <= colTotal; i++)
    {
      if ((validBit = TestBit(A, i, bitSize)) == 0) // Bit was not set
        SetBit(A, i, bitSize);
      else // Bit was set
        ClearBit(A, i, bitSize);
      colCnt++;
    }
}

/**
 * Prints out a bitmap as a 2D array where cols signifys the number of columns
 * that should exist within the bitmap as it is being printed out. In memory, this
 * bitmap is stored as an array of integers. But when manipulated and printed is handled
 * as a contiguous block of bits. The sequence moves from left to right starting from the top;
 * therefore bit 0 is always top leftmost bit while the n-1 bit will always be most bottom right bit.
 * This print allows the user to "prettify" the contiguous block of bits.
 *
 * @param *A
 * @param length
 * @param maplen
 * @param rowlen
 * @return void
 */
void printbm(int *A, int length, int maplen, int cols)
{
  int mapReached = 0, bitcnt = 0;

  // Loops through each int block
  for (int i = 0; i < length; i++)
  {
    // Iterates over each bit in a int block
    for (int j = 0; j < INT_BITS; j++)
    {
      if ((bitcnt % cols == 0 && j != 0) ) { printf("\n"); }
      else if ((bitcnt % cols == 0 && j == 0 && i != 0)) { printf("\n"); }

      // Prints bitmap from least significant bit to most significant bit in bitmap
      printf("%d ", !!((A[i] >> j) & 0x1));
      bitcnt++;

      // If total bits iterated thus far has reached the map length break and set flag
      if (bitcnt == maplen)
      {
        mapReached = 1;
        break;
      }
    } // end of current int block

    // If flag is true break out of remaining int blocks
    if (mapReached)
    {
      break;
    }
  } // end of all int blocks
  printf("\n");
}
