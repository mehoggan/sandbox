#ifndef GTKMM_EXAMPLE_RANGEWIDGETS_H
#define GTKMM_EXAMPLE_RANGEWIDGETS_H

#include <gtkmm.h>
#include <iostream>
#include <string>
#include <gtkmm/stock.h>
class DrawingArea;

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();
  virtual bool on_motion_notify_event (GdkEventMotion* event);
  virtual bool on_button_press_event(GdkEventButton* event);
  virtual bool on_button_release_event(GdkEventButton* event);
  virtual bool on_scroll_event(GdkEventScroll* event);

protected:
  // Signal handlers:
  void on_action_file_new();
  void on_action_file_open();
  void on_action_file_quit();

  // Layout widgets:
  Gtk::VBox m_Box;

  // Child widgets:
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Glib::RefPtr<Gdk::Pixbuf> m_refPixbuf;
  DrawingArea *m_DrawArea;

  // Utility functions:
  bool create_layout();
  bool create_actions();
  bool create_ui();
  bool create_menu_bar();
  bool create_tool_bar();
  bool create_drawing_area();
};

#endif //GTKMM_EXAMPLE_RANGEWIDGETS_H
