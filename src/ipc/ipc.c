/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id$
    begin       : Fri May 07 2004
    copyright   : (C) 2004 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <strings.h>

#include "ipc_p.h"
#include <gwenhywfar/net.h>
#include <gwenhywfar/debug.h>
#include <gwenhywfar/base64.h>
#include <gwenhywfar/nettransportsock.h>
#include <gwenhywfar/nettransportssl.h>


GWEN_LIST_FUNCTIONS(GWEN_IPCNODE, GWEN_IPCNode)
GWEN_LIST_FUNCTIONS(GWEN_IPCMSG, GWEN_IPCMsg)
GWEN_LIST_FUNCTIONS(GWEN_IPC__REQUEST, GWEN_IPC__Request)


static GWEN_TYPE_UINT32 gwen_ipc__lastid=0;


/* _________________________________________________________________________
 * AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
 *                                IPC Node
 * YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
 */


/* -------------------------------------------------------------- FUNCTION */
GWEN_IPCNODE *GWEN_IPCNode_new(){
  GWEN_IPCNODE *n;

  GWEN_NEW_OBJECT(GWEN_IPCNODE, n);
  DBG_MEM_INC("GWEN_IPCNODE", 0);
  GWEN_LIST_INIT(GWEN_IPCNODE, n);

  if (gwen_ipc__lastid==0)
    gwen_ipc__lastid=time(0);
  n->id=++gwen_ipc__lastid;
  n->usage=1;
  return n;
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPCNode_free(GWEN_IPCNODE *n){
  if (n) {
    DBG_MEM_DEC("GWEN_IPCNODE");
    assert(n->usage);
    if (--(n->usage)==0) {
      GWEN_NetConnection_free(n->connection);
      free(n->baseAuth);
      GWEN_LIST_FINI(GWEN_IPCNODE, n);
      GWEN_FREE_OBJECT(n);
    }
  }
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPCNode_Attach(GWEN_IPCNODE *n){
  assert(n);
  DBG_MEM_INC("GWEN_IPCNODE", 1);
  n->usage++;
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPCNode_Dump(GWEN_IPCNODE *n, FILE *f, int indent){
  int i;

  assert(n);
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "---------------------------------------\n");
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "IPC Node:\n");
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Id               : %08x\n", n->id);
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Mark             : %d\n", n->mark);
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Usage            : %d\n", n->usage);
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Is Server        : ");
  if (n->isServer)
    fprintf(f, "yes\n");
  else
    fprintf(f, "no\n");
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Is Passive Client: ");
  if (n->isPassiveClient)
    fprintf(f, "yes\n");
  else
    fprintf(f, "no\n");
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Base Auth        : %s\n", n->baseAuth);
}







/* _________________________________________________________________________
 * AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
 *                                IPC Message
 * YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
 */

/* -------------------------------------------------------------- FUNCTION */
GWEN_IPCMSG *GWEN_IPCMsg_new(GWEN_IPCNODE *n){
  GWEN_IPCMSG *m;

  assert(n);
  GWEN_NEW_OBJECT(GWEN_IPCMSG, m);
  DBG_MEM_INC("GWEN_IPCMSG", 0);
  GWEN_LIST_INIT(GWEN_IPCMSG, m);
  m->node=n;
  GWEN_IPCNode_Attach(m->node);
  return m;
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPCMsg_free(GWEN_IPCMSG *m){
  if (m) {
    DBG_MEM_DEC("GWEN_IPCMSG");
    GWEN_IPCNode_free(m->node);
    GWEN_DB_Group_free(m->db);
    GWEN_LIST_FINI(GWEN_IPCMSG, m);
    GWEN_FREE_OBJECT(m);
  }
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPCMsg_Dump(GWEN_IPCMSG *m, FILE *f, int indent){
  int i;

  assert(m);
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "---------------------------------------\n");
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "IPC Message:\n");
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Id               : %08x\n", m->id);
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "RefId            : %08x\n", m->refId);
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Node Id          : %08x\n", m->node->id);
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "DB:\n");
  GWEN_DB_Dump(m->db, f, indent+4);
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Send Time        : %s",
	  (m->sendTime)?ctime(&(m->sendTime)):"never\n");
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Receiption Time  : %s",
	  (m->receivedTime)?ctime(&(m->receivedTime)):"never\n");
}






/* _________________________________________________________________________
 * AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
 *                                IPC Request
 * YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
 */


