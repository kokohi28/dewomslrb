#include "loop.h"
#include "motor.h"
#define ga_la -150
#define ga_ku 50
#define tom_1 (digitalRead(52))
#define tom_2 (digitalRead(50))
#define tom_3 (digitalRead(48))
#define tom_4 (digitalRead(46))
#define tom_5 (digitalRead(44))
#define tom_6 (digitalRead(42))
#define tom_7 (digitalRead(40))
#define sen_inf (digitalRead(A4))//striker
//#define sen_inf (digitalRead(A8))
//#define sen_infka (digitalRead(38))
//#define sen_infki (digitalRead(36))
#define hand_on (digitalWrite(A0,HIGH))   
#define kick_on (digitalWrite(A2,HIGH))
#define hand_of (digitalWrite(A0,LOW))
#define kick_of (digitalWrite(A2,LOW)) 
#include <LiquidCrystal.h>
#include <Servo.h>
Servo ndas;
LiquidCrystal lcd(37,35,33,31,29,27);
int cam_x,cam_y,cam_rad,pol,nds=90,lit,kam_x,kam_y,wifi,us1,us2,m_side;
String posx, posy, wif1, sid1;
String datachain = "";
int data_x,data_y,data_1,data_2,dam_x,dam_y,dam_1,dam_2;
//ndas bawah 30 atas 60;
void setup() {
    lcd.begin(16,2);ndas.attach(8);
    mot.inisial(); 
    ndas.write(90);
    hand_of;
   }
void set_kompas(){
    while(1){ 
      lit++;if(lit>100){lcd.clear();lit=0;}
      lcd.setCursor(0,0);
      lcd.print("Calib");
      lcd.setCursor(0,1);
      lcd.print(mot.kempas());
      lcd.setCursor(7,0);
      lcd.print("Asli");
      lcd.setCursor(7,1);
      lcd.print(mot.kempas_asli());
    }
  }
//==========================================================================
void nilai_us(){
    while(1){ 
      lit++;if(lit>100){lcd.clear();lit=0;}
      lcd.setCursor(0,0);
      lcd.print("US1");
      lcd.setCursor(0,1);
      lcd.print(mot.us1());
      lcd.setCursor(7,0);
      lcd.print("US2");
      lcd.setCursor(7,1);
      lcd.print(mot.us2());
      }
  }

//==========================================================================  
void slow_ndas(int g){
    int u ;u = nds;int y = map(g,0,240,6,-6);
     if(y==1){u = u +1 ;}if(y==2){u = u +2 ;}if(y==3){u = u +3 ;}if(y==4){u = u +4 ;}
    if(y==5){u = u +5 ;}if(y==6){u = u +6 ;}if(y==-1){u = u -1 ;}if(y==-2){u = u -2 ;}
    if(y==-3){u = u -3 ;}if(y==-4){u = u -4 ;}if(y==-5){u = u -5 ;}if(y==-6){u = u -6 ;}
    nds = u;if(nds>90){nds=90;}if(nds<67){nds=67;}ndas.write(nds);
  }
  
//==========================================================================
void selek(){
    int h,j,k,pol;
    while(Serial3.read()==13){}
    h=Serial3.parseInt();Serial.print("H=");Serial.print(h);Serial.print(";"); 
    j=Serial3.parseInt();Serial.print("J=");Serial.print(j);Serial.print(";");
    k=Serial3.parseInt();Serial.print("K=");Serial.println(k);
    if(h<500){cam_x=h;}
    if(h>500&&h<800){cam_y=h-500;}
    if(h>800){pol=h-800;}
    if(j<500){cam_x=j;}
    if(j>500&&j<800){cam_y=j-500;}
    if(j>800){pol=j-800;}
    if(k<500){cam_x=k;}
    if(k>500&&k<800){cam_y=k-500;}
    if(k>800){pol=k-800;}
    if(pol==115){wifi=1;}//start
    if(pol==83){wifi=2;}//stop
    if(h==0||j==0||k==0){cam_x=0;cam_y=0;}
}
//==========================================================================
void cek_data(){
        selek();
        lcd.setCursor(0,0);lcd.print(cam_x);Serial.print("X = ");Serial.print(cam_x);Serial.print("||");
        lcd.setCursor(0,1);lcd.print(cam_y);Serial.print("Y = ");Serial.println(cam_y);        
    }
