/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id$
    begin       : Mon Feb 09 2004
    copyright   : (C) 2004 by Martin Preuss
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

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif


#include "window_p.h"
#include <gwenhywfar/debug.h>
#include <gwenhywfar/inherit.h>
#include "hslider.h"
#include "vslider.h"


#include <ncurses.h> // for beep, DEBUG


GWEN_INHERIT(GWEN_WIDGET, GWEN_WINDOW)



GWEN_WIDGET *GWEN_Window_new(GWEN_WIDGET *parent,
                             GWEN_TYPE_UINT32 flags,
                             const char *name,
                             const char *title,
                             int x, int y, int width, int height){
  GWEN_WIDGET *w;
  GWEN_WINDOW *win;
  int xoffs, yoffs, woffs, hoffs;

  w=GWEN_Widget_new(parent,
                    flags & ~GWEN_WIDGET_FLAGS_WINDOWFLAGS,
                    name, 0, x, y, width, height);
  GWEN_NEW_OBJECT(GWEN_WINDOW, win);
  GWEN_INHERIT_SETDATA(GWEN_WIDGET, GWEN_WINDOW, w, win,
                       GWEN_Window_freeData);

  win->previousHandler=GWEN_Widget_GetEventHandler(w);
  assert(win->previousHandler);
  GWEN_Widget_SetEventHandler(w, GWEN_Window_EventHandler);

  xoffs=0;
  yoffs=0;
  woffs=0;
  hoffs=0;

  if (flags & GWEN_WIDGET_FLAGS_BORDER) {
    xoffs++;
    yoffs++;
    woffs+=2;
    hoffs+=2;
  }
  if (flags & GWEN_WINDOW_FLAGS_TITLE) {
    DBG_NOTICE(0, "Creating title widget");
    win->wTitle=GWEN_Widget_new(w,
                                GWEN_WIDGET_FLAGS_HCENTER,
                                "Title", title,
                                xoffs, yoffs,
                                width-woffs, 1);
    GWEN_Widget_SetColour(win->wTitle, GWEN_WidgetColour_Title);
    yoffs++;
    hoffs++;
  }

  if (flags & GWEN_WINDOW_FLAGS_HSLIDER) {
    DBG_NOTICE(0, "Creating horizontal slider");
    win->wHslider=GWEN_HSlider_new(w,
                                   GWEN_WIDGET_FLAGS_DEFAULT,
                                   "HSlider",
                                   xoffs,
                                   height-
                                   ((flags & GWEN_WIDGET_FLAGS_BORDER)?2:1),
                                   width-woffs);
    hoffs++;
    GWEN_Widget_SetColour(win->wHslider, GWEN_WidgetColour_Button);
  }

  if (flags & GWEN_WINDOW_FLAGS_VSLIDER) {
    DBG_NOTICE(0, "Creating vertical slider");
    win->wVslider=GWEN_VSlider_new(w,
                                   GWEN_WIDGET_FLAGS_DEFAULT,
                                   "VSlider",
                                   width-
                                   ((flags & GWEN_WIDGET_FLAGS_BORDER)?2:1),
                                   yoffs,
                                   height-hoffs);
    woffs++;
    GWEN_Widget_SetColour(win->wVslider, GWEN_WidgetColour_Button);
  }

  win->wView=GWEN_Widget_new(w, 0, "View", 0,
                             xoffs, yoffs, width-woffs, height-hoffs);
  DBG_NOTICE(0, "Viewport is at %d/%d", xoffs, yoffs);
  return w;
}



void GWEN_Window_freeData(void *bp, void *p) {
  GWEN_WINDOW *win;

  win=(GWEN_WINDOW*)p;
  GWEN_FREE_OBJECT(win);
}



GWEN_WIDGET *GWEN_Window_GetViewPort(GWEN_WIDGET *w){
  GWEN_WINDOW *win;

  assert(w);
  win=GWEN_INHERIT_GETDATA(GWEN_WIDGET, GWEN_WINDOW, w);
  assert(win);

  return win->wView;
}



GWEN_UI_RESULT GWEN_Window_EventHandler(GWEN_WIDGET *w, GWEN_EVENT *e) {
  GWEN_WINDOW *win;
  GWEN_WIDGET *wSender;

  assert(w);
  win=GWEN_INHERIT_GETDATA(GWEN_WIDGET, GWEN_WINDOW, w);
  assert(win);
  assert(e);


  wSender=GWEN_Event_GetSender(e);
  if (wSender) {
    if (wSender==win->wView ||
        GWEN_Widget_IsChildOf(wSender, win->wView)) {
      /* event from view port received */
      switch(GWEN_Event_GetType(e)) {

      case GWEN_EventType_Scroll:
        if (!GWEN_EventScroll_GetTodo(e)) {
          int byX;
          int byY;

          byX=GWEN_EventScroll_GetXBy(e);
          byY=GWEN_EventScroll_GetYBy(e);

          /* view port has scrolled, we should adapt the sliders */
          if (win->wHslider && byX) {
            /* inform HSlider about horizontal changes */
            GWEN_Widget_Scrolled(win->wHslider, byX, byY);
          }

          if (win->wVslider && byY) {
            /* inform YSlider about vertical changes */
            GWEN_Widget_Scrolled(win->wVslider, byX, byY);
          }

          return GWEN_UIResult_Handled;
        }
        return win->previousHandler(w, e);
        break;

      case GWEN_EventType_ContentChg: {
        int cw, ch;

        cw=GWEN_EventContentChg_GetContentWidth(e);
        ch=GWEN_EventContentChg_GetContentHeight(e);
        if (win->wHslider)
          GWEN_Widget_ContentChange(win->wHslider, cw, ch);
        if (win->wVslider)
          GWEN_Widget_ContentChange(win->wVslider, cw, ch);
        return GWEN_UIResult_Handled;
      }

      default:
        break;
      } /* switch */
    }
    else if (wSender==win->wHslider) {
      /* event from horizontal slider */
    }
    else if (wSender==win->wVslider) {
      /* event from horizontal slider */
    }
  } /* if sender */


  switch(GWEN_Event_GetType(e)) {
  case GWEN_EventType_Draw:
    return win->previousHandler(w, e);

  case GWEN_EventType_ContentChg:
    break;

  case GWEN_EventType_Update:
    break;
  default:
    break;
  } /* switch */

  return win->previousHandler(w, e);
}








