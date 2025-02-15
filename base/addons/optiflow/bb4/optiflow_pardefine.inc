*File of parameters that only specific with OptiFlow, and not dependant on Balmorel

*-------------------------------------------------------------------------------
* GEOGRAPHY:
*-------------------------------------------------------------------------------
SET AAAOPTIFLOW(AAA)    'Areas that are for OptiFlow Addon'  %semislash%
$if     EXIST '../data/OPTIFLOW_AAAOPTIFLOW.inc' $INCLUDE         '../data/OPTIFLOW_AAAOPTIFLOW.inc';
$if not EXIST '../data/OPTIFLOW_AAAOPTIFLOW.inc' $INCLUDE '../../base/data/OPTIFLOW_AAAOPTIFLOW.inc';
%semislash%;

SET AAATRANSIT(AAA)   'Areas that are for waste transit only';
SET AAAIMPORT(AAA)    'Areas that are for waste import only';
ALIAS (AAATRANSIT,IATRANSITE,IATRANSITI);

SET AAATRANSIT(AAA)   'Areas that are for waste transit only'   %semislash%
$if     EXIST '../data/OPTIFLOW_AAATRANSIT.inc' $INCLUDE         '../data/OPTIFLOW_AAATRANSIT.inc';
$if not EXIST '../data/OPTIFLOW_AAATRANSIT.inc' $INCLUDE '../../base/data/OPTIFLOW_AAATRANSIT.inc';
%semislash%;

SET AAAIMPORT(AAA)    'Areas that are for waste import only'  %semislash%
$if     EXIST '../data/OPTIFLOW_AAAIMPORT.inc' $INCLUDE         '../data/OPTIFLOW_AAAIMPORT.inc';
$if not EXIST '../data/OPTIFLOW_AAAIMPORT.inc' $INCLUDE '../../base/data/OPTIFLOW_AAAIMPORT.inc';
%semislash%;

SET AAASOURCE(AAA)    'Areas that are for OptiFlow Addon for availability of resources only'  %semislash%
$if     EXIST '../data/OPTIFLOW_AAASOURCE.inc' $INCLUDE         '../data/OPTIFLOW_AAASOURCE.inc';
$if not EXIST '../data/OPTIFLOW_AAASOURCE.inc' $INCLUDE '../../base/data/OPTIFLOW_AAASOURCE.inc';
%semislash%;

*-------------------------------------------------------------------------------
* TIME:
*-------------------------------------------------------------------------------


* Set T(TTT)  specifies the time resolution of the Seasons SSS, intended for use with the energy system parts.
* Set ITWWT(T) specifies the time resolution for use with the waste system parts.
* ITWWT shall have one one element.
SET ITWWT(T) "Time periods within the season in the simulation - waste system"
/  T001 /;


ALIAS (Y,IYALIAS,IY402,Y403);

SET IY411(Y)                'IY411 The years in current model';
SET IY410(Y)                'IY410 The years in the current model except the last year' ;
SET IY401(Y)                'IY401 The years in the current model except the first year';
SET IYFIRST(Y)              "The first year in Y";
PARAMETER IY4REMAINY(Y)     "The number of remaining years in Y in the current model";
PARAMETER IY4XREMAINY(Y)    "The number of remaining years in Y for new transmission line in the current model";
SET IY411NEXTY(Y,Y)         "For any given element in IY411 (index 1): the next element in Y (index 2)";
SET IY411PREVY(Y,Y)         "For any given element in IY411 (index 1): the previous element in Y (index 2)";
IY411(Y) = YES;
*IY411PREVY(IYALIAS,IYALIAS-1) = YES;
IY401(Y) = YES;

LOOP(Y$(ORD(Y) EQ 1), IY401(Y) = NO;);
IY410(Y) = YES;
LOOP(Y$(ORD(Y) EQ CARD(Y)), IY410(Y) = NO;);
IYFIRST(Y)$(ORD(Y) EQ 1) = YES;

SCALAR IWEIGHSUMTWWT;
PARAMETER IHOURSINSTWWT(SSS,T)   'Length of time ST-segments (hours)';

PARAMETER IWEIGHSUMS  'Weight of the time of each season';
IWEIGHSUMS = SUM(S, WEIGHT_S(S));

PARAMETER IWEIGHSUMT  'Weight of the time of each time period';
IWEIGHSUMT = SUM(T, WEIGHT_T(T));


IWEIGHSUMTWWT = SUM(ITWWT, WEIGHT_T(ITWWT));
IHOURSINSTWWT(S,T) = IOF8760 * (WEIGHT_S(S)/IWEIGHSUMS)*(WEIGHT_T(T)/IWEIGHSUMTWWT);

PARAMETER IHOURSINST(SSS,TTT)   'Length of time segment (hours)';
IHOURSINST(S,T)=IOF8760*WEIGHT_S(S)*WEIGHT_T(T)/(IWEIGHSUMS*IWEIGHSUMT);

PARAMETER TIMELENGHT(TTT) 'Time lenght of each time slice'   %semislash%
$if     EXIST '../data/OPTIFLOW_TIMELENGHT.inc' $INCLUDE         '../data/OPTIFLOW_TIMELENGHT.inc';
$if not EXIST '../data/OPTIFLOW_TIMELENGHT.inc' $INCLUDE '../../base/data/OPTIFLOW_TIMELENGHT.inc';
%semislash%;


PARAMETER CYCLES(TTT);
CYCLES(T)=CARD(TTT)/(CARD(T)*TIMELENGHT(T));



*-------------------------------------------------------------------------------
* WASTE NETWORK WITHIN AREAS (PROCESSES AND FLOWS):
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
* WASTE NETWORK WITHIN AREAS (PROCESSES AND FLOWS):
*-------------------------------------------------------------------------------

* NB: for debugging, print and ailing memory nice to have FLOW elements in UPPERCASE og PROC elements in lowercase
SET PROC "All processes" %semislash%
$if     EXIST '../data/OPTIFLOW_PROC.inc' $INCLUDE         '../data/OPTIFLOW_PROC.inc';
$if not EXIST '../data/OPTIFLOW_PROC.inc' $INCLUDE '../../base/data/OPTIFLOW_PROC.inc';
%semislash%;

ALIAS (PROC,IPROC,IPROCFROM,IPROCTO,IPROCFROM2,IPROCTO2,IPROCABROAD); !!IPROCABROAD ?

