#ifndef SAMTABS_H
#define SAMTABS_H

#include "sam_debug.h"
#include "sam_pgmspace.h"

//tab40672
const unsigned char stressInputTable[] PROGMEM =
{
	'*', '1', '2', '3', '4', '5', '6', '7', '8'
};

//tab40682
const unsigned char signInputTable1[] PROGMEM =
{
	' ', '.', '?', ',', '-', 'I', 'I', 'E',
	'A', 'A', 'A', 'A', 'U', 'A', 'I', 'E',
	'U', 'O', 'R', 'L', 'W', 'Y', 'W', 'R',
	'L', 'W', 'Y', 'M', 'N', 'N', 'D', 'Q',
	'S', 'S', 'F', 'T', '/', '/', 'Z', 'Z',
	'V', 'D', 'C', '*', 'J', '*', '*', '*',
	'E', 'A', 'O', 'A', 'O', 'U', 'B', '*',
	'*', 'D', '*', '*', 'G', '*', '*', 'G',
	'*', '*', 'P', '*', '*', 'T', '*', '*',
	'K', '*', '*', 'K', '*', '*', 'U', 'U',
	'U'
};

//tab40763
const unsigned char signInputTable2[] PROGMEM =
{
	'*', '*', '*', '*', '*', 'Y', 'H', 'H',
	'E', 'A', 'H', 'O', 'H', 'X', 'X', 'R',
	'X', 'H', 'X', 'X', 'X', 'X', 'H', '*',
	'*', '*', '*', '*', '*', 'X', 'X', '*',
	'*', 'H', '*', 'H', 'H', 'X', '*', 'H',
	'*', 'H', 'H', '*', '*', '*', '*', '*',
	'Y', 'Y', 'Y', 'W', 'W', 'W', '*', '*',
	'*', '*', '*', '*', '*', '*', '*', 'X',
	'*', '*', '*', '*', '*', '*', '*', '*',
	'*', '*', '*', 'X', '*', '*', 'L', 'M',
	'N'
};

//loc_9F8C
const unsigned char flags[]={
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0xA4 , 0xA4 , 0xA4 ,
	0xA4 , 0xA4 , 0xA4 , 0x84 , 0x84 , 0xA4 , 0xA4 , 0x84 ,
	0x84 , 0x84 , 0x84 , 0x84 , 0x84 , 0x84 , 0x44 , 0x44 ,
	0x44 , 0x44 , 0x44 , 0x4C , 0x4C , 0x4C , 0x48 , 0x4C ,
	0x40 , 0x40 , 0x40 , 0x40 , 0x40 , 0x40 , 0x44 , 0x44 ,
	0x44 , 0x44 , 0x48 , 0x40 , 0x4C , 0x44 , 0x00 , 0x00 ,
	0xB4 , 0xB4 , 0xB4 , 0x94 , 0x94 , 0x94 , 0x4E , 0x4E ,
	0x4E , 0x4E , 0x4E , 0x4E , 0x4E , 0x4E , 0x4E , 0x4E ,
	0x4E , 0x4E , 0x4B , 0x4B , 0x4B , 0x4B , 0x4B , 0x4B ,
	0x4B , 0x4B , 0x4B , 0x4B , 0x4B , 0x4B , 0x80 , 0xC1 ,
	0xC1


};

//??? flags overlap flags2
//loc_9FDA
const unsigned char flags2[] =
{
	0x80 , 0xC1 , 0xC1 , 0xC1 , 0xC1 , 0x00 , 0x00 , 0x00 ,
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x10 ,
	0x10 , 0x10 , 0x10 , 0x08 , 0x0C , 0x08 , 0x04 , 0x40 ,
	0x24 , 0x20 , 0x20 , 0x24 , 0x00 , 0x00 , 0x24 , 0x20 ,
	0x20 , 0x24 , 0x20 , 0x20 , 0x00 , 0x20 , 0x00 , 0x00 ,
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
	0x00 , 0x04 , 0x04 , 0x04 , 0x00 , 0x00 , 0x00 , 0x00 ,
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x04 , 0x04 , 0x04 ,
	0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00
};



//tab45616???
const unsigned char phonemeStressedLengthTable[] PROGMEM =
{
	0x00 , 0x12 , 0x12 , 0x12 , 8 ,0xB , 9 ,0xB ,
	0xE ,0xF ,0xB , 0x10 ,0xC , 6 , 6 ,0xE ,
	0xC ,0xE ,0xC ,0xB , 8 , 8 ,0xB ,0xA ,
	9 , 8 , 8 , 8 , 8 , 8 , 3 , 5 ,
	2 , 2 , 2 , 2 , 2 , 2 , 6 , 6 ,
	8 , 6 , 6 , 2 , 9 , 4 , 2 , 1 ,
	0xE ,0xF ,0xF ,0xF ,0xE ,0xE , 8 , 2 ,
	2 , 7 , 2 , 1 , 7 , 2 , 2 , 7 ,
	2 , 2 , 8 , 2 , 2 , 6 , 2 , 2 ,
	7 , 2 , 4 , 7 , 1 , 4 , 5 , 5
};

