/**CFile****************************************************************

  FileName    [cecInt.h]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [Combinatinoal equivalence checking.]

  Synopsis    [External declarations.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - June 20, 2005.]

  Revision    [$Id: cecInt.h,v 1.00 2005/06/20 00:00:00 alanmi Exp $]

***********************************************************************/
 
#ifndef __CEC_INT_H__
#define __CEC_INT_H__

////////////////////////////////////////////////////////////////////////
///                          INCLUDES                                ///
////////////////////////////////////////////////////////////////////////

#include "satSolver.h"
#include "bar.h"
#include "gia.h"
#include "cec.h"

////////////////////////////////////////////////////////////////////////
///                         PARAMETERS                               ///
////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////
///                         BASIC TYPES                              ///
////////////////////////////////////////////////////////////////////////

// simulation pattern manager
typedef struct Cec_ManPat_t_ Cec_ManPat_t;
struct Cec_ManPat_t_
{
    Vec_Int_t *      vPattern1;      // pattern in terms of primary inputs
    Vec_Int_t *      vPattern2;      // pattern in terms of primary inputs
    Vec_Str_t *      vStorage;       // storage for compressed patterns
    int              iStart;         // position in the array where recent patterns begin
    int              nPats;          // total number of recent patterns
    int              nPatsAll;       // total number of all patterns
    int              nPatLits;       // total number of literals in recent patterns
    int              nPatLitsAll;    // total number of literals in all patterns
    int              nPatLitsMin;    // total number of literals in minimized recent patterns
    int              nPatLitsMinAll; // total number of literals in minimized all patterns
    int              nSeries;        // simulation series
    int              fVerbose;       // verbose stats
    // runtime statistics
    int              timeFind;       // detecting the pattern  
    int              timeShrink;     // minimizing the pattern
    int              timeVerify;     // verifying the result of minimisation
    int              timeSort;       // sorting literals 
    int              timePack;       // packing into sim info structures 
    int              timeTotal;      // total runtime  
    int              timeTotalSave;  // total runtime for saving  
};

// SAT solving manager
typedef struct Cec_ManSat_t_ Cec_ManSat_t;
struct Cec_ManSat_t_
{
    // parameters
    Cec_ParSat_t *   pPars;          
    // AIGs used in the package
    Gia_Man_t *      pAig;           // the AIG whose outputs are considered
    Vec_Int_t *      vStatus;        // status for each output
    // SAT solving
    sat_solver *     pSat;           // recyclable SAT solver
    int              nSatVars;       // the counter of SAT variables
    int *            pSatVars;       // mapping of each node into its SAT var
    Vec_Ptr_t *      vUsedNodes;     // nodes whose SAT vars are assigned
    int              nRecycles;      // the number of times SAT solver was recycled
    int              nCallsSince;    // the number of calls since the last recycle
    Vec_Ptr_t *      vFanins;        // fanins of the CNF node
    // SAT calls statistics
    int              nSatUnsat;      // the number of proofs
    int              nSatSat;        // the number of failure
    int              nSatUndec;      // the number of timeouts
    int              nSatTotal;      // the number of calls
    // conflicts
    int              nConfUnsat;
    int              nConfSat;
    int              nConfUndec;
    // runtime stats
    int              timeSatUnsat;   // unsat
    int              timeSatSat;     // sat
    int              timeSatUndec;   // undecided
    int              timeTotal;      // total runtime
};

// combinational simulation manager
typedef struct Cec_ManSim_t_ Cec_ManSim_t;
struct Cec_ManSim_t_
{
    // parameters
    Gia_Man_t *      pAig;           // the AIG to be used for simulation
    Cec_ParSim_t *   pPars;          // simulation parameters 
    int              nWords;         // the number of simulation words
    // recycable memory
    int *            pSimInfo;       // simulation information offsets
    unsigned *       pMems;          // allocated simulaton memory
    int              nWordsAlloc;    // the number of allocated entries
    int              nMems;          // the number of used entries  
    int              nMemsMax;       // the max number of used entries 
    int              MemFree;        // next free entry
    int              nWordsOld;      // the number of simulation words after previous relink
    // bug catcher
    Vec_Ptr_t *      vCiSimInfo;     // CI simulation info  
    Vec_Ptr_t *      vCoSimInfo;     // CO simulation info  
    void **          pCexes;         // counter-examples for each output
    int              iOut;           // first failed output
    int              nOuts;          // the number of failed outputs
    Gia_Cex_t *      pCexComb;       // counter-example for the first failed output
    // temporaries
    Vec_Int_t *      vClassOld;      // old class numbers
    Vec_Int_t *      vClassNew;      // new class numbers
    Vec_Int_t *      vClassTemp;     // temporary storage
    Vec_Int_t *      vRefinedC;      // refined const reprs
};