//==========================================================================
void mandek_jeglek(){
   while(1){  
    selek();
    mot.omni(0,0,0);
    if(wifi==1){break;}  
  }
 }
//==========================================================================
void putar_gawang_lawan(){
   int f=0,p=0;
   hand_on;
   while(1){ 
      f = mot.kempas();
      if(f>180 && f<340){mot.omni(0,0,-50);};//puter bodi kanan{mot.omni(0,0,-50);//kanan
      if(f>=340 && f<355){mot.omni(0,0,-30);}
      if(f>=30 && f<=180){mot.omni(0,0,50);}//puter bodi kiri{mot.omni(0,0,50);}kiri
      if(f<=30  && f>=6){mot.omni(0,0,30);}
      if(f==0||f>=355||f<=5){break;}
   }
    mot.omni(0,0,0);
 } 

 void putar_gawang_lawan1(){
  int f=0,p=0;
  hand_on;
  while(1) {
    f = mot.kempas_asli();
    if(f>180 && f<340){mot.omni(0,0,-50);} // kanan
    if(f>=340 && f<355){mot.omni(0,0,-30);}
    if(f>=30 && f<=180){mot.omni(0,0,50);} //kiri
    if(f<=30 && f>=6){mot.omni(0,0,-30);}
    if(f==0|| f>=355||f<5) {break;}
  }
  mot.omni(0,0,0);
}
//==========================================================================  
void kick_off(){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Bismillah");
      lcd.setCursor(0,1);
      lcd.print("Kick Off");
    
      int x,y,rad,b,hit=0;hand_of;
      static int a;
      //  while(1){selek();slow_ndas(cam_y);if(wifi==1){break;}}//wifi button
      mot.omni(0,0,0);
     while(1){
      while(1){
            mot.omni(200,0,0);
            jarak(2);
            selek();
            //if(wifi==2){mandek_jeglek();}
            a = cam_x;
            if(a!=0){b=a;}
            x = map(cam_x,1,320,16,-16);x = x*5;
            if(cam_x!=0){mot.omni(180,0,x);}
            if(cam_x==0){
              if(b<=160){mot.omni(0,0,60);}//putar kiri
              if(b>160){mot.omni(0,0,-60);}}//putar kanan  
            slow_ndas(cam_y); 
            if(nds<80){break;}
      } 
      while(1)
        {
            selek();//if(wifi==2){mandek_jeglek();}
            a = cam_x;
            if(a!=0){b=a;}
            x = map(cam_x,1,320,16,-16);x = x*5;
            if(cam_x!=0){mot.omni(180,0,x);slow_ndas(cam_y);}
            if(cam_x==0){
              if(b<=160){mot.omni(0,0,50);}//putar kiri
              if(b>160){mot.omni(0,0,-50);}}//putar kanan  
            if(nds<80){hand_on;}else{hand_of;}
            lcd.clear();
            lcd.setCursor(0,1);lcd.print(cam_y);lcd.setCursor(0,0);lcd.print(cam_x);
            if(sen_inf==LOW){delay(400);
      mot.omni(0,0,-100);delay(1000);
      mot.omni(-100,0,0);delay(1200);
      mot.omni(0,0,-100);delay(1000);
      break;}
        }
      putar_gawang_lawan();
      hand_of;delay(1000);kick_on;delay(100);kick_of;
   }
  }

