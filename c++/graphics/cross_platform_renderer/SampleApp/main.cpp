#include <FWApplication.h>
#include "MapWindow.h"

int main(int /*argc*/, char */*argv*/[])
{
  FWApplication::Initialize();
  MapWindow *win = new MapWindow(800, 600);
  win->Show();
  win->AddTimer(10000);
  FWApplication::Run();
  delete win;
}
