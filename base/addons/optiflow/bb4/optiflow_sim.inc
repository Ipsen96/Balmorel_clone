
*left hand side sets have been removed and y/IY411 have been added respectively with the right hand side
*ISOSIBUBOUND_Y(IA,PROC,FLOW,iLOUPFXSET)=SOSIBUBOUND(Y,IA,PROC,FLOW,iLOUPFXSET);
*IFLOWFROMTOPROC_Y(IA,IPROCFROM,IPROCTO,FLOW)=FLOWFROMTOPROC(Y,IA,IPROCFROM,IPROCTO,FLOW);
*IPROCINOUTFLOW_Y(IA,PROC,IFLOWIN,IFLOWOUT,IPROCINOUTRELATION)=PROCINOUTFLOW(Y,IA,PROC,IFLOWIN,IFLOWOUT,IPROCINOUTRELATION);
*IPROCINOUTFLOW_Y_set(IA,PROC,IFLOWIN,IFLOWOUT)=IPROCINOUTFLOW(Y,IA,PROC,IFLOWIN,IFLOWOUT);
*IFLOWSHAREOUT2IN_Y(IA,IPROCFROM,IPROCTO,FLOW,ILOUPFXSET)= FLOWSHAREOUT2IN(Y,IA,IPROCFROM,IPROCTO,FLOW,ILOUPFXSET);
*IFLOWSHAREOUT2OUT_Y(IA,PROC,IFLOWIN,IFLOWOUT,IFLOWOUT2,ILOUPFXSET)=FLOWSHAREOUT2OUT(Y,IA,PROC,IFLOWIN,IFLOWOUT,IFLOWOUT2,ILOUPFXSET);

*IFLOWSHAREIN2IN_Y(IA,PROC,IFLOWIN,IFLOWIN2,ILOUPFXSET)=FLOWSHAREIN2IN(Y,IA,PROC,IFLOWIN,IFLOWIN2,ILOUPFXSET);
*IPRIOVARIOUTSUM_Y(IA,PROC,IFLOWIN,IFLOWOUT)=IPRIOVARIOUTSUM(Y,IA,PROC,IFLOWIN,IFLOWOUT);
*IPRIOVARIINSUM_Y(IA,PROC,IFLOWIN,IFLOWOUT)=IPRIOVARIINSUM(Y,IA,PROC,IFLOWIN,IFLOWOUT);
*INEGPROCININFLOW_Y(IA,PROC,IFLOWIN,IFLOWIN2)=INEGPROCININFLOW(Y,IA,PROC,IFLOWIN,IFLOWIN2);
*INEGPROCOUTOUTFLOW_Y(IA,PROC,IFLOWOUT,IFLOWOUT2)=INEGPROCOUTOUTFLOW(Y,IA,PROC,IFLOWOUT,IFLOWOUT2);
*ILEAVEPROC_Y(IA,IPROCFROM,IFLOWOUT)=ILEAVEPROC(Y,IA,IPROCFROM,IFLOWOUT);
*IENTERPROC_Y(IA,IPROCTO,FLOW)=IENTERPROC(Y,IA,IPROCTO,FLOW);
*IPROCKAPFX(AAA,PROC)=PROCKAPFX(Y,AAA,PROC);
*IPROCSTORAGEBOUND(AAA,PROC)=PROCSTORAGEBOUND(Y,AAA,PROC);
*ISOSIBU2INDIC(PROC,FLOW,FLOWINDIC)=SOSIBU2INDIC(Y,PROC,FLOW,FLOWINDIC);

*IEQFLOW_Y(CCCRRRAAA,PROC,FLOW)=EQFLOW(Y,CCCRRRAAA,PROC,FLOW);
*IMAXFLOW_Y(CCCRRRAAA,PROC,FLOW)=MAXFLOW(Y,CCCRRRAAA,PROC,FLOW);
*IMINFLOW_Y(CCCRRRAAA,PROC,FLOW)=MINFLOW(Y,CCCRRRAAA,PROC,FLOW);


*IPROCKAPFX(Y,AAA,PROC,FLOW)=PROCKAPFX(Y,AAA,PROC);

