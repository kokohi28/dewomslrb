#include "loop.h"
#include "motor.h"
#define ga_la -150
#define ga_ku 50
#define tom_1 (digitalRead(A0))
#define tom_2 (digitalRead(A2))
#define tom_3 (digitalRead(A3))
#define tom_4 (digitalRead(A4))
#define sen_inf (digitalRead(48))
#define sen_infka (digitalRead(38))
#define sen_infki (digitalRead(36))
#define hand_on (digitalWrite(52,HIGH))   
#define kick_on (digitalWrite(50,HIGH))
#define hand_of (digitalWrite(52,LOW))
#define kick_of (digitalWrite(50,LOW))
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
      //Serial.print(mot.us1());
      //Serial.print(";");
      //Serial.println(mot.us2());
      }
  }
  
void slow_ndas(int g){
    int u ;u = nds;int y = map(g,0,240,6,-6);
     if(y==1){u = u +1 ;}if(y==2){u = u +2 ;}if(y==3){u = u +3 ;}if(y==4){u = u +4 ;}
    if(y==5){u = u +5 ;}if(y==6){u = u +6 ;}if(y==-1){u = u -1 ;}if(y==-2){u = u -2 ;}
    if(y==-3){u = u -3 ;}if(y==-4){u = u -4 ;}if(y==-5){u = u -5 ;}if(y==-6){u = u -6 ;}
    nds = u;if(nds>90){nds=90;}if(nds<67){nds=67;}ndas.write(nds);
  }
