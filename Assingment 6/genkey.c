#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define FIRSTBIT 0x8000000000000000

// Key schedule tables

const int Rotations[16] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

const int PC1[56] = {
   57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27,
   19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29,
   21, 13,  5, 28, 20, 12,  4
};

const int PC2[48] = {
   14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
   23, 19, 12,  4, 26,  8,
   16,  7, 27, 20, 13,  2,
   41, 52, 31, 37, 47, 55,
   30, 40, 51, 45, 33, 48,
   44, 49, 39, 56, 34, 53,
   46, 42, 50, 36, 29, 32
};


void addbit(uint64_t *block, uint64_t from,int position_from, int position_to){
    if(((from << (position_from)) & FIRSTBIT) != 0)
        *block += (FIRSTBIT >> position_to);
}

void key_schedule(uint64_t* key, uint64_t* next_key, int round){
    // Init
    uint64_t key_left = 0;
    uint64_t key_right = 0;

    uint64_t key_left_temp = 0;
    uint64_t key_right_temp = 0;

    *next_key = 0; // Important !

    // 1. First round => PC-1 : Permuted Choice 1
    if(round == 0){
        for(int ii = 0; ii < 56; ii++){
            if(ii < 28)
                addbit(&key_left, *key, PC1[ii] - 1, ii);
            else
                addbit(&key_right, *key, PC1[ii] - 1, ii % 28);
        }
    }
    // 1'. Other rounds? => Seperate key into two key halves.
    else{
        for(int ii = 0; ii < 56; ii++){
            if(ii < 28)
                addbit(&key_left, *key, ii, ii);
            else
                addbit(&key_right, *key, ii, ii % 28);
        }
    }
   
    // 2. Rotations
    key_left_temp = Rotations[round] == 1 ? FIRSTBIT : 0xC000000000000000;
    key_right_temp = Rotations[round] == 1 ? FIRSTBIT : 0xC000000000000000;
    key_left_temp = (key_left & key_left_temp) >> (28 - Rotations[round]);
    key_right_temp = (key_right & key_right_temp) >> (28 - Rotations[round]);

    key_left_temp += (key_left << Rotations[round]);
    key_right_temp += (key_right << Rotations[round]);
    
    // Combine the 2 keys into 1 (next_key)
    // Next_key will be used for following rounds
    for(int ii = 0; ii < 56; ii++){
        if(ii < 28)
            addbit(next_key, key_left_temp, ii, ii);
        else
            addbit(next_key, key_right_temp, (ii % 28), ii);
    }

    // 3. PC-2 : Permuted Choice 2
    *key = 0;

    for(int ii = 0; ii < 48; ii++)
        addbit(key, *next_key, PC2[ii] - 1, ii);

    // All Good!
    // Use key in the DES rounds.
    // Use next_key in this function again as the new key to change
}

// Function to print uint64_t in binary
void printbits(uint64_t v){
    for(int ii = 0; ii < 64; ii++){
        if( ((v << ii) & FIRSTBIT) == (uint64_t)0)
            printf("0");
        else
            printf("1");
    }
}

// Generate a 64bit random DES key
// Add parity bits (last bit of each byte)
// Check for weak keys using key_schedule
static void genkey(uint64_t* key){
    srand(time(NULL));

    // Generate key
    int parity_bit = 0;

    for(int ii = 0; ii < 64; ii++){
        // Parity bit
        if(ii % 8 == 7){
            if(parity_bit == 1)
                *key += (FIRSTBIT >> ii);
            parity_bit = 0; // Re-init parity_bit for next byte block
        }
        else{
            if(rand() % 2 == 1){
                *key += (FIRSTBIT >> ii);
                parity_bit = parity_bit == 0 ? 1 : 0;
            }
        }
    }

    // Test the key schedule
    uint64_t a_key[16];
    a_key[0] = *key;
    uint64_t next_key;

    for(int ii = 0; ii < 16; ii++){
        key_schedule(&a_key[ii], &next_key, ii);
        if(ii != 15)
            a_key[ii + 1] = next_key;
    }

    // Test for weak keys
    bool weak = false;

    for(int ii = 0; ii < 16; ii++){
        for(int jj = 0; jj < 16; jj++){
            if(jj != ii){
                if(a_key[ii] == a_key[jj])
                    weak = true;
            }
        }
    }

    // If the generated key is weak, do the algorithm one more time
    if(weak){
        genkey(key);
    }
}

int main(){
    uint64_t key = 0;

    genkey(&key);
    
    printf("Here's one key for you sir: \n");
    printbits(key);
    printf("\n");
	
	FILE *fs;
	fs = fopen("key.txt","w");
	fclose(fs);

    return EXIT_SUCCESS;
}
