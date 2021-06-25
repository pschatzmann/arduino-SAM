#ifndef DEBUG_H
#define DEBUG_H
#include "sam_config.h"

#ifdef __cplusplus
extern "C" {
#endif

void PrintPhonemes(unsigned char *phonemeindex, unsigned char *phonemeLength, unsigned char *stress);
void PrintOutput(
	unsigned char *flag, 
	unsigned char *f1, 
	unsigned char *f2, 
	unsigned char *f3,
	unsigned char *a1, 
	unsigned char *a2, 
	unsigned char *a3,
	unsigned char *p);

void PrintRule(unsigned short offset);

#ifdef __cplusplus
}
#endif

#endif