void tengah_kanan(){
      lcd.clear(); 
      lcd.setCursor(0,0);
      lcd.print("Bismillah");
      lcd.setCursor(0,1);
      lcd.print("Tengah Kanan");
    
      mot.omni(0,0,0);
      int x,y,rad,b,hit=0;hand_of;
      //mot.omni(180,0,0);
      delay(2000);
      lcd.clear();
      static int a;
      //  while(1){selek();slow_ndas(cam_y);if(wifi==1){break;}}//wifi button
     while(1){
       while(1){
           selek();
            //if(wifi==2){mandek_jeglek();}
            a = cam_x;
            if(a!=0){b=a;}
            x = map(cam_x,1,320,16,-16);x = x*5;
            if(cam_x!=0){mot.omni(180,0,x);}
            if(cam_x==0){
              if(b<=160){mot.omni(0,0,50);}//putar kiri
              if(b>160){mot.omni(0,0,-50);}}//putar kanan  
            slow_ndas(cam_y);
            lcd.setCursor(0,0);lcd.print(cam_x);
            lcd.setCursor(0,1);lcd.print(cam_y); 
            if(nds<80){break;}
    } 
      while(1)
        {
            selek();
            //if(wifi==2){mandek_jeglek();}
            a = cam_x;
            if(a!=0){b=a;}
            x = map(cam_x,1,320,16,-16);x = x*5;
            if(cam_x!=0){mot.omni(160,0,x);slow_ndas(cam_y);}
            if(cam_x==0){
              if(b<=160){mot.omni(0,0,50);}//putar kiri
              if(b>160){mot.omni(0,0,-50);}}//putar kanan  
            if(nds<80){hand_on;}else{hand_of;}
            lcd.setCursor(0,0);lcd.print(cam_x);
            lcd.setCursor(0,1);lcd.print(cam_y); 
            lcd.clear();
            lcd.setCursor(0,1);lcd.print(cam_y);lcd.setCursor(0,0);lcd.print(cam_x);
            Serial.println(sen_inf);
            if(sen_inf==LOW){delay(400);break;}
        }
      mot.omni(0,0,-100);delay(900);
      mot.omni(-100,0,0);delay(1400);
      mot.omni(0,0,-100);delay(600);
        putar_gawang_lawan1();
        hand_of;delay(1000);kick_on;delay(100);kick_of;
    }
  } 

void bola_dekat(){
      int x,y,rad,b,hit=0;hand_of;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Bismillah");
      lcd.setCursor(0,1);
      lcd.print("Bola Dekat");
      //mot.omni(180,0,0);
      //delay(3000);
      static int a;
      //while(1){selek();slow_ndas(cam_y);if(wifi==1){break;}}//wifi button
      while(1){ 
         while(1){
            selek();
            //if(wifi==2){mandek_jeglek();}
            a = cam_x;
            if(a!=0){b=a;}
            x = map(cam_x,1,320,16,-16);x = x*5;
            if(cam_x!=0){mot.omni(180,0,x);}
            if(cam_x==0){
              if(b<=160){
                 mot.omni(0,0,70);    //putar kiri
               }
              if(b>160){
                 mot.omni(0,0,-70);   //putar kanan  
               }
             }
            slow_ndas(cam_y); 
            if(nds<0){break;}
        }
      while(1){
            selek();//if(wifi==2){mandek_jeglek();}
            a = cam_x;
            if(a!=0){b=a;}
            x = map(cam_x,1,320,16,-16);x = x*5;
            if(cam_x!=0){mot.omni(80,0,x);slow_ndas(cam_y);}
            if(cam_x==0){
              if(b<=160){mot.omni(0,0,70);}//putar kiri
              if(b>160){mot.omni(0,0,-70);}}//putar kanan  
            if(nds<80){hand_on;}else{hand_of;}
            lcd.clear();
            lcd.setCursor(0,1);lcd.print(cam_y);lcd.setCursor(0,0);lcd.print(cam_x);
            if(sen_inf==LOW){delay(400);break;}
        }
      mot.omni(80,0,0);delay(1000);
      putar_gawang_lawan();
      hand_of;delay(1000);kick_on;delay(1000);kick_of;
    }
  }
