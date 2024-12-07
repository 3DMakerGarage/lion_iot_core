#include <Lion.h>

Display* Lion::display() {  return &displayController; }
TouchButtons* Lion::touchButtons() {  return &buttons; }

void Lion::begin(int duration) {
  beginTouchButtons();
  beginDisplay();
  delay(duration);
}

void Lion::beginDisplay() {
  displayController.begin();
  displayController.drawLogo();
  displayController.draw();
}

void Lion::beginTouchButtons() {
  buttons.begin();
}
