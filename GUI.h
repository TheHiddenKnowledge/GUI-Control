/* 
The Arduino compiler really hates conditional includes/compilation for some reason. 
So to change display types the correct display type must be uncommented in both this header
and the main cpp library file.
*/
#include <Adafruit_ILI9341.h>
//#include <Adafruit_SSD1331.h>
#define MAXELEMENTS 15
#define MAXTEXT 30
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
    bool enabled = true;
    uint8_t textsz;
    uint8_t padding;
    uint8_t id = 0;
};
// Label GUI element
struct LABEL : ELEMENT
{
    char *value = 0;
    ~LABEL(){delete value;}
    void draw(Adafruit_ILI9341 *SCREEN /*Adafruit_SSD1331 *SCREEN*/);
};
// Button GUI element
struct BUTTON : ELEMENT
{
    char *value = 0;
    void (*func)(int*, uint8_t);
    int *params;
    uint8_t size;
    ~BUTTON(){delete params;}
    void draw(Adafruit_ILI9341 *SCREEN /*Adafruit_SSD1331 *SCREEN*/);
};
// Entry GUI element
struct ENTRY : ELEMENT
{
    char *value = 0;
    uint8_t size;
    int8_t idx = 0;
    ~ENTRY(){delete value;}
    void draw(Adafruit_ILI9341 *SCREEN /*Adafruit_SSD1331 *SCREEN*/);
};
// Carousel GUI element
struct CAROUSEL : ELEMENT
{
    char **values = 0;
    char *value = 0;
    uint8_t size;
    int8_t idx = 0;
    ~CAROUSEL(){for(int i = 0; i < 5; i++){delete values[i];}; delete values; delete value;}
    void draw(Adafruit_ILI9341 *SCREEN /*Adafruit_SSD1331 *SCREEN*/);
};
// GUI controller class
class GUI
{
public:
    // Characteristics of the screen
    uint16_t dx;
    uint16_t dy;
    uint16_t width;
    uint16_t height;
    Adafruit_ILI9341 *screen /*Adafruit_SSD1331 *screen*/;
    int8_t index;
    int8_t selection = 0;
    // Array containing event driven GUI elements
    ELEMENT *selectionset[MAXELEMENTS];
    // Array containing all GUI elements
    ELEMENT *canvas[MAXELEMENTS];
    // Constructor for GUI class
    GUI(uint16_t w, uint16_t h, uint16_t Row, uint16_t Col, Adafruit_ILI9341 *SCREEN /*Adafruit_SSD1331 *SCREEN*/);
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
    ENTRY *Entry(short Textclr, uint8_t Textsz, uint8_t Size, short Bgclr, short Hlclr, uint8_t Padding);
    // Initializer for carousel
    CAROUSEL *Carousel(short Textclr, uint8_t Textsz, char Values[][MAXTEXT], uint8_t Size, short Bgclr, short Hlclr, uint8_t Padding);
    
    // Method that updates the screen by drawing each GUI element
    void GUI::updateElements();
    // Method that clears the screen by deleting each GUI element
    void GUI::deleteElements();
    // Determines the behavior of each event driven GUI element
    void GUI::eventManager(byte key);
    // Enables all elements 
    void GUI::enableElements(); 
    // Disables all elements
    void GUI::disableElements();
    // Method to run GUI without events 
    void GUI::run();
    // Method to run GUI with events 
    void GUI::run(byte key);
};