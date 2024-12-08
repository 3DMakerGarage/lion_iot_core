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

#ifndef TouchButtons_h
#define TouchButtons_h

#include <Arduino.h>
#include <Board.h>
#include <Deferred.h>

class TouchButtons : private OnDeferredExecutionCallback {
    public:
        enum BUTTON { A, B };
        enum BUTTON_EVENT { PRESSED, LONG_PRESSED };
        typedef void(*OnTouchButtonEvent)(BUTTON, BUTTON_EVENT);
        void setOnTouchButtonEvent(OnTouchButtonEvent callback);
        
    private:
        virtual void onDeferredExecution();
        const unsigned int LOOP_PERIOD_MS = 100;
        const unsigned int LONG_PRESS_THRESHOLD = 1500;
        unsigned long lastValidationTime = 0;
        unsigned long onPressedTimeForA = 0;
        unsigned long onPressedTimeForB = 0;
        int latestValueOnA = 0;
        int latestValueOnB = 0;
        Deferred deferredLoop = Deferred(LOOP_PERIOD_MS);
        OnTouchButtonEvent onTouchButtonEventCallback;

    protected:
        void touchButtons_begin();
        void touchButtons_onLoopExecution();
        void touchButtons_loop();
};

#endif