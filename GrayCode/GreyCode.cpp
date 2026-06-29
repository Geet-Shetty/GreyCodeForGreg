#include <set>
#include "GreyCode.h"

GreyCode64 GreyCode(uint8_t n)
{
    // set up information for return value
    GreyCode64 gcSeq{}; 

    // can't go above 64 bits with uint64_t
    // n = 64 needs so much space so not allowed so bit shifting works
    // realistically after even around 
    if (n > 63)
    {
        // explicitly set values just in case :P
        gcSeq.sequence = nullptr; 
        gcSeq.sequence_len = 0; 
        gcSeq.nbits = 0; 
        return gcSeq; 
    }
    
    // used pow instead of shift because for n = 64 would need 65 bits 
    // could use shift until 64 but honestly timed saved doesn't matter
    gcSeq.sequence_len = (uint64_t)pow(2,n);
    gcSeq.nbits = n; 

    // hardcode n = 1 sequence: 0 and 1 
    uint64_t* prev_seq = new uint64_t[2]();
    prev_seq[1] = 1; 
    uint64_t prev_seq_len = 2; 

    // each sequence is built from the previous one
    for (uint64_t i = 1; i < (uint64_t)n; i++)
    {
        // create next sequence list 
        uint64_t seq_len = (uint64_t)pow(2, (double)(i + 1));
        uint64_t* seq = new uint64_t[seq_len](); 

        // create MSB zero section 
        uint64_t j = 0; 
        for (;j < prev_seq_len && seq_len == (2 * prev_seq_len); j++)
        {
            // copy previous sequence 
            seq[j] = prev_seq[j];
        }

        // the mid point 
        uint64_t index = j; 

        // create MSB one section 
        uint64_t k = prev_seq_len - 1; 
        do
        {
            // copy previous sequence in reverse and shift one at n
            if (index < seq_len)
            {
                seq[index] = prev_seq[k] | (1i64 << i);
            }

            index++; 
            k--; 
        } 
        while (k > 0);

        // do while exits before last element 
        if (index == seq_len - 1)
        {
            seq[index] = prev_seq[k] | (1i64 << i);
        }

        // update previous sequence 
        prev_seq = seq; 
        prev_seq_len = seq_len; 
    }

    // set return value 
    gcSeq.sequence = prev_seq; 

    return gcSeq;
}

