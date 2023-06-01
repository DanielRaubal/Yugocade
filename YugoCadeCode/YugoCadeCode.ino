//#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



#include "YugoRunLogos.h"
#include "Papir.h"
#include "Options.h"
#include "MicroKauboj.h"
#include "BackGroundScroll.h"
#include "Klovan.h"
#include "Top.h"
#include "SumaCudnovata.h"
#include "SlotMasina.h"
#include "PodmornicaSc.h"



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define PIN_WIRE_SDA        (6u)
#define PIN_WIRE_SCL        (7u)

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...


#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3C 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// 'CLOWNESCAPE_Logo', 128x32px


const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;



 int PapirKO;

const int ledPin1 = 12;
const int ledPin2 = 13;
 
int counter = 0;
int DimInt;

bool Zvuk = true;

int red_light_pin= 11;
int green_light_pin = 12;
int blue_light_pin = 13;


int buzzer=1;
int UIY=0;
void setup() {

  Serial.begin(9600);
 pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

   RGB_color(255, 0, 0);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // Clear the buffer

/*
  if (ITimer0.attachInterruptInterval(5 * 1000, TimerHandler0))
  {
   display.clearDisplay();
        display.setTextSize(4);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0, 15);
        display.println("krece");
        display.display();
  }
*/

  //attachInterrupt(digitalPinToInterrupt(2), ISR_button_pressed, LOW);
      pinMode(2, INPUT);
   pinMode(buzzer, OUTPUT);
   pinMode(9, INPUT);

StartLoading();




       UIY =0;
}
float YugoUbrzanje = 1;

void MuzikaYugo()
{
  
}

void StartLoading()
{
  bool retr=false;
  int del=10;
  for(int i=0;i< 8;i++)
  {
    if(retr ==false)
    {
         display.clearDisplay();
     display.drawBitmap(0  ,0,Loading1 ,128,64,WHITE);
     display.display();
     delay(del);
     retr=true;
    }
    else
    {
       display.clearDisplay();
     display.drawBitmap(0  ,0,Loading2 ,128,64,WHITE);
     display.display();
     delay(del);
      retr=false;
    }
    del+=10;
     beep(aH, del);
  }
   beep(gH, 800);
 delay(800);

  
}



int vremeBack=5;
int PozBack=0,CekanjeBack=0;
bool CekanjeBackBool;

int delenje=10;
int DelayVreme;
int Ypoz =32;
int Xpoz =48,XpozMax =57,XpozSlot = -10;

int buttonState = 0,buttonState2=0,buttonState3=0;


void beep(int note, int duration)
{
  //Play tone on buzzerPin
  if(Zvuk)
  {
      tone(buzzer, note, duration);
 
      //Play different LED depending on value of 'counter'
      if(counter % 2 == 0)
      {
        
        delay(duration);

      }else
      {

        delay(duration);

      }
    
      //Stop tone on buzzerPin
      noTone(buzzer);
    
      delay(5);
    
      //Increment counter
      counter++;
  }
  
}







#define DEG2RAD 0.0174532925

void drawRotatedBitmap(int16_t x, int16_t y, const uint8_t *bitmap, uint16_t angle) {

  uint8_t w = pgm_read_byte(bitmap++);
  uint8_t h = pgm_read_byte(bitmap++);

  int16_t newx, newy;
  uint8_t data = 0;

  float  cosa = cos(angle * DEG2RAD), sina = sin(angle * DEG2RAD);

  x = x - ((w * cosa / 2) - (h * sina / 2));
  y = y - ((h * cosa / 2) + (w * sina / 2));

  for (int16_t j = 0; j < h; j++) {
    for (int16_t i = 0; i < w; i++ ) {
      if ((j * w + i) & 7) data <<= 1;
      else      data   = pgm_read_byte(bitmap++);

      newx = 0.5 + x + ((i * cosa) - (j * sina));
      newy = 0.5 + y + ((j * cosa) + (i * sina));

      if (data & 0x80) display.drawPixel(newx, newy, 1);
      //else            display.drawPixel(newx, newy, 0);
    }
  }
}






int YugoPozY=10,YugoGoreDole =5,YugoRupaPoz=130,YugoScore=0,YugoLogo=0, Rupa1Y=0;

int clearDD=0, IgraBroj=0, MAX_UIY=5;

int PapirLogo=0,UpdatePaperPoz=0,Papir_Player=4,Papir_PC=0,Papir_MoresPomerat=0
,Papir_PlayerScore=0,Papir_PCScore=0;
bool PapirBool=false;


int UnisteniBrodovi;
int PodmorniceX[] = {0, 38, 85};
int Bombe[3][2] = {{-10,0},{-10,0},{-10,0}};

//PLD-desno 0 levo 1
int PozicijaPodmornice=30,PodmornicaLD=0;
int PodmornicaTorpedo1Y,PodmornicaTorpedo2Y,PodmornicaTorpedo3Y;
int PodmornicaTorpedo1X,PodmornicaTorpedo2X,PodmornicaTorpedo3X;
bool PodmornicaTorpedo1Bl;
int PodmornicaBrodX;
bool PodmornicaBrodZiva = true;




int TopX=50,TopDodajOduzmi=2,GoreDole,GoreDoleMax =3;

bool slotBl,SlotBl_PocelaIgra;


const int buttonPin = 6;    


int AutoputInt=0;
bool GameOver = false;
boolean buttonStateUI = LOW,buttonStateUI1 = LOW; 

bool PomerajUI;

int Anim;



char RPGNiz[ 7 ][ 12 ] = 
{ 
{ '3','3','3','3','3','3','3','3','3','3','3','3',}, 
{ '3','0','1','0','0','0','0','0','0','0','0','3',}, 
{ '3','0','0','0','0','0','0','0','0','0','0','3',},
{ '3','0','0','0','0','0','0','0','0','0','4','3',},
{ '3','0','0','0','0','0','0','0','0','0','0','3',},
{ '3','0','0','0','0','0','0','0','0','0','0','3',},
{ '3','3','3','3','3','3','3','3','3','3','3','3',}
};
int SlotNiz[] = {0, 0, 0, 0};
//int SlotNiz[4] = {{0},{0},{0},{0}};
int SlotPoz;
int RPGX=2,RPGY=1;
int SlotLogoInt;
bool SlotPropici;

