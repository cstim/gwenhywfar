/**********************************************************
 * This file has been automatically created by "typemaker2"
 * from the file "testmodule.xml".
 * Please do not edit this file, all changes will be lost.
 * Better edit the mentioned source file instead.
 **********************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "./testmodule_p.h"

#include <gwenhywfar/misc.h>
#include <gwenhywfar/debug.h>

/* code headers */

/* macro functions */
GWEN_TREE2_FUNCTIONS(GWEN_TEST_MODULE, GWEN_Test_Module)
GWEN_INHERIT_FUNCTIONS(GWEN_TEST_MODULE)


GWEN_TEST_MODULE *GWEN_Test_Module_new(void)
{
  GWEN_TEST_MODULE *p_struct;

  GWEN_NEW_OBJECT(GWEN_TEST_MODULE, p_struct)
  p_struct->_refCount=1;
  GWEN_INHERIT_INIT(GWEN_TEST_MODULE, p_struct)
  GWEN_TREE2_INIT(GWEN_TEST_MODULE, p_struct, GWEN_Test_Module)
  /* members */
  p_struct->id=0;
  p_struct->name=NULL;
  p_struct->description=NULL;
  p_struct->result=0;
  p_struct->paramsDb=NULL;
  /* virtual functions */

  return p_struct;
}

void GWEN_Test_Module_free(GWEN_TEST_MODULE *p_struct)
{
  if (p_struct) {
    assert(p_struct->_refCount);
    if (p_struct->_refCount==1) {
      GWEN_INHERIT_FINI(GWEN_TEST_MODULE, p_struct)
      GWEN_TREE2_FINI(GWEN_TEST_MODULE, p_struct, GWEN_Test_Module)
      /* members */
      free(p_struct->name);
      p_struct->name=NULL;
      free(p_struct->description);
      p_struct->description=NULL;
      GWEN_DB_Group_free(p_struct->paramsDb);
      p_struct->paramsDb=NULL;
      p_struct->_refCount=0;
      GWEN_FREE_OBJECT(p_struct);
    }
    else
      p_struct->_refCount--;
  }
}

void GWEN_Test_Module_Attach(GWEN_TEST_MODULE *p_struct)
{
  assert(p_struct);
  assert(p_struct->_refCount);
  p_struct->_refCount++;
}

GWEN_TEST_MODULE *GWEN_Test_Module_dup(const GWEN_TEST_MODULE *p_src)
{
  GWEN_TEST_MODULE *p_struct;

  assert(p_src);
  p_struct=GWEN_Test_Module_new();
  /* member "id" */
  p_struct->id=p_src->id;

  /* member "name" */
  if (p_struct->name) {
    free(p_struct->name);
    p_struct->name=NULL;
    p_struct->name=NULL;
  }
  if (p_src->name) {
    p_struct->name=strdup(p_src->name);
  }

  /* member "description" */
  if (p_struct->description) {
    free(p_struct->description);
    p_struct->description=NULL;
    p_struct->description=NULL;
  }
  if (p_src->description) {
    p_struct->description=strdup(p_src->description);
  }

  /* member "result" */
  p_struct->result=p_src->result;

  /* member "paramsDb" */
  if (p_struct->paramsDb) {
    GWEN_DB_Group_free(p_struct->paramsDb);
    p_struct->paramsDb=NULL;
    p_struct->paramsDb=NULL;
  }
  if (p_src->paramsDb) {
    p_struct->paramsDb=GWEN_DB_Group_dup(p_src->paramsDb);
  }

  return p_struct;
}

GWEN_TEST_MODULE *GWEN_Test_Module_copy(GWEN_TEST_MODULE *p_struct, const GWEN_TEST_MODULE *p_src)
{
  assert(p_struct);
  assert(p_src);
  /* member "id" */
  p_struct->id=p_src->id;

  /* member "name" */
  if (p_struct->name) {
    free(p_struct->name);
    p_struct->name=NULL;
    p_struct->name=NULL;
  }
  if (p_src->name) {
    p_struct->name=strdup(p_src->name);
  }

  /* member "description" */
  if (p_struct->description) {
    free(p_struct->description);
    p_struct->description=NULL;
    p_struct->description=NULL;
  }
  if (p_src->description) {
    p_struct->description=strdup(p_src->description);
  }

  /* member "result" */
  p_struct->result=p_src->result;

  /* member "paramsDb" */
  if (p_struct->paramsDb) {
    GWEN_DB_Group_free(p_struct->paramsDb);
    p_struct->paramsDb=NULL;
    p_struct->paramsDb=NULL;
  }
  if (p_src->paramsDb) {
    p_struct->paramsDb=GWEN_DB_Group_dup(p_src->paramsDb);
  }

  return p_struct;
}

uint32_t GWEN_Test_Module_GetId(const GWEN_TEST_MODULE *p_struct)
{
  assert(p_struct);
  return p_struct->id;
}

