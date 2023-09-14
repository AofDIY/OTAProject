
#define URL_fw_Version "https://raw.githubusercontent.com/AofDIY/OTAProject/main/esp8266_ota/bin_version.txt"
#define URL_fw_Bin "https://raw.githubusercontent.com/AofDIY/OTAProject/main/esp8266_ota/fw.bin"

const char* hostFW = "raw.githubusercontent.com";
const int httpsPortFW = 443;

void FirmwareUpdate()
{  
  WiFiClientSecure client;
  client.setTrustAnchors(&cert);
  HTTPClient https; 
  if (!client.connect(hostFW, httpsPortFW)) {
    Serial.println("Connection failed");
    return;
  }
  client.print(String("GET ") + URL_fw_Version + " HTTP/1.1\r\n" +
               "Host: " + hostFW + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      //Serial.println("Headers received");
      break;
    }
  }

      if (https.begin(client, URL_fw_Version)) 
        {  // HTTPS

        Serial.print("[HTTPS] GET...\n");
        // start connection and send HTTP header
         int httpCode = https.GET();

      // httpCode will be negative on error
         if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        // file found at server
         if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          
 //=============================เช็คเวอร์ขั่นจากค่าที่เข้ามาผ่าน payload===================================================================================================================================
           String payload = https.getString();
           Serial.println("payload = " +payload);
           Serial.println("FirmwareVer = " +String(FirmwareVer));
             float payloadfloat = payload.toFloat();
         
           if(payloadfloat  == FirmwareVer)          //   เปลี่ยบเทียบ vertion
              {   
               Serial.println("Device already on latest firmware version"); 
             return;
              }
                else
                {
                    Serial.println("payload = "+payload);
                    Serial.println("New firmware detected");
                    ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW); 
                    t_httpUpdate_return ret = ESPhttpUpdate.update(client, URL_fw_Bin);
        
        switch (ret) {
         case HTTP_UPDATE_FAILED:
         Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        break;

       case HTTP_UPDATE_NO_UPDATES:
           Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;

       case HTTP_UPDATE_OK:
           Serial.println("HTTP_UPDATE_OK");
        break;
    } 
          
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    }
}
}
 void repeatedCall(){
    unsigned long currentMillis = millis();
    if ((currentMillis - previousMillis_3) >= interval) 
    {
      // save the last time you blinked the LED
      previousMillis_3 = currentMillis;
      setClock();
    //  FirmwareUpdate();
    }

    if ((currentMillis - previousMillis_2) >= mini_interval) {
      static int idle_counter=0;
      previousMillis_2 = currentMillis;    
      Serial.print(" Active fw version:");
      Serial.println(FirmwareVer);
      Serial.print("Idle Loop....");
      Serial.println(idle_counter++);
     if(idle_counter%2==0)
      digitalWrite(LED_BUILTIN, HIGH);
     else 
      digitalWrite(LED_BUILTIN, LOW);
     if(WiFi.status() == !WL_CONNECTED) 
        //  connect_wifi();
          check_Connect_WIFI();
   }
 }