*Rasmus + Mason, outcommented this, it is important to include - Ida help!!!:)   now we outcommented the IPROCKAPFXINV ; substituted by PROCKAPFXINV

*IPROCKAPFXINV(Y,AAA,PROC)=SUM(IYALIAS$((YVALUE(IYALIAS) GT (YVALUE(Y)-PROCDATA(PROC,'PROCLIFETIME'))) AND (YVALUE(IYALIAS) LT YVALUE(Y))),PROCKAPFXINV(IYALIAS,AAA,PROC));

IPROCKAPFXINV(Y,AAA,PROC)=SUM(IY411$((YVALUE(IY411) GT (YVALUE(Y)-PROCDATA(PROC,'PROCLIFETIME'))) AND (YVALUE(IY411) LT YVALUE(Y))),PROCKAPFXINV(IY411,AAA,PROC));


*IPROCKAPFXINV_Y(AAA,PROC)=IPROCKAPFXINV(Y,AAA,PROC);
*Updating of the existing capacity
*PROCKAPFX(Y,AAA,PROC)=PROCKAPFX(Y,AAA,PROC)+PROCKAPFXINV(Y,AAA,PROC);

*PROCKAPFX(Y,AAA,PROC)=PROCKAPFX(Y,AAA,PROC)+PROCKAPFXINV(Y,AAA,PROC)+IPROCKAPFXINV(Y,AAA,PROC);
PROCKAPFX(Y,AAA,PROC,FLOW,IFLOWINOUT)=PROCKAPFX(Y,AAA,PROC,FLOW,IFLOWINOUT)+IPROCKAPFXINV(Y,AAA,PROC);



VPROCKAPNEW.FX(Y,IA,IPROCFROM)$((NOT IAPROCKAPNEW(Y,IA,IPROCFROM)) AND (SUM((IPROCTO,FLOW)$PROCKAPDATA(Y,IPROCFROM,FLOW,'IFLOWINOUT_OUT'),FLOWFROMTOPROC(Y,IA,IPROCFROM,IPROCTO,FLOW))))=0;
VPROCKAPNEW.FX(Y,IA,IPROCTO)$((NOT IAPROCKAPNEW(Y,IA,IPROCTO)) AND (SUM((IPROCFROM,FLOW)$PROCKAPDATA(Y,IPROCTO,FLOW,'IFLOWINOUT_IN'),FLOWFROMTOPROC(Y,IA,IPROCFROM,IPROCTO,FLOW))))=0;


LOOP((Y,IA,IPROCFROM,IPROCTO,FLOW)$FLOWFROMTOPROC(Y,IA,IPROCFROM,IPROCTO,FLOW),
  IF(FLOWFROMTOPROC(Y,IA,IPROCFROM,IPROCTO,FLOW) AND(PROCKAPDATA(Y,IPROCFROM,FLOW,'IFLOWINOUT_OUT') AND PROCKAPFX(Y,IA,IPROCFROM,FLOW,'IFLOWINOUT_OUT') AND (NOT APROCKAPNEW(Y,IA,IPROCFROM)) AND (NOT PROCSTORAGE(IPROCFROM)) AND (NOT PROCSTORAGE_Y(IPROCFROM))),
    VFLOW.UP(Y,IA,IPROCFROM,IPROCTO,FLOW,S,T) = PROCKAPFX(Y,IA,IPROCFROM,FLOW,'IFLOWINOUT_OUT'));
  IF(FLOWFROMTOPROC(Y,IA,IPROCFROM,IPROCTO,FLOW) AND (PROCKAPDATA(Y,IPROCTO,FLOW,'IFLOWINOUT_IN') AND PROCKAPFX(Y,IA,IPROCTO,FLOW,'IFLOWINOUT_IN') AND (NOT APROCKAPNEW(Y,IA,IPROCTO))   AND (NOT PROCSTORAGE_Y(IPROCTO)) AND (NOT PROCSTORAGE_Y(IPROCTO))),
         VFLOW.UP(Y,IA,IPROCFROM,IPROCTO,FLOW,S,T) = PROCKAPFX(Y,IA,IPROCTO,FLOW,'IFLOWINOUT_IN'););
);