/* -------------------------------------------------------------- FUNCTION */
GWEN_IPC__REQUEST *GWEN_IPC__Request_new(){
  GWEN_IPC__REQUEST *r;

  GWEN_NEW_OBJECT(GWEN_IPC__REQUEST, r);
  DBG_MEM_INC("GWEN_IPC__REQUEST", 0);
  GWEN_LIST_INIT(GWEN_IPC__REQUEST, r);

  r->requestMsgs=GWEN_IPCMsg_List_new();
  r->responseMsgs=GWEN_IPCMsg_List_new();
  r->usage=1;
  return r;
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPC__Request_free(GWEN_IPC__REQUEST *r){
  if (r) {
    assert(r->usage);
    if (--(r->usage)==0) {
      DBG_MEM_DEC("GWEN_IPC__REQUEST");
      GWEN_IPCMsg_List_free(r->responseMsgs);
      GWEN_IPCMsg_List_free(r->requestMsgs);
      GWEN_LIST_FINI(GWEN_IPC__REQUEST, r);
      GWEN_FREE_OBJECT(r);
    }
  }
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPC__Request_Attach(GWEN_IPC__REQUEST *r){
  assert(r);
  assert(r->usage);
  r->usage++;
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPC__Request_AddRequestMsg(GWEN_IPC__REQUEST *r, GWEN_IPCMSG *m){
  assert(r);
  assert(m);
  GWEN_IPCMsg_List_Add(m, r->requestMsgs);
}



/* -------------------------------------------------------------- FUNCTION */
GWEN_IPCMSG_LIST *GWEN_IPC__Request_GetRequestMsgList(const GWEN_IPC__REQUEST *r){
  assert(r);
  return r->requestMsgs;
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPC__Request_AddResponseMsg(GWEN_IPC__REQUEST *r, GWEN_IPCMSG *m){
  assert(r);
  assert(m);
  GWEN_IPCMsg_List_Add(m, r->responseMsgs);
}



/* -------------------------------------------------------------- FUNCTION */
int GWEN_IPC__Request_HasRequestMsg(GWEN_IPC__REQUEST *r,
                                  GWEN_TYPE_UINT32 nid,
				  GWEN_TYPE_UINT32 id){
  GWEN_IPCMSG *m;

  assert(r);
  assert(id);

  m=GWEN_IPCMsg_List_First(r->requestMsgs);
  while(m) {
    if (m->node->id==nid &&
	m->id==id)
      return 1;
    m=GWEN_IPCMsg_List_Next(m);
  } /* while */

  return 0;
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPC__Request_Dump(GWEN_IPC__REQUEST *r, FILE *f, int indent){
  int i;
  GWEN_IPCMSG *m;

  assert(r);
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "---------------------------------------\n");
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "IPC Request:\n");
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Id               : %08x\n", r->id);
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Request Message(s)\n");
  m=GWEN_IPCMsg_List_First(r->requestMsgs);
  if (!m) {
    for (i=0; i<indent+4; i++)
      fprintf(f, " ");
    fprintf(f, "none\n");
  }
  while(m) {
    GWEN_IPCMsg_Dump(m, f, indent+4);
    m=GWEN_IPCMsg_List_Next(m);
  }
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Response Message(s)\n");
  m=GWEN_IPCMsg_List_First(r->responseMsgs);
  if (!m) {
    for (i=0; i<indent+4; i++)
      fprintf(f, " ");
    fprintf(f, "none\n");
  }
  while(m) {
    GWEN_IPCMsg_Dump(m, f, indent+4);
    m=GWEN_IPCMsg_List_Next(m);
  }
}







/* _________________________________________________________________________
 * AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
 *                                IPC Manager
 * YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
 */




/* -------------------------------------------------------------- FUNCTION */
GWEN_IPCMANAGER *GWEN_IPCManager_new(){
  GWEN_IPCMANAGER *mgr;

  GWEN_NEW_OBJECT(GWEN_IPCMANAGER, mgr);
  DBG_MEM_INC("GWEN_IPCMANAGER", 0);
  mgr->libId=GWEN_Net_GetLibraryId();
  mgr->nodes=GWEN_IPCNode_List_new();
  mgr->outRequests=GWEN_IPC__Request_List_new();
  mgr->newInRequests=GWEN_IPC__Request_List_new();
  mgr->oldInRequests=GWEN_IPC__Request_List_new();

  mgr->usage=1;
  return mgr;
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPCManager_Attach(GWEN_IPCMANAGER *mgr){
  assert(mgr);
  DBG_MEM_INC("GWEN_IPCMANAGER", 1);
  mgr->usage++;
}




/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPCManager_free(GWEN_IPCMANAGER *mgr){
  if (mgr) {
    DBG_MEM_DEC("GWEN_IPCMANAGER");
    assert(mgr->usage);
    if (--(mgr->usage)==0) {
      free(mgr->application);
      GWEN_IPC__Request_List_free(mgr->oldInRequests);
      GWEN_IPC__Request_List_free(mgr->newInRequests);
      GWEN_IPC__Request_List_free(mgr->outRequests);
      GWEN_IPCNode_List_free(mgr->nodes);

      GWEN_FREE_OBJECT(mgr);
    }
  }
}



/* -------------------------------------------------------------- FUNCTION */
const char *GWEN_IPCManager_GetApplicationName(const GWEN_IPCMANAGER *mgr) {
  assert(mgr);
  return mgr->application;
}


/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPCManager_SetApplicationName(GWEN_IPCMANAGER *mgr,
                                        const char *s){
  assert(mgr);
  if (s) mgr->application=strdup(s);
  else mgr->application=0;
}



/* -------------------------------------------------------------- FUNCTION */
GWEN_TYPE_UINT32 GWEN_IPCManager_AddServer(GWEN_IPCMANAGER *mgr,
                                           GWEN_NETTRANSPORT *tr,
                                           GWEN_TYPE_UINT32 mark){
  GWEN_NETCONNECTION *conn;
  GWEN_IPCNODE *n;

  /* create connection layer */
  conn=GWEN_NetConnectionHTTP_new(tr,
                                  1,              /* take */
                                  mgr->libId,     /* libId */
                                  1,0);           /* protocol version */
  GWEN_NetConnectionHTTP_AddMode(conn, GWEN_NETCONN_MODE_IPC);
  GWEN_Net_AddConnectionToPool(conn);
  if (GWEN_NetConnection_StartListen(conn)) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Could not start server");
    GWEN_NetConnection_free(conn);
    return 0;
  }

  n=GWEN_IPCNode_new();
  n->connection=conn;
  n->mark=mark;
  n->isServer=1;
  GWEN_IPCNode_List_Add(n, mgr->nodes);
  return n->id;
}



/* -------------------------------------------------------------- FUNCTION */
GWEN_TYPE_UINT32 GWEN_IPCManager_AddClient(GWEN_IPCMANAGER *mgr,
                                           GWEN_NETTRANSPORT *tr,
                                           const char *userName,
                                           const char *passwd,
                                           GWEN_TYPE_UINT32 mark){
  GWEN_NETCONNECTION *conn;
  GWEN_IPCNODE *n;

  n=GWEN_IPCNode_new();
  if (userName) {
    GWEN_BUFFER *abuf;
    GWEN_BUFFER *ebuf;

    abuf=GWEN_Buffer_new(0, strlen(userName)+strlen(passwd)+2, 0, 1);
    GWEN_Buffer_AppendString(abuf, userName);
    GWEN_Buffer_AppendByte(abuf, ':');
    GWEN_Buffer_AppendString(abuf, passwd);
    ebuf=GWEN_Buffer_new(0, GWEN_Buffer_GetUsedBytes(abuf)*4/3+16, 0, 1);
    GWEN_Buffer_AppendString(ebuf, "BASIC ");
    if (GWEN_Base64_Encode(/* GCC4 pointer-signedness fix: */ (const unsigned char*)GWEN_Buffer_GetStart(abuf),
                           GWEN_Buffer_GetUsedBytes(abuf),
                           ebuf, 0)) {
      DBG_ERROR(GWEN_LOGDOMAIN, "Could not encode authorization data");
      GWEN_Buffer_free(ebuf);
      GWEN_Buffer_free(abuf);
      GWEN_IPCNode_free(n);
      return 0;
    }
    n->baseAuth=strdup(GWEN_Buffer_GetStart(ebuf));
    GWEN_Buffer_free(ebuf);
    GWEN_Buffer_free(abuf);
  }
  /* create connection layer */
  conn=GWEN_NetConnectionHTTP_new(tr,
                                  1,              /* take */
                                  mgr->libId,     /* libId */
                                  1,0);           /* protocol version */
  GWEN_NetConnectionHTTP_AddMode(conn, GWEN_NETCONN_MODE_IPC);
  GWEN_Net_AddConnectionToPool(conn);
  GWEN_NetConnection_SetUpFn(conn, GWEN_IPCManager__Connection_Up);
  GWEN_NetConnection_SetDownFn(conn, GWEN_IPCManager__Connection_Down);
  n->connection=conn;
  n->mark=mark;
  n->isServer=0;
  GWEN_IPCNode_List_Add(n, mgr->nodes);
  return n->id;
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPCManager__RemoveNodeRequestMessages(GWEN_IPCMANAGER *mgr,
						GWEN_IPCNODE *n,
                                                GWEN_IPC__REQUEST_LIST *rl,
                                                const char *msgType) {
  GWEN_IPC__REQUEST *r;

  /* remove all messages for/of this client from request */
  r=GWEN_IPC__Request_List_First(rl);
  while(r) {
    GWEN_IPC__REQUEST *rnext;
    GWEN_IPCMSG *msg;

    rnext=GWEN_IPC__Request_List_Next(r);
    msg=GWEN_IPCMsg_List_First(r->requestMsgs);
    while(msg) {
      GWEN_IPCMSG *nextmsg;

      nextmsg=GWEN_IPCMsg_List_Next(msg);
      assert(msg->node);
      if (msg->node==n) {
        /* same node, remove msg */
	DBG_INFO(GWEN_LOGDOMAIN, "Removing %s message for/from node %08x",
		 msgType, n->id);
	if (GWEN_Logger_GetLevel(GWEN_LOGDOMAIN)>=GWEN_LoggerLevelInfo) {
	  if (msg->db) {
	    GWEN_DB_Dump(msg->db, stderr, 2);
	  }
	}
	GWEN_IPCMsg_List_Del(msg);
	GWEN_IPCMsg_free(msg);
      }
      msg=nextmsg;
    } /* while msg */

    /* check whether the request is empty */
    if (GWEN_IPCMsg_List_First(r->requestMsgs)==0) {
      /* it is, remove the request */
      DBG_INFO(GWEN_LOGDOMAIN, "Removing %s request %08x for/from node %08x",
	       msgType, r->id, n->id);
      GWEN_IPC__Request_List_Del(r);
      GWEN_IPC__Request_free(r);
    }
    r=rnext;
  } /* while r */
}



/* -------------------------------------------------------------- FUNCTION */
int GWEN_IPCManager_RemoveClient(GWEN_IPCMANAGER *mgr,
				 GWEN_TYPE_UINT32 nid) {
  GWEN_IPCNODE *n;

  DBG_DEBUG(GWEN_LOGDOMAIN, "Removing client %08x", nid);
  assert(mgr);

  /* get client node */
  n=GWEN_IPCNode_List_First(mgr->nodes);
  while(n) {
    if (n->id==nid)
      break;
    n=GWEN_IPCNode_List_Next(n);
  } /* while */
  if (!n) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Node %08x not found", nid);
    return -1;
  }

  /* remove all messages of this client in any request */
  GWEN_IPCManager__RemoveNodeRequestMessages(mgr, n, mgr->outRequests,
                                             "outRequest");
  GWEN_IPCManager__RemoveNodeRequestMessages(mgr, n, mgr->newInRequests,
                                             "newInRequest");
  GWEN_IPCManager__RemoveNodeRequestMessages(mgr, n, mgr->oldInRequests,
                                             "newOutRequest");
  /* remove node */
  GWEN_IPCNode_List_Del(n);
  GWEN_IPCNode_free(n);

  return 0;
}



/* -------------------------------------------------------------- FUNCTION */
GWEN_IPC__REQUEST *GWEN_IPCManager__FindRequest(GWEN_IPCMANAGER *mgr,
                                              GWEN_TYPE_UINT32 rid,
					      GWEN_IPC__REQUEST *r) {
  assert(mgr);
  assert(r);

  while(r) {
    if (r->id==rid)
      return r;
    r=GWEN_IPC__Request_List_Next(r);
  }
  return 0;
}



/* -------------------------------------------------------------- FUNCTION */
int GWEN_IPCManager__SendMsg(GWEN_IPCMANAGER *mgr,
                             GWEN_IPCMSG *m) {
  GWEN_BUFFER *buf;
  GWEN_BUFFEREDIO *bio;
  GWEN_ERRORCODE err;
  GWEN_DB_NODE *dbReq;
  GWEN_DB_NODE *dbCmd;
  GWEN_DB_NODE *dbVars;
  GWEN_DB_NODE *dbHeader;
  char numbuf[16];

  buf=GWEN_Buffer_new(0, 512, 0, 1);
  bio=GWEN_BufferedIO_Buffer2_new(buf, 0); /* don't relinquish buffer */

  /* encode db */
  GWEN_BufferedIO_SetWriteBuffer(bio, 0, 128);
  if (GWEN_DB_WriteToStream(m->db, bio, GWEN_DB_FLAGS_COMPACT)) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Could not encode db");
    GWEN_BufferedIO_Abandon(bio);
    GWEN_BufferedIO_free(bio);
    GWEN_Buffer_free(buf);
    return -1;
  }

  err=GWEN_BufferedIO_Close(bio);
  if (!GWEN_Error_IsOk(err)) {
    DBG_ERROR_ERR(GWEN_LOGDOMAIN, err);
    GWEN_BufferedIO_free(bio);
    GWEN_Buffer_free(buf);
    return -1;
  }
  GWEN_BufferedIO_free(bio);

  dbReq=GWEN_DB_Group_new("request");
  /* prepare command */
  dbCmd=GWEN_DB_GetGroup(dbReq, GWEN_DB_FLAGS_DEFAULT, "command");
  assert(dbCmd);

  GWEN_DB_SetCharValue(dbCmd, GWEN_DB_FLAGS_DEFAULT,
                       "cmd", "put");
  if (mgr->application && *(mgr->application))
    GWEN_DB_SetCharValue(dbCmd, GWEN_DB_FLAGS_DEFAULT,
                         "url", mgr->application);
  else
    GWEN_DB_SetCharValue(dbCmd, GWEN_DB_FLAGS_DEFAULT,
                         "url", "/gwenipc/unspecified");

  /* prepare vars */
  dbVars=GWEN_DB_GetGroup(dbCmd, GWEN_DB_FLAGS_DEFAULT, "vars");
  assert(dbVars);
  snprintf(numbuf, sizeof(numbuf), "%d", m->id);
  GWEN_DB_SetCharValue(dbVars, GWEN_DB_FLAGS_DEFAULT,
                       "id", numbuf);
  if (m->refId) {
    snprintf(numbuf, sizeof(numbuf), "%d", m->refId);
    GWEN_DB_SetCharValue(dbVars, GWEN_DB_FLAGS_DEFAULT,
                         "refid", numbuf);
  }

  GWEN_DB_SetCharValue(dbVars, GWEN_DB_FLAGS_DEFAULT,
                       "cmd", GWEN_DB_GroupName(m->db));

  /* prepare header */
  dbHeader=GWEN_DB_GetGroup(dbReq, GWEN_DB_FLAGS_DEFAULT, "header");
  assert(dbHeader);
  GWEN_DB_SetCharValue(dbHeader, GWEN_DB_FLAGS_DEFAULT,
                       "connection", "keep-alive");
  GWEN_DB_SetCharValue(dbHeader, GWEN_DB_FLAGS_DEFAULT,
                       "cache-control", "no-store");
  GWEN_DB_SetCharValue(dbHeader, GWEN_DB_FLAGS_DEFAULT,
                       "user-agent", "Gwenhywfar v"
                       GWENHYWFAR_VERSION_FULL_STRING);
  if (m->node->baseAuth)
    GWEN_DB_SetCharValue(dbHeader, GWEN_DB_FLAGS_DEFAULT,
                         "authorization", m->node->baseAuth);

  GWEN_DB_SetCharValue(dbHeader, GWEN_DB_FLAGS_DEFAULT,
                       "content-type",
                       "application/gwenipc");
  snprintf(numbuf, sizeof(numbuf), "%d", GWEN_Buffer_GetUsedBytes(buf));
  GWEN_DB_SetCharValue(dbHeader, GWEN_DB_FLAGS_DEFAULT,
                       "content-length",
                       numbuf);

  /* check for connection state, connect if necessary */
  if (GWEN_NetConnection_GetStatus(m->node->connection)==
      GWEN_NetTransportStatusPDisconnected) {
    if (GWEN_NetConnection_GetFlags(m->node->connection) &
	GWEN_NETTRANSPORT_FLAGS_RESTARTABLE) {
      /* reenable disconnected connection */
      DBG_INFO(GWEN_LOGDOMAIN, "Re-enabling disconnected connection");
      GWEN_NetConnection_SetStatus(m->node->connection,
				   GWEN_NetTransportStatusUnconnected);
    }
  }

  if (GWEN_NetConnection_GetStatus(m->node->connection)==
      GWEN_NetTransportStatusUnconnected) {
    DBG_INFO(GWEN_LOGDOMAIN, "Starting connection");
    if (GWEN_NetConnection_StartConnect(m->node->connection)) {
      DBG_ERROR(GWEN_LOGDOMAIN, "Could not start connection");
      GWEN_DB_Group_free(dbReq);
      return -1;
    }
  }

  /* send message */
  if (GWEN_NetConnectionHTTP_AddRequest(m->node->connection,
                                        dbReq,
                                        buf,
                                        0)) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Could not send message");
    GWEN_DB_Group_free(dbReq);
    return -1;
  }

  DBG_DEBUG(GWEN_LOGDOMAIN, "Message is on its way");
  m->sendTime=time(0);
  GWEN_DB_Group_free(dbReq);
  return 0;
}



/* -------------------------------------------------------------- FUNCTION */
GWEN_NETTRANSPORT_STATUS
GWEN_IPCManager_CheckConnection(GWEN_IPCMANAGER *mgr,
				GWEN_TYPE_UINT32 nid) {
  GWEN_NETCONNECTION_WORKRESULT res;
  GWEN_IPCNODE *n;

  n=GWEN_IPCNode_List_First(mgr->nodes);
  while(n) {
    if (n->id==nid)
      break;
    n=GWEN_IPCNode_List_Next(n);
  } /* while */
  if (!n) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Node %08x not found", nid);
    return GWEN_NetTransportStatusDisabled;
  }
  res=GWEN_NetConnection_WorkIO(n->connection);
  if (res==GWEN_NetConnectionWorkResult_Error) {
    DBG_ERROR(GWEN_LOGDOMAIN, "WorkIO reported an error");
  }
  return GWEN_NetConnection_GetStatus(n->connection);
}



