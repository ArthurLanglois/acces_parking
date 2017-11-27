#include "clavier.h"
#include "Arduino.h"
#include "fonction.h" 
#include "affiche.h"
#include <string.h>
#include <Wire.h>


boolean testClavier(int adresse){       //Fonction permettant de detecter si une touche est appuyee
  boolean test = false;
  ecrireDonnee(adresse, 0x0f);          //On ecrit ca pour detecter si une touche a ete appuyee
  delay(20);
  if(lireDonnee(adresse)!=(0x0f)){      //Si la touche appuyee qui est detectee, alors la touche appuyee est differente
    test = true;
  }
  return test;
}

int toucheAppuyee(int adresse){         //Fonction permettant de recuperer la valeur pour chaque touche appuyee
  int ligne, colonne, touche;
  ecrireDonnee(adresse, 0x0f);          //en mettant les colonnes et les lignes a l'etat haut
  colonne = lireDonnee(adresse);
  ecrireDonnee(adresse, 0xf0);
  ligne = lireDonnee(adresse);
  touche = colonne|ligne;               //a l'aide d'un masque OU logique qui permet de recuperer 1 seule valeur pour
  return touche;                        //une touche appuyee
}

char tradClavier(int valeur){           //Fonction permettant de traduire la touche appuyee
  int touche;                           //en fonction de la valeur donnee puis en affectant un caractere
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



int validationClavier(void){            //Fonction qui permet de verifier si le code rentre est bon
  int resultat = 0;
  char codeValide[5]={'1','2','3','4','\0'};
  char codeEntree[5]={' ',' ',' ',' ','\0'};
  int rang;
  if(testClavier(0x22)==true){        //Si une touche est appuyee
    int essais = 0;
    do{
        for(rang=0;rang<4;rang++){
            while (testClavier(0x22)==false);   //On ne fait rien tant qu'aucune touche n'est appuyee
            codeEntree[rang]=tradClavier(toucheAppuyee(0x22));  //On traduit la valeur de la touche appuyee
            while (testClavier(0x22)==true);    //On ne fait rien tant qu'une touchee est appuyee
        }
        essais++;
        if(strcmp(codeEntree,codeValide)!=0 && essais<3){ //On compare le code entre avec le code valide
          effacerAfficheur (0x3b);                        //Si cela est faux, alors on affiche ces messages ci dessous
          envoyerMessage(0x3b,MESSAGE5,LIGNE1);
          envoyerMessage(0x3b,MESSAGE6,LIGNE2);
        }
    }
    while(strcmp(codeEntree,codeValide)!=0 && essais<3);
    if(strcmp(codeEntree,codeValide)==0){     //Si le code est bon, on passe resultat a 1
      resultat = 1;
    }
    else{                                                 //Si au bout des 3 essais, l'utilisateur n'a toujours pas le bon code on lui demande de quitter la place
      effacerAfficheur (0x3b);
      envoyerMessage(0x3b,MESSAGE9,LIGNE1);
      envoyerMessage(0x3b,MESSAGE8,LIGNE2);
      while(boucleAmont()==1);
    }
  }
  return resultat;
}

