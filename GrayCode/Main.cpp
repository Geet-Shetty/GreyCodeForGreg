#include <iostream>
#include <bitset>
#include "GreyCode.h"

#define NBIT 3

int main()
{
    GreyCode64 greyCode = GreyCode(NBIT);

    for (uint64_t i = 0; i < greyCode.sequence_len; i++)
    {
        std::string binary = std::bitset<NBIT>(greyCode.sequence[i]).to_string(); //to binary
        std::cout << binary << " | " << greyCode.sequence[i] << std::endl;
    }

    std::cout << "==============================" << std::endl; 

    int x;
    std::cin >> x;
}