/* -------------------------------------------------------------- FUNCTION */
GWEN_TYPE_UINT32 GWEN_IPCManager_SendRequest(GWEN_IPCMANAGER *mgr,
                                             GWEN_TYPE_UINT32 nid,
                                             GWEN_DB_NODE *req){
  GWEN_IPCNODE *n;
  GWEN_IPC__REQUEST *r;
  GWEN_IPCMSG *m;

  n=GWEN_IPCNode_List_First(mgr->nodes);
  while(n) {
    if (n->id==nid)
      break;
    n=GWEN_IPCNode_List_Next(n);
  } /* while */
  if (!n) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Node %08x not found", nid);
    return 0;
  }

  m=GWEN_IPCMsg_new(n);
  m->db=req;
  m->id=++(n->nextMsgId);

  if (GWEN_IPCManager__SendMsg(mgr, m)) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Could not send request");
    GWEN_IPCMsg_free(m);
    return 0;
  }

  r=GWEN_IPC__Request_new();
  r->id=++gwen_ipc__lastid;
  GWEN_IPC__Request_AddRequestMsg(r, m);
  GWEN_IPC__Request_List_Add(r, mgr->outRequests);
  return r->id;
}



/* -------------------------------------------------------------- FUNCTION */
GWEN_TYPE_UINT32 GWEN_IPCManager_SendMultiRequest(GWEN_IPCMANAGER *mgr,
                                                  GWEN_TYPE_UINT32 mark,
                                                  GWEN_DB_NODE *req){
  GWEN_IPCNODE *n;
  GWEN_IPC__REQUEST *r;

  r=0;
  n=GWEN_IPCNode_List_First(mgr->nodes);
  while(n) {
    if (mark==0 || mark==n->mark) {
      GWEN_NETTRANSPORT_STATUS st;

      st=GWEN_NetConnection_GetStatus(n->connection);
      if (st!=GWEN_NetTransportStatusListening &&
          st!=GWEN_NetTransportStatusDisabled) {
        GWEN_IPCMSG *m;

        m=GWEN_IPCMsg_new(n);
        m->db=GWEN_DB_Group_dup(req);
        m->id=--(n->nextMsgId);

        if (GWEN_IPCManager__SendMsg(mgr, m)) {
          DBG_ERROR(GWEN_LOGDOMAIN, "Could not send request to node %08x", n->id);
          GWEN_IPCMsg_free(m);
        }
        else {
          if (r==0) {
            r=GWEN_IPC__Request_new();
	    r->id=++gwen_ipc__lastid;
            GWEN_IPC__Request_List_Add(r, mgr->outRequests);
          }
          GWEN_IPC__Request_AddRequestMsg(r, m);
        }
      }
    } /* if mark matches */
    n=GWEN_IPCNode_List_Next(n);
  } /* while */

  if (r) {
    return r->id;
  }
  DBG_ERROR(GWEN_LOGDOMAIN, "Could not send any request");
  return 0;
}



