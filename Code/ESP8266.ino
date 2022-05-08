
#include<ESP8266WebServer.h>
#include<ESP8266WiFi.h>


//----Web server--------------------
ESP8266WebServer ServerWeb(80);
//------------Page Html--------------------------
const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Wasser</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Libre+Bodoni:ital@0;1&family=Nunito&display=swap" rel="stylesheet">


    <style>

.titre{
    font-size: 50px;
    font-family: 'Nunito', sans-serif;
    color: #143F6B;
    margin: 10px;
    
}
body{
    text-align: center;
    background-color: #E3FDFD;
    ;
}

.inpt{
    width: 130px;
    height: 70px;
    position: absolute;
    left: 10px;
}
h2{
    font-family: 'Nunito', sans-serif;
    color: #251D3A;
    font-size:18px;
}

.zone1{
    left: 10px;
    background-color: #82A284;
    width: 300px;
    padding: 20px;
    display: inline-block;
    margin: 200px 40px 0 40px;
}

.h{
    color: #383838;
}


.btn{
    border-style:none;
    border-radius: 5px;
    border-width: 2px;
    background: linear-gradient(#4FD3C4, #247881);
    color: #E3FDFD;
    padding: 10px;
    text-decoration: none;
}
.zone2{
    position: relative;
    left: 10px;
    background-color: #82A284;
    width: 300px;
    padding: 20px;

    display: inline-block;
    margin: 200px 40px 0 40px;
}

.btn:hover{
    opacity: 0.9;
}
    </style>
    
</head>
<body>
    <img  class="inpt" src="https://upload.wikimedia.org/wikipedia/commons/9/9a/Logo_inpt.PNG" alt="">
    <h1 class="titre">Systeme d'arrosage automatique</h1>
    <div class="zone1">
            <h1 class="h">Zone 1</h1>
            
            <button class="btn" onclick="appelServeur('/switchPin1On', traiteReponse)">Demarer le systeme</button>
            <button class="btn" onclick="appelServeur('/switchPin1Off', traiteReponse)">Arréter le systeme</button>
            <h3 class="etatsys">L'etat du systeme</h3>
            <h2  id= "EtatPin1">STATUS :</h2>
    </div>
    <div class="zone2">
            <h1 class="h">Zone 2</h1>
            
            <button class="btn" onclick="appelServeur('/switchPin2On', traiteReponse)">Demarer le systeme</button>
            <button class="btn" onclick="appelServeur('/switchPin2Off', traiteReponse)">Arréter le systeme</button>
            <h3 class="etatsys">L'etat du systeme</h3>
            <h2  id= "EtatPin2">STATUS :</h2>
    </div>
    <div class="zone2">
        <h1 class="h">Zone 3</h1>
        
        <button class="btn" onclick="appelServeur('/switchPin3On', traiteReponse)">Demarer le systeme</button>
        <button class="btn" onclick="appelServeur('/switchPin3Off', traiteReponse)">Arréter le systeme</button>
        <h3 class="etatsys">L'etat du systeme</h3>
        <h2  id= "EtatPin3">STATUS :</h2>
    </div>
    
    




    <script> 
        function appelServeur(url, cFonction){
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function(){
                if(this.readyState == 4 && this.status == 200){
                   cFonction(this); 
                }
            };
            xhttp.open("GET", url, true)
            xhttp.send();
        }
        function traiteReponse(xhttp){
            document.getElementById("EtatPin1").innerHTML = "  " + xhttp.responseText;
            //document.getElementById("EtatPin2").innerHTML = "  " + xhttp.responseText;
            //document.getElementById("EtatPin3").innerHTML = "  " + xhttp.responseText;
        }
       </script>
     

    
</body>
</html>
)=====";
//----------Définition des entrées/sortie---------
#define PINLED1 D1
#define PINLED2 D2
#define PINLED3 D3
#define PINLED4 D4
bool Control4 = false ;
//-----------Information de conexion----------------------
const char * ssid ="Fahym";
const char * password = "fahym8237";

//----Gestion des evenement---------
void onConnected(const WiFiEventStationModeConnected & event);
void onGotIP(const WiFiEventStationModeGotIP & event);
//------les fonction du server webe-------------------
void switchPin1On(){
  digitalWrite(PINLED2,HIGH);
  ServerWeb.send(200,"text/plain","ON");
}
void switchPin1Off(){
  digitalWrite(PINLED2,LOW);
  ServerWeb.send(200,"text/plain","OFF");
}

void switchPin2On(){
  digitalWrite(PINLED3,HIGH);
  ServerWeb.send(200,"text/plain","ON");
}
void switchPin2Off(){
  digitalWrite(PINLED3,LOW);
  ServerWeb.send(200,"text/plain","OFF");
}

void switchPin3On(){
  digitalWrite(PINLED4,HIGH);
 // ServerWeb.send(200,"text/plain","ON");
}
void switchPin3Off(){
  digitalWrite(PINLED4,LOW);
  //ServerWeb.send(200,"text/plain","OFF");
}


void handleRoot(){
  String temp(reinterpret_cast<const __FlashStringHelper *>(index_html));
  ServerWeb.send(200,"text/html",temp);
}


void setup() {
  //----------------------Mise en place d'une liaison série-------------------
  Serial.begin(57600);
  Serial.println("  ");
  //---------Mode de conexion------------------
  WiFi.mode(WIFI_STA);

  //WiFi.softAP("Projet0");
  //------------Démarage de la conexion---------------------
  WiFi.begin(ssid,password);
  static WiFiEventHandler onConnectedHandler = WiFi.onStationModeConnected(onConnected);
  static WiFiEventHandler onGotIPHandler = WiFi.onStationModeGotIP(onGotIP);
  
  //Etat initiale des variabeles----------------
  pinMode(PINLED1,OUTPUT);
  pinMode(PINLED2,OUTPUT);
  pinMode(PINLED3,OUTPUT);
  pinMode(PINLED4,OUTPUT);
//-------Mise en place du server web---------------
  ServerWeb.on("/switchPin1On",switchPin1On );
  ServerWeb.on("/switchPin1Off",switchPin1Off );
  ServerWeb.on("/switchPin2On",switchPin2On );
  ServerWeb.on("/switchPin2Off",switchPin2Off );
  ServerWeb.on("/switchPin3On",switchPin3On );
  ServerWeb.on("/switchPin3Off",switchPin3Off );
  ServerWeb.on("/",handleRoot );
  ServerWeb.on("/index_html",handleRoot);
  
  ServerWeb.begin();
  


 
}

void loop() {
  if(WiFi.isConnected()){
    digitalWrite(PINLED1,HIGH);
    ServerWeb.handleClient();
    delay(800);
    digitalWrite(PINLED1,LOW);
    ServerWeb.handleClient();
    delay(800);
  }
  else{
    digitalWrite(PINLED1,LOW);
  }
 


  
}


 void onConnected(const WiFiEventStationModeConnected & event){
    Serial.println(" WiFi Connecté ");
  }
 void onGotIP(const WiFiEventStationModeGotIP & event){
    Serial.println(" Adresse IP : " + WiFi.localIP().toString());
    Serial.println(" Passrelle IP : " + WiFi.gatewayIP().toString());
    Serial.println(" DNS IP : " + WiFi.dnsIP().toString());
    Serial.print(" Puissance de réception : " );
    Serial.print(WiFi.RSSI() );
  }
