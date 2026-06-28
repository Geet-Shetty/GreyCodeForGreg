// GrayCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

/// <summary>
/// All data for Grey Code Sequence
/// sequence: the actual Grey Code Sequence 
/// sequence_len: the length of the array
/// nbits: how many bits where specified 
/// </summary>
struct GreyCodeSequence
{
    uint64_t* sequence; 
    uint64_t sequence_len; 
    uint8_t nbits;

};

/// <summary>
/// Generates n-bit Grey Code Sequence  
/// </summary>
/// <param name="n">number of bits</param>
/// <returns>Grey Code Sequence</returns>
static GreyCodeSequence GreyCode(uint8_t n)
{
    // add logic to have range for n? 
    // switch to using shifts for pow ops
    
    // set up information for return value
    GreyCodeSequence gcSeq{}; 
    gcSeq.sequence_len = (uint64_t)pow(2,n);
    gcSeq.nbits = n; 

    // hardcode n = 1 sequence: 0 and 1 
    uint64_t* prev_seq = new uint64_t[2]();
    prev_seq[1] = 1; 
    uint64_t prev_seq_len = 2; 

    for (uint64_t i = 1; i < (uint64_t)n; i++)
    {
        // create next sequence list 
        uint64_t seq_len = (uint64_t)pow(2, i + 1);
        uint64_t* seq = new uint64_t[seq_len](); 

        uint64_t j = 0; 
        for (;j < prev_seq_len && seq_len == (2 * prev_seq_len); j++)
        {
            // copy previous sequence 
            seq[j] = prev_seq[j];
        }

        // the mid point 
        uint64_t index = j; 

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
        if (index == seq_len - 1)
        {
            seq[index] = prev_seq[k] | (1i64 << i);
        }

        prev_seq = seq; 
        prev_seq_len = seq_len; 
    }

    gcSeq.sequence = prev_seq; 

    return gcSeq;
}

int main()
{
    GreyCodeSequence greyCode = GreyCode(4); 

    for (uint64_t i = 0; i < greyCode.sequence_len; i++)
    {
        std::cout << greyCode.sequence[i] << std::endl; 
    }

    int x; 
    std::cin >> x; 
}

