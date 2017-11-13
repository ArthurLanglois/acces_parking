#include "Arduino.h"
#include "I2C.h"
#include "affiche.h"      //Inclusion des bibliotheques appropriées
#include "fonction.h"

void setup() {
  initI2C(255);           //Vitesse de transmission
  envoyerCommande(0x20, 0xfc);
  fermerBarriere();       //fermer d'office la barrière
  Serial.begin(9600);
}

void loop() {

/*
if(testClavier(0x38)==1){
    if(entrerCode()==1){
      Serial.println("Code bon");
    }
    else{
      Serial.println("Code faux");
    }
  }
  */
  
  int tempo=0, testTempo;       //tempo permettra d'attendre les 30 secondes en entrée
  static int nombreVoiture=0;   //static qui permet de compter le nombre de véhicules dans le parking

  //Gestion de l'entrée d'un véhicule
  if (boucleAmont()==1 && boucleAval()==0){       //Arrivée d'une voiture en entrée du parking
        testTempo=1;                                                        //Initialisation de la variable de test de la tempo
        if(validation()==1){ //Code valide
        ouvrirBarriere();
        while(boucleAmont()==1 && boucleAval()==0 && testTempo==1){ //Procédure de fermeture de la barrière si la voiture reste
              tempo++;                                                                        //Plus de 30 secondes sur la boucle amont
              delay(30);
              if(tempo==1000){
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
 
}

