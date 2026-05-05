%{
#define	RETURN_S(TOKEN)	strcpy(yylval.stri, yytext);return((TOKEN));
#define	RETURN_D(TOKEN)	sscanf(yytext, "%d", &yylval.intg); return(TOKEN);
%}
A		[A-Za-z]
D		[0-9]
%%
endmodule	return(END_);
module		return(BEGIN_);
input		return(INPUT_);
output		return(OUTPUT_);
always@		return(ALWAYS_);
"("		return(LEFT);
")"		return(RIGHT);
"<="		return(ASSIGN);
\,		return(COMMA);
:		return(COLON);
;		return(SEMI);
"["		return(LB);
"]"		return(RB);
{A}({A}|{D}|_)*	{RETURN_S(NAME);}
{D}+		{RETURN_D(INTG);}
[\40\n\t]	;
%%
int yyerror(char *s)
{
	fprintf(stderr, "ERROR [%s]\n", yytext);
}
int yywrap()
{
	return(1);
}

