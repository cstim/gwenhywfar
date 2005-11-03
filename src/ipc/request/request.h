/* This file is auto-generated from "request.xml" by the typemaker
   tool of Gwenhywfar. 
   Do not edit this file -- all changes will be lost! */
#ifndef REQUEST_H
#define REQUEST_H

/** @page P_GWEN_IPC_REQUEST_PUBLIC GWEN_IpcRequest (public)
This page describes the properties of GWEN_IPC_REQUEST
@anchor GWEN_IPC_REQUEST_Id
<h3>Id</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_IpcRequest_SetId, 
get it with @ref GWEN_IpcRequest_GetId
</p>

@anchor GWEN_IPC_REQUEST_Name
<h3>Name</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_IpcRequest_SetName, 
get it with @ref GWEN_IpcRequest_GetName
</p>

@anchor GWEN_IPC_REQUEST_IpcId
<h3>IpcId</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_IpcRequest_SetIpcId, 
get it with @ref GWEN_IpcRequest_GetIpcId
</p>

@anchor GWEN_IPC_REQUEST_Expires
<h3>Expires</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_IpcRequest_SetExpires, 
get it with @ref GWEN_IpcRequest_GetExpires
</p>

@anchor GWEN_IPC_REQUEST_SubRequests
<h3>SubRequests</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_IpcRequest_SetSubRequests, 
get it with @ref GWEN_IpcRequest_GetSubRequests
</p>

@anchor GWEN_IPC_REQUEST_Status
<h3>Status</h3>
<p>
Status of the request.</p>
<p>
Set this property with @ref GWEN_IpcRequest_SetStatus, 
get it with @ref GWEN_IpcRequest_GetStatus
</p>

*/
#ifdef __cplusplus
extern "C" {
#endif

typedef struct GWEN_IPC_REQUEST GWEN_IPC_REQUEST;

#ifdef __cplusplus
} /* __cplusplus */
#endif

#include <gwenhywfar/db.h>
#include <gwenhywfar/inherit.h>
#include <gwenhywfar/misc.h>
#include <gwenhywfar/list2.h>
#include <gwenhywfar/types.h>
#include <gwenhywfar/gwentime.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  GWEN_IpcRequest_StatusUnknown=-1,
  /** New request.  */
  GWEN_IpcRequest_StatusNew=0,
  /** Request has been sent, no answer has been received.  */
  GWEN_IpcRequest_StatusSent,
  /** Request has been answered partially.  */
  GWEN_IpcRequest_StatusPartial,
  /** Request has been answered completely..  */
  GWEN_IpcRequest_StatusAnswered,
  /** Request has been finished.  */
  GWEN_IpcRequest_StatusFinished
} GWEN_IPC_REQUEST_STATUS;

GWEN_IPC_REQUEST_STATUS GWEN_IpcRequest_Status_fromString(const char *s);
const char *GWEN_IpcRequest_Status_toString(GWEN_IPC_REQUEST_STATUS v);

typedef int (*GWEN_IPC_REQUEST_WORK_FN)(GWEN_IPC_REQUEST *st);

GWEN_INHERIT_FUNCTION_LIB_DEFS(GWEN_IPC_REQUEST, GWENHYWFAR_API)
GWEN_LIST_FUNCTION_LIB_DEFS(GWEN_IPC_REQUEST, GWEN_IpcRequest, GWENHYWFAR_API)
GWEN_IPC_REQUEST_LIST *GWEN_IpcRequest_List_dup(const GWEN_IPC_REQUEST_LIST *stl);

GWEN_LIST2_FUNCTION_LIB_DEFS(GWEN_IPC_REQUEST, GWEN_IpcRequest, GWENHYWFAR_API)

/** Destroys all objects stored in the given LIST2 and the list itself
*/
GWENHYWFAR_API void GWEN_IpcRequest_List2_freeAll(GWEN_IPC_REQUEST_LIST2 *stl);
/** Creates a deep copy of the given LIST2.
*/
GWENHYWFAR_API GWEN_IPC_REQUEST_LIST2 *GWEN_IpcRequest_List2_dup(const GWEN_IPC_REQUEST_LIST2 *stl);