void jauh_kanan(){
      lcd.clear(); 
      lcd.setCursor(0,0);
      lcd.print("Bismillah");
      lcd.setCursor(0,1);
      lcd.print("Jauh Kanan");
      
      int x,y,rad,b,hit=0;hand_of;
      static int a;
      //mot.omni(0,0,-80);//Putar_Kiri
      //  while(1){selek();slow_ndas(cam_y);if(wifi==1){break;}}//wifi button
    while(1){
      while(1){ 
            selek();
            //if(wifi==2){mandek_jeglek();}
            a = cam_x;
            if(a!=0){b=a;}
            x = map(cam_x,1,320,16,-16);x = x*5;
            if(cam_x!=0){mot.omni(200,0,x);}
            if(cam_x==0){
              if(b<=160){mot.omni(0,0,80);}//putar kiri
              if(b>160){mot.omni(0,0,-80);}}//putar kanan  
            slow_ndas(cam_y); 
            if(nds<0){break;}
    }
      while(1)
        {
            selek();//if(wifi==2){mandek_jeglek();}
            a = cam_x;
            if(a!=0){b=a;}
            x = map(cam_x,1,320,16,-16);x = x*5;
            if(cam_x!=0){mot.omni(80,0,x);slow_ndas(cam_y);}
            if(cam_x==0){
              if(b<=160){mot.omni(0,0,70);}//putar kiri
              if(b>160){mot.omni(0,0,-70);}}//putar kanan  
            if(nds<80){hand_on;}else{hand_of;}
            lcd.clear();
            lcd.setCursor(0,1);lcd.print(cam_y);lcd.setCursor(0,0);lcd.print(cam_x);
            if(sen_inf==LOW){delay(400);break;}
        }
      putar_gawang_lawan1();
      hand_of;delay(1000);kick_on;delay(1000);kick_of;
   }
  }
  
void test_track(){
    lcd.clear();lcd.setCursor(0,0);lcd.print("Mode Dekat");lcd.clear();
    int k2=0,ti_kom,x,y,f,rad,hit=0,k=0,lop=0,hit2=0,ab=0,hit3=0,back;hand_of;
     
while(1){
    ndas.write(100);hit=0;hit2=0;
    ret:
        while(1){
          selek();
          //if(wifi==2){mandek_jeglek();}
          x = map(cam_x,1,320,16,-16);x = x*6,5;
          if(cam_x!=0){mot.omni(80,0,x);slow_ndas(cam_y);}
          if(cam_x==0){mot.omni(0,0,-60);slow_ndas(cam_y);}
          lcd.setCursor(0,0);lcd.print(cam_x);
          lcd.setCursor(0,1);lcd.print(nds); 
          if(nds<80){break;}
        }
            while(nds<80){
              selek();
              //if(wifi==2){mandek_jeglek();}
              x = map(cam_x,1,320,16,-16);x = x*5;
              if(cam_x!=0){mot.omni(70,0,x);slow_ndas(cam_y);}
              if(cam_x==0){mot.omni(0,0,50);slow_ndas(cam_y);}
              lcd.setCursor(0,0);lcd.print(cam_x);
              lcd.setCursor(0,1);lcd.print(nds);
              if(nds<80){hand_on;}else{hand_of;}
              if(nds>80){goto ret;}
              if(sen_inf==0){delay(400);break;} 
            }
          putar_gawang_lawan();
          hand_on;mot.omni(0,0,0);kick_on;delay(500);hand_of;delay(10);kick_of;
          goto ret;
          }
        }
 
void lurus_arah(){
    int f,g;
    f = mot.kempas();
    if(f<270){
       while(1){ 
        mot.omni(0,0,-50); 
        g = mot.kempas();
        if(g>270){break;}
      }} 
    if(f>270){
       while(1){ 
        mot.omni(0,0,50);
        g = mot.kempas();
        if(g<270){break;}
      }}
  }

