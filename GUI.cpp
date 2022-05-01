#include "GUI.h"
GUI::GUI(uint16_t w, uint16_t h, uint16_t Row, uint16_t Col, Adafruit_ILI9341 *TFT)
{
    tft = TFT;
    width = w;
    height = h;
    dx = width / Row;
    dy = height / Col;
    for (int i = 0; i < MAXELEMENTS; i++)
    {
        canvas[i] = 0;
        selectionset[i] = 0;
    }
}
void GUI::grid(ELEMENT *ele, uint16_t row, uint16_t col)
{
    int16_t x, y;
    y = (row + .5) * dx;
    x = (col + .5) * dy;
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
    y = (row + rowspan) / 2 * dx;
    x = (col + colspan) / 2 * dy;
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
    tft->setTextSize(Textsz);
    tft->getTextBounds(Text, 0, 0, &x1, &y1, &W, &H);
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
    strcpy(temp->value, Text.c_str());
    temp->bg = false;
    temp->id = 1;
    Element(temp, Text, Textclr, 0, 0, Textsz, 0);
    return temp;
}
LABEL *GUI::Label(String Text, short Textclr, uint8_t Textsz, short Bgclr, uint8_t Padding)
{
    LABEL *temp = new LABEL();
    strcpy(temp->value, Text.c_str());
    temp->bg = true;
    temp->id = 1;
    Element(temp, Text, Textclr, Bgclr, 0, Textsz, Padding);
    return temp;
}
LABEL::draw(Adafruit_ILI9341 *TFT)
{
    int16_t x1, y1;
    x1 = x - w / 2;
    y1 = y - h / 2;
    TFT->setCursor(x1, y1);
    TFT->setTextColor(textclr);
    TFT->setTextSize(textsz);
    TFT->print(value);
    if (bg)
    {
        TFT->fillRect(x1 - padding, y1 - padding, 2 * (w / 2 + padding), 2 * (h / 2 + padding), bgclr);
    }
}
BUTTON *GUI::Button(String Text, short Textclr, uint8_t Textsz, void(*F), int *Params, uint8_t Size, short Bgclr, short Hlclr, uint8_t Padding)
{
    BUTTON *temp = new BUTTON();
    strcpy(temp->value, Text.c_str());
    temp->func = F;
    temp->params = Params;
    temp->size = Size;
    temp->id = 2;
    Element(temp, Text, Textclr, Bgclr, Hlclr, Textsz, Padding);
    return temp;
}
BUTTON::draw(Adafruit_ILI9341 *TFT)
{
    int16_t x1, y1;
    x1 = x - w / 2;
    y1 = y - h / 2;
    TFT->setCursor(x1, y1);
    TFT->setTextColor(textclr);
    TFT->setTextSize(textsz);
    TFT->print(value);
    TFT->fillRect(x1 - padding, y1 - padding, 2 * (w / 2 + padding), 2 * (h / 2 + padding), tempclr);
}
ENTRY *GUI::Entry(String Text, short Textclr, uint8_t Textsz)
{
    ENTRY *temp = new ENTRY();
    temp->bg = false;
    temp->id = 3;
    Element(temp, Text, Textclr, 0, 0, Textsz, 0);
    return temp;
}
ENTRY *GUI::Entry(int Length, short Textclr, uint8_t Textsz, short Bgclr, short Hlclr, uint8_t Padding)
{
    ENTRY *temp = new ENTRY();
    String holder = "";
    for (int i = 0; i < Length; i++)
    {
        holder += "F";
    }
    temp->bg = true;
    temp->id = 3;
    Element(temp, holder, Textclr, Bgclr, Hlclr, Textsz, Padding);
    return temp;
}
ENTRY::draw(Adafruit_ILI9341 *TFT)
{
    int16_t x1, y1;
    x1 = x - w / 2;
    y1 = y - h / 2;
    TFT->setCursor(x1, y1);
    TFT->setTextColor(textclr);
    TFT->setTextSize(textsz);
    TFT->print(value);
    if (bg)
    {
        TFT->fillRect(x1 - padding, y1 - padding, 2 * (w / 2 + padding), 2 * (h / 2 + padding), bgclr);
    }
}
CAROUSEL *GUI::Carousel(short Textclr, uint8_t Textsz, char **Values, uint8_t Size, short Bgclr, short Hlclr, uint8_t Padding)
{
    CAROUSEL *temp = new CAROUSEL();
    strcpy(temp->value, Values[0]);
    temp->values = Values;
    temp->size = Size;
    temp->id = 4;
    Element(temp, String(Values[0]), Textclr, Bgclr, Hlclr, Textsz, Padding);
    return temp;
}
CAROUSEL::draw(Adafruit_ILI9341 *TFT)
{
    int16_t x1, y1;
    x1 = x - w / 2;
    y1 = y - h / 2;
    TFT->setCursor(x1, y1);
    TFT->setTextColor(textclr);
    TFT->setTextSize(textsz);
    TFT->print(value);
    TFT->fillRect(x1 - padding, y1 - padding, 2 * (w / 2 + padding), 2 * (h / 2 + padding), tempclr);
    TFT->fillTriangle(x1, y1, x1, y1 + h, x1 - w / 8, y1 + h / 2, bgclr);
    TFT->fillTriangle(x1 + w, y1, x1 + w, y1 + h, x1 + w + w / 8, y1 + h / 2, bgclr);
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
                static_cast<LABEL *>(canvas[i])->draw(tft);
                break;
            case 2:
                static_cast<BUTTON *>(canvas[i])->draw(tft);
                break;
            case 3:
                static_cast<ENTRY *>(canvas[i])->draw(tft);
                break;
            case 4:
                static_cast<CAROUSEL *>(canvas[i])->draw(tft);
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
            if (canvas[i]->id == 2 || canvas[i]->id == 3 || canvas[i]->id)
            {
                selectionset[sidx] = canvas[i];
                sidx += 1;
            }
        }
    }
    if (key == 0xF7) // Up 
    {
        selection -= 1;
    }
    else if (key == 0xF8) // Down
    {
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
    switch (selectionset[selection]->id)
    {
    case 2:              // Button
        int *bparams = static_cast<BUTTON *>(selectionset[selection])->params;
        uint8_t *bsize = static_cast<CAROUSEL *>(selectionset[selection])->size;
        if (key == 0xF1) // Enter
        {
            static_cast<BUTTON *>(selectionset[selection])->func(bparams, *bsize);
        }
    case 3: // Entry
        uint8_t *eidx = &(static_cast<ENTRY *>(selectionset[selection])->idx);
        char *evalue = static_cast<ENTRY *>(selectionset[selection])->value;
        if (*eidx < 0)
        {
            *eidx = 0;
        }
        else if (*eidx >= MAXELEMENTS)
        {
            *eidx = MAXELEMENTS - 1;
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
    case 4: // Carousel
        uint8_t *cidx = &(static_cast<CAROUSEL *>(selectionset[selection])->idx);
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