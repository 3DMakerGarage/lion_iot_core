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

class Display {
    private:
		Adafruit_SSD1306 SSD1306;
		void readFile(String filePath, uint8_t* buffer, int size = 1024);
		uint16_t getTextBounds(int16_t* size, String* text);

    public:
		Display();
		void turnOn();
		void turnOff();
        void begin();
		void clear();
		void draw();
		
		void writeText(String text);
		void writeText(int16_t x, int16_t y, String text);
		void writeText(int16_t x, int16_t y, int16_t size, String text);
		
		void writeText(char character);
		void writeText(int16_t x, int16_t y, char character);
		void writeText(int16_t x, int16_t y, int16_t size, char character);

		void writeAlignedText(int16_t y, int16_t size, HorizontalAlignment alignment, String text);
		
		void drawLogo();
		void drawPixel(int16_t x, int16_t y);
		void drawFile(String filePath, int x = 0, int y = 0, int width = 128, int height = 64);

		void setBrightness(int8 value);

		void drawRoundedRect(int x, int y, int width, int height, int radious);
		void fillRoundedRect(int x, int y, int width, int height, int radious);
};
#endif