void scan_bola(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bismillah Tatag");
    mot.omni(0,0,0);hand_of;
    int k2=0,ti_kom,x,y,f,rad,hit,k=0,lop=0,hit1,hit2,hit3,back;
//while(1){selek();slow_ndas(cam_y);if(wifi==1){break;}}
while(1){
    ndas.write(100);hit=0,hit1=0,hit2=0,hit3=0;
   mot.omni(80,0,0);delay(4000);
   mot.omni(0,-60,0);delay(3000);
      awal:
        hit=0;hit1=0; 
        while(1){  
          selek();
          //if(wifi==2){mandek_jeglek();}
          x = map(cam_x,1,320,16,-16);x = x*6,5;
            if(cam_x!=0){mot.omni(0,x,0);slow_ndas(cam_y);hit++;}
            if(cam_x==0){mot.omni(0,0,0);slow_ndas(cam_y);hit1++;}
            if(hit1>100 && cam_x==0){
              while(1){
                selek();
                //if(wifi==2){mandek_jeglek();}
                x = map(cam_x,1,320,16,-16);x = x*6,5;
                mot.omni(0,0,50);
                  if(cam_x!=0){
                      mot.omni(80,0,x);slow_ndas(cam_y);
                      if(nds<80){hand_on;}else{hand_of;}
                      if(sen_inf==LOW){delay(1000);goto sepak;goto awal;}}}}
        hand_of;
          lcd.clear();
          lcd.setCursor(0,0);lcd.print(cam_x);lcd.setCursor(8,0);lcd.print(hit);
          lcd.setCursor(0,1);lcd.print(nds);lcd.setCursor(8,1);lcd.print(hit1); 
            if(sen_inf==LOW){delay(1000);goto sepak;}
            if(nds<80){break;}
        }  
        while(nds<80){
          hit2=0,hit3=0;
             while(1){
              selek();//hit=0;hit1=0;
                //if(wifi==2){mandek_jeglek();}
                x = map(cam_x,1,320,16,-16);x = x*6,5;
                if(cam_x!=0){mot.omni(0,x,0);slow_ndas(cam_y);hit2++;}
                if(cam_x==0){mot.omni(0,0,0);slow_ndas(cam_y);hit3++;}
                if(hit2>=50 && cam_x!=0){mot.omni(100,0,x);}//gimana
                if(hit3>=50 && cam_x==0){
              while(1){
                selek();
                //if(wifi==2){mandek_jeglek();}
                x = map(cam_x,1,320,16,-16);x = x*6,5;
                mot.omni(0,0,50);
                if(cam_x!=0){
                  mot.omni(80,0,x);slow_ndas(cam_y);
                  if(nds<80){hand_on ;}else{hand_of;}
                  if(sen_inf==LOW){delay(1000);goto sepak;goto awal;}}}}
              if(nds<80){hand_on;}else{hand_of;}
              lcd.clear();
              lcd.setCursor(0,0);lcd.print(cam_x);lcd.setCursor(8,0);lcd.print(hit2);
              lcd.setCursor(0,1);lcd.print(nds);lcd.setCursor(8,1);lcd.print(hit3); 
                if(nds>80){goto awal;} 
                
                if(sen_inf==LOW){delay(1000);break;} 
            }  
        sepak:
             putar_gawang_lawan();     
             mot.omni(0,0,0);kick_on;delay(1000);hand_of;delay(10);kick_of;
        if(sen_inf==LOW){delay(1000);goto sepak;}
              mot.omni(-50,0,0);delay(2000);
        goto awal;
          }
      }
 }
