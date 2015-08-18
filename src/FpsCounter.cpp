#include "FpsCounter.h"


FpsCounter::FpsCounter()
{
}


FpsCounter::~FpsCounter()
{
}

void FpsCounter::init(GLFWwindow* window)
{
  win = window;
  cnt = 0;
  freq = Crosy::getPerformanceFrequency();
  ticks = Crosy::getPerformanceCounter();
}

void FpsCounter::pulse()
{
  cnt++;
  float timePass = float(Crosy::getPerformanceCounter() - ticks) / freq;

  if (timePass > 10)
  {
    float fps = cnt / timePass;
    const int bufSize = 256;
    char str[bufSize];
    Crosy::snprintf(str, bufSize, "Fps: %.3f", fps);
    glfwSetWindowTitle(win, str);
    ticks = Crosy::getPerformanceCounter();
    cnt = 0;
  }
}
