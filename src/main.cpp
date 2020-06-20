#include <Arduino.h>
#include <SPI.h>
#include <SdFat.h>  // https://github.com/greiman/SdFat

SPIClass SPI_0(SPI0);
SdFat sd;

const uint8_t SD_CS = SS;   // chip select for sd

//------------------------------------------------------------------------------
// print error msg, any SD error codes, and halt.
// store messages in flash
#define errorExit(msg) errorHalt(F(msg))
#define initError(msg) initErrorHalt(F(msg))
//------------------------------------------------------------------------------

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println("SdFat_ListDir");

  if (!sd.begin(SS, SPISettings(20000000U, MSBFIRST, SPI_MODE0))) {
    sd.initError("sd:");
  }

  sd.ls(LS_DATE | LS_SIZE | LS_R);

  //File read
  Serial.println("");
  Serial.println("SdFat_Reading...maixpy.bin");

  int size = 0;
  uint8_t buff[1024];
  File f = sd.open("maixpy.bin", O_READ);
  while (f.available() > 0) {
    int bytes = f.readBytes(buff, 1024);
    size += bytes;
  }
  f.close();
  Serial.printf("total = %d\n", size);
}

void loop() {
  sleep(1);
}