#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#define MAXELEMENTS 15
#define MAXTEXT 50
// Base class for all GUI elements
struct ELEMENT
{
    int16_t x;
    int16_t y;
    uint16_t w;
    uint16_t h;
    short textclr;
    short bgclr;
    short hlclr;
    short tempclr;
    bool bg;
    uint8_t textsz;
    uint8_t padding;
    uint8_t id = 0;
};
// Label GUI element
struct LABEL : ELEMENT
{
    char value[MAXTEXT];
    draw(Adafruit_ILI9341 *TFT);
};
// Button GUI element
struct BUTTON : ELEMENT
{
    char value[MAXTEXT];
    void (*func)(int*, uint8_t);
    int *params;
    uint8_t size;
    draw(Adafruit_ILI9341 *TFT);
};
// Entry GUI element
struct ENTRY : ELEMENT
{
    char value[MAXTEXT];
    uint8_t idx;
    draw(Adafruit_ILI9341 *TFT);
};
// Carousel GUI element
struct CAROUSEL : ELEMENT
{
    char **values;
    char value[MAXTEXT];
    uint8_t size;
    uint8_t idx;
    draw(Adafruit_ILI9341 *TFT);
};
// GUI controller class
class GUI
{
public:
    // Characteristics of the display
    uint16_t dx;
    uint16_t dy;
    uint16_t width;
    uint16_t height;
    Adafruit_ILI9341 *tft;
    uint8_t index;
    uint8_t selection = 0;
    // Array containing event driven GUI elements
    ELEMENT *selectionset[MAXELEMENTS];
    // Array containing all GUI elements
    ELEMENT *canvas[MAXELEMENTS];
    // Constructor for GUI class
    GUI(uint16_t w, uint16_t h, uint16_t Row, uint16_t Col, Adafruit_ILI9341 *TFT);
    // Places element on virtual grid
    void grid(ELEMENT *ele, uint16_t row, uint16_t col);
    // Places element on virtual grid with options for spanning rows/columns
    void grid(ELEMENT *ele, uint16_t row, uint16_t col, uint16_t rowspan, uint16_t colspan);
    // Places element at specified x and y coordinates
    void position(ELEMENT *ele, int16_t x, int16_t y);
    // Initializer for generic element
    void Element(ELEMENT *Element, String Text, short Textclr, short Bgclr, short Hlclr, int Textsz, int Padding);
    // Initializer for label without background
    LABEL *Label(String Text, short Textclr, uint8_t Textsz);
    // Initializer for label with background
    LABEL *Label(String Text, short Textclr, uint8_t Textsz, short Bgclr, uint8_t Padding);
    // Initializer for button
    BUTTON *Button(String Text, short Textclr, uint8_t Textsz, void(*F), int *Params, uint8_t Size, short Bgclr, short Hlclr, uint8_t Padding);
    // Initializer for entry without background
    ENTRY *Entry(String Text, short Textclr, uint8_t Textsz);
    // Initializer for entry with background
    ENTRY *Entry(int Length, short Textclr, uint8_t Textsz, short Bgclr, short Hlclr, uint8_t Padding);
    // Initializer for carousel
    CAROUSEL *Carousel(short Textclr, uint8_t Textsz, char **Values, uint8_t Size, short Bgclr, short Hlclr, uint8_t Padding);
    // Method that updates the screen by drawing each GUI element
    void GUI::updateElements();
    // Method that clears the screen by deleting each GUI element
    void GUI::deleteElements();
    // Determines the behavior of each event driven GUI element
    void GUI::eventManager(byte key);
    // Runs the GUI controller without event based elements
    void GUI::run();
    // Runs the GUI controller with event based elements
    void GUI::run(byte key);
};