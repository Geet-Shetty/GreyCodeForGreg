// GrayCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <set>

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
GreyCodeSequence GreyCode(uint8_t n)
{
    // set up information for return value
    GreyCodeSequence gcSeq{}; 

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
        uint64_t seq_len = (uint64_t)pow(2, i + 1);
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

/// <summary>
/// Verifies GreyCode Sequence, checks that sequence follow 1 bit change rule
/// </summary>
/// <param name="greyCode">Grey Code Sequence to check</param>
/// <returns>true for valid grey code and false for invalid greycode</returns>
bool VerifyGreyCode(GreyCodeSequence greyCode)
{
    // create set to check for duplicates
    std::set<uint64_t> gcSet{};
    // insert first element since loops starts at 1
    gcSet.insert(greyCode.sequence[0]); 

    for (uint64_t i = 1; i < greyCode.sequence_len; i++)
    {
        // count how many bit changes between prev and curr elements in sequence 
        int bitChanges = 0;
        for (uint64_t j = 0; j < greyCode.nbits; j++)
        {
            uint64_t curr_masked = greyCode.sequence[i] & (1i64 << j); 
            uint64_t prev_masked = greyCode.sequence[i - 1] & (1i64 << j);

            if (curr_masked ^ prev_masked)
            {
                bitChanges++; 
            }
        }

        // duplicate found 
        if (!gcSet.insert(greyCode.sequence[i]).second)
        {
            return false; 
        }

        // bit changes over 1 means generation failed 
        if (bitChanges != 1)
        {
            //std::cout << "Bitchanges: " << bitChanges << std::endl;
            return false; 
        }
    }

    return true; 
}

int main()
{
    GreyCodeSequence greyCode = GreyCode(3); 

    for (uint64_t i = 0; i < greyCode.sequence_len; i++)
    {
        std::cout << greyCode.sequence[i] << std::endl; 
    }

    if (VerifyGreyCode(greyCode))
    {
        std::cout << "WORKED" << std::endl;
    }

    std::cout << "==============================" << std::endl;

    GreyCodeSequence test{}; 
    test.nbits = 3; 
    test.sequence_len = 8; 
    uint64_t array[] = {1,1,1,1,1,1,1,1};
    test.sequence = array; 

    if (VerifyGreyCode(test))
    {
        std::cout << ":(" << std::endl;
    }
    else
    {
        std::cout << ":)" << std::endl;
    }

    int x; 
    std::cin >> x; 
}