int UsporiDisplay =25;

void loop()
{
  CekanjeBack++;
 /*
  buttonState = digitalRead(2);
  buttonState2 = digitalRead(6);
    buttonState3 = digitalRead(10);
/*
    display.clearDisplay();
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0, 15);
        display.println(buttonState2);
        display.display();
  

        display.setTextSize(1);             // Normal 1:1 pixel scale

        display.setCursor(0, 25);
        display.println(buttonState);
        display.display();

  delay(50);
  */

  
  if(CekanjeBack >=10 && CekanjeBackBool == false){
    PozBack++;

    //clearDD++;
    delay(UsporiDisplay);
     display.clearDisplay();
   
    UpdateBackground();

    


    
    if(UIY ==0)
    {
     
        UpdateYugoLogo_GameCartrige(15,128,32,YugoLogo);
        UpdateDugme_C(47,46,32,16);
        // display.drawBitmap(0  ,30,CardsLogo8 ,128,32,WHITE);
     
    }
    else if(UIY ==1)//JEBEM TI START
    {
      //UpdatePapirLogo_GameCartrige(15,128,64,Options);
         //display.drawBitmap(0  ,0,YugoRunLogo8 ,128,32,WHITE);
     
     //drawRotatedBitmap(0, 0, OptionsLogo, 45);
      UpdatePapirLogo_GameCartrige(15,128,32,YugoLogo);
      UpdateDugme_C(47,46,32,16);
    }
    else  if(UIY ==2)
    {
        //display.drawBitmap(0  ,0,OptionsLogo ,128,64,WHITE);
        //UpdateDugme_C(10,46,32,16);  
         //display.drawBitmap(0  ,0,YugoRunLogo8 ,128,32,WHITE);
    
        if(buttonState == 0)
        {
            if(Zvuk)
            {
              Zvuk = false;
            }
            else
            {
              Zvuk = true;
            }
        }

        if(Zvuk)
        {
          display.drawBitmap(30  ,0,Zvucnik2 ,64,64,WHITE);

        }
        else
        {
          display.drawBitmap(30  ,0,Zvucnik1 ,64,64,WHITE);

        }
        //delay(UsporiDisplay);



    }
    else if(UIY==3)
    {
       
        display.drawBitmap(0  ,0,CannonLogo ,128,64,WHITE);
        UpdateDugme_C(47,46,32,16);
    }
    else if(UIY==4)
    {
       
      //display.drawBitmap(0  ,0,Suma ,128,64,WHITE);
      UpdateSlotLogo_GameCartrige(-5,0,128,64,SlotLogoInt);
      //UpdateDugme_C(10,46,32,16);
    }
    else if(UIY==5)
    {
       
      //display.drawBitmap(0  ,0,Suma ,128,64,WHITE);
      UpdateSlotLogo_PodmornicaLogo(30,0,64,64,1);
      //UpdateDugme_C(10,46,32,16);
    }

      display.display();
          

    if(PozBack>6)
    {
      PozBack=0;
    }

   
     SlotLogoInt++;
    if(SlotLogoInt>5)
    {
      SlotLogoInt=1;
    }
    
    YugoLogo++;
    if(YugoLogo>9)
    {
      YugoLogo=1;
    }
    CekanjeBack=0; 
  }


  
  if(buttonState ==0 && CekanjeBackBool == false && UIY != 2)
  {//menajo sam ovde pa je prestalo da radi
    
    if(UIY ==0)
    {
       IgraBroj = 1;
    }
    else if(UIY ==1)
    {
       IgraBroj = 2;
    }
    /*
    else if(UIY ==2)
    {
      IgraBroj = 3;
    }*/
    else if(UIY ==3)
    {
      IgraBroj = 4;
    }
    else if(UIY ==4)
    {
      IgraBroj = 5;
    }
    else if(UIY ==5)
    {
      IgraBroj = 7;
    }
    
     //IgraBroj= UIY;
     CekanjeBackBool = true;
     display.clearDisplay();
  }



  //IGRICE DOLE



  if(CekanjeBackBool == true)
  {
    if(IgraBroj==1)
    {
      if(buttonState ==1&&YugoPozY<40)
      {
        YugoPozY+=YugoGoreDole;
      }
      else if(buttonState ==0)
      {
        if(GameOver == true)
        {
            ResetYugoGame();
        }
      }

      
      if(buttonState2 ==1 &&YugoPozY >0)
      {
        YugoPozY-=YugoGoreDole;
        
      }
      else if(buttonState2 ==0)
      {
        if(GameOver == true)
        {
            ResetYugoGame();
        }
      }



      if(buttonState3 ==0)
      {
         CekanjeBackBool = false;
    
         ResetYugoGame();
         display.clearDisplay();
         CekanjeBack = 10;

      }







    }
    else if(IgraBroj==2)      //PAPIR DOLE
    {
      
      //PAPIR DOLE
        if(PapirBool == false)
        {

          //display.clearDisplay();
          
           UpdatePaperPoz=1;
            UpdatePaperPozVoid();     
         UpdatePaperPozVoid_PozKarte();
         display.display();

          
                
         Papir_Player=0;
        }


      
      
       if(buttonState ==0 && Papir_Player==0 && PapirBool == true)//&& Papir_Player ==4
      {
          //p1 x29 y12
          /*
          display.clearDisplay();
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(30, 0);
        display.println(buttonState);
        display.display();
        */
          if(UpdatePaperPoz == 1)
          {
              //display.drawBitmap(29  ,12,Karta1 ,22,26,WHITE);
              Papir_Player =UpdatePaperPoz;
          }
          else   if(UpdatePaperPoz == 2)
          {
            //display.drawBitmap(29  ,12,Karta2 ,22,26,WHITE);
            Papir_Player =UpdatePaperPoz;
          }
         else   if(UpdatePaperPoz == 3)
          {
            //display.drawBitmap(29  ,12,Karta3 ,22,26,WHITE);
           Papir_Player =UpdatePaperPoz;
          }
       
          
     
      }
      /*
      else
      {
        Papir_Player=4;
      }*/
      //delay(250);


     if(buttonState2 ==0 &&Papir_Player==0)//&& Papir_Player==0
      {
          
         
         // UpdatePaperPozVoid();
          
             //  display.display();
          UpdatePaperPoz+=1;
          if(UpdatePaperPoz > 3)
          {            
             UpdatePaperPoz=1;
          }
      }


      delay(UsporiDisplay);
      if(buttonState3 ==0)
      {
         CekanjeBackBool = false;
    
         //ResetYugoGame();
         display.clearDisplay();
         CekanjeBack = 10;

      }



      



      PapirBool = true;
    }
    else if(IgraBroj==3)
    {
        
    }
    else if(IgraBroj == 4)
    {

      if(buttonState2 ==0&&buttonState3==0)
      {
        GoreDole++;
        if(GoreDole > GoreDoleMax)
        {
          GoreDole=0;
        }
        buttonState2=1;
        buttonState3=1;
      }

       if(buttonState ==0&&buttonState3==0)
      {
        GoreDole--;
        if(GoreDole < 0)
        {
          GoreDole=GoreDoleMax;
        }
        buttonState=1;
        buttonState3=1;
      }

     if(buttonState==0 && buttonState2==0)
      {
         beep(dH, 300);
      }

      
       if(buttonState ==0&&TopX<96)
      {
        TopX+=TopDodajOduzmi;
      }

       if(buttonState2 ==0 &&TopX>4)//&& Papir_Player==0
      {
          TopX-=TopDodajOduzmi;

      }
    }
    else if(IgraBroj == 5)
    {
      
      if(buttonState3==0)
      {
            slotBl = false;
            SlotNiz[0]=0;
            SlotNiz[1]=0;
            SlotNiz[2]=0;
            SlotNiz[3]=0;
            SlotNiz[4]=0;
            SlotBl_PocelaIgra = false;
              CekanjeBackBool = false;
    
         //ResetYugoGame();
         display.clearDisplay();
         CekanjeBack = 10;

      }
      
        if(buttonState2==0)
      {

        Reset_Slot();
        
        if(SlotBl_PocelaIgra)
        {
          int broj = random(0,99);
          if(broj > 66)
          {
               broj=3;
          }
          else if(broj > 33)
          {
               broj=2;
          }
          else
          {
               broj=1;
          }
          SlotNiz[SlotPoz] = broj;
                 
          SlotPoz++;
          if(SlotPoz > 3)
          {
            SlotPoz=0;
          }
                 
        }
        else
        {
          slotBl = true;
        }
         
      }

      //delay(UsporiDisplay);

    }
    else if(IgraBroj == 6)
    {
            if(UpdatePaperPoz == 1)
          {
              //display.drawBitmap(29  ,12,Karta1 ,22,26,WHITE);
              if(RPGX <12)
              {
                RPGX++;
              }
          }
          else   if(UpdatePaperPoz == 2)
          {
            //display.drawBitmap(29  ,12,Karta2 ,22,26,WHITE);
              if(RPGX >0)
              {
                RPGX--;
              }
          }
         else   if(UpdatePaperPoz == 3)
          {
            //display.drawBitmap(29  ,12,Karta3 ,22,26,WHITE);
           Papir_Player =UpdatePaperPoz;
          }


    }
    else if(IgraBroj ==7)
    {
      if(buttonState2 ==0 && PozicijaPodmornice> 0)
      {
        PozicijaPodmornice--;
        PodmornicaLD = 1;
      }
      else if(buttonState ==0 && PozicijaPodmornice< 116)
      {
        PozicijaPodmornice++;
        PodmornicaLD =0;
      }


      if(buttonState3 == 0 && !PodmornicaTorpedo1Bl)
      {
        if(GameOver)
        {
          GameOver= false;CekanjeBackBool= false;IgraBroj=0;
        }
        PodmornicaTorpedo1Bl= true;
        PodmornicaTorpedo1Y = 48;
        PodmornicaTorpedo1X = PozicijaPodmornice;
        
      }

    }

    
      
  }
  else
  {
    if(buttonState ==0)
      {
        
        
      
      }      

      if(debounceButton(buttonStateUI,6) == HIGH && buttonStateUI == LOW)
      {
        //pressed++;
        buttonStateUI = HIGH;
         UIY++;
         if(UIY > MAX_UIY)
        {
          UIY= 0;
        }
           beep(gH, 30);
           
      }
      else if(debounceButton(buttonStateUI,6) == LOW && buttonStateUI == HIGH)
      {
           buttonStateUI = LOW;
      }
      if(debounceButton(buttonStateUI1,10) == HIGH && buttonStateUI1 == LOW)
      {
        //pressed++;
        buttonStateUI1 = HIGH;
         UIY--;
         if(UIY < 0)
        {
          UIY= MAX_UIY;
        }
           beep(gH, 30);
      }
      else if(debounceButton(buttonStateUI1,10) == LOW && buttonStateUI1 == HIGH)
      {
           buttonStateUI1 = LOW;
      }
  }

  
  
  if(CekanjeBackBool == true && IgraBroj==1)
  {
 



      if(YugoRupaPoz > -63 && YugoRupaPoz < -37 &&  Rupa1Y+7 >YugoPozY && Rupa1Y-7 < YugoPozY   /*&& YugoRupaPoz+7 < YugoPozY && YugoRupaPoz-7 > YugoPozY*/)
      {
        
        GameOver = true;
      }

      if(GameOver == true)
      {
         display.clearDisplay();
        GameOverVoid(YugoScore);

        display.display();
        
      }
      else
      {


        
    display.clearDisplay();
     //display.drawBitmap(0  ,0,BackAr1 ,128,64,WHITE);
    DimFunkcija(-5,YugoPozY+10);
      YugoRupaPoz-=18;//8
      if(YugoRupaPoz < -90)
      {
        YugoRupaPoz= 130;
        Rupa1Y=random(0, 40);
      }
    
      Update_Autoput(128,32,22);

      AutoputInt++;
      display.drawBitmap(YugoRupaPoz  ,Rupa1Y,rupa  ,128,32,WHITE);

        beep(240, 5);
      
      YugoScore++;
           display.drawBitmap(-40  ,YugoPozY,YugoAuto  ,128,64,WHITE);
     
         String ScoreString = "SCR:"+String(YugoScore);
        char ScoreStringArrayCPU[50]; 
        ScoreString.toCharArray(ScoreStringArrayCPU,50);

        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0, 0);
        display.println(ScoreStringArrayCPU);


        if(YugoScore < 101)
        {
         String ScoreString1 = "SPD:"+String(YugoScore)+"kmh";
        char ScoreStringArrayCPU1[50]; 
        ScoreString1.toCharArray(ScoreStringArrayCPU1,50);
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(68, 0);
        display.println(ScoreStringArrayCPU1);
        }
        else
        {
          
        String ScoreString1 = "SPD:100kmh";
        //String ScoreString1 = "Y"+String(YugoPozY)+"|";
        char ScoreStringArrayCPU1[50]; 
        ScoreString1.toCharArray(ScoreStringArrayCPU1,50);
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(68, 0);
        display.println(ScoreStringArrayCPU1);

          /*
          String ScoreString = "Max"+String(Rupa1Y+4)+"|Min"+String(Rupa1Y-4);
        char ScoreStringArrayCPU[50]; 
        ScoreString.toCharArray(ScoreStringArrayCPU,50);
        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(58, 0);
        display.println(ScoreStringArrayCPU);*/
        }
  
        if(YugoScore > 90)
        {
          YugoUbrzanje = 1;
        }
        if(YugoScore > 60)
        {
          YugoUbrzanje = 2;
        }
        else if(YugoScore > 30)
        {
          YugoUbrzanje = 3;
        }
        else
        {
          YugoUbrzanje = 4;
        }
        
        display.display();
        delay((UsporiDisplay/2)*YugoUbrzanje);
        
      }

 
     
  }
  else if(CekanjeBackBool == true && IgraBroj==2)
    {
      //Neprijatelj X77 i Y11



       
        //display.drawBitmap(0  ,0,Karte_Default ,128,64,WHITE);
          
    
              //display.drawBitmap(77  ,11,Karta1 ,22,26,WHITE);
     
        
      if(Papir_Player > 0)//>3
      {
        display.clearDisplay();
          display.drawBitmap(0  ,0,Karte_Default ,128,64,WHITE);
          int br = random(1,4);
          if(br == 4)
          {
            br=3;
          }
          UpdatePaperPozVoid_Neprijatelj(br);
          //PapirKoPobedi(br);

          
          //UpdatePaperPozVoid();
          UpdatePaperPozVoid_PozKarte();
          PapirKoPobedi(br);
           display.setTextSize(1);             // Normal 1:1 pixel scale
            display.setTextColor(SSD1306_WHITE);        // Draw white text
            display.setCursor(13, 15);
            display.println(Papir_PlayerScore);
            


         display.setTextSize(1);             // Normal 1:1 pixel scale
            display.setTextColor(SSD1306_WHITE);        // Draw white text
            display.setCursor(105, 15);
            display.println(Papir_PCScore);
            


                
           display.display();

          if(PapirKO == 1)
          {
            PapirPobedaMuzika();
          }
          else if(PapirKO == 2)
          {
            PapirPorazMuzika();
          }
          else if(PapirKO > 2)
          {
            PapirNistaMuzika();
          }

          
           Papir_Player=0;
            PapirKO=0;
      }
      else
      
      {
        display.clearDisplay();
        //display.drawBitmap(0  ,0,Karte_Default ,128,64,WHITE);
        UpdatePaperPozVoid();
        //UpdatePaperPozVoid_PozKarte();



       
        
         display.display();
      }

      


      
        
    }
 else if(CekanjeBackBool == true && IgraBroj==3)
    {
   

/*
      display.clearDisplay();
      UpdateBackground();

      if(Zvuk)
      {
        display.drawBitmap(0  ,0,Zvucnik2 ,64,64,WHITE);
        display.display();
        
      }
      else 
      {
        
        display.drawBitmap(0  ,0,Zvucnik1 ,64,64,WHITE);
        display.display();
        
      }
      delay(UsporiDisplay);
      /*
         display.clearDisplay();
      display.drawBitmap(0  ,0,Slot ,128,32,WHITE);
        display.display();
        */
        
      }
      else if(CekanjeBackBool == true && IgraBroj==4)
      {
        display.clearDisplay();
         display.drawBitmap(0  ,0,Most  ,128,64,WHITE);
          display.drawBitmap(0  ,10,tenk  ,11,7,WHITE);
             ProveraTop();
         display.display();
     
      }
