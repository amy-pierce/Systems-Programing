#include <stdio.h>
#include <stdlib.h>

struct bitset{
    unsigned int *bits;
    int sizeInBits;
    int sizeInWords;
};

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size){

    struct bitset*result;
    int sizeInWords;

    sizeInWords = size/sizeof(unsigned int)*8;

    result = malloc(sizeof(struct bitset));

    if(size%(sizeof(unsigned int)*8)!=0){
        sizeInWords++;
    }

    result->bits = malloc(sizeof(unsigned int) * sizeInWords);


    for(int i = 0; i<sizeInWords;i++){
        result->bits[i] = 0;
    }
    result->sizeInBits = size;
    result->sizeInWords = sizeInWords;

    return result;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this){
int size = 0;

size = this->sizeInBits;

return size;
}

int bitset_lookup(struct bitset * this, int item){

int itemBit, itemPos;
itemBit = item/32;
itemPos = item%32;
unsigned int mask = 1;

mask = mask << itemPos;

if((this->bits[itemBit] & mask) !=0){
    return 1;
}
return 0;
}

int bitset_cardinality(struct bitset * this){

int result=0;
unsigned int mask = 1;
for(int i=0; i<bitset_size(this)/32; i++){
if((this->bits[i] & mask) == 1 ){
result++;
}
}
return result;
}

int bitset_add(struct bitset * this, int item){
// if(item<!0 && item>!bitset_size(this)) {
//if (this->bits[item] == 0) {

//this->bits[item] = 1;

//return 1;
// }

// return 0;
int itemBit, itemPos;
itemBit = item/32;
itemPos = item%32;
unsigned int mask =1;
mask = mask << itemPos;
this->bits[itemBit]=this->bits[itemBit] | mask;
return 1;
}

int bitset_remove(struct bitset * this, int item){
    int itemBit, itemPos;
    itemBit = item/32;
    itemPos = item%32;

    unsigned int mask = 1;
    mask = mask << itemPos;
    mask = ~mask;
    this->bits[itemBit] = this->bits[itemBit] & mask;
    return 1;
}

void bitset_union(struct bitset * c, struct bitset * a, struct bitset * b){
    for(int i = 0; i < a->sizeInWords/32 ; i++) {
        c->bits[i] = (a->bits[i] | b->bits[i]);
    }
}

void bitset_intersect(struct bitset * c, struct bitset * a, struct bitset * b){
    for(int i = 0; i < a->sizeInWords/32 ; i++) {

            c -> bits[i] =  (a->bits[i] & b->bits[i]);

    }
}

// print the contents of the bitset
void bitset_print(struct bitset * this)
{
int i;
int size = bitset_size(this);
for ( i = 0; i < size; i++ ) {
if ( bitset_lookup(this, i) == 1 ) {
printf("%d ", i);
}
}
printf("\n");
}