void scan_bolagagal(){
    lcd.setCursor(0,0);
    lcd.print("Bismillah Tatag");
    mot.omni(0,0,0);hand_of;
    int k2=0,ti_kom,x,y,f,rad,hit,k=0,lop=0,hit1,hit2,hit3,back;
//while(1){selek();slow_ndas(cam_y);if(wifi==1){break;}}
while(1){
    ndas.write(100);hit=0,hit1=0,hit2=0,hit3=0;
   mot.omni(80,0,0);delay(4000);
   mot.omni(0,-40,0);delay(3000);
      awal:
        hit=0;hit1=0; 
        while(1){   
          selek();
          //if(wifi==2){mandek_jeglek();}
          x = map(cam_x,1,320,16,-16);x = x*6,5;
            if(cam_x!=0){mot.omni(0,x,0);slow_ndas(cam_y);hit++;}
            if(cam_x==0){mot.omni(0,0,0);slow_ndas(cam_y);hit1++;}
            if(hit1>100 && cam_x==0){
              while(1){
                selek();
                //if(wifi==2){mandek_jeglek();}
                x = map(cam_x,1,320,16,-16);x = x*6,5;
                mot.omni(0,0,50);
                  if(cam_x!=0){
                      mot.omni(80,0,x);slow_ndas(cam_y);
                      if(nds<80){hand_on;}else{hand_of;}
                      if(sen_inf==LOW){delay(1000);goto sepak;goto awal;}}}}
        hand_of;
          lcd.clear();
          lcd.setCursor(0,0);lcd.print(cam_x);lcd.setCursor(8,0);lcd.print(hit);
          lcd.setCursor(0,1);lcd.print(nds);lcd.setCursor(8,1);lcd.print(hit1); 
            if(sen_inf==LOW){delay(1000);goto sepak;}
            if(nds<80){break;}
        }  
        while(nds<80){
          hit2=0,hit3=0;
             while(1){
              selek();//hit=0;hit1=0;
                //if(wifi==2){mandek_jeglek();}
              x = map(cam_x,1,320,16,-16);x = x*7;
                if(cam_x!=0){mot.omni(0,x,0);slow_ndas(cam_y);hit2++;}
                if(cam_x==0){mot.omni(0,0,0);slow_ndas(cam_y);hit3++;}
                if(hit2>=50 && cam_x!=0){mot.omni(80,0,x);}
                if(hit3>=50 && cam_x==0){
              while(1){
                selek();
                //if(wifi==2){mandek_jeglek();}
                x = map(cam_x,1,320,16,-16);x = x*6,5;
                mot.omni(0,0,50);
                if(cam_x!=0){
                  mot.omni(80,0,x);slow_ndas(cam_y);
                  if(nds<80){hand_on ;}else{hand_of;}
                  if(sen_inf==LOW){delay(1000);goto sepak;goto awal;}}}}
              if(nds<80){hand_on;}else{hand_of;}
              lcd.clear();
              lcd.setCursor(0,0);lcd.print(cam_x);lcd.setCursor(8,0);lcd.print(hit2);
              lcd.setCursor(0,1);lcd.print(nds);lcd.setCursor(8,1);lcd.print(hit3); 
                if(nds>80){goto awal;} 
                
                if(sen_inf==LOW){delay(1000);break;} 
            }  
        sepak:
             putar_gawang_lawan();     
             mot.omni(0,0,0);kick_on;delay(1000);hand_of;delay(10);kick_of;
        if(sen_inf==LOW){delay(1000);goto sepak;}
              mot.omni(-50,0,0);delay(2000);
        goto awal;
          }
      }
 }

 void bertahan_jauh(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("bertahan jauh");
    mot.omni(0,0,0);hand_of;
    int k2=0,ti_kom,x,y,f,rad,hit,k=0,lop=0,hit1,hit2,hit3,back;
//while(1){selek();slow_ndas(cam_y);if(wifi==1){break;}}
while(1){
   jarak();
   mot.omni(200,0,0);jarak(2);
   mot.omni(0,200,0);jarak(2);
   mot.omni(-200,0,0);jarak(1);
    
    ndas.write(100);hit=0,hit1=0,hit2=0,hit3=0;
      awal:
        hit=0;hit1=0; 
        while(1){  
          selek();
          //if(wifi==2){mandek_jeglek();}
          x = map(cam_x,1,320,16,-16);x = x*6,5;
            if(cam_x!=0){mot.omni(0,x,0);slow_ndas(cam_y);hit++;}
            if(cam_x==0){mot.omni(0,0,0);slow_ndas(cam_y);hit1++;}
          hand_of;
          lcd.clear();
          lcd.setCursor(0,0);lcd.print(cam_x);lcd.setCursor(8,0);lcd.print(hit);
          lcd.setCursor(0,1);lcd.print(nds);lcd.setCursor(8,1);lcd.print(hit1); 
            if(sen_inf==LOW){delay(1000);goto sepak;}
            if(nds<80){break;}
        }  
        while(nds<80){
          hit2=0,hit3=0;
             while(1){
              selek();//hit=0;hit1=0;
               //if(wifi==2){mandek_jeglek();}
              x = map(cam_x,1,320,16,-16);x = x*7;
                if(cam_x!=0){mot.omni(0,x,0);slow_ndas(cam_y);hit2++;}
                if(cam_x==0){mot.omni(0,0,0);slow_ndas(cam_y);hit3++;}
                if(hit2>=400 && cam_x!=0){mot.omni(80,0,x);}
                if(hit3>=400 && cam_x==0){
              while(1){
                selek();
                //if(wifi==2){mandek_jeglek();}
                x = map(cam_x,1,320,16,-16);x = x*7;
                mot.omni(0,0,50);
                if(cam_x!=0){
                  mot.omni(80,0,x);slow_ndas(cam_y);
                  if(nds<80){hand_on ;}else{hand_of;}
                  if(sen_inf==LOW){delay(1000);goto sepak;goto awal;}}}}
              if(nds<80){hand_on;}else{hand_of;}
              lcd.clear();
              lcd.setCursor(0,0);lcd.print(cam_x);lcd.setCursor(8,0);lcd.print(hit2);
              lcd.setCursor(0,1);lcd.print(nds);lcd.setCursor(8,1);lcd.print(hit3); 
                if(nds>80){goto awal;}       
                if(sen_inf==LOW){delay(1000);break;} 
            }
        sepak:
             putar_gawang_lawan();     
             mot.omni(0,0,0);kick_on;delay(1000);hand_of;delay(10);kick_of;
        if(sen_inf==LOW){delay(1000);goto sepak;}
              mot.omni(-50,0,0);delay(2000);
        goto awal; 
          }
      }
 }