else if(CekanjeBackBool == true && IgraBroj == 6)
{
   int k=8,m=0;
       display.clearDisplay();
       
       for(int i=0;i<12;i++)
       {
          k+=8;
          m=0;
          for(int x=0;x<7;x++)
          {
            display.setTextSize(1);             // Normal 1:1 pixel scale
            display.setTextColor(SSD1306_WHITE);        // Draw white text
            display.setCursor(0, 0);
            display.println(12);
             //display.drawBitmap(k  ,m,Neprijatelj ,7,7,WHITE);
             m+=8;
             if(RPGNiz[x][i]=='0')
             {
                display.drawBitmap(k  ,m,Mesto ,7,7,WHITE);
                //display.drawBitmap(k  ,m,Mesto ,7,7,WHITE);
             }
             else if(RPGNiz[x][i]=='1')
             {
                display.drawBitmap(k  ,m,Covek ,7,7,WHITE);
                //display.drawBitmap(k  ,m,Mesto ,7,7,WHITE);
             }
              else if(RPGNiz[x][i]=='3')
             {
                display.drawBitmap(k  ,m,Zid ,7,7,WHITE);
                //display.drawBitmap(k  ,m,Mesto ,7,7,WHITE);
             }
               else if(RPGNiz[x][i]=='4')
             {
                display.drawBitmap(k  ,m,Zid ,7,7,WHITE);
                //display.drawBitmap(k  ,m,Mesto ,7,7,WHITE);
             }
             
          }


       }
}
else if(CekanjeBackBool == true && IgraBroj == 5)
{
  delay(UsporiDisplay);
  if(slotBl)
  {
    for(int p=1;p<= 4;p++)
    {
          display.clearDisplay();
          SlotAnimInicijalni(p);
          display.display();
          //delay(15);  
    }
  }
  else
  {
    if(!SlotBl_PocelaIgra)
    {
       display.clearDisplay();
       display.drawBitmap(0  ,0,SlotE1  ,128,64,WHITE);
       display.display();
    }
    else
    {
      if(SlotNiz[4] ==0)
      {
      display.clearDisplay();
       display.drawBitmap(0  ,0,SlotE1  ,128,64,WHITE);      
       display.display();
        
             display.clearDisplay();
       display.drawBitmap(0  ,0,SlotE1  ,128,64,WHITE);
        ProvSlot(22,21,       SlotNiz[1]);
        ProvSlot(54,21,       SlotNiz[2]);
        ProvSlot(86,21,       SlotNiz[3]);
        





      
       //display.drawBitmap(54  ,21,SlotP  ,22,21,WHITE);
       //display.drawBitmap(86  ,21,SlotP  ,22,21,WHITE);
       display.display();
      //BIO RESET 

 if(SlotNiz[2] > 0 && SlotNiz[1]>0 && SlotNiz[3] > 0 && SlotPropici == false)
        {
          if(SlotNiz[1] == SlotNiz[2] && SlotNiz[2] == SlotNiz[3])
          {
   
            PapirPobedaMuzika();
            //delay(300);
            SlotPropici = true;
          }
          else
          {

                    PapirPorazMuzika();
                         //  delay(300);
                         SlotPropici = true;
          }
          
        }
      

       if(SlotNiz[2] >0)
       {
        SlotNiz[4]=1;
       }
      }
  

    }

  }
    
        
  
}
else if(CekanjeBackBool == true && IgraBroj == 7)// Podmornica Game
{
  int pozicijaTerena = 48,pozicijaMoraY=10;
  display.clearDisplay();
  //display.drawBitmap(20  ,5,PodmornicaBrod ,14,6,WHITE);
  //delay(UsporiDisplay);

  if(PodmornicaTorpedo1Bl)
  {
    display.drawBitmap(PodmornicaTorpedo1X  ,PodmornicaTorpedo1Y,ProjektilP ,4,4,WHITE);
    PodmornicaTorpedo1Y--;
    beep(2500, 10);

  }
/*
  if(PodmornicaTorpedo1Bl && PodmornicaTorpedo1Y < pozicijaMoraY)
  {
    if(PodmornicaTorpedo1X<= PodmornicaBrodX+7 && PodmornicaTorpedo1X>= PodmornicaBrodX-7)
    {
      PodmornicaBrodZiva = false;
          beep(2500, 10);
              beep(3680, 10);
                  beep(5808, 10);
                      beep(7842, 10);
    }


    PodmornicaTorpedo1Bl= false;
  }
*/

  if(GameOver == true)
  {
    display.clearDisplay();
    GameOverVoid(UnisteniBrodovi);

    display.display();
        
  }
  else
  {
  for(int x =0; x<3;x++)
  {
    if(Bombe[x][1] >= 50)
    {
      if(Bombe[x][0] <= PozicijaPodmornice+5 && Bombe[x][0] >= PozicijaPodmornice-5)
      {
          //CekanjeBackBool=false;

        GameOver = true;

      } 

      Bombe[x][1]=-10;
      Bombe[x][0] = 0;
    }
  }


 /*
    PodmorniceX[s]--;
    if(PodmorniceX[s]< 0)
    {
      PodmorniceX[s]=128;
    }
    display.drawBitmap(PodmorniceX[s]  ,5,PodmornicaBrod ,14,6,WHITE);


    Bombe[0][0] = 5;
    Bombe[0][1]+=1;
    display.drawBitmap(Bombe[0][0]  ,Bombe[0][1],ProjektilE ,4,4,WHITE);

*/
  for(int s=0; s < 3; s++)
  {
   
    int rand = random(0,101);
    if(rand > 80)
    {
      if(Bombe[s][0]==0)
      {
        Bombe[s][0] = PodmorniceX[s];
      }
    }
    
    

   
    Bombe[s][1]+=1;
    //Bombe[s][0] -= 1;
    
    display.drawBitmap(Bombe[s][0]  ,Bombe[s][1],ProjektilE ,4,4,WHITE);
    
    
    if(PodmornicaTorpedo1Bl && PodmornicaTorpedo1Y < pozicijaMoraY)
    {
      if(PodmornicaTorpedo1X<= PodmorniceX[s]+7 && PodmornicaTorpedo1X>= PodmorniceX[s]-7)
      {
        //PodmornicaBrodZiva = false;
        PodmorniceX[s] = 128;
        UnisteniBrodovi++;
            beep(2500, 10);
                beep(3680, 10);
                    beep(5808, 10);
                        beep(7842, 10);
      }
    }

    if(PodmornicaTorpedo1Bl && PodmornicaTorpedo1Y < pozicijaMoraY)
    {
      PodmornicaTorpedo1Bl= false;
    }
  }






/*
  for (byte i = 0; i < sizeof(PodmornicaTorpedo); i++) {
    //Serial.println(PodmornicaTorpedo[0][i]);
    PodmornicaTorpedo[i]++;
  }*/

  if(PodmornicaLD == 0)
  {
  display.drawBitmap(PozicijaPodmornice  ,48,PodmornicaD ,11,6,WHITE);
  }
  else
  {
  display.drawBitmap(PozicijaPodmornice  ,48,PodmornicaL ,11,6,WHITE);
  }

  for(int s=0; s < 3; s++)
  {
    PodmorniceX[s]--;
    if(PodmorniceX[s]< 0)
    {
      PodmorniceX[s]=128;
    }
    display.drawBitmap(PodmorniceX[s]  ,5,PodmornicaBrod ,14,6,WHITE);
  }

/*
 for (int i=0; i < 1; i++) {
    int s = PodmorniceX[0];
    s--;
    if(s< 0)
    {
      s=128;
    }
    PodmorniceX[0] = s;
    display.drawBitmap(PodmorniceX[0]  ,5,PodmornicaBrod ,14,6,WHITE);
*/
  
 



/*
  if(PodmornicaBrodZiva)
  {
    PodmornicaBrodX--;
    if(PodmornicaBrodX< 0)
    {
      PodmornicaBrodX=128;
    }
    display.drawBitmap(PodmornicaBrodX  ,5,PodmornicaBrod ,14,6,WHITE);
  }
*/

  for(int i=0;i<128;i++)
  {
     display.drawPixel(i, pozicijaMoraY, SSD1306_WHITE);
  }
 

  display.drawBitmap(0  ,pozicijaTerena,PodmornicaTeren ,16,16,WHITE);
  for(int i=1;i < 9;i++)
  {
    display.drawBitmap(i*16  ,pozicijaTerena,PodmornicaTeren ,16,16,WHITE);
  }
 

  display.display();
}


  }






  buttonState = digitalRead(2);
  buttonState2 = digitalRead(6);
  buttonState3 = digitalRead(10); 
}