* Indholdet i denne kan garanteres afledes af PROCPAR nedenfor, lige nu h�ndlaver vi den.
* Men i �vrigt er det formentlig sikrere (ift. bruger) at definere eksplicit her. B�r i �vrigt checkes i errorcode. TODO/done?
SET PROCSOURCE(PROC) "Source PROC (no flow entering it)" %semislash%
$if     EXIST '../data/OPTIFLOW_PROCSOURCE.inc' $INCLUDE         '../data/OPTIFLOW_PROCSOURCE.inc';
$if not EXIST '../data/OPTIFLOW_PROCSOURCE.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCSOURCE.inc';
%semislash%;

* Indholdet i denne kan garanteres afledes af PROCPAR nedenfor, lige nu h�ndlaver vi den.
* Men i �vrigt er det formentlig sikrere (ift. bruger) at definere eksplicit her. B�r i �vrigt checkes i errorcode. TODO/done?
SET PROCSINK(PROC) "Sink PROC (no flow leaving it)" %semislash%
$if     EXIST '../data/OPTIFLOW_PROCSINK.inc' $INCLUDE         '../data/OPTIFLOW_PROCSINK.inc';
$if not EXIST '../data/OPTIFLOW_PROCSINK.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCSINK.inc';
%semislash%;

SET PROCBUFFER(PROC) "... PROC (flow entering and/or leaving)" %semislash%
$if     EXIST '../data/OPTIFLOW_PROCBUFFER.inc' $INCLUDE         '../data/OPTIFLOW_PROCBUFFER.inc';
$if not EXIST '../data/OPTIFLOW_PROCBUFFER.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCBUFFER.inc';
%semislash%;

SET PROCEXIM(PROC) "PROC for exchange possibility between areas" %semislash%
$if     EXIST '../data/OPTIFLOW_PROCEXIM.inc' $INCLUDE         '../data/OPTIFLOW_PROCEXIM.inc';
$if not EXIST '../data/OPTIFLOW_PROCEXIM.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCEXIM.inc';
%semislash%;

SET PROCTIMELINK(PROC) "Storage - presently for handling of time transformations only; storage has Seasonal balance, presently no up/lo" %semislash%
$if     EXIST '../data/OPTIFLOW_PROCTIMELINK.inc' $INCLUDE         '../data/OPTIFLOW_PROCTIMELINK.inc';
$if not EXIST '../data/OPTIFLOW_PROCTIMELINK.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCTIMELINK.inc';
%semislash%;

SET PROCSTORAGE(PROC) "Storage " %semislash%
$if     EXIST '../data/OPTIFLOW_PROCSTORAGE.inc' $INCLUDE         '../data/OPTIFLOW_PROCSTORAGE.inc';
$if not EXIST '../data/OPTIFLOW_PROCSTORAGE.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCSTORAGE.inc';
%semislash%;

*"Time Link processes and storage processes";
PROCSTORAGE(PROC)=PROCTIMELINK(PROC)+PROCSTORAGE(PROC);


SET PROCSTORAGE_Y(PROC) "Interseasonal storage - annual balance" %semislash%
$if     EXIST '../data/OPTIFLOW_PROCSTORAGE_Y.inc' $INCLUDE         '../data/OPTIFLOW_PROCSTORAGE_Y.inc';
$if not EXIST '../data/OPTIFLOW_PROCSTORAGE_Y.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCSTORAGE_Y.inc';
%semislash%;

* PROC_T includes all Process that are part of a traditional energy system model. Excludes PROCSTORAGE.
SET PROC_T(PROC) "PROC that operate on high time resolution T"   %semislash%
$if     EXIST '../data/OPTIFLOW_PROC_T.inc' $INCLUDE         '../data/OPTIFLOW_PROC_T.inc';
$if not EXIST '../data/OPTIFLOW_PROC_T.inc' $INCLUDE '../../base/data/OPTIFLOW_PROC_T.inc';
%semislash%;

SET PROCSTORAGE_YT(PROC);
$if     EXIST '../data/OPTIFLOW_PROCSTORAGE_YT.inc' $INCLUDE         '../data/OPTIFLOW_PROCSTORAGE_YT.inc';
$if not EXIST '../data/OPTIFLOW_PROCSTORAGE_YT.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCSTORAGE_YT.inc';
%semislash%;




SET IPROCTIMESETS(PROC,T);
IPROCTIMESETS(PROC,ITWWT)$(NOT PROC_T(PROC))=YES;
IPROCTIMESETS(PROC,T)$PROC_T(PROC)=YES;

* todo: consider: should it be strengthened to not include non-connected proc (now with geography included)?   todo: enersys?
* NOTE: PRESENTLY USED FOR DEBUG INOF ONLY (ERROR2.INC)
SET IPROCINTERIOR(PROC) "Set of PROC that are neither Sources nor Sinks nor Buffers nor Exims nor PROCSTORAGE nor PROCSTORAGE_Y";
IPROCINTERIOR(PROC) = PROC(PROC)-PROCSOURCE(PROC)-PROCSINK(PROC)-PROCBUFFER(PROC)-PROCEXIM(PROC)-PROCSTORAGE(PROC)-PROCSTORAGE_Y(PROC); !! PROCSTORAGE?

$ifi %inv%==yes PARAMETER IY4GREMAINY(Y,PROC)  "The number of remaining years in Y for new technology in the current Balbase4 model";


$ifi %inv%==yes SET APROCKAPNEW(YYY,AAA,PROC)     'Areas for possible location of new Proc capacity';
$ifi %inv%==yes $if     EXIST '../data/OPTIFLOW_APROCKAPNEW.inc' $INCLUDE         '../data/OPTIFLOW_APROCKAPNEW.inc';
$ifi %inv%==yes $if not EXIST '../data/OPTIFLOW_APROCKAPNEW.inc' $INCLUDE '../../base/data/OPTIFLOW_APROCKAPNEW.inc';
$ifi %inv%==yes %semislash%;

$ifi %inv%==yes SET IAPROCKAPNEW(YYY,AAA,PROC) 'Area, Proc where technology may be invested based on APKN and some implicit constraints';
IAPROCKAPNEW(YYY,IA,PROC) = APROCKAPNEW(YYY,IA,PROC);    !! MORE LATER


* NB: for debugging, print and ailing memory nice to have FLOW elements in UPPERCASE og Proc elements in CamelCase.
* NONONO: I now prefer the other way:  FLOW elements in CamelCase og Proc elements in UPPERCASE!

SET FLOW "All flows"       %semislash%
$if     EXIST '../data/OPTIFLOW_FLOW.inc' $INCLUDE         '../data/OPTIFLOW_FLOW.inc';
$if not EXIST '../data/OPTIFLOW_FLOW.inc' $INCLUDE '../../base/data/OPTIFLOW_FLOW.inc';
%semislash%;