/* -------------------------------------------------------------- FUNCTION */
int GWEN_IPCManager_SendResponse(GWEN_IPCMANAGER *mgr,
                                 GWEN_TYPE_UINT32 rid,
                                 GWEN_DB_NODE *rsp){
  GWEN_IPC__REQUEST *r;
  GWEN_IPCMSG *m;
  GWEN_IPCMSG *om;

  r=GWEN_IPC__Request_List_First(mgr->oldInRequests);
  while(r) {
    if (r->id==rid)
      break;
    r=GWEN_IPC__Request_List_Next(r);
  } /* while */
  if (!r) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Request %08x not found", rid);
    return -1;
  }

  om=GWEN_IPCMsg_List_First(r->requestMsgs);
  assert(om);

  m=GWEN_IPCMsg_new(om->node);
  m->refId=om->id;
  m->db=rsp;
  m->id=++(om->node->nextMsgId);

  DBG_DEBUG(GWEN_LOGDOMAIN, "Sending response %08x for request %08x",
	    m->id, m->refId);

  if (GWEN_IPCManager__SendMsg(mgr, m)) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Could not send response");
    GWEN_IPCMsg_free(m);
    return -1;
  }

  GWEN_IPC__Request_AddResponseMsg(r, m);
  return 0;
}



/* -------------------------------------------------------------- FUNCTION */
int GWEN_IPCManager_RemoveRequest(GWEN_IPCMANAGER *mgr,
                                  GWEN_TYPE_UINT32 rid,
                                  int inOrOut){
  GWEN_IPC__REQUEST *r;

  if (inOrOut==0)
    r=GWEN_IPC__Request_List_First(mgr->oldInRequests);
  else
    r=GWEN_IPC__Request_List_First(mgr->outRequests);
  while(r) {
    if (r->id==rid)
      break;
    r=GWEN_IPC__Request_List_Next(r);
  } /* while */
  if (!r) {
    DBG_ERROR(GWEN_LOGDOMAIN, "%s request %08x not found",
	      inOrOut?"Outgoing":"Incoming", rid);
    return -1;
  }
  GWEN_IPC__Request_List_Del(r);
  GWEN_IPC__Request_free(r);
  return 0;
}



