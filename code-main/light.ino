//set light of LED panel to passed over values
void setLight(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUMPIXELS; i++) pixels.setPixelColor(i, pixels.Color(r, g, b));
  pixels.show();
}

//set light of LED panel to configured values
void setLight() {
  if (licht)  setLight(red, green, blue);
  if (!licht) {
    pixels.clear();
    pixels.show();
  }
}
