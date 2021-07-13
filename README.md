# comunicacion bidireccional arduino a raspberry
//Habilitamos SPI Y I2C
sudo raspi-config
advanced options----> SPI OK ---->I2C OK

***************************************************
sudo apt/get install python-dev python3-dev -y
wget https://github.com/Gadgetoid/py-spidev/archive/master.zip
unzip master.zip
ls
rm master.zip
cd py-spidev-master/
sudo python3 setup.py install
cd desktop
cd
cd desktop/
cd Desktop/
ls
mkdir NRF24L01
cd NRF24L01/
git clone https://github.com/BLavery/lib_nrf24
cd lib_nrf24/
ls
cp lib_nrf24.py ~/Desktop/NRF24L01/
cd
cd Desktop
git clone https://github.com/tmrh20/RF24

Conexión de Arduino con NRF24L01+
VCC:                        3.3v
GND                         GND
CSN                         Digital 10
CE                          Digital 9
MOSI                        Digital 11
MISO                        Digital 12
SCK                         Digital 13 

Conexión de Raspberry  con NRF24L01+
VCC:                        3.3v                          1
GND                         GND                           6
CSN                         GPIO 8                        24
CE                          GPIO 17                       11
MOSI                        GPIO 10                       19
MISO                        GPIO 9                        21
SCK                         GPIO 23                       23

// Aplicativo thingspeak
https://thingspeak.com/channels/1441287
