# Hardware-Aufbau

## Arduino
* 1 x Arduino Yún
	* https://www.flikto.de/products/arduino-yun
* 1 x Arduino YUN Housing Housing Transparent Clear computer box
	* http://www.amazon.de/dp/B00HFT4190
	* http://www.sbcshop.co.uk/arduino-yun-protective-case-clear-154-p.asp
* 1 x Aukey Power Bank 20.000mAh *oder* VOLTCRAFT Solarlader SL-3 0.7 W/ 140 mA (mc-Si) 4180c3 Powerbank Solar SL-3 5 V
 * http://www.amazon.de/dp/B00RJKBCM4
 * https://www.conrad.de/de/voltcraft-solarlader-sl-3-07-w-140-ma-mc-si-4180c3-powerbank-solar-sl-3-5-v-1226996.html

## Shield
*  1 x Arduino ProtoShield Revision 3 assembled
	* https://www.flikto.de/products/arduino-proto-shield-assembled
	* https://www.arduino.cc/en/Main/ArduinoProtoShield
* 1 x LED bedrahtet Rot 3 mm oder 5mm (weißer Korpus)
	* Bsp.: https://www.conrad.de/de/led-bedrahtet-rot-rund-5-mm-320-mcd-9-30-ma-19-v-vishay-tlhk-5100-184283.html
* 1 x LED bedrahtet Blau 3mm oder 5mm (weißer Korpus)
  * Bsp.: https://www.conrad.de/de/led-bedrahtet-blau-rund-5-mm-380-mcd-4-20-ma-39-v-vishay-tlhb-5800-184297.html
* 2 x Transitor BC546
	* https://www.conrad.de/de/bipolar-standard-leistungstransistor-diotec-bc546b-npn-gehaeuseart-to-92-i-c-200-ma-emitter-sperrspannung-u-ceo-65-v-155004.html
* 1 x Platinensteckverbinder-Set 5-polig
 	* Umfang: 2 Stiftleisten + 2 Buchsenleisten (inkl. Kabel).
	* http://www.voelkner.de/products/56366/Platinen-Steckverbinder-Set-5-polig.html
	* https://www.conrad.de/de/stiftleiste-standard-cis-15550-1-set-743135.html
* 2 x 39 Ohm Metallschicht-Widerstand 1% 0.6W
	* https://www.conrad.de/de/metallschicht-widerstand-39-axial-bedrahtet-0207-06-w-yageo-mf0207fte52-39r-1-st-1417703.html
* 2 x 360 Ohm Metallschicht-Widerstand 1% 0.6W
	* https://www.conrad.de/de/metallschicht-widerstand-360-axial-bedrahtet-0207-06-w-1-st-420689.html
* 2 x 820 Ohm Metallschicht-Widerstand 1% 0.6W
	* https://www.conrad.de/de/metallschicht-widerstand-820-axial-bedrahtet-0207-06-w-yageo-mf0207fte52-820r-1-st-1417734.html
* 2 x 470 kOhm Metallschicht-Widerstand 1% 0.6W
	* https://www.conrad.de/de/metallschicht-widerstand-470-k-axial-bedrahtet-0207-06-w-yageo-mf0207fte52-470k-1-st-1417688.html
* 1 x Kupferdraht Verzinnt 1 x 0.6 mm 40 m
	* https://www.conrad.de/de/kupferdraht-verzinnt-1-x-06-mm-conrad-151500640-40-m-607499.html

## Verkabelung
* 2 x Phototransistor Osram SFH313FA
 * http://www.rs-online-privat.de/Products/ProductDetail/2e23eb55-78a7-4382-ad4e-c15fc1f4cc39
 * http://www.osram-os.com/osram_os/en/products/product-catalog/infrared-emitters%2c-detectors-andsensors/silicon-photodetectors/phototransistors/phototransistors-in-plastic-package/sfh-313-fa/index.jsp
* 2 x IR-Diode Osram SFH4544
	* http://www.rs-online-privat.de/Products/ProductDetail/f3970fa4-c576-4cc7-b5be-0425a9f449ac
	* http://www.osram-os.com/osram_os/en/products/product-catalog/infrared-emitters,-detectors-andsensors/infrared-emitters/power-emitter-gt40mw/emitter-with-940-nm/sfh-4544/index.jsp
* 4 x LED-Fassung Metall mit Innenreflektor
 * https://www.conrad.de/de/led-fassung-metall-passend-fuer-led-5-mm-schraubbefestigung-signal-construct-smz1089-185957.html
* 1 x Zwillingslitze 0.14mm<sup>2</sup> rot/schwarz

## Allgemein
* 1 x Lötzinn 1.0mm (bleihaltig, da einfacher zum Löten)
* 1 x Lötstation
* 1 x Platinenhalter (Dritte Hand 3-teilig)
* 1 x Multimeter zur Überprüfung der Elektronik (z.B. kalte Lötstellen)

# Hardware Mess-Verfahren

Nach Anbringen des Proto-Shields auf dem Arduino Yún und Anbringung der Verkabelung mit den dafür vorgesehenen Platinen-Steckverbindern kann eine Messung durchgeführt werden.

## Messung LEDs
Es müssen zwischen PIN 3/PIN 5 und GND ca. 5 V abfallen, sobald auf PIN 3/PIN 5 der OUTPUT auf HIGH gesetzt wird. Wenn dies nicht der Fall ist, dann ist vermutlich eine Lötstelle kalt. Eine kalte Lötstelle ist oft optisch matt und lässt sich durch Messen finden, indem man sich die Leiterbahn entlanghangelt bis zur Masse (GND). Der Punkt ab dem keine Spannung mehr anliegt ist dann das Problem.

## Messung Lichtschranken
Bei Lichtstrom (geschlossene Lichtschranke mit ca. 2 cm Abstand) muss eine Spannung gemessen mit einem Multimeter von ca. ca. 4,7V - 5V abfallen. Der Multimeter-Pluspol muss dabei an die Kathode des Fototransistors (kurzer Anschluss des Fototransistors) und vor dem 39 Ohm Widerstand angeschlossen werden. Der Multimeter-Minuspol muss an GND des Arduino angeschlossen werden. Bei einer unterbrochenen Lichtschranke müsste dieser Wert auf 0.01V - 0.10 V absinken (z.B. durch Unterbrechung mit Hand). Dabei ist darauf zu achten, welche Lichtschranke gerade angeschlossen ist und gemessen wird. Wenn die Spannung nicht abfällt, dann wird vermutlich eine kalte Lötstelle oder ein Kurzschluss die Ursache sein.
Die Spannung kann bei einer bestückten Platine auch zwischen PIN 11 (Lichtschranke Tor 1) und GND oder zwischen PIN 8 (Lichtschranke 2) und GND gemessen werden.
