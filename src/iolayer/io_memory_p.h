/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id: crypttoken.h 1113 2007-01-10 09:14:16Z martin $
    begin       : Wed Mar 16 2005
    copyright   : (C) 2005 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/


#ifndef GWEN_IOLAYER_MEMORY_P_H
#define GWEN_IOLAYER_MEMORY_P_H

#include <gwenhywfar/io_memory.h>


typedef struct GWEN_IO_LAYER_MEMORY GWEN_IO_LAYER_MEMORY;
struct GWEN_IO_LAYER_MEMORY {
  GWEN_BUFFER *buffer;
};

static GWENHYWFAR_CB void GWEN_Io_LayerMemory_freeData(void *bp, void *p);
static GWEN_IO_LAYER_WORKRESULT GWEN_Io_LayerMemory_WorkOnRequests(GWEN_IO_LAYER *io);
static int GWEN_Io_LayerMemory_AddRequest(GWEN_IO_LAYER *io, GWEN_IO_REQUEST *r);
static int GWEN_Io_LayerMemory_DelRequest(GWEN_IO_LAYER *io, GWEN_IO_REQUEST *r);
static int GWEN_Io_LayerMemory_HasWaitingRequests(GWEN_IO_LAYER *io);




#endif



