
/*  SimpleButton
 *  A basic button implementation.
 *  Depends on the AdaFruit GFX libs for drawing.
 */

#ifndef _FRUITUI_SIMPLE_BUTTON_H
#define _FRUITUI_SIMPLE_BUTTON_H

#include <Adafruit_GFX.h>

class SimpleButton {
    
    public:
        // Constructors
        SimpleButton(void);
        SimpleButton(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char *text, Adafruit_GFX *Gfx);
        
        // Setters
        void SetContext(Adafruit_GFX *Gfx);
        void SetPosition(uint16_t x, uint16_t y);
        void SetDimensions(uint16_t w, uint16_t h);
        void SetTextColor(uint16_t color);
        void SetBackColor(uint16_t color);
        void SetOutlineColor(uint16_t color);
        void SetTextSize(uint8_t size);
        void SetText(const char *text);
        void SetCallback(void (*callback)(void));
        
        // Main Entry Points
        void Draw(void);
        void Update(int x, int y);
        
        // Helpers
        static uint16_t MakeColor(uint8_t red, uint8_t green, uint8_t blue);
        
    protected:
        // Class Members
        Adafruit_GFX   * mGfx;
        uint16_t         mX;
        uint16_t         mY;
        uint16_t         mW;
        uint16_t         mH;
        uint16_t         mOutlineColor;
        uint16_t         mBackColor;
        uint16_t         mTextColor;
        uint8_t          mTextSize;
        const char     * mText;
        void (*mCallback)(void);
        
        // Implementation
        boolean  ContainsPoint(int x, int y);
        uint16_t TextWidth(const char *s);
        uint8_t  TextHeight(void);
        uint16_t GetXCursor(void);
        uint16_t GetYCursor(void);
};

#endif