void Reset_Slot()
{
  if(SlotNiz[2] > 0 && SlotNiz[1]>0 && SlotNiz[3] > 0)
        {
          if(SlotNiz[1] == SlotNiz[2] && SlotNiz[2] == SlotNiz[3])
          {
            slotBl = false;
            SlotNiz[0]=0;
            SlotNiz[1]=0;
            SlotNiz[2]=0;
            SlotNiz[3]=0;
            SlotNiz[4]=0;
            SlotBl_PocelaIgra = false;
            //PapirPobedaMuzika();
            //delay(300);
          }
          else
          {
             slotBl = false;
            SlotNiz[0]=0;
            SlotNiz[1]=0;
            SlotNiz[2]=0;
            SlotNiz[3]=0;
            SlotNiz[4]=0;
            SlotBl_PocelaIgra = false;
                    //PapirPorazMuzika();
                         //  delay(300);
          }
          
        }
        SlotPropici = false;
}

void ProvSlot(int X,int Y,int por)
{
  if(por == 1)
  {
     display.drawBitmap(X  ,Y,SlotElement1  ,22,21,WHITE);
  }
  else if(por == 2)
  {
     display.drawBitmap(X  ,Y,SlotElement2  ,22,21,WHITE);
  }
   else if(por == 3)
  {
     display.drawBitmap(X  ,Y,SlotElement3  ,22,21,WHITE);
  }
  else 
  {
    display.drawBitmap(X  ,Y,SlotP  ,22,21,WHITE);
  }
}





