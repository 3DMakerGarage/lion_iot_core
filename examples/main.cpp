#include <Arduino.h>
#include <Lion.h>

unsigned int counter = 0;
Lion lion = Lion();

void displayCounter() {
    lion.display()->clear();
    lion.display()->writeAlignedText(20, 3, CENTER, (String)counter);
    lion.display()->draw();
}

void incrementCounter() {
    if (counter < 999) counter++;
}

void decrementCounter() {
    if (counter > 0) counter--;
}

void resetCounter() {
    counter = 0;
}

void onTouchButtonEvent(TouchButtons::BUTTON button, TouchButtons::BUTTON_EVENT event) {
    if (event ==  TouchButtons::BUTTON_EVENT::PRESSED) {
        switch (button) {
            case TouchButtons::BUTTON::A:
                decrementCounter();
                break;
            case TouchButtons::BUTTON::B:
                incrementCounter();
                break;
        }
        displayCounter();
    } else if (event ==  TouchButtons::BUTTON_EVENT::LONG_PRESSED) {
        resetCounter();
        displayCounter();
    }
}

void setup() {
    lion.begin();
    displayCounter();
}

void loop() {
    lion.touchButtons()->loop(onTouchButtonEvent);
}