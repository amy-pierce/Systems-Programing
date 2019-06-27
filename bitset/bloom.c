#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bloom.h"

const int BLOOM_HASH1 = 17;
const int BLOOM_HASH2 = 29;

// compute a hash of a string using a seed value, where the result
// falls between zero and range-1
int hash_string(char * string, int seed, int range)
{
  int i;
  int hash = 0;

  // simple loop for mixing the input string
  for ( i = 0; string[i] != '\0'; i++ ) {
    hash = hash * seed + string[i];
  }
  // check for unlikely case that hash is negative
  if ( hash < 0 ) {
    hash = -hash;
  }
  // bring the hash within the range 0..range-1
  hash = hash % range;

  return hash;
}

// create a new, empty Bloom filter with 'size' slots
struct bloom * bloom_new(int size)
{
  struct bloom * newBloom;
  newBloom= malloc(sizeof(struct bitset));
  newBloom->bit_vector = bitset_new(256);
  newBloom->size = newBloom->bit_vector->size_in_bits;

  return newBloom;
}

// check to see if a string is in the set
int bloom_lookup(struct bloom * this, char * item)
{
  int hashedItem1 = hash_string(item, BLOOM_HASH1, ((this->size)));
  int hashedItem2 = hash_string(item, BLOOM_HASH2, ((this->size)));

    int hasheditemBit1, hasheditemPos1, hasheditemBit2, hasheditemPos2;
    hasheditemBit1 = hashedItem1/32;
    hasheditemPos1 = hashedItem1%32;
    unsigned int mask1 = 1;
    mask1 = mask1 << hasheditemPos1;

    hasheditemBit2 = hashedItem2/32;
    hasheditemPos2 = hashedItem2%32;
    unsigned int mask2 = 1;
    mask2 = mask2 << hasheditemPos2;

    if((this->bit_vector->data[hasheditemBit1] & mask1) != 0) {
        if (this->bit_vector->data[hasheditemBit2] & mask2) {

          return 1;
        }
        return 0;
    }
    return 0;

}

// add a string to the set has no effect if the item is already in the
// set; note that you cannot safely remove items from a Bloom filter
void bloom_add(struct bloom * this, char * item)
{

  int hashedItem1 = hash_string(item, BLOOM_HASH1, this->size);
  int hashedItem2 = hash_string(item, BLOOM_HASH2, this->size);



  int hasheditemBit1, hasheditemPos1, hasheditemBit2, hasheditemPos2;
  hasheditemBit1 = hashedItem1/32;
  hasheditemPos1 = hashedItem1%32;
  unsigned int mask1 = 1;
  mask1 = mask1 << hasheditemPos1;

  hasheditemBit2 = hashedItem2/32;
  hasheditemPos2 = hashedItem2%32;
  unsigned int mask2 = 1;
  mask2 = mask2 << hasheditemPos2;

  this->bit_vector->data[hasheditemBit1] = this->bit_vector->data[hasheditemBit1] | mask1;
  this->bit_vector->data[hasheditemBit2] = this->bit_vector->data[hasheditemBit2] | mask2;

}



// place the union of src1 and src2 into dest
void bloom_union(struct bloom * c, struct bloom * a, struct bloom * b)
{
  for(int i=0; i<a->size; i++)
  {
    c->bit_vector->data[i] = (a->bit_vector->data[i] & b->bit_vector->data[i]);
  }

}
// place the intersection of src1 and src2 into dest
void bloom_intersect(struct bloom * c, struct bloom * a, struct bloom * b)
{
  for(int i=0; i<a->size; i++)
  {
      c->bit_vector->data[i] = (a->bit_vector->data[i] & b->bit_vector->data[i]);
  }
}


// print out the bits that are 1 in the bit vector of
// a bloom filter
void bloom_print(struct bloom * this)
{
  bitset_print(this->bit_vector);
}
