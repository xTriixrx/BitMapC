#include <stdio.h>
#include <stdlib.h>
#include "bit-ops.c"

void argumentError();
void printMenu(int, int, int);
void argumentHandler(int*, char**, int*, int*);

/**
 * This main method is used to showcase the BitMap structure and the operations
 * that can be performed. The BitMap structure and respective operations are defined
 * in the bit-ops.c file and must be included in any file that plans to use the BitMap
 * data structure. The BitMap structure is built on top of a Flexible Array Member (FAM)
 * integer array. Each integer block is assumed to contain 32 bits and the data structure is
 * also assumed to be working in little endian. This has not been testing using a big endian
 * machine but technically should still work (inversion operators and bit ordering may be flipped).
 */
int main(int argc, char **argv)
{
  int bitTotal, columns, intTotal, pos, option, validBit = 0;

  // Processes and populates command line argument fields
  argumentHandler(&argc, argv, &bitTotal, &columns);

  // Determine number of ints necessary for number of bits stored in bitmap variable
  intTotal = determineBitMapSize(bitTotal);

  // Create bitmap structure
  struct BitMap *bm = createBitMap(bm, intTotal, bitTotal);

  // Number of bits is calculate by number of int sized blocks by number of bits per block.
  printf("Total bits allocated: %d\n", (bm->int_size * INT_BITS));

  // Startup menu to help user
  printMenu(bm->bit_size, columns, (int) ceil(bm->bit_size / (columns * 1.0)));

  while(1)
  {
    printf("Option  Bit Position: ");
    scanf("%d %d", &option, &pos);

    if (option == -1)
    {
        break;
    }

    switch (option)
    {
        case 1:
          // If SetBit returns -1, a bit outside of bitmap was attempted to bit set.
          if ((validBit = SetBit(bm->map, pos, bm->bit_size)) == -1)
          {
            printf("Attempted to set bit %d outside of bitmap.\n", pos);
          }
          else
          {
            // An else condition would signify that the bit has been set within the bitmap.
          }
          break;
        case 2:
          // If ClearBit returns -1 the bit attempted to be cleared is outside of bitmap.
          if ((validBit = ClearBit(bm->map, pos, bm->bit_size)) == -1)
          {
            printf("Attempted to clear a bit outside of bitmap.\n");
          }
          else
          {
            // An else condition would signify that the bit has been cleared within the bitmap.
          }
          break;
        case 3:
          // If TestBit returns -1, the attempted bit test was outside of bitmap.
          if ((validBit = TestBit(bm->map, pos, bm->bit_size)) == -1)
          {
            printf("Attempted to test bit %d outside of bitmap.\n", pos);
          }
          else if (validBit == 0) // If TestBit returns 0, bit was not set.
          {
            printf("Bit %d in the bitmap has not been set.\n", pos);
          }
          else // If TestBit returns > 0, bit was set.
          {
            printf("Bit %d in the bitmap has been set.\n", pos);
          }
          break;
        case 4:
          invertBitMap(bm->map, bm->bit_size);
          break;
        case 5:
          invertBitMapColumn(bm->map, bm->bit_size, columns, pos);
          break;
        case 6:
          invertBitMapRow(bm->map, bm->bit_size, columns, pos);
          break;
        default:
          printf("Invalid option passed, please input an option between 1-6 or -1 to quit.\n");
          break;
    }
    printf("\n");

    // Custom 2D bitmap printout for visualization.
    printbm(bm->map, bm->int_size, bitTotal, columns);

    printf("\n");

    // Clearing user input
    fflush(stdin);
  }

  // Free memory
  free(bm);

  return 0;
}

/**
 * Takes the command line arguments and processes the input line, setting variables
 * from the caller when validation has been established.
 *
 * @param argc
 * @param argv
 * @param bitSize
 * @param cols
 * @return void
 */
void argumentHandler(int *argc, char **argv, int *bitSize, int *cols)
{
  if (*argc != 3)
    argumentError();

    *bitSize = atoi(argv[1]);
    *cols = atoi(argv[2]);
}

/**
 * Prints out a set of requirements for the process to start properly and example
 * calls to the process.
 *
 * @return void
 */
void argumentError()
{
  printf("Requires number of bits to generate bit map and number of columns.\n");
  printf("The following example produces a bitmap with 25 addressable bits & 5 printable columns.\n");
  printf("./BM 25 5\n");
  printf("The following example produces a bitmap with 81 addressable bits & 9 printable columns.\n");
  printf("./BM 81 9\n");
  printf("Please note: the underlying datatype used is an array of integer blocks due to compiler optimization.\n");
  printf("Because of this, there is usually some bits unused that is \"blocked\" by the bitmap datatype. If you choose to operate ");
  printf("a bitmap with a full int block allocation, choose bit values divisible by 32 bits, (32, 64, 128, 256, etc.).\n");
  exit(1);
}

/**
 * An intro menu that prints out the available options to the user.
 *
 * @param bitSize
 * @return void
 */
void printMenu(int bitSize, int colTotal, int rowTotal)
{
  printf("This application was made to test the BitMap structure and how it operates.\n");
  printf("The console expects 2 inputs at all times once the REPL loop begins: an option and a bit position.\n");
  printf("The following value options are available to test the functionality of the BitMap structure:\n");
  printf("\t\t 1): SetBit\n");
  printf("\t\t 2): ClearBit\n");
  printf("\t\t 3): TestBit\n");
  printf("\t\t 4): Invert BitMap\n");
  printf("\t\t 5): Invert BitMap Column\n");
  printf("\t\t 6): Invert BitMap Row\n");
  printf("\t\t-1): Quit\n");
  printf("These options above provide proper handling for attempting to access bits outside of bitmap.\n");
  printf("The available addressable bits are within the range: %d-%d.\n", 0, bitSize - 1);
  printf("The invert bitmap option (4) only requires the option 4 but any addressable bit field is required by REPL.\n");
  printf("The invert bitmap column option requires the option 5 and a column value within the range: %d-%d.\n", 1, colTotal);
  printf("The invert bitmap row option requires the option 6 and a row value within the range: %d-%d.\n", 1, rowTotal);
  printf("An example to set the 0th bit within the bitmap would be to respond with \"1 0\" to the REPL.\n");
  printf("In order to quit, you will need to add an extra argument such as responding with \"-1 -1 to the REPL.\"\n\n");
}
