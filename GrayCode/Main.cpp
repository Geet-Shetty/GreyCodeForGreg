#include <iostream>
#include <fstream>
#include <bitset>
#include "GreyCode.h"

#define NBIT 24
#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

int main()
{
    //GreyCode64 greyCode = GreyCode(NBIT);

    //bool printFlag = false; 
    //if (printFlag)
    //{
    //    for (uint64_t i = 0; i < greyCode.sequence_len; i++)
    //    {
    //        std::string binary = std::bitset<NBIT>(greyCode.sequence[i]).to_string(); //to binary
    //        std::cout << binary << " | " << greyCode.sequence[i] << std::endl;
    //    }
    //}

    // use leetcode version so binary writes as 32 bit without cast 
    std::vector<int> sequence = greycodeLeetCode(NBIT);

    // write to file 
    bool writeFlag = true; 
    if (writeFlag)
    {
        std::ofstream file("SeqFiles\\GreyCode_" TO_STRING(NBIT) "_bits.bin", std::ios::out | std::ios::binary);

        if (!file) {
            std::cerr << "Error opening file!" << std::endl;
            return 0;
        }

        for (int i = 0; i < sequence.size(); i++)
        {
            file.write(reinterpret_cast<const char*>(&sequence[i]), sizeof(int));
        }

        file.close();
    }

    std::cout << "==============================" << std::endl; 

    int x;
    std::cin >> x;
}