/* -------------------------------------------------------------- FUNCTION */
GWEN_TYPE_UINT32 GWEN_IPCManager_GetNextInRequest(GWEN_IPCMANAGER *mgr,
                                                  GWEN_TYPE_UINT32 mark){
  GWEN_IPC__REQUEST *r;

  r=GWEN_IPC__Request_List_First(mgr->newInRequests);
  while(r) {
    GWEN_IPCMSG *om;

    if (mark==0)
      break;

    om=GWEN_IPCMsg_List_First(r->requestMsgs);
    assert(om);
    assert(om->node);
    if (om->node->mark==mark)
      break;
    r=GWEN_IPC__Request_List_Next(r);
  }

  if (r) {
    GWEN_IPC__Request_List_Del(r);
    GWEN_IPC__Request_List_Add(r, mgr->oldInRequests);
    return r->id;
  }
  return 0;
}



/* -------------------------------------------------------------- FUNCTION */
GWEN_DB_NODE *GWEN_IPCManager_GetInRequestData(GWEN_IPCMANAGER *mgr,
                                               GWEN_TYPE_UINT32 rid){
  GWEN_IPC__REQUEST *r;
  GWEN_IPCMSG *om;

  r=GWEN_IPC__Request_List_First(mgr->oldInRequests);
  while(r) {
    if (r->id==rid)
      break;
    r=GWEN_IPC__Request_List_Next(r);
  } /* while */
  if (!r) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Request %08x not found", rid);
    return 0;
  }

  om=GWEN_IPCMsg_List_First(r->requestMsgs);
  assert(om);

  return om->db;
}



/* -------------------------------------------------------------- FUNCTION */
GWEN_NETCONNECTION *GWEN_IPCManager_GetConnection(GWEN_IPCMANAGER *mgr,
                                                  GWEN_TYPE_UINT32 nid){
  GWEN_IPCNODE *n;

  n=GWEN_IPCNode_List_First(mgr->nodes);
  while(n) {
    if (n->id==nid)
      break;
    n=GWEN_IPCNode_List_Next(n);
  } /* while */
  if (!n) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Node %08x not found", nid);
    return 0;
  }

  return n->connection;
}



/* -------------------------------------------------------------- FUNCTION */
GWEN_TYPE_UINT32
GWEN_IPCManager_GetClientForConnection(const GWEN_IPCMANAGER *mgr,
                                       const GWEN_NETCONNECTION *conn) {
  GWEN_IPCNODE *n;

  n=GWEN_IPCNode_List_First(mgr->nodes);
  while(n) {
    if (n->connection==conn)
      break;
    n=GWEN_IPCNode_List_Next(n);
  } /* while */
  if (!n) {
    DBG_ERROR(GWEN_LOGDOMAIN, "No node found for connection");
    return 0;
  }
  return n->id;
}