LOOP((Y,IA,IPROCFROM,PROCSTORAGE,FLOW)$FLOWFROMTOPROC(Y,IA,IPROCFROM,PROCSTORAGE,FLOW),
  IF(FLOWFROMTOPROC(Y,IA,IPROCFROM,PROCSTORAGE,FLOW) AND (PROCKAPDATA(Y,PROCSTORAGE,FLOW,'IFLOWINOUT_IN') AND PROCSTORAGEBOUND(Y,IA,PROCSTORAGE)  AND (NOT APROCKAPNEW(Y,IA,PROCSTORAGE))),
         VSTORAGEVOL.UP(Y,IA,PROCSTORAGE,FLOW,S,T)= PROCSTORAGEBOUND(Y,IA,PROCSTORAGE););
);

LOOP((Y,IA,IPROCFROM,PROCSTORAGE_Y,FLOW)$FLOWFROMTOPROC(Y,IA,IPROCFROM,PROCSTORAGE_Y,FLOW),
  IF(FLOWFROMTOPROC(Y,IA,IPROCFROM,PROCSTORAGE_Y,FLOW) AND (PROCKAPDATA(Y,PROCSTORAGE_Y,FLOW,'IFLOWINOUT_IN') AND PROCSTORAGEBOUND(Y,IA,PROCSTORAGE_Y)  AND (NOT APROCKAPNEW(Y,IA,PROCSTORAGE_Y))),
         VSTORAGEVOL_Y.UP(Y,IA,PROCSTORAGE_Y,FLOW,S)= PROCSTORAGEBOUND(Y,IA,PROCSTORAGE_Y););
);


*Fix those Source, Sink of Buffer Flows that have been given a value in ISOSIBUBOUND_Y and SOSIBUFLOW_VAR_T.
VFLOWSOURCE.LO(Y,IA,PROCSOURCE,FLOW,S,T)$(ILEAVEPROC(Y,IA,PROCSOURCE,FLOW) AND ISOSIBUFLOW_SUMST(IA,PROCSOURCE,FLOW) AND SOSIBUBOUND(Y,IA,PROCSOURCE,FLOW,'ILOUPFX_LO'))
   = (SOSIBUBOUND(Y,IA,PROCSOURCE,FLOW,'ILOUPFX_LO')*SOSIBUFLOW_VAR_T(IA,PROCSOURCE,FLOW,S,T))/ ISOSIBUFLOW_SUMST(IA,PROCSOURCE,FLOW);
VFLOWSOURCE.UP(Y,IA,PROCSOURCE,FLOW,S,T)$(ILEAVEPROC(Y,IA,PROCSOURCE,FLOW) AND ISOSIBUFLOW_SUMST(IA,PROCSOURCE,FLOW) AND SOSIBUBOUND(Y,IA,PROCSOURCE,FLOW,'ILOUPFX_UP'))
   = (SOSIBUBOUND(Y,IA,PROCSOURCE,FLOW,'ILOUPFX_UP')*SOSIBUFLOW_VAR_T(IA,PROCSOURCE,FLOW,S,T))/ ISOSIBUFLOW_SUMST(IA,PROCSOURCE,FLOW);
VFLOWSOURCE.FX(Y,IA,PROCSOURCE,FLOW,S,T)$(ILEAVEPROC(Y,IA,PROCSOURCE,FLOW) AND ISOSIBUFLOW_SUMST(IA,PROCSOURCE,FLOW) AND SOSIBUBOUND(Y,IA,PROCSOURCE,FLOW,'ILOUPFX_FX'))
   = (SOSIBUBOUND(Y,IA,PROCSOURCE,FLOW,'ILOUPFX_FX')*SOSIBUFLOW_VAR_T(IA,PROCSOURCE,FLOW,S,T))/ ISOSIBUFLOW_SUMST(IA,PROCSOURCE,FLOW);
