/*
   note for ampere per device
   ethernet shield = 180mA

  last edited by ILMI on :
  12th Aug 2021
*/
#include <Ethernet.h>
#include <PubSubClient.h>

long prevMillis;
#define delayLoop 100
#define deviceName "arduino01"
#define mqttUsername "openhabian"
#define mqttPassword "openhabian"
#define willQoS 0
#define statusTopic "arduino01/status"
#define willMessage "offline"
#define birthMessage "online"
#define willRetain true
#define birthRetain true

//---------------Konfigurasi ETHERNET-----------------
//mac address untuk ethernet shield, di edit dengan hexadecimal
byte mac[]    = {0x76, 0x98, 0xF1, 0x95, 0xC2, 0x8C};
//IP server MQTT raspberry Pi
byte server[] = {192, 168, 2, 100};
byte ip[] = {192, 168, 3, 99};

//Callback function header
void callback(char* topic, byte* payload, unsigned int length);

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

//#define pinLedServer 14
//---------------AKHIR Konfigurasi ETHERNET-----------------

//----------------Konfigurasi BUTTONs---------------
#define buttPin1 14
#define buttPin2 15
#define buttPin3 16
#define buttPin4 17
#define buttPin5 18
#define buttPin6 19

int buttValue1 = 0;
int buttValue2 = 0;
int buttValue3 = 0;
int buttValue4 = 0;
int buttValue5 = 0;
int buttValue6 = 0;

int buttState1 = 0;
int buttState2 = 0;
int buttState3 = 0;
int buttState4 = 0;
int buttState5 = 0;
int buttState6 = 0;
//----------------AKHIR Konfigurasi BUTTONs---------------

//----------------Konfigurasi RELAY---------------
#define pinRelay1  9
#define pinRelay2  8
#define pinRelay3  7
#define pinRelay4  6
#define pinRelay5  5 // jika menggunakan ethernet shield pin ini digunakan untuk pin Memory card
#define pinRelay6  4
#define pinRelay7  3
#define pinRelay8  2
//----------------AKHIR Konfigurasi RELAY---------------

void setup() {
  //Szerial.begin(9600);//initialize serial for debugging

  //konfigurasi ethernet shield
//  //Szerial.println("booting... wait 10s for network and server to be ready");
//  delay(10000);
  //for static ip
    Ethernet.begin(mac, ip);

//  while (Ethernet.begin(mac) == 0) { //remove "ip" if want to using DHCP
//    //Szerial.println("Failed to configure Ethernet using DHCP, retrying after 10 sec");
//    // no point in carrying on, so do nothing forevermore:
//    delay(10000);
//    //Szerial.println("trying to configure ethernet...");
//  }
  
// print your local IP address:
  //Szerial.print("IP:");
  //Szerial.println(Ethernet.localIP());
  
//  pinMode(pinLedServer, OUTPUT);

  pinMode(buttPin1, INPUT_PULLUP);
  pinMode(buttPin2, INPUT_PULLUP);
  pinMode(buttPin3, INPUT_PULLUP);
  pinMode(buttPin4, INPUT_PULLUP);
  pinMode(buttPin5, INPUT_PULLUP);
  pinMode(buttPin6, INPUT_PULLUP);
  
  pinMode(pinRelay1, OUTPUT);
  pinMode(pinRelay2, OUTPUT);
  pinMode(pinRelay3, OUTPUT);
  pinMode(pinRelay4, OUTPUT);
  pinMode(pinRelay5, OUTPUT);
  pinMode(pinRelay6, OUTPUT);
  pinMode(pinRelay7, OUTPUT);
  pinMode(pinRelay8, OUTPUT);
  
  //inisialisasi relay off ketika booting
  digitalWrite(pinRelay1, HIGH);
  digitalWrite(pinRelay2, HIGH);
  digitalWrite(pinRelay3, HIGH);
  digitalWrite(pinRelay4, HIGH);
  digitalWrite(pinRelay5, HIGH);
  digitalWrite(pinRelay6, HIGH);
  digitalWrite(pinRelay7, HIGH);
  digitalWrite(pinRelay8, HIGH);

//  reconnect();
//  delay(200);

  //  publish status all relay OFF to server
//  client.publish("arduino01/relay1/state", "OFF");
//  delay(200);
//  client.publish("arduino01/relay2/state", "OFF");
//  delay(200);
//  client.publish("arduino01/relay3/state", "OFF");
//  delay(200);
//  client.publish("arduino01/relay4/state", "OFF");
//  delay(200);
//  client.publish("arduino01/relay5/state", "OFF");
//  delay(200);
//  client.publish("arduino01/relay6/state", "OFF");
//  delay(200);
//  client.publish("arduino01/relay7/state", "OFF");
//  delay(200);
//  client.publish("arduino01/relay8/state", "OFF");

  prevMillis = millis();
  
}