void selek(){
    int h,j,k,pol;
    while(Serial3.read()==13){}
    h=Serial3.parseInt();//Serial.print("H=");Serial.print(h);Serial.print(";"); 
    j=Serial3.parseInt();//Serial.print("J=");Serial.print(j);Serial.print(";");
    k=Serial3.parseInt();//Serial.print("K=");Serial.println(k);
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
void selek5(){
    int h,j,k,pol;
    int pam_x,pam_y,dam_1,dam_2,cam_x,cam_y;
    if (Serial3.available()){
        int data_masuk = 
        Serial3.read();
        if(data_masuk == 13){
            int start_sub = 0;
            int end_sub = 0;
            int pos_sub = 0; 
            for (int i=0; i < datachain.length(); i++) {
              if (datachain.charAt(i) == 32) {
                  end_sub = i;
                  if (pos_sub == 0) {posx = datachain.substring(0,3);} 
                  if (pos_sub == 1) {posy = datachain.substring(6,9);} 
                  if (pos_sub == 2) {wif1 = datachain.substring(12,15);} 
                  if (pos_sub == 3) {sid1 = datachain.substring(18,21);} 
                  pos_sub++;
                } 
              }
//            Serial.print((String(posx)) + "===");
//            Serial.print((String(posy)) + "===");
//            Serial.print((String(wif1)) + "===");
//            Serial.println((String(sid1)) + "===");
            dam_x = posx.toInt();//if(dam_x>100){cam_x = dam_x - 100;}
            dam_y = posy.toInt();//if(dam_y>100){cam_y = dam_y - 100;}
            dam_1 = wif1.toInt();//if(dam_1>100){wifi = dam_1 - 100;}
            dam_2 = sid1.toInt();//if(dam_2>100){m_side = dam_2 - 100;}
            
            datachain = "";
          Serial.println(cam_x);
          //Serial.println(pam_y);
          //slow_ndas(pam_y);
          //Serial.print(wifi);
          //Serial.println(m_side);
//          }
        }        
        else {datachain += char(data_masuk);}
      }
}
void cek_data(){
  //Serial.println("TEST");
        selek();
        lcd.setCursor(0,0);lcd.print(cam_x);Serial.print("X = ");Serial.print(cam_x);Serial.print("||");
        lcd.setCursor(0,1);lcd.print(cam_y);Serial.print("Y = ");Serial.println(cam_y);        
    }
//==========================================================================
//==========================================================================
void mandek_jeglek(){
   while(1){  
    selek();
    mot.omni(0,0,0);
    if(wifi==1){break;}  
  }}
//==========================================================================
//==========================================================================
void putar_gawang_lawan(){
    int f=0,p=0;
    //hand_on;
   while(1){ 
      f = mot.kempas();
      if(f>180 && f<359)mot.omni(0,40,-50);//puter bodi kanan{mot.omni(0,0,-50);//kanan
      if(f>=1 && f<=180){mot.omni(0,-40,50);}//puter bodi kiri{mot.omni(0,0,50);}kiri
      mot.omni(0,-40,50);//puter bodi kiri
      if(f==0||f>=355||f<5){break;}
   }
    mot.omni(0,0,0);
  } 
   
void cari_bola(){
    int x =0,l=0,hit=0,hit1=0,m=0;
    ndas.write(90);
    while(1){
    selek();if(wifi==2){mandek_jeglek();}
    x = map(cam_x,1,320,16,-16);x = x*7;
    if(cam_x!=0&&l==0){l=1;if(m==1){mot.omni(0,x,0);}else{mot.omni(0,x,0);}}
    if(cam_x!=0&&l==1){if(m==1){mot.omni(0,x,0);}else{mot.omni(0,x,0);}}
    if(cam_x<190&&cam_x>130){mot.omni(0,0,0);break;}
    if(cam_x==0){
      if(l==0){mot.omni(0,40,0);}
      if(l==1){hit1++;mot.omni(0,-30,0);if(hit1>40){hit1=0;l=0;}}
      hit++;if(hit>140){m=1;ndas.write(67);}if(hit>200){hit=0;}
      if(hit<140){m=0;ndas.write(100);}
    }
  }hit=0;
  while(1){
      selek();if(wifi==2){mandek_jeglek();}
      x = map(cam_x,1,320,16,-16);x = x*4;
      mot.omni(0,x,0);slow_ndas(cam_y);  
      hit++;if(hit>10){break;}
    }
}
void start_awal(){
      lcd.setCursor(0,0);
      lcd.print("TES_1");mot.omni(0,0,0);
      int x,y,rad,hit=0;hand_of;
//   while(1){selek();slow_ndas(cam_y);if(wifi==1){break;}}//wifi button
   while(1){
      ndas.write(100);mot.omni(0,0,0);
      while(1)
        {
            selek();if(wifi==2){mandek_jeglek();}
            x = map(cam_x,1,320,16,-16);x = x*5;
            if(cam_y!=0){hit=0;mot.omni(110,0,x);slow_ndas(cam_y);}
            if(cam_y==0){hit++;mot.omni(0,0,0);}//hit
            if(nds<80){hand_on;}else{hand_of;}
            if(hit>10){cari_bola();hit=0;}
            lit++;if(lit>10){lcd.clear();lit=0;}
            lcd.setCursor(0,1);lcd.print(cam_y);lcd.setCursor(0,0);lcd.print(cam_x);
            if(sen_inf==LOW){delay(400);break;}
        }
      putar_gawang_lawan();
      hand_of;delay(400);kick_on;delay(500);kick_of;
   }
  }
void start_pick(){
      lcd.setCursor(0,0);
      lcd.print("Bismillah");mot.omni(0,0,0);
      int x,y,rad,b,hit=0;hand_of;
      static int a;
      //  while(1){selek();slow_ndas(cam_y);if(wifi==1){break;}}//wifi button
      while(1){
            selek();
            //if(wifi==2){mandek_jeglek();}
            a = cam_x;
            if(a!=0){b=a;}
            x = map(cam_x,1,320,16,-16);x = x*5;
            Serial.print(";");Serial.println(cam_x);
            if(cam_x!=0){mot.omni(110,0,x);}
            if(cam_x==0){
              if(b<=160){mot.omni(0,0,70);}//putar kiri
              if(b>160){mot.omni(0,0,-70);}}//putar kanan  
            slow_ndas(cam_y); 
            if(nds<0){break;}
    }
   while(1){
      slow_ndas(cam_y); 
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
      mot.omni(80,0,0);delay(1000);
      if(mot.us1()<=30)
      {mot.omni(0,-80,0);delay(1000);mot.omni(80,0,0);delay(1000);}
      if(mot.us2()<=30)
      {mot.omni(0,80,0);delay(1000);mot.omni(80,0,0);delay(1000);}
      if(mot.us1()<=30&&mot.us2()<=30){manuver();}
      putar_gawang_lawan();
      hand_of;delay(1000);kick_on;delay(1000);kick_of;
   }
  }
  void start_pin(){
    mot.omni(0,0,0);lcd.clear();lcd.setCursor(0,0);lcd.print("Pinalty Bos");lcd.clear();
    int k2=0,ti_kom,x,y,f,rad,hit=0,k=0,lop=0,hit2=0,ab=0,hit3=0,back;
    hand_of;
    
while(1){
    ndas.write(100);hit=0;hit2=0;
    ret:
        while(1){
          selek();
          if(wifi==2){mandek_jeglek();}
          x = map(cam_x,1,320,16,-16);x = x*5;
          mot.omni(70,0,x);slow_ndas(cam_y);
          lcd.setCursor(0,1);lcd.print(cam_y);
          if(nds<80){break;}}
        }
            while(nds<80){
              selek();
              if(wifi==2){mandek_jeglek();}
              x = map(cam_x,1,320,16,-16);x = x*5;
              mot.omni(40,0,x);slow_ndas(cam_y);
              lcd.setCursor(0,1);lcd.print(cam_y);
              if(nds<80){hand_on;}else{hand_of;}
              if(sen_inf==0){delay(400);break;} 
            }
          mot.omni(0,0,0);hand_of;delay(1000);kick_on;delay(1000);kick_of;
          goto ret;
          }
       

void mode_dekat(){
    lcd.clear();lcd.setCursor(0,0);lcd.print("Mode Dekat");lcd.clear();
    int k2=0,ti_kom,x,y,f,rad,hit=0,k=0,lop=0,hit2=0,ab=0,hit3=0,back;hand_of;
     
while(1){
    mot.omni(60,0,0);delay(2000);
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
void scan_bol_1(){
    int ti_kom,x,y,f,rad,hit=0,k=0,hit2=0,kon=0;
    ti_kom = mot.kempas(); 
    while(1){
        selek();if(wifi==2){mandek_jeglek();}
        if(cam_x!=0){kon=0;mot.omni(0,0,0);break;}
        f = mot.kempas();
        if(k==0){hit++;mot.omni(0,0,-20);}
        if(k==1){hit++;mot.omni(0,0,20);}
        if(f>(ti_kom+10)){k=1;}
        if(f<(ti_kom-10)){k=0;}
        if(hit==5){kon=1;break;}
      }hit=0;
    while(1){
      selek();if(wifi==2){mandek_jeglek();}
      x = x*2;mot.omni(0,0,x);hit++;
      x = map(cam_x,1,320,16,-16);
      slow_ndas(cam_y);  
      if(hit>10){break;}
      if(kon==1){lurus_arah();break;}
    } 
  }
  
void balik_gawang(){
     int f,l1=0,l2=0,l3=0,hit=0;
//     delay(3000);
     lcd.clear();lcd.setCursor(0,0);lcd.print("WES");
     while(1){
        f = mot.kempas();
        if(f>270){mot.omni(-30,0,15);}
        if(f<270){mot.omni(-30,0,-15);}
//        selek_us();
        if(us2<90&&l3==1){l1=1;}
        if(us1<90&&l3==1){l2=1;}
        hit++;if(hit>30){l3=1;}
        if(l2==1&&l1==1&&l3==1){break;}
        if(us1<80&&us2<80&&l3==1){break;}
      }
//    while(1){mot.omni(0,0,0);}
  }
void hadang_bola(){
    hand_on;
    int hit=0,x,y;
    while(1)
        {
            selek();if(wifi==2){mandek_jeglek();}
            x = map(cam_x,1,320,16,-16);x = x*5;
            if(cam_y!=0){hit=0;mot.omni(110,x,0);slow_ndas(cam_y);}
            if(cam_y==0){hit++;mot.omni(0,0,0);}//hit
            if(hit>10){cari_bola();hit=0;}
            lit++;if(lit>10){lcd.clear();lit=0;}
            lcd.setCursor(0,1);lcd.print(cam_y);lcd.setCursor(0,0);lcd.print(cam_x);
            if(sen_inf==LOW){delay(400);break;}
        }
  }
void cek_bol(){
  int hit=0,hit1=0,x;
   while(1){ 
    selek();
    if(cam_x!=0){scan_bola();}
    mot.omni(0,0,-30);delay(1000);
    x = map(cam_x,1,320,16,-16);x = x*5;
    while(1){
      selek();
      mot.omni(0,0,30);delay(2000);mot.omni(0,0,-30);delay(2000);hit++;
       if(hit>1){ndas.write(100);}if(hit>2||hit>4){ndas.write(90);}if(hit>3){ndas.write(60);if(cam_x!=0){scan_bola();}}
      lcd.setCursor(0,0);lcd.print(cam_x);
      } 
  }
}
void scan_bola1(){
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

 void scan_bola(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bismillah Tatag");
    mot.omni(0,0,0);hand_of;
    int k2=0,ti_kom,x,y,f,rad,hit,k=0,lop=0,hit1,hit2,hit3,back;
//while(1){selek();slow_ndas(cam_y);if(wifi==1){break;}}
while(1){
   mot.omni(80,0,0);delay(4000);
   mot.omni(0,-40,0);delay(3000);
   
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
             mot.omni(0,0,0);kick_on;delay(1000);hand_of;delay(10);kick_of;
        if(sen_inf==LOW){delay(1000);goto sepak;}
              mot.omni(-50,0,0);delay(2000);
        goto awal; 
          }
      }
 }
void pin(){
    mot.omni(0,0,0);lcd.clear();lcd.setCursor(0,0);lcd.print("Pinelaty Kiper");
    int k2=0,ti_kom,x,y,f,rad,hit=0,k=0,lop=0,hit2=0,ab=0,hit3=0;
    ndas.write(60);
    while(1){
        selek();
        if(cam_y!=0){slow_ndas(cam_y);}
        if(wifi==1){break;}

//        x = map(cam_x,1,320,16,-16);x = x *4;
//        mot.omni(0,0,x);
//        
        }//wifi button
    ndas.write(78);
    while(1){
        lit++;if(lit>5){lcd.clear();lit=0;}
        if(wifi==2){mandek_jeglek();}
        hand_on;
        lcd.setCursor(0,0);lcd.print(nds);
        selek();x = map(cam_x,1,320,16,-16);
      if(cam_x!=0){
        x = x*7;
        mot.omni(0,x,0);
      }
     if(cam_x==0){mot.omni(0,0,0);}
     if(sen_inf==LOW){delay(400);break;}
      }
   while(1){mot.omni(0,0,0);hand_of;}
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
      
      scan_bola();//kembali scan bola 
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
delay(10000);
}

//fungsi jarak (harus pakai kecepatan 180)
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

void loop() {
    
//lit++;if(lit>10){lcd.clear();lit=0;}
//lcd.setCursor(0,0);lcd.print("Pick-Str-SK-BTH");
//if(tom_1==LOW){scan_bola();}
//if(tom_2==LOW){start_pick();}
//if(tom_3==LOW){set_kompas();}
//if(tom_4==LOW){
mot.omni(180,0,0);jarak(2);//1meter
//mot.omni(180,0,0);//1meter
mot.omni(0,0,0);delay(1000000);
 
//mot.omni(0,0,0);mot.omni(0,-50,0);delay(2850);mot.omni(0,0,0);delay(4000);mot.omni(-50,0,0);delay(4000);mot.omni(0,0,0); scan_bola();}
//hand_on;
//putar_gawang_lawan();
//selek();
//Serial.println('a');
//start_pick();
//nilai_us();
//mot.us1();
//mot.us2();
//slow_ndas(cam_y);
//delay(1000);
//mot.omni(0,0,50);
//set_kompas();
//cek_data();
//Serial.println(wifi);
//lcd.setCursor(0,1);lcd.print(mot.kempas());
//lcd.setCursor(7,1);lcd.print(mot.kempas_asli());
//manuver();
//mot.omni(0,80,-40);//puter bodi kiri
}