ALIAS (FLOW,IFLOWIN,IFLOWIN2,IFLOWOUT,IFLOWOUT2);


ALIAS (AAA,IAAAE,IAAAI)
ALIAS (IA,IAE,IAI)

* Distance matrix (not necessarily symmetric) for transport between areas.
* Diagonal element must be NA.
PARAMETER   TRANSDIST(PROC,IAAAE,IAAAI) "Distance between two areas (not necessarily symmetric) (km)"  %semislash%
$if     EXIST '../data/OPTIFLOW_TRANSDIST.inc' $INCLUDE         '../data/OPTIFLOW_TRANSDIST.inc';
$if not EXIST '../data/OPTIFLOW_TRANSDIST.inc' $INCLUDE '../../base/data/OPTIFLOW_TRANSDIST.inc';
%semislash%;

SET ITRANSFROMTO(IAAAE,IAAAI) "Set of Areas that are connected by transport (not necessarily symmetric)";
ITRANSFROMTO(IAE,IAI)$SUM(PROC,TRANSDIST(PROC,IAE,IAI)) =  YES;
* Remove diagonal elements :
ITRANSFROMTO(IA,IA) = NO;




SET PROCDATASET  'Process addons/OptiFlow/data types' %semislash%   !! TODO: what kind of addons/OptiFlow/data? not all, some are  clearly in  procinoutflow
$if     EXIST '../data/OPTIFLOW_PROCDATASET.inc' $INCLUDE         '../data/OPTIFLOW_PROCDATASET.inc';
$if not EXIST '../data/OPTIFLOW_PROCDATASET.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCDATASET.inc';
%semislash%;

PARAMETER PROCDATA(PROC,PROCDATASET)    'Process data (*)' %semislash%   !! TODO: what kind of data not all, some are  clearly in  procinoutflow
$if     EXIST '../data/OPTIFLOW_PROCDATA.inc' $INCLUDE         '../data/OPTIFLOW_PROCDATA.inc';
$if not EXIST '../data/OPTIFLOW_PROCDATA.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCDATA.inc';
%semislash%;

* Capacity is implemented as a bound on a Flow (index 4) that enters or leaves PROC (index 3).
* The value of IFLOWINOUT determines whether the Flow enters or leaves PROC.
* Hence, with 'IFLOWINOUT_OUT' the bound will be on the Flow from PROC,
* while  with 'IFLOWINOUT_IN'  the bound will be on the Flow to PROC.
* The PROC can have only one Flow Bundle. ASSUMPTION   NOT ANYMORE NEEDED
* Capacity cannot be given for entering Flow with IMANYONE in PROCINOUTFLOW nor for leaving Flow with IONEMANY.

SET IFLOWINOUT "Specifies for PROCKAPFX that if the capacity of Proc (index 3) is set as a bound on entering/leaving Flow from/to Proc (index 4)" / IFLOWINOUT_IN, IFLOWINOUT_OUT /;


SET  PROCKAPDATA(YYY,PROC,FLOW,IFLOWINOUT)    "Process addons/OptiFlow/data: capacity relative to FLOW and in/out direction"  %semislash%
$if     EXIST '../data/OPTIFLOW_PROCKAPDATA.inc' $INCLUDE         '../data/OPTIFLOW_PROCKAPDATA.inc';
$if not EXIST '../data/OPTIFLOW_PROCKAPDATA.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCKAPDATA.inc';
%semislash%;




PARAMETER PROCKAPFX(YYY,AAA,PROC,FLOW,IFLOWINOUT) "Capacity of Process (U/h)" %semislash%
$if     EXIST '../data/OPTIFLOW_PROCKAPFX.inc' $INCLUDE         '../data/OPTIFLOW_PROCKAPFX.inc';
$if not EXIST '../data/OPTIFLOW_PROCKAPFX.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCKAPFX.inc';
%semislash%;




PARAMETER PROCKAPNEWSCALE(PROC) "Capacity of Process (U/h)" %semislash%
$if     EXIST '../data/OPTIFLOW_PROCKAPNEWSCALE.inc' $INCLUDE         '../data/OPTIFLOW_PROCKAPNEWSCALE.inc';
$if not EXIST '../data/OPTIFLOW_PROCKAPNEWSCALE.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCKAPNEWSCALE.inc';
%semislash%;


Scalar M_EconomyScale "Number without units used as a mathematical trick in integer formulation, it should be big enough to ensure the equation QPROCKAUP_SCALE2 holds but as small as possible to speed up the solution"
$if     EXIST '../data/OPTIFLOW_M_EconomyScale.inc' $INCLUDE         '../data/OPTIFLOW_M_EconomyScale.inc';
$if not EXIST '../data/OPTIFLOW_M_EconomyScale.inc' $INCLUDE '../../base/data/OPTIFLOW_M_EconomyScale.inc';
%semislash%;

*Decommisioning of technologies

SET PROCKAPDECOM(PROC)"Technologies that might be decomissioned"
$if     EXIST '../data/OPTIFLOW_PROCKAPDECOM.inc' $INCLUDE         '../data/OPTIFLOW_PROCKAPDECOM.inc';
$if not EXIST '../data/OPTIFLOW_PROCKAPDECOM.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCKAPDECOM.inc';
%semislash%;



IAPROCKAPNEW(YYY,IA,PROC)$(PROCDATA(PROC,'PROCKAPVARIABLE') EQ 0) = NO;   !! Not needed, is implicit in APROCKAPNEW
* TODO: add condition for COMBINATION OF Y AND PROCFROMYEAR  (which may reduce IAPROCKAPNEW).


*-------------------------------------------------------------------------------
*----- Any declarations and definitions of sets, aliases and acronyms for addon:
*-------------------------------------------------------------------------------
* Addon APKNdisc: discrete size investments in PROC.
$ifi %APKNdisc%==yes $include "../addons/OptiFlow/bb4/apkndisc/apkndiscdecls.inc";
$ifi %APKNdisc%==yes $include "../addons/OptiFlow/bb4/apkndisc/datainc.inc";
$ifi %APKNdisc%==yes $include "../addons/OptiFlow/bb4/apkndisc/apkndiscinternals.inc";



*-------------------------------------------------------------------------------
* End: Any declarations and definitions of sets, aliases and acronyms for addon
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
* INDICATORS (COEFFICIENTS, BOUNDS FOR USE WITH OBJECTIVE FUNCTION)
*-------------------------------------------------------------------------------