/* -------------------------------------------------------------- FUNCTION */
GWEN_DB_NODE *GWEN_IPCManager_PeekResponseData(GWEN_IPCMANAGER *mgr,
                                               GWEN_TYPE_UINT32 rid){
  GWEN_IPC__REQUEST *r;
  GWEN_IPCMSG *m;
  GWEN_DB_NODE *db;

  r=GWEN_IPC__Request_List_First(mgr->outRequests);
  while(r) {
    if (r->id==rid)
      break;
    r=GWEN_IPC__Request_List_Next(r);
  } /* while */
  if (!r) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Request %08x not found", rid);
    return 0;
  }

  m=GWEN_IPCMsg_List_First(r->responseMsgs);
  if (!m) {
    DBG_DEBUG(GWEN_LOGDOMAIN, "No response yet");
    return 0;
  }
  db=m->db;
  assert(m->node);
  assert(m->node->id);
  return db;
}



/* -------------------------------------------------------------- FUNCTION */
GWEN_DB_NODE *GWEN_IPCManager_GetResponseData(GWEN_IPCMANAGER *mgr,
                                              GWEN_TYPE_UINT32 rid){
  GWEN_IPC__REQUEST *r;
  GWEN_IPCMSG *m;
  GWEN_DB_NODE *db;

  r=GWEN_IPC__Request_List_First(mgr->outRequests);
  while(r) {
    if (r->id==rid)
      break;
    r=GWEN_IPC__Request_List_Next(r);
  } /* while */
  if (!r) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Request %08x not found", rid);
    return 0;
  }

  m=GWEN_IPCMsg_List_First(r->responseMsgs);
  if (!m) {
    DBG_VERBOUS(GWEN_LOGDOMAIN, "No response yet");
    return 0;
  }

  db=m->db;
  assert(m->node);
  assert(m->node->id);
  m->db=0;
  GWEN_IPCMsg_List_Del(m);
  GWEN_IPCMsg_free(m);
  return db;
}



/* -------------------------------------------------------------- FUNCTION */
int GWEN_IPCManager__Collect(GWEN_IPCMANAGER *mgr, int maxMsg) {
  GWEN_IPCNODE *n;
  int msgs;

  msgs=0;
  n=GWEN_IPCNode_List_First(mgr->nodes);
  while(n && (maxMsg==0 || msgs<maxMsg)) {
    GWEN_NETMSG *nm;

    DBG_DEBUG(GWEN_LOGDOMAIN, "Checking node");
    if (n->isServer) {
      GWEN_NETTRANSPORT *tr;

      DBG_DEBUG(GWEN_LOGDOMAIN, "Node is a server");
      /* collect connections */
      tr=GWEN_NetConnection_GetNextIncoming(n->connection);
      if (tr) {
        GWEN_NETCONNECTION *newconn;
        GWEN_IPCNODE *newnode;

        DBG_INFO(GWEN_LOGDOMAIN, "Got an incoming connection");
        newconn=GWEN_NetConnectionHTTP_new(tr,
                                           1,          /* take */
                                           mgr->libId, /* libId */
                                           1,0);       /* protocol version */
        GWEN_NetConnectionHTTP_AddMode(newconn, GWEN_NETCONN_MODE_IPC);
        GWEN_NetConnection_SetUserMark(newconn,
                                       GWEN_NetConnection_GetUserMark
                                       (n->connection));
        GWEN_NetConnection_SetUpFn(newconn, GWEN_IPCManager__Connection_Up);
        GWEN_NetConnection_SetDownFn(newconn,
				     GWEN_IPCManager__Connection_Down);
        newnode=GWEN_IPCNode_new();
        newnode->connection=newconn;
	newnode->mark=n->mark;
	newnode->isPassiveClient=1;
        GWEN_IPCNode_List_Add(newnode, mgr->nodes);
        GWEN_Net_AddConnectionToPool(newconn);
        GWEN_NetConnection_Up(newconn);
      }
      else {
        DBG_DEBUG(GWEN_LOGDOMAIN, "No incoming connection");
      }
    }
    else {
      DBG_DEBUG(GWEN_LOGDOMAIN, "Node is NOT a server");
      nm=GWEN_NetConnection_GetInMsg(n->connection);
      if (nm) {
        GWEN_DB_NODE *dbCmd;
        GWEN_TYPE_UINT32 msgId;
        GWEN_TYPE_UINT32 refId;

        DBG_DEBUG(GWEN_LOGDOMAIN, "Got an incoming message");
        if (GWEN_Logger_GetLevel(0)>=GWEN_LoggerLevelDebug)
          GWEN_DB_Dump(GWEN_NetMsg_GetDB(nm), stderr, 10);
        dbCmd=GWEN_DB_GetGroup(GWEN_NetMsg_GetDB(nm),
                               GWEN_PATH_FLAGS_NAMEMUSTEXIST,
                               "command");
        assert(dbCmd);
        msgId=GWEN_DB_GetIntValue(dbCmd, "vars/id", 0, 0);
        refId=GWEN_DB_GetIntValue(dbCmd, "vars/refId", 0, 0);

        if (msgId<=n->lastMsgId) {
	  DBG_ERROR(GWEN_LOGDOMAIN, "Bad message id (%d<=%d)",
		    msgId, n->lastMsgId);
	}
	else {
	  GWEN_DB_NODE *dbMsg;
	  GWEN_DB_NODE *dbBody;
	  GWEN_BUFFER *mbuf;
	  GWEN_TYPE_UINT32 pos;
          int msgError;

          msgError=0;
          n->lastMsgId=msgId;
	  dbMsg=GWEN_DB_Group_new("msg");
	  GWEN_DB_AddGroupChildren(dbMsg, GWEN_NetMsg_GetDB(nm));
	  GWEN_DB_SetIntValue(dbMsg, GWEN_DB_FLAGS_OVERWRITE_VARS,
			      "ipc/nodeId", n->id);
	  GWEN_DB_SetIntValue(dbMsg, GWEN_DB_FLAGS_OVERWRITE_VARS,
			      "ipc/msgId", msgId);
	  dbBody=GWEN_DB_GetGroup(dbMsg, GWEN_DB_FLAGS_DEFAULT, "body");

          mbuf=GWEN_NetMsg_GetBuffer(nm);
          assert(mbuf);
          pos=GWEN_Buffer_GetBookmark(mbuf, 1);
	  if (pos && pos<GWEN_Buffer_GetUsedBytes(mbuf)) {
	    GWEN_BUFFEREDIO *bio;

	    GWEN_Buffer_SetPos(mbuf, pos);
	    GWEN_Buffer_SetPos(mbuf, pos);
	    bio=GWEN_BufferedIO_Buffer2_new(mbuf, 0);
	    GWEN_BufferedIO_SetReadBuffer(bio, 0, 128);

	    if (GWEN_DB_ReadFromStream(dbBody, bio,
				       GWEN_DB_FLAGS_DEFAULT|
				       GWEN_PATH_FLAGS_CREATE_GROUP)){
	      DBG_WARN(GWEN_LOGDOMAIN, "Bad message received (invalid body)");
              GWEN_DB_Group_free(dbMsg);
	      msgError=1;
	    }
	    GWEN_BufferedIO_free(bio);
	  }

	  if (msgError) {
	    DBG_WARN(GWEN_LOGDOMAIN, "Bad message received (invalid body)");
          }
	  else {
	    /* found a valid body */
	    if (refId) {
	      GWEN_IPC__REQUEST *r;

	      /* it pretends to be a response, check it */
	      GWEN_DB_SetIntValue(dbMsg, GWEN_DB_FLAGS_OVERWRITE_VARS,
				  "ipc/refId", refId);
	      r=GWEN_IPC__Request_List_First(mgr->outRequests);
	      while(r) {
		if (GWEN_IPC__Request_HasRequestMsg(r, n->id, refId))
		  break;
		r=GWEN_IPC__Request_List_Next(r);
	      } /* while r */
	      if (!r) {
		DBG_WARN(GWEN_LOGDOMAIN,
			 "Got a response for invalid request (%08x)",
			 refId);
		GWEN_DB_Group_free(dbMsg);
	      }
	      else {
		GWEN_IPCMSG *m;

		DBG_DEBUG(GWEN_LOGDOMAIN, "Got a response for request %08x",
			  r->id);
		m=GWEN_IPCMsg_new(n);
		m->db=dbMsg;
		m->id=msgId;
		m->refId=refId;
		m->receivedTime=time(0);
		GWEN_IPC__Request_AddResponseMsg(r, m);
	      }
	    }
	    else {
	      GWEN_IPC__REQUEST *r;
	      GWEN_IPCMSG *m;

	      /* this is a new incoming request */
	      DBG_DEBUG(GWEN_LOGDOMAIN, "Got an incoming request (%08x)",
			msgId);
	      m=GWEN_IPCMsg_new(n);
	      m->db=dbMsg;
	      m->id=msgId;
	      m->refId=refId;
	      m->receivedTime=time(0);
	      r=GWEN_IPC__Request_new();
	      r->id=++gwen_ipc__lastid;
	      GWEN_IPC__Request_AddRequestMsg(r, m);
	      GWEN_IPC__Request_List_Add(r, mgr->newInRequests);
	    }
	  } /* if body is valid */
	} /* if message id is ok */
	GWEN_NetMsg_free(nm);
        msgs++;
      } /* if there was a netmessage */
      else {
        DBG_DEBUG(GWEN_LOGDOMAIN, "No message");
      }
    } /* if listening */
    n=GWEN_IPCNode_List_Next(n);
  } /* while */

  return msgs;
}



