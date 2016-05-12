#include <LiquidCrystal.h>
#define DEBUGMODE true
#define btnRIGHT  0 
#define btnUP     1 
#define btnDOWN   2 
#define btnLEFT   3 
#define btnSELECT 4 
#define btnNONE   5 
/***************************/
#define DB4       4
#define DB5       5
#define DB6       6
#define DB7       7
#define RS        8
#define ENABLE    9
#define BACKLIGHT 10
#define NUMBEROPTIONS 4
  /* 
Analog 0	Button (select, up, right, down and left)
Digital 4	DB4
Digital 5	DB5
Digital 6	DB6
Digital 7	DB7
Digital 8	RS (Data or Signal Display Selection)
Digital 9	Enable
Digital 10	Backlit Control 
*/

boolean changed            = false;
byte customChar[8] = {
    0b01000,
    0b01100,
    0b01110,
    0b01111,
    0b01110,
    0b01100,
    0b01000,
    0b00000
};
uint8_t btnPressed          = btnNONE;
uint8_t currentMenuItem  = 0;
String menu[NUMBEROPTIONS] = { "Option 1", "Option 2", "Option 3", "Option 4"};
int btnRange[]           = { 60,200,400,600,800 };
LiquidCrystal lcd(RS, ENABLE, DB4, DB5, DB6, DB7);

uint8_t readLCDBtn()
{
    int x = analogRead(0);
    uint8_t choice = btnNONE;
    if (DEBUGMODE)
    {
        lcd.setCursor(1, 0);
        lcd.print(x);
    }
    if (x < btnRange[btnRIGHT])
        choice = btnRIGHT;
    else if (x < btnRange[btnUP])
        choice = btnUP;
    else if (x < btnRange[btnDOWN])
        choice = btnDOWN;
    else if (x < btnRange[btnLEFT])
        choice = btnLEFT;
    else if (x < btnRange[btnSELECT])
        choice = btnSELECT;
    return choice;
}

void setup()
{
    lcd.begin(16, 2);
    lcd.createChar((uint8_t)0, customChar);
    lcd.noCursor();
    displayMenu();
}

void loop()
{
    btnPressed = readLCDBtn();
    if (btnPressed != btnNONE)
        processChoice(btnPressed);
    delay(50);
}

void displayMenu()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write((uint8_t)0);
    lcd.setCursor(0, 1);
    lcd.print(menu[currentMenuItem]);
    lcd.setCursor(1,0);
    lcd.print(menu[(currentMenuItem+1) % NUMBEROPTIONS]);
}



void processChoice(uint8_t selection)
{
    switch (selection)
    {
    case btnRIGHT:
        break;
    case btnUP:
        --currentMenuItem;
        if (currentMenuItem == -1)
            currentMenuItem = NUMBEROPTIONS - 1;
        displayMenu();
        break;
    case btnDOWN:
        ++currentMenuItem;
        if (currentMenuItem == NUMBEROPTIONS)
            currentMenuItem = 0;
        displayMenu();
        break;
    case btnLEFT:
        break;
    case btnSELECT:
    default:
        return;
        break;
    }
    Serial.print(btnPressed);
    btnPressed = btnNONE;
}
