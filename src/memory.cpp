#include "memory.hpp"

// custom pins for the SPI communication
int sck = 18;
int miso = 19;
int mosi = 23;
int cs = 2;

const char *healP = "/heal.mp3";
const char *attackP = "/attack.mp3";

void listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root)
  {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory())
  {
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file)
  {
    if (file.isDirectory())
    {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels)
      {
        listDir(fs, file.path(), levels - 1);
      }
    }
    else
    {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void readFile(fs::FS &fs, const char *path)
{
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file)
  {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while (file.available())
  {
    Serial.write(file.read());
  }
  Serial.println("Ende");
  file.close();
}

void setupMemory()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(10);
  }

  SPI.begin(sck, miso, mosi, cs);

  if (!SD.begin())
  {
    Serial.println("Card Mount Failed");
    return;
  }

  listDir(SD, "/", 0);
  // readFile(SD, healP);
  // readFile(SD, attackP);
  Serial.println("END");
}