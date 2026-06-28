#include <iostream>
#include "GreyCode.h"

int main()
{
    GreyCodeSequence greyCode = GreyCode(5);

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
    uint64_t array[] = { 1,1,1,1,1,1,1,1 };
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