void ProveraTop()
{
  if(GoreDole==0)
  {
      display.drawBitmap(TopX  ,30,Top1  ,24,32,WHITE);
  }
  else if(GoreDole == 1)
  {
      display.drawBitmap(TopX  ,30,Top2  ,24,32,WHITE);
  }
  else if(GoreDole == 2)
  {
      display.drawBitmap(TopX  ,30,Top3  ,24,32,WHITE);
  }
  else if(GoreDole==3)
  {
      display.drawBitmap(TopX  ,30,Top4  ,24,32,WHITE);
  }
  

}










void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}


void SlotAnimInicijalni(int PozBack1)
{
  
  if(PozBack1==1)
  {
       //  display.clearDisplay();
     display.drawBitmap(0  ,0,SlotE1 ,128,64,WHITE);
//display.drawBitmap(0  ,0,ClownEscapeLogo ,128,64,WHITE);
     //display.display();
  }
    else if(PozBack1==2)
  {
       //  display.clearDisplay();
     display.drawBitmap(0  ,0,SlotE2 ,128,64,WHITE);
        //  display.drawBitmap(0  ,0,ClownEscapeLogo ,128,64,WHITE);
     //display.display();
  }
    else if(PozBack1==3)
  {
        // display.clearDisplay();
     display.drawBitmap(0  ,0,SlotE3 ,128,64,WHITE);
          //display.drawBitmap(0  ,0,ClownEscapeLogo ,128,64,WHITE);
     //display.display();
  }
    else if(PozBack1==4)
  {
       //  display.clearDisplay();
     display.drawBitmap(0  ,0,SlotE4 ,128,64,WHITE);
       //   display.drawBitmap(0  ,0,ClownEscapeLogo ,128,64,WHITE);
     //display.display();
     slotBl =false;
     SlotBl_PocelaIgra = true;
  }

}
void PapirPobedaMuzika()
{
       beep(fSH, 300);
     beep(aH, 250);
     beep(fSH, 300);

}
void PapirPorazMuzika()
{
     beep(cSH, 300);
     beep(b, 250);
     beep(cSH, 300);
}
void PapirNistaMuzika()
{
       beep(dH, 300);
     beep(dSH, 250);
     beep(eH, 300);
        beep(dH, 250);
}
void PapirKoPobedi(int Neprijatelj)
{

   if(Papir_Player == 1 && Neprijatelj == 3)
   {
       Papir_PlayerScore++;
          //PapirPobedaMuzika();
          PapirKO++;
   }
   else if(Papir_Player == 2 && Neprijatelj == 1)
   {
       Papir_PlayerScore++;
        //PapirPobedaMuzika();
        PapirKO++;
   }
   else if(Papir_Player == 3 && Neprijatelj == 2)
   {
       Papir_PlayerScore++;
       //PapirPobedaMuzika();
       PapirKO++;
   }
   else if(Papir_Player == Neprijatelj)
   {
      //PapirNistaMuzika();
      PapirKO=3;
   }


   else
   {
    Papir_PCScore++;
           //PapirPorazMuzika();
           PapirKO=2;
   }


   
}
void UpdatePaperPozVoid()
{
 

  
  if(UpdatePaperPoz==1)
  {
        display.drawBitmap(0  ,0,KartaAkcija1 ,128,64,WHITE);
  }
  else if(UpdatePaperPoz==2)
  {
        display.drawBitmap(0  ,0,KartaAkcija2 ,128,64,WHITE);
  }
  else if(UpdatePaperPoz==3)
  {
    
    display.drawBitmap(0  ,0,KartaAkcija3 ,128,64,WHITE);

  }


  

}
void UpdatePaperPozVoid_PozKarte()
{
          if(UpdatePaperPoz == 1)
          {
              display.drawBitmap(29  ,12,Karta1 ,22,26,WHITE);
              
          }
          else   if(UpdatePaperPoz == 2)
          {
            display.drawBitmap(29  ,12,Karta2 ,22,26,WHITE);
            
          }
         else   if(UpdatePaperPoz == 3)
          {
            display.drawBitmap(29  ,12,Karta3 ,22,26,WHITE);
           
          }
}
void UpdatePaperPozVoid_Neprijatelj(int broj)
{
 
          if(broj == 1)
          {
              display.drawBitmap(77  ,11,Karta1 ,22,26,WHITE);   
          }
          else   if(broj == 2)
          {
            display.drawBitmap(77  ,11,Karta2 ,22,26,WHITE);
          }
         else   if(broj == 3)
          {
            display.drawBitmap(77  ,11,Karta3 ,22,26,WHITE);         
          }     
}