/** Creates a new object.
*/
GWENHYWFAR_API GWEN_IPC_REQUEST *GWEN_IpcRequest_new();
/** Destroys the given object.
*/
GWENHYWFAR_API void GWEN_IpcRequest_free(GWEN_IPC_REQUEST *st);
/** Increments the usage counter of the given object, so an additional free() is needed to destroy the object.
*/
GWENHYWFAR_API void GWEN_IpcRequest_Attach(GWEN_IPC_REQUEST *st);
/** Creates and returns a deep copy of thegiven object.
*/
GWENHYWFAR_API GWEN_IPC_REQUEST *GWEN_IpcRequest_dup(const GWEN_IPC_REQUEST*st);
/** Creates an object from the data in the given GWEN_DB_NODE
*/
GWENHYWFAR_API GWEN_IPC_REQUEST *GWEN_IpcRequest_fromDb(GWEN_DB_NODE *db);
/** Stores an object in the given GWEN_DB_NODE
*/
GWENHYWFAR_API int GWEN_IpcRequest_toDb(const GWEN_IPC_REQUEST*st, GWEN_DB_NODE *db);
/** Returns 0 if this object has not been modified, !=0 otherwise
*/
GWENHYWFAR_API int GWEN_IpcRequest_IsModified(const GWEN_IPC_REQUEST *st);
/** Sets the modified state of the given object
*/
GWENHYWFAR_API void GWEN_IpcRequest_SetModified(GWEN_IPC_REQUEST *st, int i);


/**
* Returns the property @ref GWEN_IPC_REQUEST_Id
*/
GWENHYWFAR_API GWEN_TYPE_UINT32 GWEN_IpcRequest_GetId(const GWEN_IPC_REQUEST *el);
/**
* Set the property @ref GWEN_IPC_REQUEST_Id
*/
GWENHYWFAR_API void GWEN_IpcRequest_SetId(GWEN_IPC_REQUEST *el, GWEN_TYPE_UINT32 d);

/**
* Returns the property @ref GWEN_IPC_REQUEST_Name
*/
GWENHYWFAR_API const char *GWEN_IpcRequest_GetName(const GWEN_IPC_REQUEST *el);
/**
* Set the property @ref GWEN_IPC_REQUEST_Name
*/
GWENHYWFAR_API void GWEN_IpcRequest_SetName(GWEN_IPC_REQUEST *el, const char *d);

/**
* Returns the property @ref GWEN_IPC_REQUEST_IpcId
*/
GWENHYWFAR_API GWEN_TYPE_UINT32 GWEN_IpcRequest_GetIpcId(const GWEN_IPC_REQUEST *el);
/**
* Set the property @ref GWEN_IPC_REQUEST_IpcId
*/
GWENHYWFAR_API void GWEN_IpcRequest_SetIpcId(GWEN_IPC_REQUEST *el, GWEN_TYPE_UINT32 d);

/**
* Returns the property @ref GWEN_IPC_REQUEST_Expires
*/
GWENHYWFAR_API const GWEN_TIME *GWEN_IpcRequest_GetExpires(const GWEN_IPC_REQUEST *el);
/**
* Set the property @ref GWEN_IPC_REQUEST_Expires
*/
GWENHYWFAR_API void GWEN_IpcRequest_SetExpires(GWEN_IPC_REQUEST *el, const GWEN_TIME *d);

/**
* Returns the property @ref GWEN_IPC_REQUEST_SubRequests
*/
GWENHYWFAR_API GWEN_IPC_REQUEST_LIST *GWEN_IpcRequest_GetSubRequests(const GWEN_IPC_REQUEST *el);
/**
* Set the property @ref GWEN_IPC_REQUEST_SubRequests
*/
GWENHYWFAR_API void GWEN_IpcRequest_SetSubRequests(GWEN_IPC_REQUEST *el, GWEN_IPC_REQUEST_LIST *d);

/**
* Returns the property @ref GWEN_IPC_REQUEST_Status
*/
GWENHYWFAR_API GWEN_IPC_REQUEST_STATUS GWEN_IpcRequest_GetStatus(const GWEN_IPC_REQUEST *el);
/**
* Set the property @ref GWEN_IPC_REQUEST_Status
*/
GWENHYWFAR_API void GWEN_IpcRequest_SetStatus(GWEN_IPC_REQUEST *el, GWEN_IPC_REQUEST_STATUS d);

/**
* Returns the property @ref GWEN_IPC_REQUEST_WorkFn
*/
GWENHYWFAR_API GWEN_IPC_REQUEST_WORK_FN GWEN_IpcRequest_GetWorkFn(const GWEN_IPC_REQUEST *st);
/**
* Set the property @ref GWEN_IPC_REQUEST_WorkFn
*/
GWENHYWFAR_API void GWEN_IpcRequest_SetWorkFn(GWEN_IPC_REQUEST *st, GWEN_IPC_REQUEST_WORK_FN d);
/**
*/
GWENHYWFAR_API int GWEN_IpcRequest_WorkFn(GWEN_IPC_REQUEST *st);


#ifdef __cplusplus
} /* __cplusplus */
#endif


#endif /* REQUEST_H */