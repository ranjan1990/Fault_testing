#ifndef ALL_H_
#define ALL_H_

#include<set>
#include<iostream>
#define GT 0	    //gate AND,OR,etc  
#define PI 1        // Primary Input.
#define FB 2        // Forward Branch.
#define PO 3        // Primary Output.

//if the node is gate type
#define G_PI    0   // Primary Input.
#define G_BRNCH 1   // Forward Branch.
#define G_XOR   2   // XOR Gate.
#define G_OR    3   // OR Gate.
#define G_NOR   4   // NOR Gate.
#define G_NOT   5   // NOT Gate.
#define G_NAND  6   // NAND Gate.
#define G_AND   7   // AND Gate.
#define G_XNOR  8   // XNOR Gate. Not implemented in out circuits.

//for geting the output from the matrix output 
#define ZERO    0
#define ONE     1
#define D       2
#define B       3   // This is Dbar.
#define X       4

//2 input-> output gate 

                                    //  0   1   D   B   X
int ANDTABLE[5][5]  =   {/* 0 */    {   0,  0,  0,  0,  0   },
                         /* 1 */    {   0,  1,  D,  B,  X   },
                         /* D */    {   0,  D,  D,  0,  X   },
                         /* B */    {   0,  B,  0,  B,  X   },
                         /* X */    {   0,  X,  X,  X,  X   }
                        };

                                    //  0   1   D   B   X
int NANDTABLE[5][5]  =  {/* 0 */    {   1,  1,  1,  1,  1   },
                         /* 1 */    {   1,  0,  B,  D,  X   },
                         /* D */    {   1,  B,  B,  1,  X   },
                         /* B */    {   1,  D,  1,  D,  X   },
                        };

                              //  0   1   D
int CON_LINE[3][3]={/* 0 */   {   0,  -1,  0}, 
                   /* 1 */    {   -1,  1,  1},
                   /* D */    {   0,   1,  D},
                   };

                          //  0   1   D   B   X
int ORTABLE[5][5]   =   {/* 0 */    {   0,  1,  D,  B,  X   },
                         /* 1 */    {   1,  1,  1,  1,  1   },
                         /* D */    {   D,  1,  D,  1,  X   },
                         /* B */    {   B,  1,  1,  B,  X   },
                         /* X */    {   X,  1,  X,  X,  X   }
                        };

                                    //  0   1   D   B   X
int XORTABLE[5][5]  =   {/* 0 */    {   0,  1,  D,  B,  X   },
                         /* 1 */    {   1,  0,  B,  D,  X   },
                         /* D */    {   D,  B,  0,  1,  X   },
                         /* B */    {   B,  D,  1,  0,  X   },
                         /* X */    {   X,  X,  X,  X,  X   }
                        };

                                    //  0   1   D   B   X
int XNORTABLE[5][5]  =  {/* 0 */    {   1,  0,  B,  D,  X   },
                         /* 1 */    {   0,  1,  D,  B,  X   },
                         /* D */    {   B,  D,  1,  0,  X   },
                         /* B */    {   D,  B,  0,  1,  X   },
                         /* X */    {   X,  X,  X,  X,  X   }
                        };


int NORTABLE[5][5]  =   {/* 0 */    {   1,  0,  B,  D,  X   },
                         /* 1 */    {   0,  0,  0,  0,  0   },
                         /* D */    {   B,  0,  B,  0,  X   },
                         /* B */    {   D,  0,  0,  D,  X   },
                         /* X */    {   X,  0,  X,  X,  X   }
                        };

//single input
                                    //  0   1   D   B   X
int INVTABLE [5]    =   {               1,  0,  B,  D,  X   };

                                    //  0   1   D   B   X
int BRNCHTABLE [5]  =   {               0,  1,  D,  B,  X   };

                                    //  0   1   D   B   X
int ONEXORTABLE [5] =   {               0,  0,  0,  0,  X   };



int RNAND[2][5][2]={ /*0*/ {{0,1},{1,0},{0,0},{0,D},{D,0}},
	      /*1*/ {{1,1}}
	    };

#endif




