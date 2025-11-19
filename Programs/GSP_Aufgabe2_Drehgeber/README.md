Modulkonzept

 Modul          Aufgabe
 main.c         Loop (Direct Digital Control), Initialisierung aller Module
 encoder.c      Einlesen der Eingänge (A/B), Bestimmen der Phasen, Richtungs- und Fehlererkennung
 display.c      Steuerung der LCD-Ausgabe (Winkel, Geschwindigkeit, Statusmeldungen)
 led_control.c  Ausgabe an LEDs (D8–D15, D21–D23)
 timer.c        Zeitmessung und Berechnung der Zeitfenster
 error.c        Verwaltung von Fehlerzuständen und Rücksetzen per Taste S6
