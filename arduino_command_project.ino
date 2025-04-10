#include <Bounce2.h>
Bounce bouton = Bounce();
#define BTN_VERT          48
#define BTN_ROUGE         49
#define BTN_BLEU          50
#define SWITCH_V          51
#define SWITCH_R          52
#define SWITCH_B          53
#define CPRESENCE_COULEUR 34
#define CPRESENCE_METAL   35
#define CPRESENCE_RONDELLE 36
#define CAPTEUR1          37
#define CAPTEUR2          38
#define CAPTEUR3          39
#define CAPTEUR_TUBE      33
#define CAPTEUR_POUSSE1   32
#define CAPTEUR_POUSSE2   31
#define CAPTEUR_PINCE     30
#define CAPTEUR_PINCE_POUSSE1 28
#define CAPTEUR_PINCE_POUSSE2 29
#define CAPTEUR_POINT_INITIAL_PINCE 24
#define CAPTEUR_POINT_FINAL_PINCE 27
#define CAPTEUR_POINT1_PINCE 25
#define CAPTEUR_POINT2_PINCE 26
#define BAISSER_PINCE     2
#define OUVRE_PINCE       3
#define POUSSE_POUSSOIR   4
#define WARNING_LIGHT     5
#define LED1              7
#define LED2              8
#define LED3              9
#define POUSSE_GAUCHE     11
#define POUSSE_DROITE     12
#define ARDUINO_LED       13
static int poussoir = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BTN_VERT, INPUT_PULLUP);
  pinMode(BTN_ROUGE, INPUT_PULLUP);
  pinMode(BTN_BLEU, INPUT_PULLUP);
  pinMode(SWITCH_V, INPUT_PULLUP);
  pinMode(SWITCH_R, INPUT_PULLUP);
  pinMode(SWITCH_B, INPUT_PULLUP);
  pinMode(CPRESENCE_COULEUR, INPUT_PULLUP);
  pinMode(CPRESENCE_METAL, INPUT_PULLUP);
  pinMode(CPRESENCE_RONDELLE, INPUT_PULLUP);
  pinMode(CAPTEUR1, INPUT_PULLUP);
  pinMode(CAPTEUR2, INPUT_PULLUP);
  pinMode(CAPTEUR3, INPUT_PULLUP);
  pinMode(CAPTEUR_TUBE, INPUT_PULLUP);
  pinMode(CAPTEUR_POUSSE1, INPUT_PULLUP);
  pinMode(CAPTEUR_POUSSE2, INPUT_PULLUP);
  pinMode(CAPTEUR_PINCE, INPUT_PULLUP);
  pinMode(CAPTEUR_PINCE_POUSSE1, INPUT_PULLUP);
  pinMode(CAPTEUR_PINCE_POUSSE2, INPUT_PULLUP);
  pinMode(CAPTEUR_POINT_INITIAL_PINCE, INPUT_PULLUP);
  pinMode(CAPTEUR_POINT_FINAL_PINCE, INPUT_PULLUP);
  pinMode(CAPTEUR_POINT1_PINCE, INPUT_PULLUP);
  pinMode(CAPTEUR_POINT2_PINCE, INPUT_PULLUP);
  pinMode(BAISSER_PINCE, OUTPUT);
  pinMode(OUVRE_PINCE, OUTPUT);
  pinMode(POUSSE_POUSSOIR, OUTPUT);
  pinMode(WARNING_LIGHT, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(POUSSE_GAUCHE, OUTPUT);
  pinMode(POUSSE_DROITE, OUTPUT);
  pinMode(ARDUINO_LED, OUTPUT);
  bouton.attach(BTN_ROUGE);
  bouton.interval(65);
 
}

int detect_couleur()
{
  if(digitalRead(CPRESENCE_RONDELLE)==LOW && digitalRead(CPRESENCE_COULEUR)==HIGH && digitalRead(CPRESENCE_METAL)==HIGH)
  {
    return 3; //noir
  }
  else if(digitalRead(CPRESENCE_RONDELLE)==LOW && digitalRead(CPRESENCE_COULEUR)==LOW && digitalRead(CPRESENCE_METAL)==HIGH) 
   {
    return 1; //rouge
  }
  else if (digitalRead(CPRESENCE_RONDELLE)==LOW && digitalRead(CPRESENCE_COULEUR)==LOW && digitalRead(CPRESENCE_METAL)==LOW)
  {
    return 2; //metal
  }
}

void automatique(){
  int couleur_rondelle;
  while(digitalRead(CAPTEUR_TUBE) == LOW && digitalRead(SWITCH_B) == HIGH)
  { 
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    pos_ini();
    if (digitalRead(CPRESENCE_RONDELLE) == LOW){
      jeter();
    }
    pousse();
    delay(50);
    couleur_rondelle = detect_couleur();
    descend_bras ();
    fermer_pince ();
    depousse();
    monte_bras ();
    aller_bonne_chute(couleur_rondelle);
    descend_bras ();
    ouvre_pince_auto ();
    monte_bras ();
    pos_ini();
  }

}