// combinational simulation manager
typedef struct Cec_ManFra_t_ Cec_ManFra_t;
struct Cec_ManFra_t_
{
    // parameters
    Gia_Man_t *      pAig;           // the AIG to be used for simulation
    Cec_ParFra_t *   pPars;          // SAT sweeping parameters 
    // simulation patterns
    Vec_Int_t *      vXorNodes;      // nodes used in speculative reduction
    int              nAllProved;     // total number of proved nodes
    int              nAllDisproved;  // total number of disproved nodes
    int              nAllFailed;     // total number of failed nodes
    // runtime stats
    int              timeSim;        // unsat
    int              timePat;        // unsat
    int              timeSat;        // sat
    int              timeTotal;      // total runtime
};

////////////////////////////////////////////////////////////////////////
///                      MACRO DEFINITIONS                           ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                    FUNCTION DECLARATIONS                         ///
////////////////////////////////////////////////////////////////////////

/*=== cecCore.c ============================================================*/
/*=== cecClass.c ============================================================*/
extern int                  Cec_ManSimClassesPrepare( Cec_ManSim_t * p );
extern int                  Cec_ManSimClassesRefine( Cec_ManSim_t * p );
extern int                  Cec_ManSimSimulateRound( Cec_ManSim_t * p, Vec_Ptr_t * vInfoCis, Vec_Ptr_t * vInfoCos );
/*=== cecIso.c ============================================================*/
extern int *                Cec_ManDetectIsomorphism( Gia_Man_t * p );
/*=== cecMan.c ============================================================*/
extern Cec_ManSat_t *       Cec_ManSatCreate( Gia_Man_t * pAig, Cec_ParSat_t * pPars );
extern void                 Cec_ManSatPrintStats( Cec_ManSat_t * p );
extern void                 Cec_ManSatStop( Cec_ManSat_t * p );
extern Cec_ManPat_t *       Cec_ManPatStart();
extern void                 Cec_ManPatPrintStats( Cec_ManPat_t * p );
extern void                 Cec_ManPatStop( Cec_ManPat_t * p );
extern Cec_ManSim_t *       Cec_ManSimStart( Gia_Man_t * pAig, Cec_ParSim_t *  pPars ); 
extern void                 Cec_ManSimStop( Cec_ManSim_t * p );  
extern Cec_ManFra_t *       Cec_ManFraStart( Gia_Man_t * pAig, Cec_ParFra_t *  pPars );  
extern void                 Cec_ManFraStop( Cec_ManFra_t * p );
/*=== cecPat.c ============================================================*/
extern void                 Cec_ManPatSavePattern( Cec_ManPat_t *  pPat, Cec_ManSat_t *  p, Gia_Obj_t * pObj );
extern Vec_Ptr_t *          Cec_ManPatCollectPatterns( Cec_ManPat_t *  pMan, int nInputs, int nWords );
/*=== cecSolve.c ============================================================*/
extern int                  Cec_ObjSatVarValue( Cec_ManSat_t * p, Gia_Obj_t * pObj );
extern void                 Cec_ManSatSolve( Cec_ManPat_t * pPat, Gia_Man_t * pAig, Cec_ParSat_t * pPars );
/*=== ceFraeep.c ============================================================*/
extern Gia_Man_t *          Cec_ManFraSpecReduction( Cec_ManFra_t * p );
extern int                  Cec_ManFraClassesUpdate( Cec_ManFra_t * p, Cec_ManSim_t * pSim, Cec_ManPat_t * pPat, Gia_Man_t * pNew );

#ifdef __cplusplus
}
#endif

#endif

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////

