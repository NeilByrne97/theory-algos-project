#include <stdio.h>
#include <inttypes.h>

#define W 32
#define WORD uint32_t
#define PF PRIX32
#define BYTE uint8_t

union Block {
    BYTE bytes[64];
    WORD words[16];
};

int main(int argc, char *argv[]){
    
    int i;
    // Current Block
    union Block B;
    // Total number of bits read
    uint64_t nobits = 0;

    FILE *f;
    f = fopen(argv[1], "r");

    size_t nobytes;
    nobytes = fread(B.bytes, 1, 64, f);
    printf("Read %d bytes. \n", nobytes);
    nobits = nobits + (8 * nobytes);

    for(i = 0;i < 16;i++){
        printf("%08" PF " ", B.words[i]);
        if((i + 1) % 8 == 0)
        printf("\n");
    }
    while (!feof(f)){
        nobytes = fread(&B.bytes, 1, 64, f);
        printf("Read %d bytes. \n", nobytes);

    for(i = 0;i < 16;i++){
        printf("%08" PF " ", B.words[i]);
        if((i + 1) % 8 == 0)
        printf("\n");
    }
        
    }

    fclose(f);
    printf("Total bits read: %d, \n", nobits);

    return 0;

}