const char *GWEN_Test_Module_GetName(const GWEN_TEST_MODULE *p_struct)
{
  assert(p_struct);
  return p_struct->name;
}

const char *GWEN_Test_Module_GetDescription(const GWEN_TEST_MODULE *p_struct)
{
  assert(p_struct);
  return p_struct->description;
}

int GWEN_Test_Module_GetResult(const GWEN_TEST_MODULE *p_struct)
{
  assert(p_struct);
  return p_struct->result;
}

const GWEN_DB_NODE *GWEN_Test_Module_GetParamsDb(const GWEN_TEST_MODULE *p_struct)
{
  assert(p_struct);
  return p_struct->paramsDb;
}

void GWEN_Test_Module_SetId(GWEN_TEST_MODULE *p_struct, uint32_t p_src)
{
  assert(p_struct);
  p_struct->id=p_src;
}

void GWEN_Test_Module_SetName(GWEN_TEST_MODULE *p_struct, const char *p_src)
{
  assert(p_struct);
  if (p_struct->name) {
    free(p_struct->name);
    p_struct->name=NULL;
  }
  if (p_src) {
    p_struct->name=strdup(p_src);
  }
  else {
    p_struct->name=NULL;
  }
}

void GWEN_Test_Module_SetDescription(GWEN_TEST_MODULE *p_struct, const char *p_src)
{
  assert(p_struct);
  if (p_struct->description) {
    free(p_struct->description);
    p_struct->description=NULL;
  }
  if (p_src) {
    p_struct->description=strdup(p_src);
  }
  else {
    p_struct->description=NULL;
  }
}

void GWEN_Test_Module_SetResult(GWEN_TEST_MODULE *p_struct, int p_src)
{
  assert(p_struct);
  p_struct->result=p_src;
}

void GWEN_Test_Module_SetParamsDb(GWEN_TEST_MODULE *p_struct, const GWEN_DB_NODE *p_src)
{
  assert(p_struct);
  if (p_struct->paramsDb) {
    GWEN_DB_Group_free(p_struct->paramsDb);
    p_struct->paramsDb=NULL;
  }
  if (p_src) {
    p_struct->paramsDb=GWEN_DB_Group_dup(p_src);
  }
  else {
    p_struct->paramsDb=NULL;
  }
}

/* code for virtual functions */
int GWEN_Test_Module_Test(GWEN_TEST_MODULE *p_struct)
{
  assert(p_struct);
  if (p_struct->testFn)
    return p_struct->testFn(p_struct);
  else
    return GWEN_ERROR_NOT_IMPLEMENTED;
}

/* setters for virtual functions */
GWEN_TEST_MODULE_TEST_FN GWEN_Test_Module_SetTestFn(GWEN_TEST_MODULE *p_struct, GWEN_TEST_MODULE_TEST_FN fn)
{
  GWEN_TEST_MODULE_TEST_FN oldFn;

  assert(p_struct);
  oldFn=p_struct->testFn;
  p_struct->testFn=fn;
  return oldFn;
}

void GWEN_Test_Module_ReadDb(GWEN_TEST_MODULE *p_struct, GWEN_DB_NODE *p_db)
{
  assert(p_struct);
  /* member "id" */
  p_struct->id=GWEN_DB_GetIntValue(p_db, "id", 0, 0);

  /* member "name" */
  if (p_struct->name) {
    free(p_struct->name);
    p_struct->name=NULL;
  }
  {
    const char *s;
    s=GWEN_DB_GetCharValue(p_db, "name", 0, NULL);
    if (s)
      p_struct->name=strdup(s);
  }
  if (p_struct->name==NULL) {
    p_struct->name=NULL;
  }

  /* member "description" */
  if (p_struct->description) {
    free(p_struct->description);
    p_struct->description=NULL;
  }
  {
    const char *s;
    s=GWEN_DB_GetCharValue(p_db, "description", 0, NULL);
    if (s)
      p_struct->description=strdup(s);
  }
  if (p_struct->description==NULL) {
    p_struct->description=NULL;
  }

  /* member "result" */
  p_struct->result=GWEN_DB_GetIntValue(p_db, "result", 0, 0);

  /* member "paramsDb" */
  if (p_struct->paramsDb) {
    GWEN_DB_Group_free(p_struct->paramsDb);
    p_struct->paramsDb=NULL;
  }
  {
    GWEN_DB_NODE *dbSrc;
    dbSrc=GWEN_DB_GetGroup(p_db, GWEN_PATH_FLAGS_NAMEMUSTEXIST, "paramsDb");
    if (dbSrc) {
      p_struct->paramsDb=GWEN_DB_Group_dup(dbSrc);
    }
    else
      p_struct->paramsDb=NULL;
  }
  if (p_struct->paramsDb==NULL) {
    p_struct->paramsDb=NULL;
  }

}

