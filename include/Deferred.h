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

#ifndef Deferred_h
#define Deferred_h

#include <Arduino.h>

class OnDeferredExecutionCallback {
    public:
        virtual void onDeferredExecution();
};

class Deferred {
    private:
        unsigned long deferredPeriod = 0;
        unsigned long lastExecutionTime = 0;
        boolean doExecute();

    public:
        typedef void(*DeferredCallback)();
        
        Deferred(unsigned int executeEveryMS = 100);
        
        void execute(DeferredCallback callback);
        void execute(OnDeferredExecutionCallback *owner);
};

#endif