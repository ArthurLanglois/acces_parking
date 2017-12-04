#include "Arduino.h"
#include "I2C.h"
#include "affiche.h"      //Inclusion des bibliotheques appropriées
#include "fonction.h"
#include "clavier.h"
#include "cartepuce.h"
#include <Wire.h>

void setup() {
  initI2C(255);           //Vitesse de transmission
  fermerBarriere();       //fermer d'office la barrière
  Serial.begin(9600);
  initAfficheur(0x3b);
  setEclairage(0x21,LOW);
}

void loop() {

if (testClavier(0x22)==true){
Wire.beginTransmission(0x57);
  Wire.write(0x10);
  Wire.write(1);
  Wire.write(2);
  Wire.write(3);
  Wire.write(4);
  Wire.endTransmission();

  Wire.beginTransmission(0x57);
  Wire.write(0x10);
  Wire.requestFrom(0x57, 5, true);
  Wire.read();
  Serial.println(Wire.read());
  Serial.println(Wire.read());
  Serial.println(Wire.read());
  Serial.println(Wire.read());
  Wire.endTransmission();
}

/*
  static int drapeauTexte = 0;
  int tempo=0, testTempo;       //tempo permettra d'attendre les 30 secondes en entrée
  static int nombreVoiture=0;   //static qui permet de compter le nombre de véhicules dans le parking


  //Gestion de l'entrée d'un véhicule
  if (boucleAmont()==1 && boucleAval()==0){       //Arrivée d'une voiture en entrée du parking
        testTempo=1;                                                        //Initialisation de la variable de test de la tempo
        setEclairage(0x21,HIGH);
        if (drapeauTexte == 0){
          envoyerMessage(0x3b,MESSAGE1,LIGNE1);
          delay(2000);
          drapeauTexte = 1;
          effacerAfficheur (0x3b);
          envoyerMessage(0x3b,MESSAGE21,LIGNE1);
          envoyerMessage(0x3b,MESSAGE22,LIGNE2);
        }
        if(validation()==1){ //Code valide
        ouvrirBarriere();
        while(boucleAmont()==1 && boucleAval()==0 && testTempo==1){ //Procédure de fermeture de la barrière si la voiture reste
              tempo++;                                                                        //Plus de 30 secondes sur la boucle amont
              delay(30);
              if(tempo==1000){
                  effacerAfficheur (0x3b);
                  envoyerMessage(0x3b,MESSAGE10,LIGNE1);
                  envoyerMessage(0x3b,MESSAGE8,LIGNE2);
                  fermerBarriere();
                  testTempo=0;              //On met la variable à 0 pour recommencer la procédure et pour sortir de la boucle
              }
        }
        if(boucleAmont()==0 || boucleAval()==1){
            if (boucleAval()==1 || boucleAmont()==1){  //Si la voiture avance
                while(boucleAval()==1 || boucleAmont()==1);  //On attend que la voiture ait passée la barrière
                  nombreVoiture++;
            }
        }
        fermerBarriere();   //Et on incrémente le nombre de voitures dans le parking
        }
        
  }
  else{
    drapeauTexte = 0;
    effacerAfficheur (0x3b);
    setEclairage(0x21,LOW);
  }

  
    //Gestion de la sortie d'un véhicule on ne décremente que si la voiture traverse les 2 boucles
    if(boucleAval()==1 && boucleAmont()==0){
            ouvrirBarriere();
            while(boucleAval()==1 && boucleAmont()==0);
            if(boucleAval()==1 || boucleAmont()==1){
              while(boucleAval()==1 || boucleAmont()==1);
              fermerBarriere();
              nombreVoiture--;
            }
    } //Fin de sortie d'un véhicule
*/
}