int GWEN_Test_Module_WriteDb(const GWEN_TEST_MODULE *p_struct, GWEN_DB_NODE *p_db)
{
  int p_rv;

  assert(p_struct);
  /* member "id" */
  p_rv=GWEN_DB_SetIntValue(p_db, GWEN_DB_FLAGS_OVERWRITE_VARS, "id", p_struct->id);
  if (p_rv<0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  /* member "name" */
  if (p_struct->name)
    p_rv=GWEN_DB_SetCharValue(p_db, GWEN_DB_FLAGS_OVERWRITE_VARS, "name", p_struct->name);
  else {
    GWEN_DB_DeleteVar(p_db, "name");
    p_rv=0;
  }
  if (p_rv<0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  /* member "description" */
  if (p_struct->description)
    p_rv=GWEN_DB_SetCharValue(p_db, GWEN_DB_FLAGS_OVERWRITE_VARS, "description", p_struct->description);
  else {
    GWEN_DB_DeleteVar(p_db, "description");
    p_rv=0;
  }
  if (p_rv<0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  /* member "result" */
  p_rv=GWEN_DB_SetIntValue(p_db, GWEN_DB_FLAGS_OVERWRITE_VARS, "result", p_struct->result);
  if (p_rv<0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  /* member "paramsDb" */
  if (p_struct->paramsDb) {
    GWEN_DB_NODE *dbCopy;
    dbCopy=GWEN_DB_GetGroup(p_db, GWEN_DB_FLAGS_DEFAULT, "paramsDb");
    assert(dbCopy);
    p_rv=GWEN_DB_AddGroupChildren(dbCopy, p_struct->paramsDb);
  }
  else {
    GWEN_DB_DeleteGroup(p_db, "paramsDb");
    p_rv=0;
  }
  if (p_rv<0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)\n", p_rv);
    return p_rv;
  }

  return 0;
}

GWEN_TEST_MODULE *GWEN_Test_Module_fromDb(GWEN_DB_NODE *p_db)
{
  GWEN_TEST_MODULE *p_struct;
  p_struct=GWEN_Test_Module_new();
  GWEN_Test_Module_ReadDb(p_struct, p_db);
  return p_struct;
}

int GWEN_Test_Module_toDb(const GWEN_TEST_MODULE *p_struct, GWEN_DB_NODE *p_db)
{
  return GWEN_Test_Module_WriteDb(p_struct, p_db);
}

GWEN_TEST_MODULE *GWEN_Test_Module_Tree2_GetById(const GWEN_TEST_MODULE *p_object, uint32_t p_cmp)
{
  GWEN_TEST_MODULE *p_struct;

  assert(p_object);
  p_struct = GWEN_Test_Module_Tree2_GetFirstChild(p_object);
  while (p_struct) {
    int p_rv;

    if (p_struct->id==p_cmp)
      p_rv=0;
    else if (p_cmp<p_struct->id)
      p_rv=-1;
    else
      p_rv=1;
    if (p_rv == 0)
      return p_struct;
    p_struct = GWEN_Test_Module_Tree2_GetBelow(p_struct);
  }
  return NULL;
}

GWEN_TEST_MODULE *GWEN_Test_Module_AddTest(GWEN_TEST_MODULE *st, const char *tName, GWEN_TEST_MODULE_TEST_FN fn,
                                           const char *tDescr)
{
  GWEN_TEST_MODULE *mod;

  mod=GWEN_Test_Module_new();
  if (tName && *tName)
    GWEN_Test_Module_SetName(mod, tName);
  if (tDescr && *tDescr)
    GWEN_Test_Module_SetDescription(mod, tDescr);
  if (fn)
    GWEN_Test_Module_SetTestFn(mod, fn);

  GWEN_Test_Module_Tree2_AddChild(st, mod);
  return mod;
}
GWEN_TEST_MODULE *GWEN_Test_Module_AddModule(GWEN_TEST_MODULE *st, const char *tName, const char *tDescr)
{
  GWEN_TEST_MODULE *mod;

  mod=GWEN_Test_Module_new();
  if (tName && *tName)
    GWEN_Test_Module_SetName(mod, tName);
  if (tDescr && *tDescr)
    GWEN_Test_Module_SetDescription(mod, tDescr);

  GWEN_Test_Module_Tree2_AddChild(st, mod);
  return mod;
}
const char *GWEN_Test_Module_GetCharParam(const GWEN_TEST_MODULE *st, const char *paramName, const char *defVal)
{
  assert(st);
  while (st) {
    if (st->paramsDb) {
      const char *s;

      s=GWEN_DB_GetCharValue(st->paramsDb, paramName, 0, NULL);
      if (s)
        return s;
    }
    st=GWEN_Test_Module_Tree2_GetParent(st);
  }

  return defVal;
}
void GWEN_Test_Module_SetCharParam(GWEN_TEST_MODULE *st, const char *paramName, const char *val)
{
  assert(st);
  if (st->paramsDb==NULL)
    st->paramsDb=GWEN_DB_Group_new("params");
  GWEN_DB_SetCharValue(st->paramsDb, GWEN_DB_FLAGS_OVERWRITE_VARS, paramName, val);
}

/* code headers */

