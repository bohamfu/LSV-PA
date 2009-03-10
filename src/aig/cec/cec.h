/**CFile****************************************************************

  FileName    [cec.h]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [Combinatinoal equivalence checking.]

  Synopsis    [External declarations.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - June 20, 2005.]

  Revision    [$Id: cec.h,v 1.00 2005/06/20 00:00:00 alanmi Exp $]

***********************************************************************/
 
#ifndef __CEC_H__
#define __CEC_H__

////////////////////////////////////////////////////////////////////////
///                          INCLUDES                                ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                         PARAMETERS                               ///
////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////
///                         BASIC TYPES                              ///
////////////////////////////////////////////////////////////////////////

// dynamic SAT parameters
typedef struct Cec_ParSat_t_ Cec_ParSat_t;
struct Cec_ParSat_t_
{
    int              nBTLimit;      // conflict limit at a node
    int              nSatVarMax;    // the max number of SAT variables
    int              nCallsRecycle; // calls to perform before recycling SAT solver
    int              fPolarFlip;    // flops polarity of variables
    int              fCheckMiter;   // the circuit is the miter
    int              fFirstStop;    // stop on the first sat output
    int              fVerbose;      // verbose stats
};

// simulation parameters
typedef struct Cec_ParSim_t_ Cec_ParSim_t;
struct Cec_ParSim_t_
{
    int              nWords;        // the number of simulation words
    int              nRounds;       // the number of simulation rounds
    int              TimeLimit;     // the runtime limit in seconds
    int              fDoubleOuts;   // miter with separate outputs
    int              fCheckMiter;   // the circuit is the miter
    int              fFirstStop;    // stop on the first sat output
    int              fSeqSimulate;  // performs sequential simulation
    int              fVeryVerbose;  // verbose stats
    int              fVerbose;      // verbose stats
};

// combinational SAT sweeping parameters
typedef struct Cec_ParFra_t_ Cec_ParFra_t;
struct Cec_ParFra_t_
{
    int              nWords;        // the number of simulation words
    int              nRounds;       // the number of simulation rounds
    int              nItersMax;     // the maximum number of iterations of SAT sweeping
    int              nBTLimit;      // conflict limit at a node
    int              TimeLimit;     // the runtime limit in seconds
    int              nLevelMax;     // restriction on the level nodes to be swept
    int              nDepthMax;     // the depth in terms of steps of speculative reduction
    int              fRewriting;    // enables AIG rewriting
    int              fCheckMiter;   // the circuit is the miter
    int              fFirstStop;    // stop on the first sat output
    int              fDoubleOuts;   // miter with separate outputs
    int              fColorDiff;    // miter with separate outputs
    int              fVeryVerbose;  // verbose stats
    int              fVerbose;      // verbose stats
};

// combinational equivalence checking parameters
typedef struct Cec_ParCec_t_ Cec_ParCec_t;
struct Cec_ParCec_t_
{
    int              nBTLimit;      // conflict limit at a node
    int              TimeLimit;     // the runtime limit in seconds
    int              fFirstStop;    // stop on the first sat output
    int              fUseSmartCnf;  // use smart CNF computation
    int              fRewriting;    // enables AIG rewriting
    int              fVeryVerbose;  // verbose stats
    int              fVerbose;      // verbose stats
};

////////////////////////////////////////////////////////////////////////
///                      MACRO DEFINITIONS                           ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                    FUNCTION DECLARATIONS                         ///
////////////////////////////////////////////////////////////////////////

/*=== cecCec.c ==========================================================*/
extern int           Cec_ManVerify( Gia_Man_t * p, Cec_ParCec_t * pPars );
extern int           Cec_ManVerifyTwo( Gia_Man_t * p0, Gia_Man_t * p1, int fVerbose );
/*=== cecCore.c ==========================================================*/
extern void          Cec_ManSatSetDefaultParams( Cec_ParSat_t * p );
extern void          Cec_ManSimSetDefaultParams( Cec_ParSim_t * p );
extern void          Cec_ManFraSetDefaultParams( Cec_ParFra_t * p );
extern void          Cec_ManCecSetDefaultParams( Cec_ParCec_t * p );
extern Gia_Man_t *   Cec_ManSatSweeping( Gia_Man_t * pAig, Cec_ParFra_t * pPars );
extern Gia_Man_t *   Cec_ManSatSolving( Gia_Man_t * pAig, Cec_ParSat_t * pPars );
extern void          Cec_ManSimulation( Gia_Man_t * pAig, Cec_ParSim_t * pPars );

#ifdef __cplusplus
}
#endif

#endif

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////