SET FLOWINDIC(FLOW) "The indicator flows that we are interested in evaluating" %semislash%
$if     EXIST '../data/OPTIFLOW_FLOWINDIC.inc' $INCLUDE         '../data/OPTIFLOW_FLOWINDIC.inc';
$if not EXIST '../data/OPTIFLOW_FLOWINDIC.inc' $INCLUDE '../../base/data/OPTIFLOW_FLOWINDIC.inc';
%semislash%;

ALIAS (FLOWINDIC,IFLOWINDICIN,IFLOWINDICOUT);

SET PROCINDIC(PROC) "The indicator NODEs (source/sink/buffer(/exim?)) with net balances that we are interested in evaluating";
$if     EXIST '../data/OPTIFLOW_PROCINDIC.inc' $INCLUDE         '../data/OPTIFLOW_PROCINDIC.inc';
$if not EXIST '../data/OPTIFLOW_PROCINDIC.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCINDIC.inc';
%semislash%;

PARAMETER SOSIBU2INDIC(YYY,PROC,FLOW,FLOWINDIC) "Coefficients for transformation of VSOURCE, VSINK and VBUFFER flows to FLOWINDIC values"  %semislash%
$if     EXIST '../data/OPTIFLOW_SOSIBU2INDIC.inc' $INCLUDE         '../data/OPTIFLOW_SOSIBU2INDIC.inc';
$if not EXIST '../data/OPTIFLOW_SOSIBU2INDIC.inc' $INCLUDE '../../base/data/OPTIFLOW_SOSIBU2INDIC.inc';
%semislash%;

* The number of SOSIBU2INDIC_xyz may se extended

PARAMETER SOSIBU2INDIC_A(AAA,PROC,FLOW,FLOWINDIC) "Coefficients for transformation of VSOURCE, VSINK and VBUFFER flows to FLOWINDIC values"  %semislash%
$if     EXIST '../data/OPTIFLOW_SOSIBU2INDIC_A.inc' $INCLUDE         '../data/OPTIFLOW_SOSIBU2INDIC_A.inc';
$if not EXIST '../data/OPTIFLOW_SOSIBU2INDIC_A.inc' $INCLUDE '../../base/data/OPTIFLOW_SOSIBU2INDIC_A.inc';
%semislash%;


PARAMETER SOSIBU2INDIC_AST(AAA,PROC,FLOW,FLOWINDIC,SSS,TTT) "Coefficients for transformation of VSOURCE, VSINK and VBUFFER flows to FLOWINDIC values"  %semislash%
$if     EXIST '../data/OPTIFLOW_SOSIBU2INDIC_AST.inc' $INCLUDE         '../data/OPTIFLOW_SOSIBU2INDIC_AST.inc';
$if not EXIST '../data/OPTIFLOW_SOSIBU2INDIC_AST.inc' $INCLUDE '../../base/data/OPTIFLOW_SOSIBU2INDIC_AST.inc';
%semislash%;


PARAMETER SOSIBU2INDIC_AS(AAA,PROC,FLOW,FLOWINDIC,SSS) "Coefficients for transformation of VSOURCE, VSINK and VBUFFER flows to FLOWINDIC values" %semislash%
$if     EXIST '../data/OPTIFLOW_SOSIBU2INDIC_AS.inc' $INCLUDE         '../data/OPTIFLOW_SOSIBU2INDIC_AS.inc';
$if not EXIST '../data/OPTIFLOW_SOSIBU2INDIC_AS.inc' $INCLUDE '../../base/data/OPTIFLOW_SOSIBU2INDIC_AS.inc';
%semislash%;

PARAMETER SOSIBU2INDIC_RST(RRR,PROC,FLOW,FLOWINDIC,SSS,TTT) "Coefficients for transformation of VSOURCE, VSINK and VBUFFER flows to FLOWINDIC values"  %semislash%
$if     EXIST '../data/OPTIFLOW_SOSIBU2INDIC_RST.inc' $INCLUDE         '../data/OPTIFLOW_SOSIBU2INDIC_RST.inc';
$if not EXIST '../data/OPTIFLOW_SOSIBU2INDIC_RST.inc' $INCLUDE '../../base/data/OPTIFLOW_SOSIBU2INDIC_RST.inc';
%semislash%;

PARAMETER PROCSTORAGEBOUND(YYY,AAA,PROC) "Upper bound (capacity) of Storage for Flow (U)"  %semislash%
$if     EXIST '../data/OPTIFLOW_PROCSTORAGEBOUND.inc' $INCLUDE         '../data/OPTIFLOW_PROCSTORAGEBOUND.inc';
$if not EXIST '../data/OPTIFLOW_PROCSTORAGEBOUND.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCSTORAGEBOUND.inc';
%semislash%;


PARAMETER IPROCKAPFX(AAA,PROC) "Capacity of Process (U/h)";
*PARAMETER IPROCKAPFX(Y,AAA,PROC) "Capacity of Process (U/h)";
*PARAMETER IPROCKAPFX(Y,AAA,PROC,FLOW);


PARAMETER IPROCSTORAGEBOUND(AAA,PROC) "Upper bound (capacity) of Storage for Flow (U)";
PARAMETER ISOSIBU2INDIC(PROC,FLOW,FLOWINDIC) "Coefficients for transformation of VSOURCE, VSINK and VBUFFER flows to FLOWINDIC values"  %semislash%


* Assumptions for good addons/OptiFlow/data: for any (PROC,FLOWINDIC) there should be non-zero values in at most one of the three above files.
* Further, these files are relevant only for Source, Sink and Buffer nodes.

PARAMETER PROCKAPFXINV(YYY,AAA,PROC) "Investments in plants endogenously calculated from previous years"  %semislash%
$if     EXIST '../data/OPTIFLOW_PROCKAPFXINV.inc' $INCLUDE         '../data/OPTIFLOW_PROCKAPFXINV.inc';
$if not EXIST '../data/OPTIFLOW_PROCKAPFXINV.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCKAPFXINV.inc';
%semislash%;

PARAMETER IPROCKAPFXINV(YYY,AAA,PROC) "Investments in plants from previous years, adding flow characteristics";
PARAMETER IPROCKAPFXINV_Y(AAA,PROC) "Investments in plants from previous years in the specific year of simulation)";


* ------------------------------------------------------------------------------

%ONOFFDATALISTING%


