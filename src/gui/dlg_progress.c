/***************************************************************************
 begin       : Tue Feb 16 2010
 copyright   : (C) 2010 by Martin Preuss
 email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
# include <config.h>
#endif


#include "dlg_progress_p.h"

#include <gwenhywfar/gwenhywfar.h>
#include <gwenhywfar/pathmanager.h>
#include <gwenhywfar/debug.h>



#define DIALOG_MINWIDTH  400
#define DIALOG_MINHEIGHT 400



GWEN_INHERIT(GWEN_DIALOG, GWEN_DLGPROGRESS)





GWEN_DIALOG *GWEN_DlgProgress_new(const char *dialogId) {
  GWEN_DIALOG *dlg;
  GWEN_DLGPROGRESS *xdlg;
  GWEN_BUFFER *fbuf;
  int rv;

  dlg=GWEN_Dialog_new(dialogId);
  GWEN_NEW_OBJECT(GWEN_DLGPROGRESS, xdlg);

  GWEN_INHERIT_SETDATA(GWEN_DIALOG, GWEN_DLGPROGRESS, dlg, xdlg,
		       GWEN_DlgProgress_FreeData);

  GWEN_Dialog_SetSignalHandler(dlg, GWEN_DlgProgress_SignalHandler);

  /* get path of dialog description file */
  fbuf=GWEN_Buffer_new(0, 256, 0, 1);
  rv=GWEN_PathManager_FindFile(GWEN_PM_LIBNAME, GWEN_PM_SYSDATADIR,
			       "gwenhywfar/dialogs/dlg_progress.dlg",
			       fbuf);
  if (rv<0) {
    DBG_INFO(GWEN_LOGDOMAIN, "Dialog description file not found (%d).", rv);
    GWEN_Buffer_free(fbuf);
    GWEN_Dialog_free(dlg);
    return NULL;
  }

  /* read dialog from dialog description file */
  rv=GWEN_Dialog_ReadXmlFile(dlg, GWEN_Buffer_GetStart(fbuf));
  if (rv<0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d).", rv);
    GWEN_Buffer_free(fbuf);
    GWEN_Dialog_free(dlg);
    return NULL;
  }
  GWEN_Buffer_free(fbuf);

  return dlg;
}



void GWEN_DlgProgress_FreeData(void *bp, void *p) {
  GWEN_DLGPROGRESS *xdlg;

  xdlg=(GWEN_DLGPROGRESS*) p;

  GWEN_FREE_OBJECT(xdlg);
}



void GWEN_DlgProgress_SetAllowClose(GWEN_DIALOG *dlg, int b) {
  GWEN_DLGPROGRESS *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GWEN_DLGPROGRESS, dlg);
  assert(xdlg);

  xdlg->allowClose=b;
}



GWEN_PROGRESS_DATA *GWEN_DlgProgress_GetFirstProgress(const GWEN_DIALOG *dlg) {
  GWEN_DLGPROGRESS *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GWEN_DLGPROGRESS, dlg);
  assert(xdlg);

  return xdlg->firstProgress;
}



void GWEN_DlgProgress_SetFirstProgress(GWEN_DIALOG *dlg, GWEN_PROGRESS_DATA *pd) {
  GWEN_DLGPROGRESS *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GWEN_DLGPROGRESS, dlg);
  assert(xdlg);

  xdlg->firstProgress=pd;

  if (xdlg->wasInit) {
    if (xdlg->firstProgress) {
      GWEN_Dialog_SetIntProperty(dlg, "allProgress", GWEN_DialogProperty_Enabled, 0, 1, 0);
      GWEN_Dialog_SetIntProperty(dlg, "allProgress", GWEN_DialogProperty_MaxValue, 0,
				 GWEN_ProgressData_GetTotal(xdlg->firstProgress), 0);
      GWEN_Dialog_SetIntProperty(dlg, "allProgress", GWEN_DialogProperty_Value, 0,
				 GWEN_ProgressData_GetCurrent(xdlg->firstProgress), 0);
    }
    else {
      /* let it show 100 % */
      GWEN_Dialog_SetIntProperty(dlg, "allProgress", GWEN_DialogProperty_MaxValue, 0, 100, 0);
      GWEN_Dialog_SetIntProperty(dlg, "allProgress", GWEN_DialogProperty_Value, 0, 100, 0);
    }
  }
}



