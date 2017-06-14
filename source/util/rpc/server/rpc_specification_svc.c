/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "rpc_specification.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

#define DEVICE_PROPERTIES "/etc/device.properties"

static void
rpc_tool1_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		rpc_CommandBuf executecommand_1_arg;
		rpc_CommandBuf exec_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case EXECUTECOMMAND:
		_xdr_argument = (xdrproc_t) xdr_rpc_CommandBuf;
		_xdr_result = (xdrproc_t) xdr_rpc_CommandBuf;
		local = (char *(*)(char *, struct svc_req *)) executecommand_1_svc;
		break;
	
	case exec:
		_xdr_argument = (xdrproc_t) xdr_rpc_CommandBuf;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) exec_1_svc;
		break;		

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (RPC_TOOL1, RPC_TOOL1_V1);

        FILE *fPointer;
        char buf[512] = {0} ; 
        const char splitChar[2] = "=";
        char* token;
        unsigned long ulIpAddress;
        int found=0;
        int udpSock, tcpSock;
        int ret;
        struct sockaddr_in ip_addr;
        memset(&ip_addr, '\0', sizeof(ip_addr));

        // Get PEER_ARPING_IP from device.properties file
        fPointer = fopen(DEVICE_PROPERTIES, "r");
        if(fPointer)
        {
            while (fgets(buf, sizeof(buf), fPointer))
            {
              token = strtok(buf, splitChar);
              while(token != NULL)
              {
#ifdef _COSA_INTEL_USG_ATOM_
                if(!strcmp("PEER_ARPING_IP",token))
#elif _COSA_INTEL_USG_ARM_
                if(!strcmp("HOST_ARPING_IP",token))
#else
                if(!strcmp("PEER_ARPING_IP",token))
#endif
                {
                  printf("rpcserver - %s, ARPING_IP found\n",__FUNCTION__);
                  token = strtok(NULL, splitChar);
                  printf("rpcserver - %s,token of ip : %s\n",__FUNCTION__,token);
                  //Populate values for socket creation and break form loop
                  ip_addr.sin_family = AF_INET;
                  ip_addr.sin_addr.s_addr = inet_addr(token);
                  found=1;
                  break;
                }
                else
                {
                   printf("rpcserver - %s, ARPING_IP NOT found\n",__FUNCTION__);
                   token=NULL;
                }
              }
              
              if (found==1)
                 break;
            }
            fclose(fPointer);
        }
        else
        {
            printf("rpcserver - %s, fPointer is NULL, can't open /etc/device.properties\n",__FUNCTION__);
        }
     
        // If ARPING_IP is not found, then start rpcserver on RPC_ANYSOCK 
        if(found==0)
        {
            printf("rpcserver - %s, ARPING_IP NOT found, starting udp rpcserver on RPC_ANYSOCK\n",__FUNCTION__);
            transp = svcudp_create(RPC_ANYSOCK);
        }
        else
        {
            //Create UDP socket and bind it before passing to svcudp_create()
            printf("rpcserver - %s, Starting udp rpcserver on ARPING_IP\n",__FUNCTION__);
            udpSock=socket(AF_INET, SOCK_DGRAM, 0);
            if (udpSock < 0) {
               printf("rpcserver - %s, udp socket creation failed\n",__FUNCTION__);
               return udpSock;
            }
            int yes=1; 
            if (setsockopt(udpSock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0)
            {
               printf("rpcserver - %s setsockopt failed\n",__FUNCTION__);
               exit(1);
            }
            ret = bind(udpSock, (struct sockaddr*)(&ip_addr), sizeof(ip_addr));
            if (ret < 0) {
               printf("rpcserver - %s, bind failed %d\n",__FUNCTION__,ret);
               return ret;
            }
            transp = svcudp_create(udpSock);
        }
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, RPC_TOOL1, RPC_TOOL1_V1, rpc_tool1_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (RPC_TOOL1, RPC_TOOL1_V1, udp).");
		exit(1);
	}

        // If ARPING_IP is not found, then start rpcserver on RPC_ANYSOCK
        if(found==0)
        {
            printf("rpcserver - %s, ARPING_IP NOT found, starting tcp rpcserver on RPC_ANYSOCK\n",__FUNCTION__);
	    transp = svctcp_create(RPC_ANYSOCK, 0, 0);
        }
        else
        {
            //Create TCP socket and bind it before passing to svctcp_create()
            printf("rpcserver - %s, Starting tcp rpcserver on ARPING_IP\n",__FUNCTION__);
            tcpSock = socket(AF_INET, SOCK_STREAM, 0);
            if(tcpSock < 0 )
            {
               printf("rpcserver - %s, tcp socket creation failed\n",__FUNCTION__);
               return tcpSock;
            }
            int yes=1;
            if (setsockopt(tcpSock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0)
            {
               printf("rpcserver - %s tcp setsockopt failed\n",__FUNCTION__);
               exit(1);
            }
       
            ret = bind(tcpSock, (struct sockaddr*)(&ip_addr), sizeof(ip_addr));
            if (ret < 0) {
               printf("rpcserver - %s, bind failed\n",__FUNCTION__);
               return ret;
            }
       	    transp = svctcp_create(tcpSock, 0, 0);
        }
        found=0;

	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, RPC_TOOL1, RPC_TOOL1_V1, rpc_tool1_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (RPC_TOOL1, RPC_TOOL1_V1, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
