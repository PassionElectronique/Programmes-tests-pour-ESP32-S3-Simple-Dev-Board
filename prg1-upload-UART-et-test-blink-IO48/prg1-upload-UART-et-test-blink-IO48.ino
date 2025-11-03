/*
   ______               _                  _///_ _           _                   _
  /   _  \             (_)                |  ___| |         | |                 (_)
  |  [_|  |__  ___  ___ _  ___  _ __      | |__ | | ___  ___| |_ _ __ ___  _ __  _  ___  _   _  ___
  |   ___/ _ \| __|| __| |/ _ \| '_ \_____|  __|| |/ _ \/  _|  _| '__/   \| '_ \| |/   \| | | |/ _ \
  |  |  | ( ) |__ ||__ | | ( ) | | | |____| |__ | |  __/| (_| |_| | | (_) | | | | | (_) | |_| |  __/
  \__|   \__,_|___||___|_|\___/|_| [_|    \____/|_|\___|\____\__\_|  \___/|_| |_|_|\__  |\__,_|\___|
                                                                                      | |
                                                                                      \_|
  Fichier :       prg1-upload-UART-et-test-blink-IO48.ino
  Dépôt :         https://github.com/PassionElectronique/Programmes-tests-ESP32-Simple-Dev-Board
  
  Description :   Programme permettant de faire clignoter une LED branchée sur la broche IO48,
                  à une fréquence de 1 hertz

  Licence :       BY-NC-ND 4.0 CC (https://creativecommons.org/licenses/by-nc-nd/4.0/deed.fr)

  Remarque :      Téléchargement via adaptateur USB/UART + auto-boot/auto-reset

  Auteur :        Jérôme TOMSKI (https://passionelectronique.fr/)
  Créé le :       31.10.2025
  
*/


// Définition de la broche utilisée ici
#define BROCHE_LED  48                          // Led branchée sur pin GPIO 48


// ========================
// Initialisation programme
// ========================
void setup() {

  // Configure la broche "led" en sortie
  pinMode(BROCHE_LED, OUTPUT);

}


// =================
// Boucle principale
// =================
void loop() {

  // Allume la LED, puis attend une demi seconde
  digitalWrite(BROCHE_LED, HIGH);
  delay(500);

  // Éteint la LED, puis attend une demi seconde
  digitalWrite(BROCHE_LED, LOW);
  delay(500);

}