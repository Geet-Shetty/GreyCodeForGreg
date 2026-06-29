#pragma once

/// <summary>
/// All data for Grey Code Sequence 32 bits
/// </summary>
struct GreyCode32
{
    /// <summary>
    /// the actual Grey Code Sequence 
    /// </summary>
    uint32_t * sequence;
    /// <summary>
    /// the length of the array
    /// </summary>
    uint32_t sequence_len;
    /// <summary>
    /// how many bits where specified (Max: 31)
    /// </summary>
    uint8_t nbits;
};

/// <summary>
/// All data for Grey Code Sequence 64 bits
/// </summary>
struct GreyCode64
{
    /// <summary>
    /// the actual Grey Code Sequence 
    /// </summary>
    uint64_t* sequence;
    /// <summary>[pl
    /// the length of the array
    /// </summary>
    uint64_t sequence_len;
    /// <summary>
    /// how many bits where specified (Max: 63)
    /// </summary>
    uint8_t nbits;
};

/// <summary>
/// Generates n-bit Grey Code Sequence  
/// </summary>
/// <param name="n">number of bits</param>
/// <returns>Grey Code Sequence</returns>
GreyCode64 GreyCode(uint8_t n); 