/* -------------------------------------------------------------- FUNCTION */
GWEN_IPCMSG *GWEN_IPCManager__MakeErrorResponse(GWEN_IPCMANAGER *mgr,
                                                GWEN_IPCMSG *m,
                                                int code,
                                                const char *txt) {
  GWEN_DB_NODE *db;
  GWEN_IPCMSG *newm;

  db=GWEN_DB_Group_new("Error");
  GWEN_DB_SetIntValue(db, GWEN_DB_FLAGS_DEFAULT,
                      "code", code);
  if (txt)
    GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_DEFAULT,
                         "text", txt);

  newm=GWEN_IPCMsg_new(m->node);
  newm->db=db;
  return newm;
}



/* -------------------------------------------------------------- FUNCTION */
int GWEN_IPCManager__CheckRequests(GWEN_IPCMANAGER *mgr) {
  GWEN_IPC__REQUEST *r;

  r=GWEN_IPC__Request_List_First(mgr->outRequests);
  while(r) {
    GWEN_IPCMSG *m;
    GWEN_IPC__REQUEST *nextr;

    nextr=GWEN_IPC__Request_List_Next(r);
    m=GWEN_IPCMsg_List_First(r->requestMsgs);
    while(m) {
      GWEN_IPCMSG *nextm;
      int removeIt;

      nextm=GWEN_IPCMsg_List_Next(m);
      removeIt=0;
      assert(m->node);

      /* check connection status */
      assert(m->node->connection);
      if (GWEN_NetConnection_GetStatus(m->node->connection)==
          GWEN_NetTransportStatusDisabled) {
        GWEN_IPCMSG *errm;

        /* connection broken, remove msg */
        DBG_INFO(GWEN_LOGDOMAIN, "Connection broken");
        errm=GWEN_IPCManager__MakeErrorResponse(mgr,
                                                m,
                                                GWEN_IPC_ERROR_CONNERR,
                                                "Connection down");
        GWEN_IPCMsg_List_Add(errm, r->responseMsgs);
        removeIt=1;
      }

      /* check timeout */
      if (m->sendTime && mgr->sendTimeOut) {
        if (difftime(time(0), m->sendTime)>mgr->sendTimeOut) {
          GWEN_IPCMSG *errm;

          DBG_INFO(GWEN_LOGDOMAIN, "Message timed out");
          errm=GWEN_IPCManager__MakeErrorResponse(mgr,
                                                  m,
                                                  GWEN_IPC_ERROR_TIMEOUT,
                                                  "Message timed out");
          GWEN_IPCMsg_List_Add(errm, r->responseMsgs);
          removeIt=1;
        }
      }

      if (removeIt) {
        GWEN_IPCMsg_List_Del(m);
        GWEN_IPCMsg_free(m);
      }
      m=nextm;
    } /* while */

    r=nextr;
  } /* while */

  return 0;
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPCManager__Connection_Up(GWEN_NETCONNECTION *conn){
  char addrBuffer[128];

  GWEN_InetAddr_GetAddress(GWEN_NetConnection_GetPeerAddr(conn),
                           addrBuffer, sizeof(addrBuffer));

  DBG_INFO(GWEN_LOGDOMAIN, "Connection to %s (port %d) up",
           addrBuffer,
           GWEN_InetAddr_GetPort(GWEN_NetConnection_GetPeerAddr(conn)));
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPCManager__Connection_Down(GWEN_NETCONNECTION *conn){
  char addrBuffer[128];

  GWEN_InetAddr_GetAddress(GWEN_NetConnection_GetPeerAddr(conn),
                           addrBuffer, sizeof(addrBuffer));

  DBG_INFO(GWEN_LOGDOMAIN, "Connection to %s (port %d) down",
           addrBuffer,
           GWEN_InetAddr_GetPort(GWEN_NetConnection_GetPeerAddr(conn)));
}



/* -------------------------------------------------------------- FUNCTION */
int GWEN_IPCManager_Work(GWEN_IPCMANAGER *mgr, int maxmsg) {
  int msgs;

  assert(mgr);

  msgs=GWEN_IPCManager__Collect(mgr, maxmsg);
  if (msgs) {
    DBG_DEBUG(GWEN_LOGDOMAIN, "Collected %d messages", msgs);
  }

  if (GWEN_IPCManager__CheckRequests(mgr)) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Error checking requests");
  }

  return msgs?0:1;
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPCManager_SetUpFn(GWEN_IPCMANAGER *mgr,
                             GWEN_TYPE_UINT32 nid,
                             GWEN_NETCONNECTION_UPFN fn){
  GWEN_IPCNODE *n;

  n=GWEN_IPCNode_List_First(mgr->nodes);
  while(n) {
    if (n->id==nid)
      break;
    n=GWEN_IPCNode_List_Next(n);
  } /* while */
  if (!n) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Node %08x not found", nid);
    return;
  }

  GWEN_NetConnection_SetUpFn(n->connection, fn);
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPCManager_SetDownFn(GWEN_IPCMANAGER *mgr,
			       GWEN_TYPE_UINT32 nid,
			       GWEN_NETCONNECTION_DOWNFN fn){
  GWEN_IPCNODE *n;

  n=GWEN_IPCNode_List_First(mgr->nodes);
  while(n) {
    if (n->id==nid)
      break;
    n=GWEN_IPCNode_List_Next(n);
  } /* while */
  if (!n) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Node %08x not found", nid);
    return;
  }

  GWEN_NetConnection_SetDownFn(n->connection, fn);
}



/* -------------------------------------------------------------- FUNCTION */
int GWEN_IPCManager_Disconnect(GWEN_IPCMANAGER *mgr, GWEN_TYPE_UINT32 nid){
  GWEN_IPCNODE *n;
  int rv;

  n=GWEN_IPCNode_List_First(mgr->nodes);
  while(n) {
    if (n->id==nid)
      break;
    n=GWEN_IPCNode_List_Next(n);
  } /* while */
  if (!n) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Node %08x not found", nid);
    return -1;
  }

  n->nextMsgId=0;
  n->lastMsgId=0;

  /* remove all messages of this client in any request */
  GWEN_IPCManager__RemoveNodeRequestMessages(mgr, n, mgr->outRequests,
                                             "outRequest");
  GWEN_IPCManager__RemoveNodeRequestMessages(mgr, n, mgr->newInRequests,
                                             "newInRequest");
  GWEN_IPCManager__RemoveNodeRequestMessages(mgr, n, mgr->oldInRequests,
                                             "newOutRequest");

  rv=GWEN_NetConnection_StartDisconnect(n->connection);
  GWEN_NetConnection_Reset(n->connection);
  return rv;
}



