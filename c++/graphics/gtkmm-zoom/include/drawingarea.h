#ifndef DRAWINGAREA_H_
#define DRAWINGAREA_H_

#include <iostream>
#include <algorithm>
#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include <cairomm/context.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <glibmm/fileutils.h>

class PNGFileReader;

class DrawingArea : public Gtk::DrawingArea
{
public:
  DrawingArea();
  virtual ~DrawingArea();
  virtual bool on_motion_notify_event (GdkEventMotion* event);
  virtual bool on_button_press_event(GdkEventButton* event);
  virtual bool on_button_release_event(GdkEventButton* event);
  virtual bool on_scroll_event(GdkEventScroll* event);

protected:
  // Signals
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
  void zoom(double zoom_factor);

  // Member variables
  gdouble m_Distance;
  PNGFileReader *m_pPNGFileReader;  

  // Child Wigets
  Glib::RefPtr<Gdk::Pixbuf> m_Image;
};

#endif // DRAWINGAREA_H_
