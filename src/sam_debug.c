#include <stdio.h>
#include "sam_config.h"

char log_buffer_sam[LOG_BUFFER_LEN] = {0};
extern unsigned char signInputTable1[];
extern unsigned char signInputTable2[];

void PrintPhonemes(unsigned char *phonemeindex, unsigned char *phonemeLength, unsigned char *stress)
{
	int i = 0;
	SAM_LOG("===========================================");

	SAM_LOG("Internal Phoneme presentation:");
	SAM_LOG(" idx    phoneme  length  stress");
	SAM_LOG("------------------------------");

	while((phonemeindex[i] != 255) && (i < 255))
	{
		if (phonemeindex[i] < 81)
		{
			SAM_LOG(" %3i      %c%c      %3i       %i",
			phonemeindex[i],
			signInputTable1[phonemeindex[i]],
			signInputTable2[phonemeindex[i]],
			phonemeLength[i],
			stress[i]
			);
		} else
		{
			SAM_LOG(" %3i      ??      %3i       %i", phonemeindex[i], phonemeLength[i], stress[i]);
		}
		i++;
	}
	SAM_LOG("===========================================");
	SAM_LOG("");
}

void PrintOutput(
	unsigned char *flag, 
	unsigned char *f1, 
	unsigned char *f2, 
	unsigned char *f3,
	unsigned char *a1, 
	unsigned char *a2, 
	unsigned char *a3,
	unsigned char *p)
{
	int i = 0;
	SAM_LOG("===========================================");
	SAM_LOG("Final data for speech output:");
	SAM_LOG(" flags ampl1 freq1 ampl2 freq2 ampl3 freq3 pitch");
	SAM_LOG("------------------------------------------------");
	while(i < 255)
	{
		SAM_LOG("%5i %5i %5i %5i %5i %5i %5i %5i", flag[i], a1[i], f1[i], a2[i], f2[i], a3[i], f3[i], p[i]);
		i++;
	}
	SAM_LOG("===========================================");

}

extern unsigned char GetRuleByte(unsigned short mem62, unsigned char Y);

void PrintRule(unsigned short offset)
{
	unsigned char i = 1;
	unsigned char A = 0;
	SAM_LOG("Applying rule: ");
	do
	{
		A = GetRuleByte(offset, i);
		if ((A&127) == '=') {
			SAM_LOG(" -> ");
		} else{
		 	SAM_LOG("%c", A&127);
		}
		i++;
	} while ((A&128)==0);
	SAM_LOG("");
}
