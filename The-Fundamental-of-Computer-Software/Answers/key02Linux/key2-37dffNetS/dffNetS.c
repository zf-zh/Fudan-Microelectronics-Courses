/* File: dffNetS.c
  	[exe2-27] compile serial dff in Verilog	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PORT struct port
#define NET struct net
PORT
{
	char portName[16];
	PORT *next;
};
NET
{
	char netName[16];
	PORT *port;
	NET *next;
};
int  bit=0;
char DffName[10];
char portD[10], portQ[10], portClock[10];
char pinD[10]="D", pinQ[10]="Q", pinClock[10]="CK";
char prevNet[10];
char NamePort[10];
NET *Net=NULL, *netClock=NULL;
void error(char *string)
{
	printf("%s\n", string);
	exit(0);
}
void getDffName(char *string)
{
	strcpy(DffName, string);
}
void getPortD(char *string)
{
	strcpy(portD, string);
}
void getPortQ(char *string)
{
	strcpy(portQ, string);
}
void getPinClock(char *string)
{
	strcpy(pinClock, string);
}
NET *makeNet(char *netName)
{
	NET *net;
	if((net = (NET*)malloc(sizeof(NET))) == NULL)
		error("fail to create NET!");
	strcpy(net->netName, netName);
	net->port = NULL;
	net->next = Net;
	Net = net;
	return(net);
}
void makePort(NET *net)
{
	PORT *port;
	if((port = (PORT*)malloc(sizeof(PORT))) == NULL)
		error("fail to create PORT!");
	strcpy(port->portName, NamePort);
	port->next = net->port;
	net->port = port;
}
void getPortClock(char *string)
{
	strcpy(portClock, string);
	/* make a net for netClock			*/
	/* complete the following code	*/
	netClock = makeNet(portClock);
	/* make and insert portClock into netClock	*/
	/* complete the following code	*/
	strcpy(NamePort, portClock);
	makePort(netClock);
}
void getNet(char *netQ, char *netD)
{
	NET *net;
	if(bit == 0)
	{
		if(strcmp(netD, portD) != 0)
			error("portD != prime input!");
		/* make and insert a net for netD	*/
		net = makeNet(netD);
		/* keep netQ as prevNet	*/
		strcpy(prevNet, netQ);
		/* make and insert a port for pinD	*/
		strcpy(NamePort, netD);
		makePort(net);
	}
	else
	{
		if(strcmp(netD, prevNet) != 0)
			error("netD != prevNet!");
		/* make and insert a port for netD	*/
		net = makeNet(netD);
		/* keep netQ as prevNet	*/
		strcpy(prevNet, netQ);
		/* make and insert a port for pinQ	*/
		sprintf(NamePort, "%s%d->%s\0", DffName, bit-1, pinQ);
		makePort(net);
	}
	/* make and insert a port for pinD	*/
	sprintf(NamePort, "%s%d->%s\0", DffName, bit, pinD);
	makePort(net);
	/* make and insert a port in netClock for pinClock	*/
	sprintf(NamePort, "%s%d->%s\0", DffName, bit, pinClock);
	makePort(netClock);
	bit++;
}
void getLastNet()
{
	NET *net;
	/* make and insert last net	*/
	/* because (# of net) == (# of assign state) + 1	*/
	net = makeNet(portQ);
	/* make and insert a port for last pinQ	*/
	sprintf(NamePort, "%s%d->%s\0", DffName, bit-1, pinQ);
	makePort(net);
	/* make and insert a port for portQ	*/
	strcpy(NamePort, portQ);
	makePort(net);
}
void prtPort(PORT *port)
{
	if(port == NULL)
		return;
	prtPort(port->next);
	printf(" %s", port->portName);
}
void prtNet(NET *net)
{
	if(net == NULL)
		return;
	prtNet(net->next);
	printf("%s", net->netName);
	prtPort(net->port);
	printf(";\n");
}
int main()
{
	yyparse();
	prtNet(Net);
}