void ResetYugoGame()
{
  GameOver =false;
  YugoScore=0;
  YugoRupaPoz= 130;
  YugoPozY=20;
}
void UpdateBackground()
{

  if(PozBack==1)
  {
       //  display.clearDisplay();
     display.drawBitmap(0  ,0,BackAr1 ,128,64,WHITE);
//display.drawBitmap(0  ,0,ClownEscapeLogo ,128,64,WHITE);
     //display.display();
  }
    else if(PozBack==2)
  {
       //  display.clearDisplay();
     display.drawBitmap(0  ,0,BackAr2 ,128,64,WHITE);
        //  display.drawBitmap(0  ,0,ClownEscapeLogo ,128,64,WHITE);
     //display.display();
  }
    else if(PozBack==3)
  {
        // display.clearDisplay();
     display.drawBitmap(0  ,0,BackAr3 ,128,64,WHITE);
          //display.drawBitmap(0  ,0,ClownEscapeLogo ,128,64,WHITE);
     //display.display();
  }
    else if(PozBack==4)
  {
       //  display.clearDisplay();
     display.drawBitmap(0  ,0,BackAr4 ,128,64,WHITE);
       //   display.drawBitmap(0  ,0,ClownEscapeLogo ,128,64,WHITE);
     //display.display();
  }
    else if(PozBack==5)
  {
         //display.clearDisplay();
     display.drawBitmap(0  ,0,BackAr5 ,128,64,WHITE);
         // display.drawBitmap(0  ,0,ClownEscapeLogo ,128,64,WHITE);
     //display.display();
  }
    else if(PozBack==6)
  {
         //display.clearDisplay();
     display.drawBitmap(0  ,0,BackAr6 ,128,64,WHITE);
        //  display.drawBitmap(0  ,0,ClownEscapeLogo ,128,64,WHITE);
     //display.display();
  }
     else if(PozBack==7)
  {
         //display.clearDisplay();
     display.drawBitmap(0 ,0,BackAr7 ,128,64,WHITE);
         // display.drawBitmap(0  ,0,ClownEscapeLogo ,128,64,WHITE);
     //display.display();
  }

}

