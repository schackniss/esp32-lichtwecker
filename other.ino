//convert bool array[7] to uint8_t; useful for saving wecker.weekdays[] to EEPROM
uint8_t arrayToInt(boolean array[7])  {
  uint8_t x = 0;
  for (int i = 0; i < 7; i++) {
    if (array[i]) x+= pow(2, i);
  }
  return x;
}

//convert uint8_t to bool array[7]; useful for reading wecker.weekdays[] from EEPROM
void intToArray(uint8_t x, boolean *array)  {
  for (int i = 0; i < 7; i++) {
    array[i] = x % 2;
    x /= 2;
  }
}
