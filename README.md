Arduino Smart Home Automation

Smart Home - siguranta, confort si economisire. 
Monitorizarea si controlul locuintei folosind platforma Arduino prin culegerea datelor de la senzori 
(anti-efractie, calitatea aerului, temperature, umiditate, consum energetic) si controlul la distanta (prin smartphone) 
a proceselor de climatizare si iluminat natural/artificial, etc.
	
  
  In linii mari, casa va include:
  
Siguranta: senzori de miscare

Confort: senzori de lumina ambientala; senzori pentru masurarea calitatii aerului; senzori de umiditate, 
temperatura; ridicare/coborare automata a roletelor, etc.

Economisire: pornire/oprire controlata a aerului conditionat/instalatiei de caldura; a iluminatului, 
masurare consum curent, etc.

Se va crea un site care va afisa informatii de interes din SmartHome si deasemenea va permite trasmiterea 
de comenzi spre elemente din casa. Va vom pune la dispozitie server pe care sa fie gazduit site-ul.
Ar fi interesant ca la final chiar sa se creeze casa fizic, din materiale elementare (carton, etc).




Required tools:

1. Arduino IDE https://www.arduino.cc/en/main/software
2. Atmel Studio https://www.microchip.com/mplab/avr-support/atmel-studio-7
3. CodeBlocks with MINGW http://www.codeblocks.org/downloads
4. Arduino Mega 2560 board.

After installing all tools, a configuration is required.
1. Connect board to PC via USB cable, start Arduino IDE and check what COM port is being used from "serial monitor". 
2. Settings -> Compiler -> Global Compiler Settings -> Compiler settings -> Select Compiler "GNU GCC Compiler for AVR"
3. Settings -> Compiler -> Global Compiler Settings -> Toolchain Executables -> Select the path for GNU GCC AVR compiler.
4. Right Click on project -> Build Options... -> Pre/post build steps -> "Change COM port number to the value from step 1"