void bertahan_dekat(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bertahan dekat");
    mot.omni(0,0,0);hand_of;
    int k2=0,ti_kom,x,y,f,rad,hit,k=0,lop=0,hit1,hit2,hit3,back;
//while(1){selek();slow_ndas(cam_y);if(wifi==1){break;}}
while(1){
   mot.omni(80,0,0);delay(3000);
   mot.omni(0,60,0);delay(3000);
   mot.omni(-60,0,0);delay(1000);
    
    ndas.write(100);hit=0,hit1=0,hit2=0,hit3=0;
      awal:
        hit=0;hit1=0; 
        while(1){  
          selek();
          //if(wifi==2){mandek_jeglek();}
          x = map(cam_x,1,320,16,-16);x = x*6,5;
            if(cam_x!=0){mot.omni(0,x,0);slow_ndas(cam_y);hit++;}
            if(cam_x==0){mot.omni(0,0,0);slow_ndas(cam_y);hit1++;}
          hand_of;
          lcd.clear();
          lcd.setCursor(0,0);lcd.print(cam_x);lcd.setCursor(8,0);lcd.print(hit);
          lcd.setCursor(0,1);lcd.print(nds);lcd.setCursor(8,1);lcd.print(hit1); 
            if(sen_inf==LOW){delay(1000);goto sepak;}
            if(nds<80){break;}
        }  
        while(nds<80){
          hit2=0,hit3=0;
             while(1){
              selek();//hit=0;hit1=0;
               //if(wifi==2){mandek_jeglek();}
              x = map(cam_x,1,320,16,-16);x = x*7;
                if(cam_x!=0){mot.omni(0,x,0);slow_ndas(cam_y);hit2++;}
                if(cam_x==0){mot.omni(0,0,0);slow_ndas(cam_y);hit3++;}
                if(hit2>=400 && cam_x!=0){mot.omni(80,0,x);}
                if(hit3>=400 && cam_x==0){
              while(1){
                selek();
                //if(wifi==2){mandek_jeglek();}
                x = map(cam_x,1,320,16,-16);x = x*6,5;
                mot.omni(0,0,50);
                if(cam_x!=0){
                  mot.omni(80,0,x);slow_ndas(cam_y);
                  if(nds<80){hand_on ;}else{hand_of;}
                  if(sen_inf==LOW){delay(1000);goto sepak;goto awal;}}}}
              if(nds<80){hand_on;}else{hand_of;}
              lcd.clear();
              lcd.setCursor(0,0);lcd.print(cam_x);lcd.setCursor(8,0);lcd.print(hit2);
              lcd.setCursor(0,1);lcd.print(nds);lcd.setCursor(8,1);lcd.print(hit3); 
                if(nds>80){goto awal;}       
                if(sen_inf==LOW){delay(1000);break;} 
            }
        sepak:
             putar_gawang_lawan();     
             mot.omni(0,0,0);kick_on;delay(1000);hand_of;delay(100);kick_of;
        if(sen_inf==LOW){delay(1000);goto sepak;}
              mot.omni(-50,0,0);delay(2000);
        goto awal; 
          }
      }
 }