void UpdateSlotLogo_GameCartrige(int PozEkranX,int PozEkranY,int X,int Y, int Poz)
{

  if(Poz==1)
  {
     display.drawBitmap(PozEkranX  ,PozEkranY,SlotLogo1 ,X,Y,WHITE);
  
  }
    else if(Poz==2)
  { 
     display.drawBitmap(PozEkranX  ,PozEkranY,SlotLogo2 ,X,Y,WHITE);

  }
    else if(Poz==3)
  {
     display.drawBitmap(PozEkranX  ,PozEkranY,SlotLogo3 ,X,Y,WHITE);

  }
    else if(Poz==4)
  {
     display.drawBitmap(PozEkranX  ,PozEkranY,SlotLogo4 ,X,Y,WHITE);

  }
    else if(Poz==5)
  {
     display.drawBitmap(PozEkranX  ,PozEkranY,SlotLogo5 ,X,Y,WHITE);

  }

}


void UpdateSlotLogo_PodmornicaLogo(int PozEkranX,int PozEkranY,int X,int Y, int Poz)
{

  if(Poz==1)
  {
     display.drawBitmap(PozEkranX  ,PozEkranY,PodmornicaLOGO ,X,Y,WHITE);
  
  }
    else if(Poz==2)
  { 
     display.drawBitmap(PozEkranX  ,PozEkranY,PodmornicaLOGO ,X,Y,WHITE);

  }
    else if(Poz==3)
  {
     display.drawBitmap(PozEkranX  ,PozEkranY,PodmornicaLOGO ,X,Y,WHITE);

  }
    else if(Poz==4)
  {
     display.drawBitmap(PozEkranX  ,PozEkranY,PodmornicaLOGO ,X,Y,WHITE);

  }
    else if(Poz==5)
  {
     display.drawBitmap(PozEkranX  ,PozEkranY,PodmornicaLOGO ,X,Y,WHITE);

  }

}

