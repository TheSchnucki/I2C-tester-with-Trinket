/*
 * Valve board test Programm. To test Valveboards for RCONT8 with anAdafruit Trinket (5V).
 * Additional to the USB connection 24V DC are needed to power the valveboard.
 * 
 * Pin connections
 * #0 SDA (RD)    #2 SCL (YL)
 * 5VUSB (OR)&(BN)
 * GND (GN)
 * 
 * Other wires of the 10-wire bus cable
 * 24V+ (BK) & (WT)
 * GND (GY)&(BL)&(VT)
 * 
 * Additional to that a pullup resistor (4k7) is necessary from #0 to 5V and from #2 to 5V
 * 
 */

 #include <TinyWireM.h>

 byte address = 39;                                    //Adresse of the PCF 8574
 byte addressA = 63;                                   //Adresse of the PCF 8574A
 byte valve[7] = {126, 125, 123, 119, 111, 95, 63} ;   //Adresses of the individual Valves inverted
 int timer = 50;                                        // the time each state is shown
 int led = 1;                                           // blink 'digital' pin 1 - AKA the built in red LED

void setup() {
    pinMode(led, OUTPUT);
    TinyWireM.begin();                                 // join i2c bus
}

void loop() {
  for (int i=0; i<=6; i++) {
    int j = (sizeof(valve)/sizeof(byte))-i-1;
    TinyWireM.beginTransmission(address);           // transmit to device specified in adress
    TinyWireM.write(valve[i]);                        // sends value byte 
    TinyWireM.endTransmission();
    TinyWireM.beginTransmission(addressA);          // transmit to device specified in adress
    TinyWireM.write(valve[j]);                       // sends value byte 
    TinyWireM.endTransmission();

    digitalWrite(led, HIGH); 
    delay(timer);
    digitalWrite(led, LOW);
    delay(timer);
  }
}
