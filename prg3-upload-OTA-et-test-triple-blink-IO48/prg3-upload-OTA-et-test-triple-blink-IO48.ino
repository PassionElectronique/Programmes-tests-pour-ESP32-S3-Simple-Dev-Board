/*
   ______               _                  _///_ _           _                   _
  /   _  \             (_)                |  ___| |         | |                 (_)
  |  [_|  |__  ___  ___ _  ___  _ __      | |__ | | ___  ___| |_ _ __ ___  _ __  _  ___  _   _  ___
  |   ___/ _ \| __|| __| |/ _ \| '_ \_____|  __|| |/ _ \/  _|  _| '__/   \| '_ \| |/   \| | | |/ _ \
  |  |  | ( ) |__ ||__ | | ( ) | | | |____| |__ | |  __/| (_| |_| | | (_) | | | | | (_) | |_| |  __/
  \__|   \__,_|___||___|_|\___/|_| [_|    \____/|_|\___|\____\__\_|  \___/|_| |_|_|\__  |\__,_|\___|
                                                                                      | |
                                                                                      \_|
  Fichier :       prg3-upload-OTA-et-test-triple-blink-IO48.ino
  Dépôt :         https://github.com/PassionElectronique/Programmes-tests-ESP32-Simple-Dev-Board
  
  Description :   Programme permettant de faire clignoter triplement une LED branchée sur la broche IO48

  Licence :       BY-NC-ND 4.0 CC (https://creativecommons.org/licenses/by-nc-nd/4.0/deed.fr)

  Remarque :      Téléchargement via WiFi / OTA ESP32

  Auteur :        Jérôme TOMSKI (https://passionelectronique.fr/)
  Créé le :       01.11.2025
  
*/


// Inclusion des librairies nécessaires
#include <WiFi.h>
#include <ArduinoOTA.h>

// Définition de la broche ESP32 où est branchée la LED embarquée
#define BROCHE_LED  48                                                // Sur GPIO 48, donc

// Codes WiFi (box internet)
const char* ssid_WiFi         = "SSID_WIFI";
const char* mot_de_passe_WiFi = "MOT_DE_PASSE_WIFI";

// Codes OTA (permettant l'upload ultérieur de programmes dans l'ESP32, via le WiFi)
const char* nom_OTA           = "Mon-ESP32-S3-OTA";
const char* mot_de_passe_OTA  = "mdp-OTA";

// ========================
// Initialisation programme
// ========================
void setup() {

  // -----------------------------------------------------------------------------------------------------------------
  // Configuration de base ESP32/WiFi
  // -----------------------------------------------------------------------------------------------------------------

  // Configure la "broche LED" en sortie
  pinMode(BROCHE_LED, OUTPUT);

  // Ouverture du port série
  Serial.begin(115200);
  Serial.print("\n\n");
  Serial.print("=== ESP32-S3 OTA Boot ===");
  Serial.print("\n");

  // Connexion au WiFi
  WiFi.begin(ssid_WiFi, mot_de_passe_WiFi);
  Serial.print("Connexion à "); Serial.print(ssid_WiFi);

  // Attente confirmation WiFi connecté
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");                              // On affiche des "." toutes les 200 ms, en attendant la connexion
  }
  Serial.println("");

  // Affichage adresse IP, pour confirmer connexion WiFi
  Serial.println("WiFi connecté !");
  Serial.print("Adresse IP : "); Serial.println(WiFi.localIP());


  // -----------------------------------------------------------------------------------------------------------------
  // Configuration de l'OTA
  // -----------------------------------------------------------------------------------------------------------------

  // Configuration de l'OTA
  ArduinoOTA.setHostname(nom_OTA);              // Nom qui apparaîtra dans la liste des ports COM d'Arduino IDE, une fois ce programme chargé dans l'ESP32
  ArduinoOTA.setPassword(mot_de_passe_OTA);     // Mot de passe OTA (optionnel, car on aurait très bien pu ne pas en mettre, en fait)

  // Fonction OTA s'exécutant au démarrage de l'upload
  ArduinoOTA.onStart([]() {
    String type = (ArduinoOTA.getCommand() == U_FLASH) ? "sketch" : "filesystem";
    Serial.println("Début upload OTA : " + type);
  });

  // Fonction OTA s'exécutant à la fin de l'upload
  ArduinoOTA.onEnd([]() {
    Serial.println(""); Serial.println("OTA terminé ! Redémarrage...");
  });

  // Fonction OTA s'exécutant pendant l'upload
  ArduinoOTA.onProgress([](unsigned int progression, unsigned int total) {
    static int dernierPourcentage = -1;
    int pourcentage_d_avancement = (progression * 100) / total;
    if (pourcentage_d_avancement != dernierPourcentage && pourcentage_d_avancement % 10 == 0) {
      Serial.printf("Progression : %u%%\r", pourcentage_d_avancement);
      dernierPourcentage = pourcentage_d_avancement;
    }
  });

  // Fonction OTA s'exécutant lors d'une erreur
  ArduinoOTA.onError([](ota_error_t code_erreur) {
    Serial.printf("Erreur OTA[%u] : ", code_erreur);
    if (code_erreur == OTA_AUTH_ERROR) Serial.println("Échec d'authentification");
    else if (code_erreur == OTA_BEGIN_ERROR) Serial.println("Échec de démarrage");
    else if (code_erreur == OTA_CONNECT_ERROR) Serial.println("Échec de connexion");
    else if (code_erreur == OTA_RECEIVE_ERROR) Serial.println("Échec lors de la réception");
    else if (code_erreur == OTA_END_ERROR) Serial.println("Échec de fin OTA");
  });

  // -----------------------------------------------------------------------------------------------------------------
  // Démarrage de l'OTA
  // -----------------------------------------------------------------------------------------------------------------

  ArduinoOTA.begin();

  Serial.println("");
  Serial.println("----------");
  Serial.println("OTA prêt !");
  Serial.println("----------");
  Serial.println("");
  Serial.print("Remarque : ensuite, pour uploader un programme ESP32 via le WiFi, il faudra aller dans le menu 'Outils' d'Arduino IDE,\n");
  Serial.print("           et sélectionner le port COM nommé '"); Serial.print(nom_OTA); Serial.print(" at "); Serial.print(WiFi.localIP()); Serial.println("'");
  Serial.println("");

}


// =================
// Boucle principale
// =================
void loop() {

  // Maintien de l'OTA actif en permanence, pour gérer les uploads
  ArduinoOTA.handle();

  // Triple clignotement LED
  digitalWrite(BROCHE_LED, HIGH); delay(100);
  digitalWrite(BROCHE_LED, LOW); delay(200);

  digitalWrite(BROCHE_LED, HIGH); delay(100);
  digitalWrite(BROCHE_LED, LOW); delay(200);

  digitalWrite(BROCHE_LED, HIGH); delay(100);
  digitalWrite(BROCHE_LED, LOW); delay(200);

  // Pause avant rebouclage
  delay(1100);

}
