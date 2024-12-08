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

#ifndef DisplayController_h
#define DisplayController_h

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LittleFS.h>

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DEFAULT_TEXT_SIZE 3
#define SCREEN_I2C_ADDRESS 0x3C //0x3C, 0x78
#define ERROR_INITIALIZINF_DISPLAY "ERROR --> Initializing OLED Driver on I2C Address: 0x3C"

enum HorizontalAlignment { LEFT, CENTER, RIGHT };
enum VerticalAlignment { TOP, MIDDLE, BOTTOM };

class Display {
    private:
		Adafruit_SSD1306 SSD1306;
		void readFile(String filePath, uint8_t* buffer, int size = 1024);

	protected:
		Display();
		void display_begin();

    public:
		void display_turnOn();
		void display_turnOff();
		void display_clear();
		void display_draw();
		
		void display_writeText(String text);
		void display_writeText(int16_t x, int16_t y, String text);
		void display_writeText(int16_t x, int16_t y, int16_t size, String text);
		
		void display_writeText(char character);
		void display_writeText(int16_t x, int16_t y, char character);
		void display_writeText(int16_t x, int16_t y, int16_t size, char character);

		void display_writeAlignedText(int16_t size, String text);
		void display_writeAlignedText(
			HorizontalAlignment horizonatlAlignment,
			VerticalAlignment verticalAlignment, 
			int16_t size,
			String text
		);
		
		void display_drawLogo();
		void display_drawPixel(int16_t x, int16_t y);
		void display_drawFile(String filePath, int x = 0, int y = 0, int width = 128, int height = 64);

		void display_setBrightness(int8 value);

		void display_drawRoundedRect(int x, int y, int width, int height, int radious);
		void display_fillRoundedRect(int x, int y, int width, int height, int radious);

		void display_getTextBounds(int16_t *size, String *text, uint16_t *textWidth, uint16_t *textHeight);
};
#endif