* PROCINOUTFLOW shows for interior nodes relations between incoming and leaving FLOW for each node.
* The relations are logical as well as quantitative.
* The last index (IPROCINOUTRELATION) and the parameter values entered have the following interpretation:
* IONEONE and positive:   Used for linking one incoming and one outcoming flow in fixed proportions
* IONEONE and negative:   Used for linking two incoming flows in fixed proportions
* IMANYONE:  Used for making the sum of incoming flows with this value equal to outcoming flow
* IONEMANY: Used for making the sum of outcoming flows with this value equal to incoming flow
* IONEONEREC: the reciprocal value is entered.
* The quantititive values specifies how large share of the input flow flow is transferred to the output flow, or briefly: FLOWOUT=value*FLOWIN.
* Numerical values may be less than 1, 1 or grater than one, e.g.:
*   0.5 for each of two output FLOW for one input flow if the input FLOW is split equally between the two output FLOW
*   1 if the input FLOW is directly and losslessly transferred to an output flow (with loss the number would be smaller than 1)
*   1.3 if the input flow is transformed in the node and thereby consumes some not-otherwise-accounted material, e.g., oxygen from the air
*   if the incoming and outcoming FLOW are in different units (e.g., ton and GJ) the coefficient will usually be different from 1.
* The numerical non-acronym values will be multiplied onto the FLOW in the second index position.      !TODO: REFORMULATE
* Note that for numerical non-acronym values only the numerical value is used for the multiplication, not the sign.
* The values IONEMANY and IMANYONE are used to indicate that
*   IMANYONE:  the specified identical input  FLOW are summarized in variable (endogenous) proportions and equated to a single output FLOW
*   IONEMANY:  the specified identical output FLOW are split      in variable (endogenous) proportions and equated to a single input  FLOW

SET IPROCINOUTRELATION "Possible relationships between process inflow and outflow" / IONEONE, IONEMANY, IMANYONE, IONEONEREC /;

SET FLOWFROMTOPROC(YYY,AAA,IPROCFROM,IPROCTO,FLOW) "FLOW from PROC (index 2) to PROC (index 3)" %semislash%
$if     EXIST '../data/OPTIFLOW_FLOWFROMTOPROC.inc' $INCLUDE         '../data/OPTIFLOW_FLOWFROMTOPROC.inc';
$if not EXIST '../data/OPTIFLOW_FLOWFROMTOPROC.inc' $INCLUDE '../../base/data/OPTIFLOW_FLOWFROMTOPROC.inc';
%semislash%
SET IFLOWFROMTOPROC_Y(AAA,IPROCFROM,IPROCTO,FLOW) "FLOW from PROC (index 2) to PROC (index 3) in the year of optimization";


PARAMETER PROCINOUTFLOW(YYY,AAA,PROC,IFLOWIN,IFLOWOUT,IPROCINOUTRELATION) "Relationship at PROC between FLOWIN (index 3) and FLOWOUT (index 4); interior PROC only (~)"  %semislash%
$if     EXIST '../data/OPTIFLOW_PROCINOUTFLOW.inc' $INCLUDE         '../data/OPTIFLOW_PROCINOUTFLOW.inc';
$if not EXIST '../data/OPTIFLOW_PROCINOUTFLOW.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCINOUTFLOW.inc';
%semislash%

PARAMETER IPROCINOUTFLOW_Y(AAA,PROC,IFLOWIN,IFLOWOUT,IPROCINOUTRELATION) "Relationship at PROC between FLOWIN (index 3) and FLOWOUT (index 4); interior PROC only (~)"  %semislash%


SET  IPROCINOUTFLOW(YYY,AAA,PROC,IFLOWIN,IFLOWOUT) "Set of combinations of (AAA,PROC,IFLOWIN,IFLOWOUT) in PROCINOUTFLOW";
IPROCINOUTFLOW(Y,IA,PROC,IFLOWIN,IFLOWOUT) = YES$(SUM(IPROCINOUTRELATION$PROCINOUTFLOW(Y,IA,PROC,IFLOWIN,IFLOWOUT,IPROCINOUTRELATION),1));

SET  IPROCINOUTFLOW_Y_set(AAA,PROC,IFLOWIN,IFLOWOUT) "Set of combinations of (AAA,PROC,IFLOWIN,IFLOWOUT) in PROCINOUTFLOW";


* TODO: Reconsider name (no 'VARI...' anymore)
PARAMETER IPRIOVARIOUTSUM(YYY,AAA,PROC,IFLOWIN,IFLOWOUT) "Indicator for use with VARIOUTSUM: 0: not outsum, 1: outsum primary, 2: outsumt secondary;  only primary used for equation indexes (~)";
IPRIOVARIOUTSUM(Y,IA,PROC,IFLOWIN,IFLOWOUT) = 0;
LOOP((Y,PROC,IFLOWIN),
  LOOP(IA,
  ISCALAR1 = 0;
  LOOP(IFLOWOUT$PROCINOUTFLOW(Y,IA,PROC,IFLOWIN,IFLOWOUT,"IONEMANY"),
    ISCALAR1= MIN(2,ISCALAR1+1);
    IPRIOVARIOUTSUM(Y,IA,PROC,IFLOWIN,IFLOWOUT) = ISCALAR1;
)));

* TODO: Reconsider name (no 'VARIIN' anymore)
PARAMETER IPRIOVARIINSUM(YYY,AAA,PROC,IFLOWIN,IFLOWOUT) "Indicator for use with variinsum: 0: not insum, 1: insum primary, 2: insum secondary; only primary used for equation indexes (~)";
IPRIOVARIINSUM(Y,IA,PROC,IFLOWIN,IFLOWOUT) = 0;
LOOP((Y,PROC,IFLOWOUT),
  LOOP(IA,
  ISCALAR1= 0;
  LOOP(IFLOWIN$PROCINOUTFLOW(Y,IA,PROC,IFLOWIN,IFLOWOUT,"IMANYONE"),
    ISCALAR1= MIN(2,ISCALAR1+1);
    IPRIOVARIINSUM(Y,IA,PROC,IFLOWIN,IFLOWOUT) = ISCALAR1;
)));


SET ILEAVEPROC(YYY,AAA,PROC,FLOW) "For each PROC: the set of FLOW that originate from this PROC (based on FLOWFROMTOPROC)";
ILEAVEPROC(Y,IA,IPROCFROM,IFLOWOUT) = YES$(SUM(IPROCTO$FLOWFROMTOPROC(Y,IA,IPROCFROM,IPROCTO,IFLOWOUT),1));

