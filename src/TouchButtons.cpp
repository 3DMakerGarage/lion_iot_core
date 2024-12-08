/*
 * Copyright 3D Maker Garage 2024
 *
 * This file is part of some open source application.
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 * Contact: 3dmakergarage@gmail.com
 */

#include <TouchButtons.h>

void TouchButtons::setOnTouchButtonEvent(OnTouchButtonEvent callback) {
    onTouchButtonEventCallback = callback;
}

void TouchButtons::touchButtons_begin() {
    pinMode(TOUCH_BUTTON_A, OUTPUT);
    pinMode(TOUCH_BUTTON_B, OUTPUT);

    digitalWrite(TOUCH_BUTTON_A, LOW);
    digitalWrite(TOUCH_BUTTON_B, LOW);
}

void TouchButtons::onDeferredExecution() {
    if (onTouchButtonEventCallback) {
        unsigned long now = millis();
        int currentValueOnA = digitalRead(TOUCH_BUTTON_A);
        bool longPressedA = false;
        bool longPressedB = false;
        if (latestValueOnA == 0 && currentValueOnA == 1) {
            onPressedTimeForA = now;
        } else if (latestValueOnA == 1 && currentValueOnA == 0) {
            unsigned long difference = now - onPressedTimeForA;
            if (difference >= LONG_PRESS_THRESHOLD) {
                longPressedA = true;
            } else {
                onTouchButtonEventCallback(BUTTON::A, BUTTON_EVENT::PRESSED);
            }
        }
        int currentValueOnB = digitalRead(TOUCH_BUTTON_B);   
        if (latestValueOnB == 0 && currentValueOnB == 1) {
            onPressedTimeForB = now;
        } else if (latestValueOnB == 1 && currentValueOnB == 0) {
            unsigned long difference = now - onPressedTimeForB;
            if (difference >= LONG_PRESS_THRESHOLD) {
                longPressedB = true;
            } else {
                onTouchButtonEventCallback(TouchButtons::BUTTON::B, TouchButtons::BUTTON_EVENT::PRESSED);
            }
        }

        if (longPressedA && !longPressedB) {
            onTouchButtonEventCallback(TouchButtons::BUTTON::A, TouchButtons::BUTTON_EVENT::LONG_PRESSED);
        } else if (!longPressedA && longPressedB) {
            onTouchButtonEventCallback(TouchButtons::BUTTON::B, TouchButtons::BUTTON_EVENT::LONG_PRESSED);
        }
        
        latestValueOnA = currentValueOnA;
        latestValueOnB = currentValueOnB;
    }
}

void TouchButtons::touchButtons_loop() {
    deferredLoop.execute(this);    
}