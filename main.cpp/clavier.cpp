#include "clavier.h"
#include "Arduino.h"
#include "fonction.h" 
#include "affiche.h"
#include <string.h>
#include <Wire.h>


boolean testClavier(int adresse){
  boolean test = false;
  ecrireDonnee(adresse, 0x0f);
  delay(20);
  if(lireDonnee(adresse)!=(0x0f)){
    test = true;
  }
  return test;
}

int toucheAppuyee(int adresse){
  int ligne, colonne, touche;
  ecrireDonnee(adresse, 0x0f);
  colonne = lireDonnee(adresse);
  ecrireDonnee(adresse, 0xf0);
  ligne = lireDonnee(adresse);
  touche = colonne|ligne;
  return touche;
}

char tradClavier(int valeur){
  int touche;
  switch(valeur){
    case 238 :  Serial.println("1");
                touche = '1';
                break;
    case 237 :  Serial.println("4");
                touche = '4';
                break;
    case 235 :  Serial.println("7");
                touche = '7';
                break;
    case 222 :  Serial.println("2");
                touche = '2';
                break;
    case 221 :  Serial.println("5");
                touche = '5';
                break;
    case 219 :  Serial.println("8");
                touche = '8';
                break;
    case 190 :  Serial.println("3");
                touche = '3';
                break;
    case 189 :  Serial.println("6");
                touche = '6';
                break;
    case 187 :  Serial.println("9");
                touche = '9';
                break;
    case 123 :  Serial.println("@");
                touche = 'A';
                break;
    case 183 :  Serial.println("#");
                touche = '#';
                break;
    case 215 :  Serial.println("0");
                touche = '0';
                break;
    case 231 :  Serial.println("*");
                touche = '*';
                break;
    default : Serial.println("essaie encore");
  }
  return touche;
}

int validation(void){
  int valid = 0;
  if(testClavier(0x22)==true){
    if(validationClavier()==1){
      valid = 1;
      effacerAfficheur (0x3b);
      envoyerMessage(0x3b,MESSAGE3,LIGNE1);
      envoyerMessage(0x3b,MESSAGE4,LIGNE2);
    }
  }
  return valid;
}


int validationClavier(void){
  int resultat = 0;
  char codeValide[5]={'1','2','3','4','\0'};
  char codeEntree[5]={' ',' ',' ',' ','\0'};
  int rang;
  if(testClavier(0x22)==true){
    int essais = 0;
    do{
        for(rang=0;rang<4;rang++){
            while (testClavier(0x22)==false);
            codeEntree[rang]=tradClavier(toucheAppuyee(0x22));
            while (testClavier(0x22)==true);
        }
        essais++;
        if(strcmp(codeEntree,codeValide)!=0 && essais<3){
          effacerAfficheur (0x3b);
          envoyerMessage(0x3b,MESSAGE5,LIGNE1);
          envoyerMessage(0x3b,MESSAGE6,LIGNE2);
        }
    }while(strcmp(codeEntree,codeValide)!=0 && essais<3);
    if(strcmp(codeEntree,codeValide)==0){
      resultat = 1;
    }
    else{
      effacerAfficheur (0x3b);
      envoyerMessage(0x3b,MESSAGE9,LIGNE1);
      envoyerMessage(0x3b,MESSAGE8,LIGNE2);
      while(boucleAmont()==1);
    }
  }
  return resultat;
}

