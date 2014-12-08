#include<L1_api.h>

/** 
 * This structure represents the seed to be used to generate pseudo random numbers.
 */
typedef struct{
	L1_UINT32 m_z;
	L1_UINT32 m_w;
} L1_prngSeed;


 /**
 * Initialises the seed for the pseudo random number generator.
 *
 * @param self this points to a L1_prngSeed structure, which will be read and modifed in the process.
 * @param seed the seed used to initialise the L1_prngSeed structure.
 * @return L1_STATUS
 *   - RC_OK If the random number could be calculated.
 *   - RC_FAIL If any of the given pointers was NULL.
 */
L1_Status L1_prngInitWithSeed(L1_prngSeed* self, L1_UINT32 seed);

/**
 * Initialises the seed for the pseudo random number generator.
 *
 * @param self this points to a L1_prngSeed structure, which will be read and modifed in the process.
 * @return L1_STATUS
 * 		- RC_OK If the random number could be calculated.
 *  	- RC_FAIL If any of the given pointers was NULL.
 */
L1_Status L1_prngInit(L1_prngSeed* self);

/**
 * Generates the next 32 bit unsigned integer value from the seed.
 *
 * @param self this points to a L1_prngSeed structure, which will be read and modifed in the process.
 * @param pResult pointer to a variable of type L1_UINT32. After this function returns the generated random number is stored in this varaible.
 * @return L1_STATUS
 * 		- RC_OK If the random number could be calculated.
 *  	- RC_FAIL If any of the given pointers was NULL.
 */
L1_Status L1_prngGetNextUINT32(L1_prngSeed* self, L1_UINT32* pResult);