void pos_ini(){
digitalWrite(OUVRE_PINCE, LOW);
digitalWrite(BAISSER_PINCE, LOW);
digitalWrite(POUSSE_GAUCHE, HIGH);
while(digitalRead(CAPTEUR_POINT_INITIAL_PINCE));
digitalWrite(POUSSE_GAUCHE, LOW);
}
void detect_tube()
{
  if (digitalRead(CAPTEUR_TUBE) == LOW)
  {
    pousse();
  }
}

void pousse(){

  digitalWrite (POUSSE_POUSSOIR, HIGH);
  while(digitalRead(CAPTEUR_POUSSE2));}

void depousse(){

  digitalWrite (POUSSE_POUSSOIR, LOW);
  while(digitalRead(CAPTEUR_POUSSE1));
}

void descend_bras ()
{
  digitalWrite (BAISSER_PINCE, HIGH);
  while (digitalRead(CAPTEUR_PINCE_POUSSE2));
}

void fermer_pince ()
{
  digitalWrite(OUVRE_PINCE, HIGH);
  while (digitalRead(CAPTEUR_PINCE));
}
void monte_bras ()
{
  digitalWrite (BAISSER_PINCE, LOW);
  while (digitalRead(CAPTEUR_POUSSE1));
}

void bras_chute1()
{
  digitalWrite(POUSSE_DROITE, HIGH);
  while(digitalRead(CAPTEUR_POINT1_PINCE) == HIGH);
  digitalWrite(POUSSE_DROITE, LOW);
}

void bras_chute2()
{
  digitalWrite(POUSSE_DROITE, HIGH);
  while(digitalRead(CAPTEUR_POINT2_PINCE) == HIGH);
  digitalWrite(POUSSE_DROITE, LOW);
}

void bras_chute3()
{
  digitalWrite(POUSSE_DROITE, HIGH);
  while(digitalRead(CAPTEUR_POINT_FINAL_PINCE) == HIGH);
  digitalWrite(POUSSE_DROITE, LOW);
}
void aller_bonne_chute (int couleur_rondelle)
{
  if(couleur_rondelle==3){
    Serial.println("Noir bouge");
    bras_chute3();
  }
  else if(couleur_rondelle ==  1){
    Serial.println("Rouge bouge");
    bras_chute1();
    }
  else if(couleur_rondelle == 2){
    Serial.println("Métal bouge");
    bras_chute2();
  }
}
void ouvre_pince_auto()
{
  digitalWrite(OUVRE_PINCE, LOW);
  while(digitalRead(CAPTEUR_PINCE));
}
  


void manuel() {
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, HIGH);
  pousse_droite();
  pousse_gauche();
  pousse_poussoir();
  ouvre_pince ();
  baisser_pince();
}
void pousse_droite(){
  if(digitalRead(BTN_BLEU) == LOW)
    {
      digitalWrite(POUSSE_DROITE, HIGH);
    }
  if(digitalRead(BTN_BLEU) == HIGH){
      digitalWrite(POUSSE_DROITE, LOW);
    }
}

void pousse_gauche(){
    if(digitalRead(BTN_VERT) == LOW)
    {
      digitalWrite(POUSSE_GAUCHE, HIGH);
    }
  else {
      digitalWrite(POUSSE_GAUCHE, LOW);
    }
}
void pousse_poussoir(){
  if (bouton.rose()) { // Bouton relâché
    
    if(poussoir == 0)
    {
      digitalWrite(POUSSE_POUSSOIR, HIGH);
      poussoir = 1;
    } else if(poussoir == 1)
    {
      digitalWrite(POUSSE_POUSSOIR, LOW);
      poussoir = 0;
    }
  }
}

void ouvre_pince (){
  if(digitalRead(SWITCH_V) == LOW)
  {
    digitalWrite(OUVRE_PINCE, HIGH);
  }
  if(digitalRead(SWITCH_V) == HIGH)
  {
   digitalWrite(OUVRE_PINCE, LOW);
  }
}

void baisser_pince(){
    if(digitalRead(SWITCH_R) == HIGH)
   {
    digitalWrite(BAISSER_PINCE, HIGH);
   }
   else {
    digitalWrite(BAISSER_PINCE, LOW);
   }
}
void bug()
{
  while (digitalRead(CAPTEUR_POUSSE1)==LOW && digitalRead(CPRESENCE_RONDELLE)==HIGH);
  digitalWrite(WARNING_LIGHT, HIGH);
  while (digitalRead(CAPTEUR_POUSSE1)==HIGH && digitalRead(CPRESENCE_RONDELLE)==LOW);
  digitalWrite(WARNING_LIGHT, LOW);

}

void jeter()
{
  digitalWrite(WARNING_LIGHT, HIGH);
  descend_bras ();
  fermer_pince ();
  monte_bras ();
  digitalWrite(POUSSE_DROITE, HIGH);
  delay (15000);
  digitalWrite(POUSSE_DROITE, LOW);
  descend_bras ();
  ouvre_pince_auto ();
  monte_bras ();
  pos_ini();
  digitalWrite(WARNING_LIGHT, LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(BTN_VERT) == LOW && digitalRead(SWITCH_B) == HIGH)
  {
    automatique();
  }
  else if (digitalRead(SWITCH_B) == LOW)
  {
    manuel();
  }
  bouton.update();
}