//tab45536???
const unsigned char phonemeLengthTable[] PROGMEM =
{
	0 , 0x12 , 0x12 , 0x12 , 8 , 8 , 8 , 8 ,
	8 ,0xB , 6 ,0xC ,0xA , 5 , 5 ,0xB ,
	0xA ,0xA ,0xA , 9 , 8 , 7 , 9 , 7 ,
	6 , 8 , 6 , 7 , 7 , 7 , 2 , 5 ,
	2 , 2 , 2 , 2 , 2 , 2 , 6 , 6 ,
	7 , 6 , 6 , 2 , 8 , 3 , 1 , 0x1E ,
	0xD ,0xC ,0xC ,0xC ,0xE , 9 , 6 , 1 ,
	2 , 5 , 1 , 1 , 6 , 1 , 2 , 6 ,
	1 , 2 , 8 , 2 , 2 , 4 , 2 , 2 ,
	6 , 1 , 4 , 6 , 1 , 4 , 0xC7 , 0xFF
};



/*

Ind  | phoneme |  flags   |
-----|---------|----------|
0    |   *     | 00000000 |
1    |  .*     | 00000000 |
2    |  ?*     | 00000000 |
3    |  ,*     | 00000000 |
4    |  -*     | 00000000 |

VOWELS
5    |  IY     | 10100100 |
6    |  IH     | 10100100 |
7    |  EH     | 10100100 |
8    |  AE     | 10100100 |
9    |  AA     | 10100100 |
10   |  AH     | 10100100 |
11   |  AO     | 10000100 |
17   |  OH     | 10000100 |
12   |  UH     | 10000100 |
16   |  UX     | 10000100 |
15   |  ER     | 10000100 |
13   |  AX     | 10100100 |
14   |  IX     | 10100100 |

DIPHTONGS
48   |  EY     | 10110100 |
49   |  AY     | 10110100 |
50   |  OY     | 10110100 |
51   |  AW     | 10010100 |
52   |  OW     | 10010100 |
53   |  UW     | 10010100 |


21   |  YX     | 10000100 |
20   |  WX     | 10000100 |
18   |  RX     | 10000100 |
19   |  LX     | 10000100 |
37   |  /X     | 01000000 |
30   |  DX     | 01001000 |


22   |  WH     | 01000100 |


VOICED CONSONANTS
23   |  R*     | 01000100 |
24   |  L*     | 01000100 |
25   |  W*     | 01000100 |
26   |  Y*     | 01000100 |
27   |  M*     | 01001100 |
28   |  N*     | 01001100 |
29   |  NX     | 01001100 |
54   |  B*     | 01001110 |
57   |  D*     | 01001110 |
60   |  G*     | 01001110 |
44   |  J*     | 01001100 |
38   |  Z*     | 01000100 |
39   |  ZH     | 01000100 |
40   |  V*     | 01000100 |
41   |  DH     | 01000100 |

unvoiced CONSONANTS
32   |  S*     | 01000000 |
33   |  SH     | 01000000 |
34   |  F*     | 01000000 |
35   |  TH     | 01000000 |
66   |  P*     | 01001011 |
69   |  T*     | 01001011 |
72   |  K*     | 01001011 |
42   |  CH     | 01001000 |
36   |  /H     | 01000000 |

43   |  **     | 01000000 |
45   |  **     | 01000100 |
46   |  **     | 00000000 |
47   |  **     | 00000000 |


55   |  **     | 01001110 |
56   |  **     | 01001110 |
58   |  **     | 01001110 |
59   |  **     | 01001110 |
61   |  **     | 01001110 |
62   |  **     | 01001110 |
63   |  GX     | 01001110 |
64   |  **     | 01001110 |
65   |  **     | 01001110 |
67   |  **     | 01001011 |
68   |  **     | 01001011 |
70   |  **     | 01001011 |
71   |  **     | 01001011 |
73   |  **     | 01001011 |
74   |  **     | 01001011 |
75   |  KX     | 01001011 |
76   |  **     | 01001011 |
77   |  **     | 01001011 |


SPECIAL
78   |  UL     | 10000000 |
79   |  UM     | 11000001 |
80   |  UN     | 11000001 |
31   |  Q*     | 01001100 |

*/

#endif