GWEN_PROGRESS_DATA *GWEN_DlgProgress_GetSecondProgress(const GWEN_DIALOG *dlg) {
  GWEN_DLGPROGRESS *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GWEN_DLGPROGRESS, dlg);
  assert(xdlg);

  return xdlg->secondProgress;
}



void GWEN_DlgProgress_SetSecondProgress(GWEN_DIALOG *dlg, GWEN_PROGRESS_DATA *pd) {
  GWEN_DLGPROGRESS *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GWEN_DLGPROGRESS, dlg);
  assert(xdlg);

  xdlg->secondProgress=pd;

  if (xdlg->wasInit) {
    if (xdlg->secondProgress) {
      GWEN_Dialog_SetIntProperty(dlg, "currentProgress", GWEN_DialogProperty_Enabled, 0, 1, 0);
      GWEN_Dialog_SetIntProperty(dlg, "currentProgress", GWEN_DialogProperty_MaxValue, 0,
				 GWEN_ProgressData_GetTotal(xdlg->secondProgress), 0);
      GWEN_Dialog_SetIntProperty(dlg, "currentProgress", GWEN_DialogProperty_Value, 0,
				 GWEN_ProgressData_GetCurrent(xdlg->secondProgress), 0);
    }
    else {
      GWEN_Dialog_SetIntProperty(dlg, "currentProgress", GWEN_DialogProperty_Value, 0, 0, 0);
      GWEN_Dialog_SetIntProperty(dlg, "currentProgress", GWEN_DialogProperty_Enabled, 0, 0, 0);
    }
  }
}



void GWEN_DlgProgress_AddLogText(GWEN_DIALOG *dlg,
				 GWEN_LOGGER_LEVEL level,
				 const char *s) {
  GWEN_DLGPROGRESS *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GWEN_DLGPROGRESS, dlg);
  assert(xdlg);

  DBG_ERROR(0, "Would log: [%s]", s);
  // TODO
}



void GWEN_DlgProgress_Init(GWEN_DIALOG *dlg) {
  GWEN_DLGPROGRESS *xdlg;
  int i;
  GWEN_DB_NODE *dbParams;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GWEN_DLGPROGRESS, dlg);
  assert(xdlg);

  dbParams=GWEN_Dialog_GetPreferences(dlg);
  assert(dbParams);

  /* read width */
  i=GWEN_DB_GetIntValue(dbParams, "dialog_width", 0, -1);
  if (i<DIALOG_MINWIDTH)
    i=DIALOG_MINWIDTH;
  GWEN_Dialog_SetIntProperty(dlg, "", GWEN_DialogProperty_Width, 0, i, 0);

  /* read height */
  i=GWEN_DB_GetIntValue(dbParams, "dialog_height", 0, -1);
  if (i<DIALOG_MINHEIGHT)
    i=DIALOG_MINHEIGHT;
  GWEN_Dialog_SetIntProperty(dlg, "", GWEN_DialogProperty_Height, 0, i, 0);


  if (xdlg->firstProgress) {
    const char *s;

    s=GWEN_ProgressData_GetTitle(xdlg->firstProgress);
    if (s && *s)
      GWEN_Dialog_SetCharProperty(dlg, "", GWEN_DialogProperty_Title, 0, s, 0);

    s=GWEN_ProgressData_GetText(xdlg->firstProgress);
    if (s && *s)
      GWEN_Dialog_SetCharProperty(dlg, "descrLabel", GWEN_DialogProperty_Title, 0, s, 0);

    GWEN_Dialog_SetIntProperty(dlg, "allProgress", GWEN_DialogProperty_MaxValue, 0,
			       GWEN_ProgressData_GetTotal(xdlg->firstProgress), 0);
    GWEN_Dialog_SetIntProperty(dlg, "allProgress", GWEN_DialogProperty_Value, 0,
			       GWEN_ProgressData_GetCurrent(xdlg->firstProgress), 0);
  }

  if (xdlg->secondProgress) {
    GWEN_Dialog_SetIntProperty(dlg, "currentProgress", GWEN_DialogProperty_MaxValue, 0,
			       GWEN_ProgressData_GetTotal(xdlg->secondProgress), 0);
    GWEN_Dialog_SetIntProperty(dlg, "currentProgress", GWEN_DialogProperty_Value, 0,
			       GWEN_ProgressData_GetCurrent(xdlg->secondProgress), 0);
  }

  GWEN_Dialog_SetIntProperty(dlg, "abortButton", GWEN_DialogProperty_Enabled, 0, 1, 0);
  GWEN_Dialog_SetIntProperty(dlg, "closeButton", GWEN_DialogProperty_Enabled, 0, 0, 0);

  xdlg->wasInit=1;
}



