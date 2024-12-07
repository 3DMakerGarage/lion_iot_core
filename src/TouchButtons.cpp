#include <TouchButtons.h>

int TouchButtons::latestValueOnA = 0;
int TouchButtons::latestValueOnB = 0;
unsigned long TouchButtons::onPressedTimeForA = 0;
unsigned long TouchButtons::onPressedTimeForB = 0;
unsigned long TouchButtons::lastValidationTime = 0;
TouchButtons::OnTouchButtonEvent TouchButtons::onTouchButtonEvent;
Debounce TouchButtons::loopDebounce = Debounce(LOOP_PERIOD_MS);

void TouchButtons::begin() {
    pinMode(PIN_BUTTON_A, OUTPUT);
    pinMode(PIN_BUTTON_B, OUTPUT);

    digitalWrite(PIN_BUTTON_A, LOW);
    digitalWrite(PIN_BUTTON_B, LOW);
}

void TouchButtons::onLoopExecution() {
    if (onTouchButtonEvent) {
        unsigned long now = millis();
        int currentValueOnA = digitalRead(PIN_BUTTON_A);
        bool longPressedA = false;
        bool longPressedB = false;
        if (latestValueOnA == 0 && currentValueOnA == 1) {
            onPressedTimeForA = now;
        } else if (latestValueOnA == 1 && currentValueOnA == 0) {
            unsigned long difference = now - onPressedTimeForA;
            if (difference >= LONG_PRESS_THRESHOLD) {
                longPressedA = true;
            } else {
                onTouchButtonEvent(BUTTON::A, BUTTON_EVENT::PRESSED);
            }
        }
        int currentValueOnB = digitalRead(PIN_BUTTON_B);   
        if (latestValueOnB == 0 && currentValueOnB == 1) {
            onPressedTimeForB = now;
        } else if (latestValueOnB == 1 && currentValueOnB == 0) {
            unsigned long difference = now - onPressedTimeForB;
            if (difference >= LONG_PRESS_THRESHOLD) {
                longPressedB = true;
            } else {
                onTouchButtonEvent(BUTTON::B, BUTTON_EVENT::PRESSED);
            }
        }

        if (longPressedA && !longPressedB) {
            onTouchButtonEvent(BUTTON::A, BUTTON_EVENT::LONG_PRESSED);
        } else if (!longPressedA && longPressedB) {
            onTouchButtonEvent(BUTTON::B, BUTTON_EVENT::LONG_PRESSED);
        }
        
        latestValueOnA = currentValueOnA;
        latestValueOnB = currentValueOnB;
    }
}

void TouchButtons::loop(OnTouchButtonEvent callback) {
    onTouchButtonEvent = callback;
    loopDebounce.execute(onLoopExecution);    
}