void pick_up_kiper(){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Kiper Pick Up");
      mot.omni(0,0,0);
      int x,y,rad,hit=0;hand_of;
      mot.omni(80,0,0);delay(2000);//ini maju
      mot.omni(0,0,0);delay(300);//stop
      mot.omni(0,-60,0);delay(4000);//ini kanan
      mot.omni(0,0,0);delay(300);//stop
      mot.omni(-50,0,0);delay(2000);//ini mundur 
      mot.omni(0,0,0);delay(300);//stop
      
      //scan_bola();//kembali scan bola 
  }

void manuver(){
mot.omni(80,0,0);
delay(1000);
mot.omni(0,80,-40);//puter bodi kiri
delay(2800);
mot.omni(-100,0,0);
delay(1000);    
mot.omni(0,0,-100);
delay(1200);
mot.omni(80,0,0);
delay(1000);
mot.omni(0,0,0);
delay(1000);
}

void jarak(float jrk){
  float l;
  float t = 70;
  float t1,t2;

  if(jrk<5){
    l = jrk * 950; 
    t1= t * jrk;
    delay(l-t1);
  }
  if(jrk>5){
    l = jrk * 900;
    t2 = t * 5;
    delay(l-t2);
  }
}

void loop(){
    
lit++;
if(lit>10){
   lcd.clear();
   lit=0;
  }

lcd.setCursor(0,0);
lcd.print("B.dkt-T.Kan-J.Kan");
lcd.setCursor(0,1);
lcd.print("BD-BJ-K.off-Kmps");

if(tom_1==LOW){
    mot.omni(200,0,0);
    jarak(3);
    kick_off();
  } 
if(tom_2==LOW){
   bertahan_jauh();
  } 
if(tom_3==LOW){
   bertahan_dekat();
  }
if(tom_4==LOW){
   mot.omni(180,0,0);
   delay(1000);
   tengah_kanan();
  }
if(tom_5==LOW){
   mot.omni(200,0,0);
   delay(4000);
   mot.omni(0,0,0);
   delay(500);
   jauh_kanan();
  }
if(tom_6==LOW){
   bola_dekat();
  }
if(tom_7==LOW){
   set_kompas();
  }
}
