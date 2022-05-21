#include "LiquidCrystal.h"
#include <Servo.h>


etalonnage_capteurs();
lecture_capteur();
avancer();
tourner();
affichage_capteurs();

//parametres du LCD :
LiquidCrystal LCD(0, 1, 12, 11, 10, 9);

void setup(){
//définition de tous les ports de la carte
lcd.begin(16, 2);
Servo servo_gauche;
Servo servo_droit;

}



int main()
{
    int valeur_etalonnage = etalonnage_capteurs(analogRead(4), analogRead(5), analogRead(6), analogRead(8), analogRead(3), analogRead(2),analogRead(1), analogRead(7));
    lecture_capteur(D1(),D2(),D3(),D4(),G1(),G2(),G3(),G4());

    avancer(100,true);

    

}


int etalonnage_capteurs(D1,D2,D3,D4,G1,G2,G3,G4){
    //en attente de placement de tous les capteurs sur du blanc
    //attente bouton
    int blanc = moyenne(D1,D2,D3,G1,G2,G3);
    //en attente de placement de tous les capteur sur ligne noir
    //attente bouton 
    int noir = moyenne(D1,D2,D3,G1,G2,G3);
    //affichage des valeurs D4 / G4 
    //attente bouton
    return (blanc - noir)/2;
}


int lecture_capteur(D1,D2,D3,D4,G1,G2,G3,G4){
// tous les capteurs sont inversées : G1 = D1, G2 = D2, G3 = D3, G4 = D4, LD = LG
//lit les valeurs de tous les capteurs et return le total

    int total=16;
    if (D1 == true){
        total = total + 1;
    }
    if (D2 == true){
        total = total + 2;
    }
    if (D3 == true){
        total = total + 4;
    }
    if (D4 == true){
        total = total + 8;
    }
    if (G1 == true){
        total = total - 1;
    }
    if (G2 == true){
        total = total - 2;
    }
    if (G3 == true){
        total = total - 4;
    }
    if (G4 == true){
        total = total - 8;
    }
    return total;
}



boolean LD(valeur_etalonnage){
//retourne valeur du capteur LG
if (analogRead(7) < valeur_etalonnage){
    return true;
}
else{
    return false;
}
}
boolean D1(valeur_etalonnage){
// detection du capteur de ligne G1
if ( analogRead(4)  < valeur_etalonnage) {
    return true;
    }
else{
    return false;
    }
}

boolean D2(valeur_etalonnage){
// detection du capteur de ligne G2
if ( analogRead(5)  < valeur_etalonnage) {
    return true;
    }
else{
    return false;
    }
}

boolean D3(valeur_etalonnage){
// detection du capteur de ligne G3
if ( analogRead(6)  < valeur_etalonnage) {
    return true;
    }
else{
    return false;
    }
}
boolean D4(valeur_etalonnage){
// detection du capteur de ligne G4
if ( digitalRead(8)  < valeur_etalonnage) {
    return true;
    }
else{
    return false;
    }
}
boolean LG(valeur_etalonnage){
//retourne valeur du capteur LD
if (analogRead(A0) < valeur_etalonnage){
    return true;
}
else{
    return false;
}
}
boolean G1(valeur_etalonnage){
// detection du capteur de ligne D1
if ( analogRead(3)  < valeur_etalonnage) {
    return true;
    }
else{
    return false;
    }
}
boolean G2(valeur_etalonnage){
// detection du capteur de ligne D2
if ( analogRead(2)  < valeur_etalonnage) {
    return true;
    }
else{
    return false;
    }
}
boolean G3(valeur_etalonnage){
// detection du capteur de ligne D3
if ( analogRead(1)  < valeur_etalonnage) {
    return true;
    }
else{
    return false;
    }
}
boolean G4(valeur_etalonnage){
// detection du capteur de ligne D4
if ( digitalRead(7)  < valeur_etalonnage) {
    return true;
    }
else{
    return false;
    }
}


void affichage_capteurs(D1,D2,D3,D4,G1,G2,G3,G4){
//affiche les valeurs des capteurs sur l'écran LCD
lcd.clear();
lcd.setCursor(0,0);
lcd.print("D1:");
lcd.print(D1);
lcd.setCursor(0,1);
lcd.print("D2:");
lcd.print(D2);
lcd.setCursor(0,2);
lcd.print("D3:");
lcd.print(D3);
lcd.setCursor(0,3);
lcd.print("D4:");
lcd.print(D4);
lcd.setCursor(0,4);
lcd.print("G1:");
lcd.print(G1);
lcd.setCursor(0,5);
lcd.print("G2:");
lcd.print(G2);
lcd.setCursor(0,6);
lcd.print("G3:");
lcd.print(G3);
lcd.setCursor(0,7);
lcd.print("G4:");
lcd.print(G4);
}



void avancer(int vitesse,boolean sens){
//fonction qui permet de faire avancer le robot
//vitesse : vitesse de déplacement
//sens : sens de déplacement
//sens = true : avance
//sens = false : recule

if (sens = true){
     myservo.writeMicroseconds(1500 + (vitesse*15));
}
else{
    myservo.writeMicroseconds(1500 + (vitesse*(-15)));
}
}

void tourner(valeur_capteur){
//fonction qui permet de faire tourner le robot
//vitesse : vitesse de déplacement
//sens : sens de déplacement
//sens = true : tourne à gauche
//sens = false : tourne à droite

// ----------------------------------------------------------------------------------- SUITE PAS SUR !!!!
// trouver equation vitesse moteur en fonction des capteurs !!!

if (valeur_capteur < 16){
    //tourner à gauche
     Servo_gauche.writeMicroseconds(1500 + (valeur_capteur*93.75));
     Servo_droit.writeMicroseconds(3000);
}
else{
    //tourner à droite
    valeur_capteur = valeur_capteur - 16;
    Servo_droit.writeMicroseconds(1500 + (valeur_capteur*93.75));
    Servo_gauche.writeMicroseconds(3000);
}

}