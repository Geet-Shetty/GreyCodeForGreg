#include "pch.h"
#include "CppUnitTest.h"
#include "../GrayCode/GreyCode.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CodeTester
{
    /// <summary>
    /// Possible errors for Grey Code Sequence 
    /// </summary>
    enum Error
    {
        /// <summary>
        /// no error 
        /// </summary>
        NONE,
        /// <summary>
        /// bit change in sequence is not 1
        /// </summary>
        BITCHANGE, 
        /// <summary>
        /// duplicate number in sequence 
        /// </summary>
        DUPLICATE
    };

    /// <summary>
    /// returned by verification function 
    /// </summary>
    struct Verify
    {
        /// <summary>
        /// error check
        /// </summary>
        Error error;
        /// <summary>
        /// number is either dup or bit change amount
        /// </summary>
        uint64_t number; 
    };

    /// <summary>
    /// Verifies GreyCode Sequence, checks that sequence follow 1 bit change rule
    /// </summary>
    /// <param name="greyCode">Grey Code Sequence to check</param>
    /// <returns>true for valid grey code and false for invalid greycode</returns>
    Verify VerifyGreyCode64(GreyCode64 greyCode)
    {
        // create error info 
        Verify result{}; 
        // create set to check for duplicates
        std::set<uint64_t> gcSet{};
        // insert first element since loops starts at 1
        gcSet.insert(greyCode.sequence[0]);

        for (uint64_t i = 1; i < greyCode.sequence_len; i++)
        {
            // count how many bit changes between prev and curr elements in sequence 
            uint64_t bitChanges = 0;
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
                result.error = DUPLICATE; 
                result.number = greyCode.sequence[i]; 
            }

            // no bit changes or bit changes over 1 means generation failed 
            if (bitChanges != 1)
            {
                result.error = BITCHANGE; 
                result.number = bitChanges; 
            }
        }

        return result;
    }

    /// <summary>
    /// check if two arrays are equal
    /// </summary>
    /// <param name="array1">first array</param>
    /// <param name="array2">second array</param>
    /// <param name="len">length of both arrays</param>
    /// <returns></returns>
    bool ArrayEqual(uint64_t* array1, uint64_t* array2, uint64_t len)
    {
        for (uint64_t i = 0; i < len; i++)
        {
            if (array1[i] != array2[i])
            {
                return false; 
            }
        }
        return true; 
    }

	TEST_CLASS(CodeTester64)
	{
	public:
		TEST_METHOD(GreyCode64_1bit)
		{
			GreyCode64 gc = GreyCode(1); 
            
            // checks 
            bool check_nbits = gc.nbits == 1;
            bool check_len = gc.sequence_len == 2; 

            uint64_t seq[] = {0, 1};
            bool check_seq = ArrayEqual(seq, gc.sequence, gc.sequence_len); 

            Verify result = VerifyGreyCode64(gc); 

            Assert::AreEqual(true, check_nbits && check_len && check_seq); 
            Assert::AreEqual(true, result.error == NONE && result.number == 0); 
		}

        TEST_METHOD(GreyCode64_2bit)
        {
            GreyCode64 gc = GreyCode(2);

            // checks 
            bool check_nbits = gc.nbits == 2;
            bool check_len = gc.sequence_len == 4;

            uint64_t seq[] = { 0, 1, 3, 2};
            bool check_seq = ArrayEqual(seq, gc.sequence, gc.sequence_len);

            Verify result = VerifyGreyCode64(gc);

            Assert::AreEqual(true, check_nbits && check_len && check_seq);
            Assert::AreEqual(true, result.error == NONE && result.number == 0);
        }

        TEST_METHOD(GreyCode64_3bit)
        {
            GreyCode64 gc = GreyCode(3);

            // checks 
            bool check_nbits = gc.nbits == 3;
            bool check_len = gc.sequence_len == 8;

            uint64_t seq[] = { 0, 1, 3, 2, 6, 7, 5, 4 };
            bool check_seq = ArrayEqual(seq, gc.sequence, gc.sequence_len);

            Verify result = VerifyGreyCode64(gc);

            Assert::AreEqual(true, check_nbits && check_len && check_seq);
            Assert::AreEqual(true, result.error == NONE && result.number == 0);
        }


        TEST_METHOD(GreyCode64_4bit)
        {
            GreyCode64 gc = GreyCode(4);

            // checks 
            bool check_nbits = gc.nbits == 4;
            bool check_len = gc.sequence_len == 16;

            uint64_t seq[] = { 0, 1, 3, 2, 6, 7, 5, 4, 12, 13, 15, 14, 10, 11, 9, 8 };
            bool check_seq = ArrayEqual(seq, gc.sequence, gc.sequence_len);

            Verify result = VerifyGreyCode64(gc);

            Assert::AreEqual(true, check_nbits && check_len && check_seq);
            Assert::AreEqual(true, result.error == NONE && result.number == 0);
        }

        TEST_METHOD(GreyCode64_5bit)
        {
            GreyCode64 gc = GreyCode(5);

            // checks 
            bool check_nbits = gc.nbits == 5;
            bool check_len = gc.sequence_len == 32;

            uint64_t seq[] = { 
                0, 1, 3, 2, 6, 7, 5, 4, 12, 13, 15, 14, 10, 11, 9, 8, 
                24, 25, 27, 26, 30, 31, 29, 28, 20, 21, 23, 22, 18, 19, 17, 16
            };
            bool check_seq = ArrayEqual(seq, gc.sequence, gc.sequence_len);

            Verify result = VerifyGreyCode64(gc);

            Assert::AreEqual(true, check_nbits && check_len && check_seq);
            Assert::AreEqual(true, result.error == NONE && result.number == 0);
        }

        TEST_METHOD(GreyCode64_24bit)
        {
            GreyCode64 gc = GreyCode(24);

            // checks 
            bool check_nbits = gc.nbits == 24;
            bool check_len = gc.sequence_len == (1 << 24); // 2^24

            Verify result = VerifyGreyCode64(gc);

            Assert::AreEqual(true, check_nbits && check_len);
            Assert::AreEqual(true, result.error == NONE && result.number == 0);
        }
	};
}
