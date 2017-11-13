#include "Arduino.h"
#include "fonction.h" 
#include "affiche.h"
#include <Wire.h>



int lireDonnee(int adress){
  int octet;
  Wire.beginTransmission(adress);
  Wire.requestFrom(adress, 1);
  while(Wire.available()){
    octet = Wire.read();
  }
  return octet;
}

void ouvrirBarriere(void){
  envoyerCommande(0x20, 0xfd);
}

void fermerBarriere(void){
  envoyerCommande(0x20, 0xfe);
}

int boucleAmont(void){
  if (((lireDonnee(0x20)&0x20)>>5)==1){
    return 0;
  }
  else{
    return 1;
  }
}

int boucleAval(void){
  if (((lireDonnee(0x20)&0x40)>>6)==1){
    return 0;
  }
  else{
    return 1;
  }
}

int testClavier(int adresse){
  int test = 0;
  envoyerCommande(adresse, 0x0f);
  if(lireDonnee(0x38)!=(0x0f)){
    test = 1;
  }
  return test;
}

int toucheAppuyee(int adresse){
  int ligne, colonne, touche;
  envoyerCommande(adresse, 0x0f);
  colonne = lireDonnee(adresse);
  envoyerCommande(adresse, 0xf0);
  ligne = lireDonnee(adresse);
  delay(50);
  touche = (colonne)|ligne;
  return touche;
}

int tradClavier(int valeur){
  int touche;
  switch(valeur){
    case 238 :  Serial.println("1");
                touche = 1;
                break;
    case 237 :  Serial.println("4");
                touche = 4;
                break;
    case 235 :  Serial.println("7");
                touche = 7;
                break;
    case 222 :  Serial.println("2");
                touche = 2;
                break;
    case 221 :  Serial.println("5");
                touche = 5;
                break;
    case 219 :  Serial.println("8");
                touche = 8;
                break;
    case 190 :  Serial.println("3");
                touche = 3;
                break;
    case 189 :  Serial.println("6");
                touche = 6;
                break;
    case 187 :  Serial.println("9");
                touche = 9;
                break;
    case 125 :  Serial.println("?");
                touche = 14;
                break;
    case 126 :  Serial.println("?");
                touche = 10;
                break;
    case 123 :  Serial.println("@");
                touche = 11;
                break;
    case 119 :  Serial.println("?");
                touche = 12;
                break;
    case 183 :  Serial.println("#");
                touche = 13;
                break;
    case 215 :  Serial.println("0");
                touche = 0;
                break;
    case 231 :  Serial.println("*");
                touche = 15;
                break;
    default : Serial.println("essaie encore");
  }
  return touche;
}

int validation(void){
  int valid = 0;
  Serial.println("Entrez votre code ou inserer une carte");
  if(testClavier(0x22)==1){
    if(entrerCode()==1){
      valid = 1;
      Serial.println("Code bon");
    }
    else{
      Serial.println("Code faux");
    }
  }
  return valid;
}

int entrerCode(void){
  int code_bon;
  int nombreEssais = 3;
  //while(nombreEssais!=0){
    Serial.println("entrez votre code");
    code_bon = 1;
    if(tradClavier(toucheAppuyee(0x22))!=1){
      code_bon = 0;
    }
    delay(200);
    while(testClavier(0x22)==0);
    if(tradClavier(toucheAppuyee(0x22))!=2){
      code_bon = 0;
    }
    delay(200);
    while(testClavier(0x22)==0);
    if(tradClavier(toucheAppuyee(0x22))!=3){
      code_bon = 0;
    }
    delay(200);
    while(testClavier(0x22)==0);
    if(tradClavier(toucheAppuyee(0x22))!=4){
      code_bon = 0;
    }
    delay(200);
    if(code_bon = 0){
      Serial.println("mauvais code");
      nombreEssais--;
    }
  //}
  return code_bon;
}

