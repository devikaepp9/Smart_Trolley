#include <ESP8266WiFi.h>
#include <Wire.h>
// #include "FB_Firestore.h" 
// #include <ESP8266WiFi.h
#include <FirebaseESP8266.h>
#include "ArduinoJson.h"

#define FIREBASE_HOST "smtdemo-cdeb7-default-rtdb.firebaseio.com/"  //Without http:// or https:// schemes
#define FIREBASE_AUTH "BUhRhqqACWs67aOIwrqVJv0NUG5HmiaeX6xRIGyd"

const char ssid[] = "Devika";
const char pass[] = "bhagya123";

bool maggicard = false;
bool kitkatcard = false;
bool buttercard = false;
bool bourboncard = false;

String maggicardFirebase = "";
String buttercardFirebase = "";
String bourboncardFirebase = "";
String kitkatcardFirebase = "";

char card_no[12];

FirebaseData firebaseData;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\n connected!");
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  connect();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void checkaccess(String temp, String item, int price)  //Function to check if an identified tag is registered to allow access
{
  FirebaseJson json;
  json.add("id", temp);
  json.add("itemname", item);
  json.add("price", price);

  if (item == "Maggi") {
    if (Firebase.push(firebaseData, "/items", json)) {
      Serial.println(firebaseData.dataPath() + firebaseData.pushName() + item + " Added");
      Serial.println(firebaseData.pushName());
      maggicardFirebase = firebaseData.pushName();

    } else {
      Serial.println(firebaseData.errorReason());
    }
  }
  else if (item == "Bourbon") {
    if (Firebase.push(firebaseData, "/items", json)) {
      Serial.println(firebaseData.dataPath() + firebaseData.pushName() + item + " Added");
      Serial.println(firebaseData.pushName());
      bourboncardFirebase = firebaseData.pushName();

    } else {
      Serial.println(firebaseData.errorReason());
    }
  }
  else if (item == "Butter") {
    if (Firebase.push(firebaseData, "/items", json)) {
      Serial.println(firebaseData.dataPath() + firebaseData.pushName() + item + " Added");
      Serial.println(firebaseData.pushName());
      buttercardFirebase = firebaseData.pushName();

    } else {
      Serial.println(firebaseData.errorReason());
    }
  }
  else if (item == "Kitkat") {
    if (Firebase.push(firebaseData, "/items", json)) {
      Serial.println(firebaseData.dataPath() + firebaseData.pushName() + item + " Added");
      Serial.println(firebaseData.pushName());
      kitkatcardFirebase = firebaseData.pushName();

    } else {
      Serial.println(firebaseData.errorReason());
    }
  }
}

void removeaccess(String card) {
  String path = "/items/" + card;
  Firebase.deleteNode(firebaseData, path);
  if (firebaseData.dataAvailable()) {
    Serial.println("Document removed successfully");
  } else {
    Serial.println(firebaseData.errorReason());
  }
}

void loop() {
  if (Serial.available()) {
    int count = 0;
    // removeaccess();
    while (Serial.available() && count < 12) {
      card_no[count] = Serial.read();
      count++;
      delay(5);
    }
    if (count == 12) {
      if ((strncmp(card_no, "540079FEA97A", 12) == 0)) {
        if (!maggicard) {
          maggicard = true;
          checkaccess("540079FEA97A", "Maggi", 14);
        } else {
          removeaccess(maggicardFirebase);
          maggicard = false;
        }
      } else if ((strncmp(card_no, "54007A7897C1", 12) == 0)) {
        if (!bourboncard) {
          bourboncard = true;
          checkaccess("54007A7897C1", "Bourbon", 10);
        } else {
          removeaccess(bourboncardFirebase);
          bourboncard = false;
        }
      } else if ((strncmp(card_no, "54007A33001D", 12) == 0)) {
        if (!buttercard) {
          buttercard = true;
          checkaccess("54007A33001D", "Butter", 56);
        } else {
          removeaccess(buttercardFirebase);
          buttercard = false;
        }
      } else if ((strncmp(card_no, "540"07A681F59", 12) == 0)) {
        if (!kitkatcard) {
          kitkatcard = true;
          checkaccess("54007A681F59", "Kitkat, 25);
        } else {
          removeaccess(kitkatcardFirebase);
          kitkatcard = false;
        }
      }
    }
  }
}
