TASK=	dffNetS
OBJ=	dffNetS.o y.tab.o
$(TASK): $(OBJ)
	cc -o $@ $(OBJ)
.c.o:
	cc -c $<
y.tab.c:yacc.y lex.yy.c
	yacc yacc.y 
lex.yy.c: lex.l
	lex lex.l
clean:; rm $(OBJ) lex.yy.c y.tab.c 
