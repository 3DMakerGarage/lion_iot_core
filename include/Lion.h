#ifndef LION_H
#define LION_H

#include <Arduino.h>
#include <Display.h>
#include <TouchButtons.h>
#include <Board.h>

class Lion {
public:
    void begin(int duration = 1500);
    Display* display();
    TouchButtons* touchButtons();

private:
    Display displayController = Display();
    TouchButtons buttons = TouchButtons();

    void beginDisplay();
    void beginTouchButtons();
};

#endif
