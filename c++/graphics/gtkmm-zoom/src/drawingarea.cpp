#include <drawingarea.h>
#include <pngfilereader.h>


DrawingArea::DrawingArea() :
  m_Distance(100.0)
{
  try
  {
    m_Image = Gdk::Pixbuf::create_from_file("/home/matt6809/Downloads/"
      "fractuals.png");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
  }
  catch(const Gdk::PixbufError& ex)
  {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }
  add_events(Gdk::POINTER_MOTION_MASK | Gdk::POINTER_MOTION_HINT_MASK | 
    Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::SCROLL_MASK);
  m_pPNGFileReader = new PNGFileReader();
}

DrawingArea::~DrawingArea()
{
  if(m_pPNGFileReader)
  {
    delete m_pPNGFileReader;
  }
}

// Event handlers:
bool DrawingArea::on_motion_notify_event (GdkEventMotion* event)
{
  return true;
}

bool DrawingArea::on_button_press_event(GdkEventButton* event)
{
  if (event->type == GDK_2BUTTON_PRESS && event->button == 1)
  {
    return true;
  }
  else if (event->type == GDK_2BUTTON_PRESS && event->button == 3)
  {
    return true;
  }
  else if (event->button == 1)
  {
    return true;
  }
  else if (event->button == 3)
  {
    return true;
  }
  return false;
}

bool DrawingArea::on_button_release_event(GdkEventButton* event)
{
  return true;
}

bool DrawingArea::on_scroll_event(GdkEventScroll* event)
{
  if (event->direction == GDK_SCROLL_UP)
  {
    zoom(10);
    return true;
  }
  else if (event->direction == GDK_SCROLL_DOWN)
  {
    zoom(-10);
    return true;
  }
  return false;
}

bool DrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  if (!m_Image)
    return false;

  Gdk::Cairo::set_source_pixbuf(cr, m_Image);
  cr->paint();

  return true;
}

void DrawingArea::zoom(double zoom_factor)
{
  m_Distance += zoom_factor;

  m_pPNGFileReader->decompress_png_to_raw("/home/matt6809/Downloads/"
    "fractuals.png");
}

