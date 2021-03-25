#include <stdio.h>
#include <inttypes.h>

#define W 32    // Length of word
#define WORD uint32_t
#define PF PRIX32   // Print format - 32 bits HEX
#define BYTE uint8_t

// SHA256 works on blocks of 512 bits
union Block {
    // 8 x 64 = 512 - dealing with block as bytes
    BYTE bytes[64];
    // 32 x 16 = 512 - dealing with block as words
    WORD words[16];
    // 64 x 8 = 512 - dealing with the last 64 bits of the last block
    uint64_t sixf[8];
};

// Keeping track of where we are in the input message/padding
enum Status{
    READ, PAD, END
};

// Returns 1 if it create a new block from original message or padding
// Returns 0 if all padded message has already been consumed - DONE
int next_block(FILE *f, union Block *B, enum Status *S, uint64_t *nobits){
    // Number of bytes read
    size_t nobytes;

    if(*S == END){
        return 0;
    } else if (*S == READ){
        // Try to read 64 bytes from the input file
        nobytes = fread(B->bytes, 1, 64, f);
        // Calculate total bits read so far
        *nobits = *nobits + (8 * nobytes);
        // Enough room for padding
        if(nobytes == 64){
            // This happends when we can read 64 bytes from f
            return 1;
        } else if(nobytes < 56){
            // This happends when we have enough room for all the padding
            // Append a 1 but (and seven 0 bits to make a full bytes)
            B->bytes[nobytes++] = 0x80; // in bits: 1000000
            // Append enough 0 bits, leaving 64 at the end
            for(; nobytes++ < 56; nobytes++){
                B->bytes[nobytes] = 0x00; // In bits: 0000000
            }
            // Append length of orignal input (CHECK ENDIANESS)
            B->sixf[7] = *nobits;
            *S = END;

        } else{
            // Get to the end of the input message
            // Not enough room in this block for all padding
            // Append a 1 bit (and seven 0 bits to make a full byte)
            B->bytes[nobytes] = 0x80;
            // Append 0 bits
            while(nobytes++ < 64){
                B->bytes[nobytes] = 0x00; // In bits: 0000000
            }
            // Change the status to PAD
            *S = PAD;   // Runs if block again to return 0
        }
    } else if (*S == PAD){
        nobytes = 0;
        // Append 0 bits
        for(nobytes = 0; nobytes < 56; nobytes++){
            B->bytes[nobytes] = 0x00; // In bits: 0000000
        }
        // Appends nobuts as an int. (CHECK ENDIANESS)
        B->sixf[7] = *nobits;
        // Change the status to PAD
        *S = END;       
    }

    return 1;
}

int main(int argc, char *argv[]){
    
    int i;
    // Current Block
    union Block B;
    // Total number of bits read
    uint64_t nobits = 0;

    size_t nobytes;
    // Current status of reading input
    enum Status S = READ;
    FILE *f;
    // Open file from command line for reading
    f = fopen(argv[1], "r");

    // Loop through preproc blocks 
    while (next_block(f, &B, &S, &nobits)){
        for(i = 0;i < 16;i++){
            printf("%08" PF " ", B.words[i]);
        }
        printf("\n");
    }

    fclose(f);
    printf("Total bits read: %d, \n", nobits);

    return 0;

}

