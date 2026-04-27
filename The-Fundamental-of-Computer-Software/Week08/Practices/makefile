TASK = net
OBJ = a b c
ND = a.ND b.ND c.ND

all: $(TASK)

$(TASK): abc index
	c2n $^ net sfile

abc: $(ND)
	cat $^ >abc 

%.ND: ND %
	c2d $< $*

clean:
	rm -f $(TASK) $(ND) abc sfile
