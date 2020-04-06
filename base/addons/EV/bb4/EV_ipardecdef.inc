$ifi not %EV_PROFILE_AVG%==yes  $goto NO_EV_PROFILE_AVG
PARAMETER IEV_BEV_Dumb(YYY,SSS,TTT,RRR);
PARAMETER IEV_BEV_SOCDumb(YYY,SSS,TTT,RRR);
PARAMETER IEV_BEV_Flex(YYY,SSS,TTT,RRR);
PARAMETER IEV_BEV_Inflex(YYY,SSS,TTT,RRR);
PARAMETER IEV_BEV_SOCFlex(YYY,SSS,TTT,RRR);
PARAMETER IEV_BEV_Avail(YYY,SSS,TTT,RRR);
PARAMETER IEV_BEV_Max(YYY,SSS,TTT,RRR);
PARAMETER IEV_BEV_Min(YYY,SSS,TTT,RRR);
PARAMETER IEV_PHEV_Dumb(YYY,SSS,TTT,RRR);
PARAMETER IEV_PHEV_SOCDumb(YYY,SSS,TTT,RRR);
PARAMETER IEV_PHEV_Flex(YYY,SSS,TTT,RRR);
PARAMETER IEV_PHEV_Inflex(YYY,SSS,TTT,RRR);
PARAMETER IEV_PHEV_SOCFlex(YYY,SSS,TTT,RRR);
PARAMETER IEV_PHEV_Avail(YYY,SSS,TTT,RRR);
PARAMETER IEV_PHEV_Max(YYY,SSS,TTT,RRR);
PARAMETER IEV_PHEV_Min(YYY,SSS,TTT,RRR);

LOOP(SSS$S(SSS),
   LOOP(TTT$T(TTT),
         IEV_BEV_Dumb(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_BEV_Dumb(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
         IEV_BEV_SOCDumb(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_BEV_SOCDumb(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
         IEV_BEV_Flex(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_BEV_Flex(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
         IEV_BEV_Inflex(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_BEV_Inflex(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
         IEV_BEV_SOCFlex(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_BEV_SOCFlex(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
         IEV_BEV_Avail(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_BEV_Avail(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
         IEV_BEV_Max(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_BEV_Max(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
         IEV_BEV_Min(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_BEV_Min(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
         IEV_PHEV_Dumb(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_PHEV_Dumb(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
         IEV_PHEV_SOCDumb(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_PHEV_SOCDumb(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
         IEV_PHEV_Flex(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_PHEV_Flex(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
         IEV_PHEV_Inflex(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_PHEV_Inflex(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
         IEV_PHEV_SOCFlex(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_PHEV_SOCFlex(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
         IEV_PHEV_Avail(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_PHEV_Avail(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
         IEV_PHEV_Max(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_PHEV_Max(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
         IEV_PHEV_Min(Y,SSS,TTT,IR)=SUM(ITTTALIAS$((ORD(ITTTALIAS) - CHRONOHOUR(SSS,TTT)) LT ORD(TTT) AND ORD(ITTTALIAS) GE ORD(TTT)),EV_PHEV_Min(Y,SSS,ITTTALIAS,IR)/CHRONOHOUR(SSS,TTT));
   );
);

*Replacing values
EV_BEV_Dumb(Y,S,T,IR)=IEV_BEV_Dumb(Y,S,T,IR);
EV_BEV_SOCDumb(Y,S,T,IR)=IEV_BEV_SOCDumb(Y,S,T,IR);
EV_BEV_Flex(Y,S,T,IR)=IEV_BEV_Flex(Y,S,T,IR);
EV_BEV_Inflex(Y,S,T,IR)=IEV_BEV_Inflex(Y,S,T,IR);
EV_BEV_SOCFlex(Y,S,T,IR)=IEV_BEV_SOCFlex(Y,S,T,IR);
EV_BEV_Avail(Y,S,T,IR)=IEV_BEV_Avail(Y,S,T,IR);
EV_BEV_Max(Y,S,T,IR)=IEV_BEV_Max(Y,S,T,IR);
EV_BEV_Min(Y,S,T,IR)=IEV_BEV_Min(Y,S,T,IR);
EV_PHEV_Dumb(Y,S,T,IR)=IEV_PHEV_Dumb(Y,S,T,IR);
EV_PHEV_SOCDumb(Y,S,T,IR)=IEV_PHEV_SOCDumb(Y,S,T,IR);
EV_PHEV_Flex(Y,S,T,IR)=IEV_PHEV_Flex(Y,S,T,IR);
EV_PHEV_Inflex(Y,S,T,IR)=IEV_PHEV_Inflex(Y,S,T,IR);
EV_PHEV_SOCFlex(Y,S,T,IR)=IEV_PHEV_SOCFlex(Y,S,T,IR);
EV_PHEV_Avail(Y,S,T,IR)=IEV_PHEV_Avail(Y,S,T,IR);
EV_PHEV_Max(Y,S,T,IR)=IEV_PHEV_Max(Y,S,T,IR);
EV_PHEV_Min(Y,S,T,IR)=IEV_PHEV_Min(Y,S,T,IR);

*Cleaning not used parameters
IEV_BEV_Dumb(YYY,S,TTT,RRR)=0;
IEV_BEV_SOCDumb(YYY,S,TTT,RRR)=0;
IEV_BEV_Flex(YYY,S,TTT,RRR)=0;
IEV_BEV_Inflex(YYY,S,TTT,RRR)=0;
IEV_BEV_SOCFlex(YYY,S,TTT,RRR)=0;
IEV_BEV_Avail(YYY,S,TTT,RRR)=0;
IEV_BEV_Max(YYY,S,TTT,RRR)=0;
IEV_BEV_Min(YYY,S,TTT,RRR)=0;
IEV_PHEV_Dumb(YYY,S,TTT,RRR)=0;
IEV_PHEV_SOCDumb(YYY,S,TTT,RRR)=0;
IEV_PHEV_Flex(YYY,S,TTT,RRR)=0;
IEV_PHEV_Inflex(YYY,S,TTT,RRR)=0;
IEV_PHEV_SOCFlex(YYY,S,TTT,RRR)=0;
IEV_PHEV_Avail(YYY,S,TTT,RRR)=0;
IEV_PHEV_Max(YYY,S,TTT,RRR)=0;
IEV_PHEV_Min(YYY,S,TTT,RRR)=0;

$label NO_EV_PROFILE_AVG

*Cleaning parameters not used in the simulation
EV_BEV_Dumb(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
EV_BEV_SOCDumb(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
EV_BEV_Flex(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
EV_BEV_Inflex(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
EV_BEV_SOCFlex(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
EV_BEV_Avail(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
EV_BEV_Max(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
EV_BEV_Min(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
EV_PHEV_Dumb(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
EV_PHEV_SOCDumb(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
EV_PHEV_Flex(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
EV_PHEV_Inflex(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
EV_PHEV_SOCFlex(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
EV_PHEV_Avail(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
EV_PHEV_Max(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;
EV_PHEV_Min(YYY,SSS,TTT,RRR)$((NOT Y(YYY)) OR (NOT IR(RRR)) OR (NOT S(SSS)) OR (NOT T(TTT))) = 0;