/* -------------------------------------------------------------- FUNCTION */
void GWEN_IPCManager_Dump(GWEN_IPCMANAGER *mgr, FILE *f, int indent){
  int i;
  GWEN_IPCNODE *n;
  GWEN_IPC__REQUEST *r;

  assert(mgr);
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "=======================================\n");
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "IPC Manager:\n");
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Active Nodes     : %ld\n",
	  GWEN_MemoryDebug_GetObjectCount("GWEN_IPCNODE"));
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Active Messages  : %ld\n",
	  GWEN_MemoryDebug_GetObjectCount("GWEN_IPCMSG"));
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Active Requests  : %ld\n",
          GWEN_MemoryDebug_GetObjectCount("GWEN_IPC__REQUEST"));
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Application      : %s\n", mgr->application);
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Library Id       : %08x\n", mgr->libId);
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Nodes(s)\n");
  n=GWEN_IPCNode_List_First(mgr->nodes);
  if (!n) {
    for (i=0; i<indent+4; i++)
      fprintf(f, " ");
    fprintf(f, "none\n");
  }
  while(n) {
    GWEN_IPCNode_Dump(n, f, indent+4);
    n=GWEN_IPCNode_List_Next(n);
  }
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Outgoing Request(s)\n");
  r=GWEN_IPC__Request_List_First(mgr->outRequests);
  if (!r) {
    for (i=0; i<indent+4; i++)
      fprintf(f, " ");
    fprintf(f, "none\n");
  }
  while(r) {
    GWEN_IPC__Request_Dump(r, f, indent+4);
    r=GWEN_IPC__Request_List_Next(r);
  }
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Unhandled Incoming Request(s)\n");
  r=GWEN_IPC__Request_List_First(mgr->newInRequests);
  if (!r) {
    for (i=0; i<indent+4; i++)
      fprintf(f, " ");
    fprintf(f, "none\n");
  }
  while(r) {
    GWEN_IPC__Request_Dump(r, f, indent+4);
    r=GWEN_IPC__Request_List_Next(r);
  }
  for (i=0; i<indent; i++)
    fprintf(f, " ");
  fprintf(f, "Incoming Request(s) in Work\n");
  r=GWEN_IPC__Request_List_First(mgr->oldInRequests);
  if (!r) {
    for (i=0; i<indent+4; i++)
      fprintf(f, " ");
    fprintf(f, "none\n");
  }
  while(r) {
    GWEN_IPC__Request_Dump(r, f, indent+4);
    r=GWEN_IPC__Request_List_Next(r);
  }
}



















