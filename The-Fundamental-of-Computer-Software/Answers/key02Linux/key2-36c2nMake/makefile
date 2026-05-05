# FUNC: make file for task "net"	
TASK =	net 
NDfile = a.ND b.ND c.ND
$(TASK): abc
	c2n abc index net sfile
abc:	${NDfile}
	cat ${NDfile} >abc
a.ND:	ND
	c2d ND a
b.ND:	ND
	c2d ND b
c.ND:	ND
	c2d ND c
clean:;	rm ${NDfile} $(TASK) abc sfile
