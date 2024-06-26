void Wifi_Reset_begin() {
  long previousMillis_reset = 0;
  long interval_reset = 10000;
  currentState = digitalRead(RESET_PIN);
  if (lastState == HIGH && currentState == LOW) {
    Serial.println("Wifi Reset? Pls. waiting 30S..");
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    // Display static text
    display.println("Wifi Reset? Pls. waiting 30S.. ");
    display.setCursor(30, 0);
    display.display();
    // Display static text
    delay(15000);

    Serial.println("WiFi Reset Settings....OK!.");
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    display.println("Connect FIWI config.. ");
    display.setCursor(30, 20);
    display.println("Temperature CHG.. ");
    display.display();
    delay(15000);
    // คำสั่ง รีเซตค่า
    WiFiManager wm;
    wm.resetSettings();
    ESP.eraseConfig();
    SPIFFS.format();
    delay(3000);
    ESP.restart();
    // delay(3000);

    Serial.println(" reset succes ...");


  }
  else if (lastState == LOW && currentState == HIGH) {
    Serial.println("The button is released");
  }
  // save the the last state
  lastState = currentState;

}