SET IENTERPROC(YYY,AAA,PROC,FLOW) "For each PROC: the set of FLOW that enter this PROC (based on FLOWFROMTOPROC)";
IENTERPROC(Y,IA,IPROCTO,FLOW) = YES$(SUM(IPROCFROM$FLOWFROMTOPROC(Y,IA,IPROCFROM,IPROCTO,FLOW),1));

Option IENTERPROC:3:0:1; display ILEAVEPROC,IENTERPROC;

* For handling cases with a fixed relation between two incoming or two outgoing FLOWs
SET INEGPROCININFLOW(YYY,AAA,PROC,IFLOWIN,IFLOWIN2)       "Set with two incoming FLOW to a PROC (negative value of PROCINOUTFLOW)";
SET INEGPROCOUTOUTFLOW(YYY,AAA,PROC,IFLOWOUT,IFLOWOUT2)   "Set with two outcoming FLOW to a PROC (negative value of PROCINOUTFLOW)";

LOOP((Y,IA,PROC,IFLOWIN,IFLOWIN2)$(IENTERPROC(Y,IA,PROC,IFLOWIN) AND IENTERPROC(Y,IA,PROC,IFLOWIN2) AND PROCINOUTFLOW(Y,IA,PROC,IFLOWIN,IFLOWIN2,"IONEONE")),
  IF((PROCINOUTFLOW(Y,IA,PROC,IFLOWIN,IFLOWIN2,"IONEONE") < 0 ),
    INEGPROCININFLOW(Y,IA,PROC,IFLOWIN,IFLOWIN2) = YES;
););


SET IFLOWEXIM(FLOW) "Flows that may transported between areas";
IFLOWEXIM(FLOW)$(SUM((Y,IAAAE,PROCEXIM)$(ILEAVEPROC(Y,IAAAE,PROCEXIM,FLOW) OR IENTERPROC(Y,IAAAE,PROCEXIM,FLOW)),1)) = YES;

PARAMETER TRANSFLOWMAX(IAAAE,IAAAI,PROC,FLOW)  "Transport quantity maximum value (ton/h)"  %semislash%
$if     EXIST '../data/OPTIFLOW_TRANSFLOWMAX.inc' $INCLUDE         '../data/OPTIFLOW_TRANSFLOWMAX.inc';
$if not EXIST '../data/OPTIFLOW_TRANSFLOWMAX.inc' $INCLUDE '../../base/data/OPTIFLOW_TRANSFLOWMAX.inc';
%semislash%;

SET ITRANSFLOWFROMTO(IAAAE,IAAAI,FLOW) "Set of Area pairs that are connected by transport of FLOW (symmetric?)";
* IA can be a member if FLOW is connected to a ProcExim in that area.
* (IAE,IAI) is a member if both can be member according to the above.
* The relations internal to an area:
ITRANSFLOWFROMTO(IAAAE,IAAAI,FLOW)$(SUM((Y,PROCEXIM),(ILEAVEPROC(Y,IAAAE,PROCEXIM,FLOW) OR IENTERPROC(Y,IAAAE,PROCEXIM,FLOW)) AND
                                    (ILEAVEPROC(Y,IAAAI,PROCEXIM,FLOW) OR IENTERPROC(Y,IAAAI,PROCEXIM,FLOW)) AND
*                                    (ORD(IAAAE) NE ORD(IAAAI)) AND     !! This line should not be needed due to next line
                                     ITRANSFROMTO(IAAAE,IAAAI)) ) = YES;

* Add Transit areas: non-transit and transit connection:
ITRANSFLOWFROMTO(IAAAE,IATRANSITI,FLOW)$(SUM((Y,PROCEXIM),(NOT IATRANSITE(IAAAE)) AND (ILEAVEPROC(Y,IAAAE,PROCEXIM,FLOW) OR IENTERPROC(Y,IAAAE,PROCEXIM,FLOW)) AND
                                          ITRANSFROMTO(IAAAE,IATRANSITI))) = YES;

* Add Transit areas: non-transit and transit connection:
ITRANSFLOWFROMTO(IATRANSITI,IAAAE,FLOW)$(SUM((Y,PROCEXIM),(NOT IATRANSITE(IAAAE)) AND (ILEAVEPROC(Y,IAAAE,PROCEXIM,FLOW) OR IENTERPROC(Y,IAAAE,PROCEXIM,FLOW)) AND
                                         ITRANSFROMTO(IATRANSITI,IAAAE))) = YES;


* Add transit to transit connection; Note that the following assignment may add too many Flows:
ITRANSFLOWFROMTO(IATRANSITE,IATRANSITI,IFLOWEXIM)$(ITRANSFROMTO(IATRANSITE,IATRANSITI) AND (ORD(IATRANSITE) NE ORD(IATRANSITI))) = YES;
* MISSING LOOP(FLOW$(SUM((IAAAE,IATRANSITI)$ITRANSFLOWFROMTO(IAAAE,IATRANSITI,FLOW),1) AND SUM((IATRANSITE,IAAAI)$ITRANSFLOWFROMTO(IATRANSITE,IAAAI,FLOW),1)),
* MISSING );


SET TRANSCOSTDATASET "Transport cost element addons/OptiFlow/data and mapping to FLOWINDIC"   %semislash%
$if     EXIST '../data/OPTIFLOW_TRANSCOSTDATASET.inc' $INCLUDE         '../data/OPTIFLOW_TRANSCOSTDATASET.inc';
$if not EXIST '../data/OPTIFLOW_TRANSCOSTDATASET.inc' $INCLUDE '../../base/data/OPTIFLOW_TRANSCOSTDATASET.inc';
%semislash%;

PARAMETER TRANSCOST(TRANSCOSTDATASET,TRANSDISTWEIGHT,PROC,FLOWINDIC) "Transport 'cost' in terms of INDICS"   %semislash%
$if     EXIST '../data/OPTIFLOW_TRANSCOST.inc' $INCLUDE         '../data/OPTIFLOW_TRANSCOST.inc';
$if not EXIST '../data/OPTIFLOW_TRANSCOST.inc' $INCLUDE '../../base/data/OPTIFLOW_TRANSCOST.inc';
%semislash%;

PARAMETER IPRIOVARIOUTSUM_Y(AAA,PROC,IFLOWIN,IFLOWOUT);
PARAMETER IPRIOVARIINSUM_Y(AAA,PROC,IFLOWIN,IFLOWOUT);
PARAMETER INEGPROCININFLOW_Y(AAA,PROC,IFLOWIN,IFLOWIN2);
PARAMETER INEGPROCOUTOUTFLOW_Y(AAA,PROC,IFLOWOUT,IFLOWOUT2);
PARAMETER ILEAVEPROC_Y(AAA,IPROCFROM,IFLOWOUT);
PARAMETER IENTERPROC_Y(AAA,IPROCTO,FLOW);



