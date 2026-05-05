%token      BEGIN_  END_  INPUT_  OUTPUT_  ALWAYS_
%token      LEFT  RIGHT  ASSIGN  COLON  COMMA  SEMI  LB  RB
%token      <stri>  NAME 
%token      <intg>  INTG
%union      {char   stri[100];
            int     intg;}
%start      dffFile
%%
dffFile:    BEGIN_ dffSpec pinSpec END_ {getLastNet();};
dffSpec:    dffName LEFT portList RIGHT SEMI;
portList:   INPUT_ portClock COMMA
            INPUT_ portD COMMA
            OUTPUT_ portQ;
pinSpec:    ALWAYS_ LEFT pinClock RIGHT pinState;
pinState:   netSpec 
        |   pinState netSpec;
dffName:    NAME{getDffName($1);};
portClock:  NAME{getPortClock($1);};
portD:      NAME{getPortD($1);};
portQ:      NAME{getPortQ($1);};
pinClock:   NAME{getPinClock($1);};
netSpec:    NAME ASSIGN NAME SEMI{getNet($1,$3);};
%%
#include "lex.yy.c"
void parse()
{
    yyparse();
    fclose(yyin);
}
