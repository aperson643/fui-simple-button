
/*  SimpleButton
 *  A basic button implementation.
 *  Depends on the AdaFruit GFX libs for drawing.
 */

#include "SimpleButton.h"

// Constructors

SimpleButton::SimpleButton(void) {
    mGfx      = NULL;
    mX        = 0;
    mY        = 0;
    mW        = 0;
    mH        = 0;
    mText     = "";
    mTextSize = 2;
    mOutlineColor = 0xFFFF;
    mBackColor    = 0x0000;
    mTextColor    = 0xFFFF;
}

SimpleButton::SimpleButton(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char *text, Adafruit_GFX *Gfx) {
    mGfx      = Gfx;
    mX        = x;
    mY        = y;
    mW        = w;
    mH        = h;
    mText     = text;
    mTextSize = 2;
    mOutlineColor = 0xFFFF;
    mBackColor    = 0x0000;
    mTextColor    = 0xFFFF;
}

// Setters

void SimpleButton::SetContext(Adafruit_GFX *Gfx) {
    mGfx = Gfx;
}

void SimpleButton::SetPosition(uint16_t x, uint16_t y) {
    mX = x;
    mY = y;
}

void SimpleButton::SetDimensions(uint16_t w, uint16_t h) {
    mW = w;
    mH = h;
}

void SimpleButton::SetTextColor(uint16_t color) {
    mTextColor = color;
}

void SimpleButton::SetBackColor(uint16_t color) {
    mBackColor = color;
}

void SimpleButton::SetOutlineColor(uint16_t color) {
    mOutlineColor = color;
}

void SimpleButton::SetTextSize(uint8_t size) {
    mTextSize = size;
}

void SimpleButton::SetText(const char *text) {
    mText = text;
}

void SimpleButton::SetCallback(void (*callback)(void)) {
    mCallback = callback;
}

// Helpers

uint16_t SimpleButton::MakeColor(uint8_t red, uint8_t green, uint8_t blue) {
    // Convert byte color components into rgb565 format.
    // We could do this in a one liner, but this is more readable.
    uint8_t r = red   >> 3;
    uint8_t g = green >> 2;
    uint8_t b = blue  >> 3;
    
    return (r << 11) |
           (g << 5 ) |
           (b << 0 );
}

// Main Entry Points

void SimpleButton::Draw(void) {
    if (mGfx) {
        mGfx->drawRoundRect(mX, mY, mW, mH, 5, mOutlineColor);
        mGfx->fillRoundRect(mX+1, mY+1, mW-2, mH-2, 5, mBackColor);
        mGfx->setCursor(GetXCursor(), GetYCursor());
        mGfx->setTextSize(mTextSize);
        mGfx->setTextColor(mTextColor);
        mGfx->print(mText);
    }
}

void SimpleButton::Update(int x, int y) {
    if (ContainsPoint(x,y)) {
        mCallback();
    }
}

// Implementation

boolean SimpleButton::ContainsPoint(int x, int y) {
    return (x >= mX && x <= (mX + mW)) &&
           (y >= mY && y <= (mY + mH));
}

uint16_t SimpleButton::TextWidth(const char *s) {
    // This calculation is from Adafruit_GFX::write.
    // It would be nice to be able to get the textsize 
    // from the Gfx, but it's private with no getter.
    return strlen(s) * (mTextSize * 6);
}

uint8_t SimpleButton::TextHeight(void) {
    // As above, this is from the Adafruit_GFX::write
    // implementation.
    return mTextSize * 8;
}

uint16_t SimpleButton::GetXCursor(void) {
    return mX + (mW/2) - (TextWidth(mText)/2);
}

uint16_t SimpleButton::GetYCursor(void) {
    return mY + (mH/2) - (TextHeight()/2);
}