* ------------------------------------------------------------------------------
* BOUNDS:
* ------------------------------------------------------------------------------

* There are possibilities for setting bounds on incividul flows
* or on certain combinations of flows.
* Bounds may be lower, upper of fixed values.
display ITRANSFROMTO;

SET ILOUPFXSET "Set representing lower, upper and fixed values "
/
ILOUPFX_LO    "Lower limit"
ILOUPFX_UP    "Upper limit"
ILOUPFX_FX    "Fixed value"
/;

* Bounds on Source(So), Sink(Si) or Buffer (Bu) FLOW:

* TODO: to reconsider - comments in the files

PARAMETER SOSIBUBOUND(YYY,AAA,PROC,FLOW,ILOUPFXSET) 'Bounds on Source, Sink and Buffer Process Flows - Annual values';
$if     EXIST '../data/OPTIFLOW_SOSIBUBOUND.inc' $INCLUDE         '../data/OPTIFLOW_SOSIBUBOUND.inc';
$if not EXIST '../data/OPTIFLOW_SOSIBUBOUND.inc' $INCLUDE '../../base/data/OPTIFLOW_SOSIBUBOUND.inc';
%semislash%;

PARAMETER ISOSIBUBOUND_Y(AAA,PROC,FLOW,iLOUPFXSET) "Bounds on Source, Sink and Buffer Process Flows - for the year of optimization";


PARAMETER SOSIBUFLOW_VAR_T(AAA,PROC,FLOW,SSS,TTT) "Variation in some Source, Sink or Buffer Flows over the year (~)"  %semislash%
$if     EXIST '../data/OPTIFLOW_SOSIBUFLOW_VAR_T.inc' $INCLUDE         '../data/OPTIFLOW_SOSIBUFLOW_VAR_T.inc';
$if not EXIST '../data/OPTIFLOW_SOSIBUFLOW_VAR_T.inc' $INCLUDE '../../base/data/OPTIFLOW_SOSIBUFLOW_VAR_T.inc';
%semislash%;

*This has to be dependant of T, not if ITWWT as it was written Amalia 16-06-2015
PARAMETER ISOSIBUFLOW_SUMST(AAA,PROC,FLOW) "Annual time weighted amount of SOSIBUFLOW_VAR_T values (~)"; !! TODO: misvisende beskrivelse ... ?
ISOSIBUFLOW_SUMST(IA,PROC,FLOW) = SUM((S,T),IHOURSINST(S,T)*SOSIBUFLOW_VAR_T(IA,PROC,FLOW,S,T));

* Bounds on individual interior FLOWs:
* The value 0 or white space implies no bound. The value 'eps' restricts to zero.
* Note: if specific values are given in other parameters they will supplement (by overwriting) the values given here.

* Bounds on shares in relation to IONEMANY (variable split of outflow) and IMANYONE (sum of inflow)
* Use EPS for the value 0. Entering 0 or nothing will be interpreted as 'not relevant'.
* TODO: may become part of ... , see the addons/OptiFlow/data file  for that
PARAMETER FLOWSHAREOUT2IN(YYY,AAA,IPROCFROM,IPROCTO,FLOW/*,SSS,TTT*/,ILOUPFXSET) "Bounds on shares of variable splits of outflow from PROC (share)"  %semislash%
$if     EXIST '../data/OPTIFLOW_FLOWSHAREOUT2IN.inc' $INCLUDE         '../data/OPTIFLOW_FLOWSHAREOUT2IN.inc';
$if not EXIST '../data/OPTIFLOW_FLOWSHAREOUT2IN.inc' $INCLUDE '../../base/data/OPTIFLOW_FLOWSHAREOUT2IN.inc';
%semislash%;

PARAMETER FLOWSHAREOUT2OUT(YYY,AAA,PROC,IFLOWIN,IFLOWOUT,IFLOWOUT2,ILOUPFXSET) "Fixed relation (index 4 divided by 5) between two split FLOWs leaving PROC (share)"
$if     EXIST '../data/OPTIFLOW_FLOWSHAREOUT2OUT.inc' $INCLUDE         '../data/OPTIFLOW_FLOWSHAREOUT2OUT.inc';
$if not EXIST '../data/OPTIFLOW_FLOWSHAREOUT2OUT.inc' $INCLUDE '../../base/data/OPTIFLOW_FLOWSHAREOUT2OUT.inc';
%semislash%;

PARAMETER FLOWSHAREIN2IN(YYY,AAA,PROC,IFLOWIN,IFLOWIN2,ILOUPFXSET) "Relationship between two input flows"  %semislash%
$if     EXIST '../data/OPTIFLOW_FLOWSHAREIN2IN.inc' $INCLUDE         '../data/OPTIFLOW_FLOWSHAREIN2IN.inc';
$if not EXIST '../data/OPTIFLOW_FLOWSHAREIN2IN.inc' $INCLUDE '../../base/data/OPTIFLOW_FLOWSHAREIN2IN.inc';
%semislash%;

PARAMETER IFLOWSHAREOUT2IN_Y(AAA,IPROCFROM,IPROCTO,FLOW/*,SSS,TTT*/,ILOUPFXSET) "Bounds on shares of variable splits of outflow from PROC (share)"  %semislash%
PARAMETER IFLOWSHAREOUT2OUT_Y(AAA,PROC,IFLOWIN,IFLOWOUT,IFLOWOUT2,ILOUPFXSET) "Fixed relation (index 4 divided by 5) between two split FLOWs leaving PROC (share)"
PARAMETER IFLOWSHAREIN2IN_Y(AAA,PROC,IFLOWIN,IFLOWIN2,ILOUPFXSET) "Relationship between two input flows"  %semislash%


PARAMETER PROCRAMPUP(PROC) "Constraint of the plants which will be subjet to a ramp-up and down limitations"  %semislash%;
$if     EXIST '../data/OPTIFLOW_PROCRAMPUP.inc' $INCLUDE         '../data/OPTIFLOW_PROCRAMPUP.inc';
$if not EXIST '../data/OPTIFLOW_PROCRAMPUP.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCRAMPUP.inc';
%semislash%;