void loop() {
  //trying to connect to server, when disconnected
  if (!client.connected())
  {
//    digitalWrite(pinLedServer, LOW);
    reconnect();
  }

//  digitalWrite(pinLedServer, HIGH);

  if (millis() - prevMillis > delayLoop) {

    //    sensorFlame();
    pressButt();
  
    prevMillis = millis();
  }


  client.loop();
}

void pressButt(){
  buttValue1 = digitalRead(buttPin1);
  if (buttValue1 == LOW && buttState1 == 0) {//if pressed
    digitalWrite(pinRelay3, LOW);
    buttState1 = 1;
    //hati-hati ini nge-link ke void callback
    delay(100);
    client.publish("arduino01/relay3/state", "ON");
  } else if (buttValue1 == LOW && buttState1 == 1) {
    digitalWrite(pinRelay3, HIGH);
    buttState1 = 0;
    //hati-hati ini nge-link ke void callback
    delay(100);
    client.publish("arduino01/relay3/state", "OFF");
  }
  
  buttValue2 = digitalRead(buttPin2);
  if (buttValue2 == LOW && buttState2 == 0) {//if pressed
    digitalWrite(pinRelay4, LOW);
    buttState2 = 1;
    //hati-hati ini nge-link ke void callback
    delay(100);
    client.publish("arduino01/relay4/state", "ON");
  } else if (buttValue2 == LOW && buttState2 == 1) {
    digitalWrite(pinRelay4, HIGH);
    buttState2 = 0;
    //hati-hati ini nge-link ke void callback
    delay(100);
    client.publish("arduino01/relay4/state", "OFF");
  }
  
  buttValue3 = digitalRead(buttPin3);
  if (buttValue3 == LOW && buttState3 == 0) {//if pressed
    digitalWrite(pinRelay6, LOW);
    buttState3 = 1;
    //hati-hati ini nge-link ke void callback
    delay(100);
    client.publish("arduino01/relay6/state", "ON");
  } else if (buttValue3 == LOW && buttState3 == 1) {
    digitalWrite(pinRelay6, HIGH);
    buttState3 = 0;
    //hati-hati ini nge-link ke void callback
    delay(100);
    client.publish("arduino01/relay6/state", "OFF");
  }
  
  buttValue4 = digitalRead(buttPin4);
  if (buttValue4 == LOW && buttState4 == 0) {//if pressed
    digitalWrite(pinRelay5, LOW);
    buttState4 = 1;
    //hati-hati ini nge-link ke void callback
    delay(100);
    client.publish("arduino01/relay5/state", "ON");
  } else if (buttValue4 == LOW && buttState4 == 1) {
    digitalWrite(pinRelay5, HIGH);
    buttState4 = 0;
    //hati-hati ini nge-link ke void callback
    delay(100);
    client.publish("arduino01/relay5/state", "OFF");
  }
  
  buttValue5 = digitalRead(buttPin5);
  if (buttValue5 == LOW && buttState5 == 0) {//if pressed
    digitalWrite(pinRelay2, LOW);
    buttState5 = 1;
    //hati-hati ini nge-link ke void callback
    delay(100);
    client.publish("arduino01/relay2/state", "ON");
  } else if (buttValue5 == LOW && buttState5 == 1) {
    digitalWrite(pinRelay2, HIGH);
    buttState5 = 0;
    //hati-hati ini nge-link ke void callback
    delay(100);
    client.publish("arduino01/relay2/state", "OFF");
  }

  
  buttValue6 = digitalRead(buttPin6);
  if (buttValue6 == LOW && buttState6 == 0) {//if pressed
    digitalWrite(pinRelay1, LOW);
    buttState6 = 1;
    //hati-hati ini nge-link ke void callback
    delay(100);
    client.publish("arduino01/relay1/state", "ON");
  } else if (buttValue6 == LOW && buttState6 == 1) {
    digitalWrite(pinRelay1, HIGH);
    buttState6 = 0;
    //hati-hati ini nge-link ke void callback
    delay(100);
    client.publish("arduino01/relay1/state", "OFF");
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    //Szerial.print("Attempting MQTT connection...");

    // Create a random client ID
    //    String clientId = "lens_5kchta2dWhdRS2AQz0TeTuhplPE"; // membuat nama clientId random, jadi tidak pakai nama "arduinoclient" lagi
    //    clientId += String(random(0xffff), HEX);

    // Attempt to connect
    //    if (client.connect(clientId.c_str(),"openhabian", "password")) { // ini code jika ingin pakai password mqtt

    if (client.connect(deviceName , mqttUsername, mqttPassword, statusTopic, willQoS, willRetain, willMessage )) {
      //Szerial.println("connected");
      // print your local IP address:
      //      //Szerial.print("IP:");
      //      //Szerial.println(Ethernet.localIP());
      // Once connected, publish an announcement...
      client.publish(statusTopic, birthMessage, birthRetain );
      // ... and resubscribe
      client.subscribe("arduino01/#");
    } else {
      //Szerial.print("failed, rc=");
      //Szerial.print(client.state());
      //Szerial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  //Szerial.print("#Callback,");
  //Szerial.print(" Topic:");
  //Szerial.print(topic);
  //Szerial.print(", Length:");
  //Szerial.print(length);
  //Szerial.print(", Payload:");
  //Szerial.write(payload, length);
  //Szerial.println();



  // ini adalah algoritma untuk relay1
  if (strcmp(topic, "arduino01/relay1/com") == 0) {
    if (payload[1] == 'F') {
      digitalWrite(pinRelay1, HIGH);
      delay(100);
      client.publish("arduino01/relay1/state", "OFF");
      buttState6 = 0; //hati-hati ini nge-link dengan void pressButt
    } else if (payload[1] == 'N') {
      digitalWrite(pinRelay1, LOW);
      delay(100);
      client.publish("arduino01/relay1/state", "ON");
      buttState6 = 1; //hati-hati ini nge-link dengan void pressButt
    }
  }

  // ini adalah algoritma untuk relay2
  if (strcmp(topic, "arduino01/relay2/com") == 0) {
    if (payload[1] == 'F') {
      digitalWrite(pinRelay2, HIGH);
      delay(100);
      client.publish("arduino01/relay2/state", "OFF");
      buttState5 = 0; //hati-hati ini nge-link dengan void pressButt
    } else if (payload[1] == 'N') {
      digitalWrite(pinRelay2, LOW);
      delay(100);
      client.publish("arduino01/relay2/state", "ON");
      buttState5 = 1; //hati-hati ini nge-link dengan void pressButt
    }
  }

  // ini adalah algoritma untuk relay3
  if (strcmp(topic, "arduino01/relay3/com") == 0) {
    if (payload[1] == 'F') {
      digitalWrite(pinRelay3, HIGH);
      delay(100);
      client.publish("arduino01/relay3/state", "OFF");
      buttState1 = 0; //hati-hati ini nge-link dengan void pressButt
    } else if (payload[1] == 'N') {
      digitalWrite(pinRelay3, LOW);
      delay(100);
      client.publish("arduino01/relay3/state", "ON");
      buttState1 = 1; //hati-hati ini nge-link dengan void pressButt
    }
  }

  // ini adalah algoritma untuk relay4
  if (strcmp(topic, "arduino01/relay4/com") == 0) {
    if (payload[1] == 'F') {
      digitalWrite(pinRelay4, HIGH);
      delay(100);
      client.publish("arduino01/relay4/state", "OFF");
      buttState2 = 0; //hati-hati ini nge-link dengan void pressButt
    } else if (payload[1] == 'N') {
      digitalWrite(pinRelay4, LOW);
      delay(100);
      client.publish("arduino01/relay4/state", "ON");
      buttState2 = 1; //hati-hati ini nge-link dengan void pressButt
    }
  }

  // ini adalah algoritma untuk relay5
  if (strcmp(topic, "arduino01/relay5/com") == 0) {
    if (payload[1] == 'F') {
      digitalWrite(pinRelay5, HIGH);
      delay(100);
      client.publish("arduino01/relay5/state", "OFF");
      buttState4 = 0; //hati-hati ini nge-link dengan void pressButt
    } else if (payload[1] == 'N') {
      digitalWrite(pinRelay5, LOW);
      delay(100);
      client.publish("arduino01/relay5/state", "ON");
      buttState4 = 1; //hati-hati ini nge-link dengan void pressButt
    }
  }

  // ini adalah algoritma untuk relay6
  if (strcmp(topic, "arduino01/relay6/com") == 0) {
    if (payload[1] == 'F') {
      digitalWrite(pinRelay6, HIGH);
      delay(100);
      client.publish("arduino01/relay6/state", "OFF");
      buttState3 = 0; //hati-hati ini nge-link dengan void pressButt
    } else if (payload[1] == 'N') {
      digitalWrite(pinRelay6, LOW);
      delay(100);
      client.publish("arduino01/relay6/state", "ON");
      buttState3 = 1; //hati-hati ini nge-link dengan void pressButt
    }
  }

  // ini adalah algoritma untuk relay7
  if (strcmp(topic, "arduino01/relay7/com") == 0) {
    if (payload[1] == 'F') {
      digitalWrite(pinRelay7, HIGH);
      delay(100);
      client.publish("arduino01/relay7/state", "OFF");
    } else if (payload[1] == 'N') {
      digitalWrite(pinRelay7, LOW);
      delay(100);
      client.publish("arduino01/relay7/state", "ON");
    }
  }

  if (strcmp(topic, "arduino01/relay8/com") == 0) {
    if (payload[1] == 'F') {
      //      overide = true;
      digitalWrite(pinRelay8, HIGH);
      delay(100);
      client.publish("arduino01/relay8/state", "OFF");
    } else if (payload[1] == 'N') {
      //      overide = false;
      digitalWrite(pinRelay8, LOW);
      delay(100);
      client.publish("arduino01/relay8/state", "ON");
    }
  }

}
