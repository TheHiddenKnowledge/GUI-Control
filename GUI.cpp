#include "GUI.h"
GUI::GUI(uint16_t w, uint16_t h, uint16_t Row, uint16_t Col, Adafruit_ILI9341 *SCREEN /*Adafruit_SSD1331 *SCREEN*/)
{
    screen = SCREEN;
    width = w;
    height = h;
    dx = width / Col;
    dy = height / Row;
    for (int i = 0; i < MAXELEMENTS; i++)
    {
        canvas[i] = 0;
        selectionset[i] = 0;
    }
}
void GUI::grid(ELEMENT *ele, uint16_t row, uint16_t col)
{
    int16_t x, y;
    y = (row)*dy + dy / 2;
    x = (col)*dx + dx / 2;
    ele->x = x;
    ele->y = y;
}
void GUI::grid(ELEMENT *ele, uint16_t row, uint16_t col, uint16_t rowspan, uint16_t colspan)
{
    if (row + rowspan > height / dy || col + colspan > width / dx)
    {
        return;
    }
    int16_t x, y;
    y = rowspan * dy / 2 + (row)*dy;
    x = colspan * dx / 2 + (col)*dx;
    ele->x = x;
    ele->y = y;
}
void GUI::position(ELEMENT *ele, int16_t x, int16_t y)
{
    ele->x = x;
    ele->y = y;
}
void GUI::Element(ELEMENT *Element, String Text, short Textclr, short Bgclr, short Hlclr, int Textsz, int Padding)
{
    // Gets the bounds of the elements text
    uint16_t W, H;
    int16_t x1, y1;
    screen->setTextSize(Textsz);
    screen->getTextBounds(Text, 0, 0, &x1, &y1, &W, &H);
    Element->textclr = Textclr;
    Element->bgclr = Bgclr;
    Element->hlclr = Hlclr;
    Element->tempclr = Bgclr;
    Element->textsz = Textsz;
    Element->padding = Padding;
    Element->w = W;
    Element->h = H;
    canvas[index] = Element;
    index += 1;
}
LABEL *GUI::Label(String Text, short Textclr, uint8_t Textsz)
{
    LABEL *temp = new LABEL();
    temp->value = new char[MAXTEXT];
    strcpy(temp->value, Text.c_str());
    temp->bg = false;
    temp->id = 1;
    Element(temp, Text, Textclr, 0, 0, Textsz, 0);
    return temp;
}
LABEL *GUI::Label(String Text, short Textclr, uint8_t Textsz, short Bgclr, uint8_t Padding)
{
    LABEL *temp = new LABEL();
    temp->value = new char[MAXTEXT];
    strcpy(temp->value, Text.c_str());
    temp->bg = true;
    temp->id = 1;
    Element(temp, Text, Textclr, Bgclr, 0, Textsz, Padding);
    return temp;
}
void LABEL::draw(Adafruit_ILI9341 *SCREEN /*Adafruit_SSD1331 *SCREEN*/)
{
    int16_t x1, y1;
    x1 = x - w / 2;
    y1 = y - h / 2;
    if (bg)
    {
        SCREEN->fillRect(x1 - padding, y1 - padding, 2 * (w / 2 + padding), 2 * (h / 2 + padding), bgclr);
    }
    SCREEN->setCursor(x1, y1);
    SCREEN->setTextColor(textclr);
    SCREEN->setTextSize(textsz);
    SCREEN->print(value);
}
BUTTON *GUI::Button(String Text, short Textclr, uint8_t Textsz, void(*F), int *Params, uint8_t Size, short Bgclr, short Hlclr, uint8_t Padding)
{
    BUTTON *temp = new BUTTON();
    temp->value = new char[MAXTEXT];
    temp->params = new int[10];
    strcpy(temp->value, Text.c_str());
    temp->func = F;
    for (int i = 0; i < Size; i++)
    {
        temp->params[i] = Params[i];
    }
    temp->size = Size;
    temp->id = 2;
    Element(temp, Text, Textclr, Bgclr, Hlclr, Textsz, Padding);
    return temp;
}
void BUTTON::draw(Adafruit_ILI9341 *SCREEN /*Adafruit_SSD1331 *SCREEN*/)
{
    int16_t x1, y1;
    x1 = x - w / 2;
    y1 = y - h / 2;
    SCREEN->fillRect(x1 - padding, y1 - padding, 2 * (w / 2 + padding), 2 * (h / 2 + padding), tempclr);
    SCREEN->setCursor(x1, y1);
    SCREEN->setTextColor(textclr);
    SCREEN->setTextSize(textsz);
    SCREEN->print(value);
}
ENTRY *GUI::Entry(String Text, short Textclr, uint8_t Textsz)
{
    ENTRY *temp = new ENTRY();
    temp->value = new char[MAXTEXT];
    strcpy(temp->value, Text.c_str());
    temp->bg = false;
    temp->id = 3;
    Element(temp, Text, Textclr, 0, 0, Textsz, 0);
    return temp;
}
ENTRY *GUI::Entry(short Textclr, uint8_t Textsz, uint8_t Size, short Bgclr, short Hlclr, uint8_t Padding)
{
    ENTRY *temp = new ENTRY();
    temp->value = new char[MAXTEXT];
    String holder = "";
    for (int i = 0; i < Size; i++)
    {
        holder += "F";
    }
    temp->bg = true;
    temp->size = Size;
    temp->id = 3;
    Element(temp, holder, Textclr, Bgclr, Hlclr, Textsz, Padding);
    return temp;
}
void ENTRY::draw(Adafruit_ILI9341 *SCREEN /*Adafruit_SSD1331 *SCREEN*/)
{
    int16_t x1, y1;
    x1 = x - w / 2;
    y1 = y - h / 2;
    if (bg)
    {
        SCREEN->fillRect(x1 - padding, y1 - padding, 2 * (w / 2 + padding), 2 * (h / 2 + padding), bgclr);
    }
    SCREEN->setCursor(x1, y1);
    SCREEN->setTextColor(textclr);
    SCREEN->setTextSize(textsz);
    SCREEN->print(value);
}
CAROUSEL *GUI::Carousel(short Textclr, uint8_t Textsz, char Values[][MAXTEXT], uint8_t Size, short Bgclr, short Hlclr, uint8_t Padding)
{
    CAROUSEL *temp = new CAROUSEL();
    temp->values = new char *[5];
    temp->value = new char[MAXTEXT];
    strcpy(temp->value, Values[0]);
    for (uint8_t i = 0; i < Size; i++)
    {
        temp->values[i] = new char[50];
        strcpy(temp->values[i], Values[i]);
    }
    temp->size = Size;
    temp->id = 4;
    Element(temp, String(Values[0]), Textclr, Bgclr, Hlclr, Textsz, Padding);
    return temp;
}
void CAROUSEL::draw(Adafruit_ILI9341 *SCREEN /*Adafruit_SSD1331 *SCREEN*/)
{
    int16_t x1, y1;
    x1 = x - w / 2;
    y1 = y - h / 2;
    SCREEN->fillRect(x1 - padding, y1 - padding, 2 * (w / 2 + padding), 2 * (h / 2 + padding), tempclr);
    SCREEN->fillTriangle(x1 - padding, y1 - padding, x1 - padding, y1 + h + padding, x1 - padding - w / 8, y1 + h / 2, bgclr);
    SCREEN->fillTriangle(x1 + w + padding, y1 - padding, x1 + w + padding, y1 + h + padding, x1 + padding + w + w / 8, y1 + h / 2, bgclr);
    SCREEN->setCursor(x1, y1);
    SCREEN->setTextColor(textclr);
    SCREEN->setTextSize(textsz);
    SCREEN->print(value);
}
void GUI::updateElements()
{
    index = 0;
    for (int i = 0; i < MAXELEMENTS; i++)
    {
        if (canvas[i])
        {
            switch (canvas[i]->id)
            {
            case 1:
                static_cast<LABEL *>(canvas[i])->draw(screen);
                break;
            case 2:
                static_cast<BUTTON *>(canvas[i])->draw(screen);
                break;
            case 3:
                static_cast<ENTRY *>(canvas[i])->draw(screen);
                break;
            case 4:
                static_cast<CAROUSEL *>(canvas[i])->draw(screen);
                break;
            }
        }
    }
}
void GUI::deleteElements()
{
    index = 0;
    for (int i = 0; i < MAXELEMENTS; i++)
    {
        delete canvas[i];
        canvas[i] = 0;
        selectionset[i] = 0;
    }
}
void GUI::eventManager(byte key)
{
    int sidx = 0;
    for (int i = 0; i < MAXELEMENTS; i++)
    {
        if (canvas[i])
        {
            if (canvas[i]->id == 2 || canvas[i]->id == 3 || canvas[i]->id == 4)
            {
                selectionset[sidx] = canvas[i];
                sidx += 1;
            }
        }
    }
    if (key == 0xF7) // Up
    {
        selectionset[selection]->tempclr = selectionset[selection]->bgclr;
        selection -= 1;
    }
    else if (key == 0xF8) // Down
    {
        selectionset[selection]->tempclr = selectionset[selection]->bgclr;
        selection += 1;
    }
    if (selection < 0)
    {
        selection = 0;
    }
    else if (selection >= sidx)
    {
        selection = sidx - 1;
    }
    selectionset[selection]->tempclr = selectionset[selection]->hlclr;
    if (selectionset[selection]->id == 2)
    { // Button
        int *bparams = static_cast<BUTTON *>(selectionset[selection])->params;
        uint8_t *bsize = static_cast<CAROUSEL *>(selectionset[selection])->size;
        if (key == 0xF1) // Enter
        {
            static_cast<BUTTON *>(selectionset[selection])->func(bparams, *bsize);
        }
    }
    else if (selectionset[selection]->id == 3)
    { // Entry
        int8_t *eidx = &(static_cast<ENTRY *>(selectionset[selection])->idx);
        uint8_t *esize = &(static_cast<ENTRY *>(selectionset[selection])->size);
        char *evalue = static_cast<ENTRY *>(selectionset[selection])->value;
        if (*eidx < 0)
        {
            *eidx = 0;
        }
        else if (*eidx >= *esize)
        {
            *eidx = *esize - 1;
        }
        if (key == 0xF0)
        {
            evalue[*eidx] = '/0';
            *eidx -= 1;
        }
        else if (key != 0xFA)
        {
            evalue[*eidx] = key;
            *eidx += 1;
        }
    }
    else if (selectionset[selection]->id == 4)
    { // Carousel
        int8_t *cidx = &(static_cast<CAROUSEL *>(selectionset[selection])->idx);
        uint8_t *csize = &(static_cast<CAROUSEL *>(selectionset[selection])->size);
        char **cvalues = static_cast<CAROUSEL *>(selectionset[selection])->values;
        char *cvalue = static_cast<CAROUSEL *>(selectionset[selection])->value;
        if (key == 0xF6)
        {
            *cidx -= 1;
        }
        else if (key == 0xF9)
        {
            *cidx += 1;
        }
        if (*cidx < 0)
        {
            *cidx = 0;
        }
        else if (*cidx >= *csize)
        {
            *cidx = *csize - 1;
        }
        strcpy(cvalue, cvalues[*cidx]);
    }
}
void GUI::enableElements()
{
    for (int i = 0; i < MAXELEMENTS; i++)
    {
        canvas[i]->enabled = true;
    }
}
void GUI::disableElements()
{
    for (int i = 0; i < MAXELEMENTS; i++)
    {
        canvas[i]->enabled = false;
    }
}
void GUI::run()
{
    updateElements();
    deleteElements();
}
void GUI::run(byte key)
{
    eventManager(key);
    updateElements();
    deleteElements();
}