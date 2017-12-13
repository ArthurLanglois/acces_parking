#include "Arduino.h"
#include "I2C.h"
#include "affiche.h"      //Inclusion des bibliotheques appropriées
#include "fonction.h"
#include "clavier.h"
#include "cartepuce.h"
#include "terminal.h"
#include <Wire.h>

void setup() {
  initI2C(255);           //Vitesse de transmission
  fermerBarriere();       //fermer d'office la barrière
  Serial3.begin(9600);
  initAfficheur(0x3b);
  setEclairage(0x21,LOW);
  
  terminalInit();
  terminalPosition(3,6);
  Serial3.print("----");
  terminalPosition(4,4);
  Serial3.print("/      \\");
  terminalPosition(5,3);
  Serial3.print("|        |");
  terminalPosition(6,4);
  Serial3.print("\\      /");
  terminalPosition(7,6);
  Serial3.print("----");
  terminalPosition(3,30);
  Serial3.print("0    Vehicule(s) dans le parking");
  terminalPosition(5,30);
  Serial3.print("--> ------ d'un véhicule");
  terminalPosition(7,30);
  Serial3.print("La barrière est FERMEE ");
}

void loop() {

/* 
 terminalPosition(4,5);
 terminalCouleur (37,41);
 Serial3.print("      ");
 terminalPosition(5,4);
 Serial3.print("        ");
 terminalPosition(6,5);
 Serial3.print("      ");
 delay(500);
 terminalPosition(4,5);
 terminalCouleur (37,40);
 Serial3.print("      ");
 terminalPosition(5,4);
 Serial3.print("        ");
 terminalPosition(6,5);
 Serial3.print("      ");
 delay(500);
*/

  static int drapeauTexte = 0;
  int tempo=0, testTempo;       //tempo permettra d'attendre les 30 secondes en entrée
  static int nombreVoiture=0;   //static qui permet de compter le nombre de véhicules dans le parking


  //Gestion de l'entrée d'un véhicule
  if (boucleAmont()==1 && boucleAval()==0){       //Arrivée d'une voiture en entrée du parking
        testTempo=1;                                                        //Initialisation de la variable de test de la tempo
        setEclairage(0x21,HIGH);
        if (drapeauTexte == 0){
          envoyerMessage(0x3b,MESSAGE1,LIGNE1);
          delay(1500);
          drapeauTexte = 1;
          effacerAfficheur (0x3b);
          envoyerMessage(0x3b,MESSAGE21,LIGNE1);
          envoyerMessage(0x3b,MESSAGE22,LIGNE2);
        }
        if(validation()==1){ //Code valide
        ouvrirBarriere();
        terminalPosition(7,46);
        Serial3.print("OUVERTE");
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
            }
        }
        fermerBarriere();
        terminalPosition(7,46);
        Serial3.print("FERMEE ");
        
        }
        nombreVoiture++;  //Et on incrémente le nombre de voitures dans le parking
        terminalPosition(3,30);
        Serial3.print(nombreVoiture);
  }
  else{
    drapeauTexte = 0;
    effacerAfficheur (0x3b);
    setEclairage(0x21,LOW);
  }

  
    //Gestion de la sortie d'un véhicule on ne décremente que si la voiture traverse les 2 boucles
    if(boucleAval()==1 && boucleAmont()==0){
            ouvrirBarriere();
            terminalPosition(7,46);
            Serial3.print("OUVERTE");
            while(boucleAval()==1 && boucleAmont()==0);
            if(boucleAval()==1 || boucleAmont()==1){
              while(boucleAval()==1 || boucleAmont()==1);
              fermerBarriere();
              terminalPosition(7,46);
              Serial3.print("FERMEE ");
              nombreVoiture--;
              terminalPosition(3,30);
              Serial3.print(nombreVoiture);
            }
    } //Fin de sortie d'un véhicule

}