void GWEN_DlgProgress_Fini(GWEN_DIALOG *dlg) {
  int i;
  GWEN_DB_NODE *dbParams;

  dbParams=GWEN_Dialog_GetPreferences(dlg);
  assert(dbParams);

  /* store dialog width */
  i=GWEN_Dialog_GetIntProperty(dlg, "", GWEN_DialogProperty_Width, 0, -1);
  if (i<DIALOG_MINWIDTH)
    i=DIALOG_MINWIDTH;
  GWEN_DB_SetIntValue(dbParams,
		      GWEN_DB_FLAGS_OVERWRITE_VARS,
		      "dialog_width",
		      i);

  /* store dialog height */
  i=GWEN_Dialog_GetIntProperty(dlg, "", GWEN_DialogProperty_Height, 0, -1);
  if (i<DIALOG_MINHEIGHT)
    i=DIALOG_MINHEIGHT;
  GWEN_DB_SetIntValue(dbParams,
		      GWEN_DB_FLAGS_OVERWRITE_VARS,
		      "dialog_height",
		      i);
}




int GWEN_DlgProgress_HandleActivated(GWEN_DIALOG *dlg, const char *sender) {
  GWEN_DLGPROGRESS *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GWEN_DLGPROGRESS, dlg);
  assert(xdlg);

  DBG_ERROR(0, "Activated: %s", sender);
  if (strcasecmp(sender, "closeButton")==0) {
    return GWEN_DialogEvent_ResultHandled;
  }
  else if (strcasecmp(sender, "abortButton")==0) {
    if (xdlg->firstProgress)
      GWEN_ProgressData_SetAborted(xdlg->firstProgress, 1);
    if (xdlg->secondProgress)
      GWEN_ProgressData_SetAborted(xdlg->secondProgress, 1);

    GWEN_Dialog_SetIntProperty(dlg, "abortButton", GWEN_DialogProperty_Enabled, 0, 0, 0);
    GWEN_Dialog_SetIntProperty(dlg, "closeButton", GWEN_DialogProperty_Enabled, 0, 1, 0);

    return GWEN_DialogEvent_ResultHandled;
  }

  return GWEN_DialogEvent_ResultNotHandled;
}




int GWEN_DlgProgress_SignalHandler(GWEN_DIALOG *dlg,
				   GWEN_DIALOG_EVENTTYPE t,
				   const char *sender) {
  GWEN_DLGPROGRESS *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GWEN_DLGPROGRESS, dlg);
  assert(xdlg);

  switch(t) {
  case GWEN_DialogEvent_TypeInit:
    GWEN_DlgProgress_Init(dlg);
    return GWEN_DialogEvent_ResultHandled;;

  case GWEN_DialogEvent_TypeFini:
    GWEN_DlgProgress_Fini(dlg);
    return GWEN_DialogEvent_ResultHandled;;

  case GWEN_DialogEvent_TypeValueChanged:
    break;

  case GWEN_DialogEvent_TypeActivated:
    return GWEN_DlgProgress_HandleActivated(dlg, sender);

  case GWEN_DialogEvent_TypeEnabled:
  case GWEN_DialogEvent_TypeDisabled:
  case GWEN_DialogEvent_TypeGetImagePath:
  case GWEN_DialogEvent_TypeGetIconPath:

  case GWEN_DialogEvent_TypeClose:
    if (xdlg->allowClose==0)
      return GWEN_DialogEvent_ResultReject;
    else
      return GWEN_DialogEvent_ResultAccept;

  case GWEN_DialogEvent_TypeLast:
    return GWEN_DialogEvent_ResultNotHandled;
  }

  return GWEN_DialogEvent_ResultNotHandled;

}