PARAMETER PROCRAMPDOWN(PROC) "Constraint of the plants which will be subjet to a ramp-up and down limitations"  %semislash%;
$if     EXIST '../data/OPTIFLOW_PROCRAMPDOWN.inc' $INCLUDE         '../data/OPTIFLOW_PROCRAMPDOWN.inc';
$if not EXIST '../data/OPTIFLOW_PROCRAMPDOWN.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCRAMPDOWN.inc';
%semislash%;


PARAMETER EQFLOW(YYY,CCCRRRAAA,PROC,FLOW) "Constraint about fuel use requirements"  %semislash%;
*PARAMETER IEQFLOW_Y(CCCRRRAAA,PROC,FLOW) "Internal parameter about fuel use requirements (U/year)";
$if     EXIST '../data/OPTIFLOW_EQFLOW.inc' $INCLUDE         '../data/OPTIFLOW_EQFLOW.inc';
$if not EXIST '../data/OPTIFLOW_EQFLOW.inc' $INCLUDE '../../base/data/OPTIFLOW_EQFLOW.inc';
%semislash%;

PARAMETER MAXFLOW(YYY,CCCRRRAAA,PROC,FLOW) "Constraint about fuel use limitations"  %semislash%;
PARAMETER IMAXFLOW_Y(CCCRRRAAA,PROC,FLOW) "Internal parameter about fuel use limitations (U/year)";
$if     EXIST '../data/OPTIFLOW_MAXFLOW.inc' $INCLUDE         '../data/OPTIFLOW_MAXFLOW.inc';
$if not EXIST '../data/OPTIFLOW_MAXFLOW.inc' $INCLUDE '../../base/data/OPTIFLOW_MAXFLOW.inc';
%semislash%;

PARAMETER MINFLOW(YYY,CCCRRRAAA,PROC,FLOW) "Constraint about minimum fuel use"  %semislash%;
PARAMETER IMINFLOW_Y(CCCRRRAAA,PROC,FLOW) "Internal parameter about minimum fuel use (U/year)";
$if     EXIST '../data/OPTIFLOW_MINFLOW.inc' $INCLUDE         '../data/OPTIFLOW_MINFLOW.inc';
$if not EXIST '../data/OPTIFLOW_MINFLOW.inc' $INCLUDE '../../base/data/OPTIFLOW_MINFLOW.inc';
%semislash%;


*Internal set generated when a non PROC_T process is connected to a PROC_T process without a storage in the middle
SET IFLOW_T(FLOW);
IFLOW_T(FLOW)=YES$(SUM((Y,IA,IPROCFROM,IPROCTO),
   (FLOWFROMTOPROC(Y,IA,IPROCFROM,IPROCTO,FLOW) AND ((PROC_T(IPROCFROM) AND (NOT PROC_T(IPROCTO))) OR (PROC_T(IPROCTO) AND (NOT PROC_T(IPROCFROM))))
    AND (NOT PROCTIMELINK(IPROCFROM)) AND (NOT PROCTIMELINK(IPROCTO)))
));



* Some helpers:

LOOP((Y,IA,PROC,IFLOWOUT,IFLOWOUT2)$(ILEAVEPROC(Y,IA,PROC,IFLOWOUT) AND ILEAVEPROC(Y,IA,PROC,IFLOWOUT2) AND PROCINOUTFLOW(Y,IA,PROC,IFLOWOUT,IFLOWOUT2,"IONEONE")),
 IF((PROCINOUTFLOW(Y,IA,PROC,IFLOWOUT,IFLOWOUT2,"IONEONE") < 0 ),
   INEGPROCOUTOUTFLOW(Y,IA,PROC,IFLOWOUT,IFLOWOUT2) = YES;
));


*The scalar should also include single technologies, as the return on investments might be technologically dependent
SCALAR RateOfReturn     "Rate of return of the investments"     %semislash%
$if     EXIST '../data/OPTIFLOW_RateOfReturn.inc' $INCLUDE         '../data/OPTIFLOW_RateOfReturn.inc';
$if not EXIST '../data/OPTIFLOW_RateOfReturn.inc' $INCLUDE '../../base/data/OPTIFLOW_RateOfReturn.inc';
%semislash%;


* ------------------------------------------------------------------------------
* OBJECTIVES:
* ------------------------------------------------------------------------------

SET IPROCINDICS(PROCINDIC,FLOWINDIC) "Set of relevant combinations of (PROCINDIC ,INDICS)";
IPROCINDICS(PROCINDIC,FLOWINDIC)$(SUM((Y,IA,IPROCFROM)$(FLOWFROMTOPROC(Y,IA,IPROCFROM,PROCINDIC,FLOWINDIC)),1)) = YES;
IPROCINDICS(PROCINDIC,FLOWINDIC)$(SUM((Y,IA,IPROCTO)$(FLOWFROMTOPROC(Y,IA,PROCINDIC,IPROCTO,FLOWINDIC)),1)) = YES;


SET IINDICLIMGOALSET "Limits and desirable values of INDICS"
/
INDICMIN    "Lower limit for Indic value (?ton/y) for models OPTIWASTE_Q and OPTIWASTE_WQ (-INF means unlimited downwards)"
INDICMAX    "Upper limit for Indic value (?ton/y) for models OPTIWASTE_Q and OPTIWASTE_WQ (+INF means unlimited upwards)"
INDICGOAL   "Desirable Indic value (?ton/y) for model ... (ikke formulert endnu)"
INDICWEIGHT "Indic relative weight (?) for model OPTIWASTE_W"
/;

PARAMETER INDICLIMGOAL(FLOWINDIC,IINDICLIMGOALSET) "Limits, desirable quantities and weight of Indics"  %semislash%;
$if     EXIST '../data/OPTIFLOW_INDICLIMGOAL.inc' $INCLUDE         '../data/OPTIFLOW_INDICLIMGOAL.inc';
$if not EXIST '../data/OPTIFLOW_INDICLIMGOAL.inc' $INCLUDE '../../base/data/OPTIFLOW_INDICLIMGOAL.inc';
%semislash%;

SCALAR IPENALTYQ   "Penalty on violation of equation" / 1e9 /;
SCALAR ILOUPBOUNDS "Default lower and upper bounds to guard against unbounded solution" /1e10/;

*mason

Set PROCTECHTYPE(PROC,TECH_GROUP) "Type of technology aggrigated"  %semislash%;
$if     EXIST '../data/OPTIFLOW_PROCTECHTYPE.inc' $INCLUDE         '../data/OPTIFLOW_PROCTECHTYPE.inc';
$if not EXIST '../data/OPTIFLOW_PROCTECHTYPE.inc' $INCLUDE '../../base/data/OPTIFLOW_PROCTECHTYPE.inc';
%semislash%;

