void UpdateYugoLogo_GameCartrige(int PozEkranY,int X,int Y, int Poz)
{

  if(Poz==1)
  {
     display.drawBitmap(0  ,PozEkranY,YugoRunLogo1 ,X,Y,WHITE);
  
  }
    else if(Poz==2)
  { 
     display.drawBitmap(0  ,PozEkranY,YugoRunLogo2 ,X,Y,WHITE);

  }
    else if(Poz==3)
  {
     display.drawBitmap(0  ,PozEkranY,YugoRunLogo3 ,X,Y,WHITE);

  }
    else if(Poz==4)
  {
     display.drawBitmap(0  ,PozEkranY,YugoRunLogo4 ,X,Y,WHITE);

  }
    else if(Poz==5)
  {
     display.drawBitmap(0  ,PozEkranY,YugoRunLogo5 ,X,Y,WHITE);

  }
    else if(Poz==6)
  {
     display.drawBitmap(0  ,PozEkranY,YugoRunLogo6 ,X,Y,WHITE);

  }
     else if(Poz==7)
  { 
     display.drawBitmap(0 ,PozEkranY,YugoRunLogo7 ,128,64,WHITE);

  }
     else if(Poz==8)
  {  
     display.drawBitmap(0 ,PozEkranY,YugoRunLogo8 ,X,Y,WHITE);

  }
     else if(Poz==9)
  {  
     display.drawBitmap(0 ,PozEkranY,YugoRunLogo9 ,X,Y,WHITE);

  }
}
void UpdatePapirLogo_GameCartrige(int PozEkranY,int X,int Y,int Poz)
{

  if(Poz==1)
  {
     display.drawBitmap(0  ,PozEkranY,CardsLogo1 ,X,Y,WHITE);
  
  }
    else if(Poz==2)
  { 
     display.drawBitmap(0  ,PozEkranY,CardsLogo2 ,X,Y,WHITE);

  }
    else if(Poz==3)
  {
     display.drawBitmap(0  ,PozEkranY,CardsLogo3 ,X,Y,WHITE);

  }
    else if(Poz==4)
  {
     display.drawBitmap(0  ,PozEkranY,CardsLogo4 ,X,Y,WHITE);

  }
    else if(Poz==5)
  {
     display.drawBitmap(0  ,PozEkranY,CardsLogo5 ,X,Y,WHITE);

  }
    else if(Poz==6)
  {
     display.drawBitmap(0  ,PozEkranY,CardsLogo6 ,X,Y,WHITE);

  }
     else if(Poz==7)
  { 
     display.drawBitmap(0 ,PozEkranY,CardsLogo7 ,128,64,WHITE);

  }
     else if(Poz==8)
  {  
     display.drawBitmap(0 ,PozEkranY,CardsLogo8 ,X,Y,WHITE);

  }
     else if(Poz==9)
  {  
     display.drawBitmap(0 ,PozEkranY,CardsLogo9 ,X,Y,WHITE);

  }
}
int UpdateDugme_C_Int;
void UpdateDugme_C(int PozEkranX,int PozEkranY,int X,int Y)
{
  UpdateDugme_C_Int++;
  if(UpdateDugme_C_Int==1)
  {
     display.drawBitmap(PozEkranX  ,PozEkranY,DugmeFrame_C1 ,X,Y,WHITE);
  
  }
    else if(UpdateDugme_C_Int==2)
  { 
     display.drawBitmap(PozEkranX  ,PozEkranY,DugmeFrame_C2 ,X,Y,WHITE);

  }
    else if(UpdateDugme_C_Int==3)
  {
     display.drawBitmap(PozEkranX  ,PozEkranY,DugmeFrame_C3 ,X,Y,WHITE);

  }
  else
  {
    UpdateDugme_C_Int=0;
    display.drawBitmap(PozEkranX  ,PozEkranY,DugmeFrame_C1 ,X,Y,WHITE);
  }

}



void GameOverVoid(int Score)
{
  
          display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(10, 10);
        display.println("GAME OVER");


        String ScoreString = "SCORE: "+String(Score);
        char ScoreStringArrayCPU[50]; 
        ScoreString.toCharArray(ScoreStringArrayCPU,50);

        display.setTextSize(1);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(34, 40);
        display.println(ScoreStringArrayCPU);
        
}

void DimFunkcija(int X,int Y)
{
  
  if(DimInt==0)
  {
     display.drawBitmap(X  ,Y,Dim1  ,16,16,WHITE);
  }
    else if(DimInt==1)
  {
     display.drawBitmap(X  ,Y,Dim2 ,16,16,WHITE);
  }
   else if(DimInt==2)
  {
     display.drawBitmap(X  ,Y,Dim3 ,16,16,WHITE);
  }
  else
  {
    DimInt=0;
    display.drawBitmap(X  ,Y,Dim1  ,16,16,WHITE);
  }
  DimInt++;
}

void Update_Autoput(int X,int Y,int Ypoz)
{
  if(AutoputInt==0)
  {
     display.drawBitmap(0  ,Ypoz,Autoput1  ,X,Y,WHITE);
  }
    else if(AutoputInt==1)
  {
     display.drawBitmap(0  ,Ypoz,Autoput2 ,X,Y,WHITE);
  }
   else if(AutoputInt==2)
  {
     display.drawBitmap(0  ,Ypoz,Autoput3 ,X,Y,WHITE);
  }
   else if(AutoputInt==3)
  {
     display.drawBitmap(0  ,Ypoz,Autoput4 ,X,Y,WHITE);
     AutoputInt=0;
  }
}
boolean debounceButton(boolean state,int Pin)
{
  boolean stateNow = digitalRead(Pin);
  if(state!=stateNow)
  {
    delay(10);
    stateNow = digitalRead(Pin);
  }
  return stateNow;
  
}
/*
void ISR_button_pressed() {
    display.drawBitmap(XpozSlot  ,22,SlotFull ,128,32,WHITE);
    display.display();
}*/
