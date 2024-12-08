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

#include <Arduino.h>
#include <Lion.h>

unsigned int counter = 0;
Lion lion = Lion();

void displayCounter() {
    lion.display_clear();
    lion.display_writeAlignedText(3, (String)counter);
    lion.display_draw();
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
    lion.setOnTouchButtonEvent(onTouchButtonEvent);
    
    displayCounter();
}

void loop() {
    lion.loop();
}