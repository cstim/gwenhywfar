/***************************************************************************
 $RCSfile$
 -------------------
 cvs         : $Id$
 begin       : Thu Sep 11 2003
 copyright   : (C) 2003 by Martin Preuss
 email       : martin@libchipcard.de

 ***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 *                                                                         *
 ***************************************************************************/


#ifndef GWENHYWFAR_GWENHYWFAR_H
#define GWENHYWFAR_GWENHYWFAR_H

#include <gwenhywfar/gwenhywfarapi.h>
#include <gwenhywfar/error.h>
#include <gwenhywfar/buffer.h>
#include <gwenhywfar/stringlist.h>


/**
 * This is used as the destLib name for paths of Gwenhywfar when used
 * with @ref GWEN_PathManager_AddPath and other functions of that group.
 */
#define GWEN_PM_LIBNAME "gwenhywfar"

/** Path identifier for the installation prefix of this gwenhywfar
    installation, which might point to e.g. "/usr" */
#define GWEN_PM_INSTALLDIR   "installdir"
/** Path identifier for the system-wide configuration directory of
    this gwenhywfar installation, which might point to e.g. "/etc" */
#define GWEN_PM_SYSCONFDIR   "sysconfdir"
/** Path identifier for the locale data directory of this gwenhywfar
    installation, which might point to e.g. "/usr/share/locale" */
#define GWEN_PM_LOCALEDIR    "localedir"
/** Path identifier for the library files of this gwenhywfar
    installation, which point to e.g.  "/usr/lib" */
#define GWEN_PM_LIBDIR    "libdir"
/** Path identifier for the plugin library files of this
    gwenhywfar installation, which point to e.g.
    "/usr/lib/gwenhywfar/plugins/0" */
#define GWEN_PM_PLUGINDIR    "plugindir"



#ifdef __cplusplus
extern "C" {
#endif


GWENHYWFAR_API
GWEN_ERRORCODE GWEN_Init();

GWENHYWFAR_API
GWEN_ERRORCODE GWEN_Fini();


GWENHYWFAR_API
void GWEN_Version(int *major,
                  int *minor,
                  int *patchlevel,
                  int *build);

/**
 * Returns the installation prefix of gwenhywfar.
 * On WIN32 systems this value is taken from the Registry (key is
 * "Software\\Gwenhywfar\\Paths\\prefix"). On POSIX systems (or when this
 * key does not exist) the hardcoded installation prefix is returned
 * ($prefix).
 */
GWENHYWFAR_API
int GWEN_GetInstallPath(GWEN_BUFFER *pbuf);


GWENHYWFAR_API
int GWEN_GetPluginPath(GWEN_BUFFER *pbuf);



#ifdef __cplusplus
}
#endif


#endif