VFLOWSINK.LO(Y,IA,PROCSINK,FLOW,S,T)$(IENTERPROC(Y,IA,PROCSINK,FLOW) AND ISOSIBUFLOW_SUMST(IA,PROCSINK,FLOW) AND SOSIBUBOUND(Y,IA,PROCSINK,FLOW,'ILOUPFX_LO'))
   = (SOSIBUBOUND(Y,IA,PROCSINK,FLOW,'ILOUPFX_LO')*SOSIBUFLOW_VAR_T(IA,PROCSINK,FLOW,S,T)) / ISOSIBUFLOW_SUMST(IA,PROCSINK,FLOW); !! SEEMS
VFLOWSINK.UP(Y,IA,PROCSINK,FLOW,S,T)$(IENTERPROC(Y,IA,PROCSINK,FLOW) AND ISOSIBUFLOW_SUMST(IA,PROCSINK,FLOW) AND SOSIBUBOUND(Y,IA,PROCSINK,FLOW,'ILOUPFX_UP'))
   = (SOSIBUBOUND(Y,IA,PROCSINK,FLOW,'ILOUPFX_UP')*SOSIBUFLOW_VAR_T(IA,PROCSINK,FLOW,S,T)) / ISOSIBUFLOW_SUMST(IA,PROCSINK,FLOW); !! SEEMS
VFLOWSINK.FX(Y,IA,PROCSINK,FLOW,S,T)$(IENTERPROC(Y,IA,PROCSINK,FLOW) AND ISOSIBUFLOW_SUMST(IA,PROCSINK,FLOW) AND SOSIBUBOUND(Y,IA,PROCSINK,FLOW,'ILOUPFX_FX'))
   = (SOSIBUBOUND(Y,IA,PROCSINK,FLOW,'ILOUPFX_FX')*SOSIBUFLOW_VAR_T(IA,PROCSINK,FLOW,S,T)) / ISOSIBUFLOW_SUMST(IA,PROCSINK,FLOW); !! SEEMS
VFLOWBUFFER.LO(Y,IA,PROCBUFFER,FLOW,S,T)$((IENTERPROC(Y,IA,PROCBUFFER,FLOW) OR ILEAVEPROC(Y,IA,PROCBUFFER,FLOW)) AND ISOSIBUFLOW_SUMST(IA,PROCBUFFER,FLOW) AND SOSIBUBOUND(Y,IA,PROCBUFFER,FLOW,'ILOUPFX_LO'))
    = (SOSIBUBOUND(Y,IA,PROCBUFFER,FLOW,'ILOUPFX_LO')*SOSIBUFLOW_VAR_T(IA,PROCBUFFER,FLOW,S,T)) / ISOSIBUFLOW_SUMST(IA,PROCBUFFER,FLOW);
VFLOWBUFFER.UP(Y,IA,PROCBUFFER,FLOW,S,T)$((IENTERPROC(Y,IA,PROCBUFFER,FLOW) OR ILEAVEPROC(Y,IA,PROCBUFFER,FLOW)) AND ISOSIBUFLOW_SUMST(IA,PROCBUFFER,FLOW) AND SOSIBUBOUND(Y,IA,PROCBUFFER,FLOW,'ILOUPFX_UP'))
    = (SOSIBUBOUND(Y,IA,PROCBUFFER,FLOW,'ILOUPFX_UP')*SOSIBUFLOW_VAR_T(IA,PROCBUFFER,FLOW,S,T)) / ISOSIBUFLOW_SUMST(IA,PROCBUFFER,FLOW);
VFLOWBUFFER.FX(Y,IA,PROCBUFFER,FLOW,S,T)$((IENTERPROC(Y,IA,PROCBUFFER,FLOW) OR ILEAVEPROC(Y,IA,PROCBUFFER,FLOW)) AND ISOSIBUFLOW_SUMST(IA,PROCBUFFER,FLOW) AND SOSIBUBOUND(Y,IA,PROCBUFFER,FLOW,'ILOUPFX_FX'))
    = (SOSIBUBOUND(Y,IA,PROCBUFFER,FLOW,'ILOUPFX_FX')*SOSIBUFLOW_VAR_T(IA,PROCBUFFER,FLOW,S,T)) / ISOSIBUFLOW_SUMST(IA,PROCBUFFER,FLOW);


