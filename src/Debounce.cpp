#include <Debounce.h>

Debounce::Debounce(unsigned int period) {
    debouncePeriod = period;
}

void Debounce::execute(Callback callback) {
    unsigned long currentTime = millis();
    unsigned long timeDifference = currentTime - lastExecutionTime;
    if (timeDifference >= debouncePeriod) {
        callback();
        lastExecutionTime = currentTime;
    }
}