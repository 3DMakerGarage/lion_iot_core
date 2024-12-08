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

#include <Deferred.h>

Deferred::Deferred(unsigned int executeEveryMS) {
    deferredPeriod = executeEveryMS;
}

boolean Deferred::doExecute() {
    unsigned long currentTime = millis();
    unsigned long timeDifference = currentTime - lastExecutionTime;
    if (timeDifference >= deferredPeriod) {
        lastExecutionTime = currentTime;
        return true;
    }
    return false;
}

void Deferred::execute(DeferredCallback callback) {
    if (doExecute()) {
        callback();
    }
}

void Deferred::execute(OnDeferredExecutionCallback *owner) {
    if (doExecute()) {
        owner->onDeferredExecution();
    }
}
