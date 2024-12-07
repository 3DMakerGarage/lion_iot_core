#ifndef Debounce_h
#define Debounce_h

#include <Arduino.h>

class Debounce {
    private:
        unsigned long debouncePeriod = 0;
        unsigned long lastExecutionTime = 0;

    public:
        typedef void(*Callback)();
        Debounce(unsigned int period = 100);
        void execute(Callback callback);
};

#endif