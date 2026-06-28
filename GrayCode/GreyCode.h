#pragma once


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
GreyCodeSequence GreyCode(uint8_t n); 

/// <summary>
/// Verifies GreyCode Sequence, checks that sequence follow 1 bit change rule
/// </summary>
/// <param name="greyCode">Grey Code Sequence to check</param>
/// <returns>true for valid grey code and false for invalid greycode</returns>
bool VerifyGreyCode(GreyCodeSequence greyCode); 