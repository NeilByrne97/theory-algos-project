#include <stdio.h>
#include <inttypes.h>

#define W 32
#define WORD uint32_t
#define PF PRIX32
#define BYTE uint8_t

union Block {
    BYTE bytes[64];
    WORD words[16];
    uint64_t sixf[8];
};

enum Status{
    READ, PAD, END
};

// Get next block
int next_block(FILE *f, union Block *B, enum Status *S, uint64_t *nobits){
    // Number of bytes read
    size_t nobytes;

    if(*S == END){
        return 0;
    } else if (*S == READ){
        // Try to read 64 bytes
        nobytes = fread(B->bytes, 1, 64, f);
        // Calculayte total bits read so far
        *nobits = *nobits + (8 * nobytes);
        // Enough room for padding
        if(nobytes == 64){
            return 1;
        } else if(nobytes <= 55){
            // Append a 1 but (and seven 0 bits to make a full bytes)
            B->bytes[nobytes++] = 0x80; // in bits: 1000000
            // Append enough 0 bits, leaving 64 at the end
            while(nobytes++ < 56){
                B->bytes[nobytes] = 0x00; // In bits: 0000000
            }
            // Append length of orignal input (CHECK ENDIANESS)
            B->sixf[7] = *nobits;
            *S = END;

        } else{
            // Gotten to the end of the input message
            // Not enough room in this block fo all padding
            // Append a 1 bit (and seven 0 bits to make a full byte)
            B->bytes[nobytes] = 0x80;
            // Append 0 bits
            while(nobytes++ < 64){
                B->bytes[nobytes] = 0x00; // In bits: 0000000
            }
            // Change the status to PAD
            *S = PAD;
        }
    } else if (*S == PAD){
        nobytes = 0;
        // Append 0 bits
        while(nobytes++ < 64){
            B->bytes[nobytes] = 0x00; // In bits: 0000000
        }
        // Appends nobuts as an int
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

