#ifndef TouchButtons_h
#define TouchButtons_h

#include <Arduino.h>
#include <Debounce.h>

#define PIN_BUTTON_A D0
#define PIN_BUTTON_B D3

class TouchButtons {
    public:
        enum BUTTON { A, B };
        enum BUTTON_EVENT { PRESSED, LONG_PRESSED };
        typedef void(*OnTouchButtonEvent)(BUTTON, BUTTON_EVENT);
        static void begin();
        static void loop(OnTouchButtonEvent callback);

    private:
        static const unsigned int LOOP_PERIOD_MS = 100;
        static const unsigned int LONG_PRESS_THRESHOLD = 1500;
        static unsigned long lastValidationTime;
        static unsigned long onPressedTimeForA;
        static unsigned long onPressedTimeForB;
        static int latestValueOnA;
        static int latestValueOnB;
        static Debounce loopDebounce;
        static void onLoopExecution();
        static OnTouchButtonEvent onTouchButtonEvent;
};

extern TouchButtons Buttons; 

#endif