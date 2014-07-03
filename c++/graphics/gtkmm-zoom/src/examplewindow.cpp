#include <examplewindow.h>
#include <iostream>
#include <string>
#include <gtkmm/stock.h>
#include <drawingarea.h>

ExampleWindow::ExampleWindow() :
  Gtk::Window()
{
  set_title("Main Menu Example");
  set_default_size(800, 600);
  if (!create_layout() ||
      !create_actions() ||
      !create_ui() ||
      !create_menu_bar() ||
      !create_tool_bar() || 
      !create_drawing_area()
     ) {
       std::cerr << "Failure to create GUI" << std::endl;
       throw "Failure to create Main Window and its components";
  }

  add_events(Gdk::POINTER_MOTION_MASK | Gdk::POINTER_MOTION_HINT_MASK | Gdk::BUTTON_PRESS_MASK | 
             Gdk::BUTTON_RELEASE_MASK | Gdk::SCROLL_MASK);
  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
  if(m_DrawArea != NULL)
  {
    delete m_DrawArea;
    m_DrawArea= 0;
  }
}

// Event handlers:
bool ExampleWindow::on_motion_notify_event (GdkEventMotion* event)
{
  return true;
}

bool ExampleWindow::on_button_press_event(GdkEventButton* event)
{
  if (event->type == GDK_2BUTTON_PRESS && event->button == 1) 
  {
    std::cout << "Left mouse pressed: Double Click" << std::endl;
  }
  else if (event->type == GDK_2BUTTON_PRESS && event->button == 3)
  {
    std::cout << "Right mouse pressed: Double Click" << std::endl;
  }
  else if (event->button == 1)
  {
    std::cout << "Left mouse pressed: Single Click" << std::endl;
  }
  else if (event->button == 3) 
  {
    std::cout << "Right mouse pressed: Single Click" << std::endl;
  }
  return true;
}

bool ExampleWindow::on_button_release_event(GdkEventButton* event)
{
  return true;
}

bool ExampleWindow::on_scroll_event(GdkEventScroll* event)
{
  std::cout << "Mouse scroll" << std::endl;
  return true;
}


// Signal handlers:
void ExampleWindow::on_action_file_new()
{
}

void ExampleWindow::on_action_file_open()
{
}

void ExampleWindow::on_action_file_quit()
{
  hide();
}

// Utility functions:
bool ExampleWindow::create_layout()
{
  add(m_Box);
  return true;
}

bool ExampleWindow::create_actions()
{
  m_refActionGroup = Gtk::ActionGroup::create();
  m_refActionGroup->add(Gtk::Action::create("MenuFile", "_File") );
  m_refActionGroup->add(Gtk::Action::create("New", Gtk::Stock::NEW),
      sigc::mem_fun(*this, &ExampleWindow::on_action_file_new));
  m_refActionGroup->add(Gtk::Action::create("Open", Gtk::Stock::OPEN),
      sigc::mem_fun(*this, &ExampleWindow::on_action_file_open));
  m_refActionGroup->add(Gtk::Action::create("Quit", Gtk::Stock::QUIT),
      sigc::mem_fun(*this, &ExampleWindow::on_action_file_quit));
  return true;
}

bool ExampleWindow::create_ui()
{
  m_refUIManager = Gtk::UIManager::create();
  m_refUIManager->insert_action_group(m_refActionGroup);
  add_accel_group(m_refUIManager->get_accel_group());

  Glib::ustring ui_info =
    "<ui>"
    "  <menubar name='MenuBar'>"
    "    <menu action='MenuFile'>"
    "      <menuitem action='New'/>"
    "      <menuitem action='Open'/>"
    "      <menuitem action='Quit'/>"
    "    </menu>"
    "  </menubar>"
    "  <toolbar  name='ToolBar'>"
    "    <toolitem action='Open'/>"
    "    <toolitem action='Quit'/>"
    "  </toolbar>"
    "</ui>";

  try
  {
    m_refUIManager->add_ui_from_string(ui_info);
  }
  catch (const Glib::Error &ex)
  {
    std::cerr << "Failed to build menus" << ex.what();
    throw ex;
  }
  return true;
}

bool ExampleWindow::create_menu_bar()
{
  Gtk::Widget *pMenubar = m_refUIManager->get_widget("/MenuBar");

  if (pMenubar) {
    m_Box.pack_start(*pMenubar, Gtk::PACK_SHRINK);
    return true;
  } else {
    return false;
  }
}

bool ExampleWindow::create_tool_bar()
{
  Gtk::Widget *pToolbar = m_refUIManager->get_widget("/ToolBar");

  if (pToolbar) {
    m_Box.pack_start(*pToolbar, Gtk::PACK_SHRINK);
    return true;
  } else {
    return false;
  }
}

bool ExampleWindow::create_drawing_area()
{
  m_DrawArea = new DrawingArea();
  m_Box.pack_end(*(m_DrawArea));
  return true;
}
