# Handoff – aktueller Arbeitsstand

**Aktualisiert:** 21. Oktober 2026 · Branch `main`

## Aktuelles Ziel

Prototyp mit X + Dual-Z + einem Servo mechanisch fertig aufbauen und die erste Fachbildung per G-Code testen.

## Letzter Stand

- 21.10.2026: Erster Servo-Test mit L00m-Pattern am Gerät: `M280` läuft der X-Fahrt voraus (offener Punkt 8).
- 21.10.2026: Controller-Alternativen für X + Z1/Z2 mit Squaring, 1–6 Servos, WLAN, Neopixel, OLED und 1–2 Tastern
  recherchiert (nur Datenblätter, Schaltpläne und Quellcode, nichts am Gerät getestet). Wahrscheinlichster Weg:
  erst R4 per USB (A), dann ESP32-S3 als grblHAL-Host (C); Details unter „Controller-Recherche“.
- 19.10.2026: Muster-Generator in das eigene Repo
  [L00m-Pattern](https://github.com/DeRGiPsKoPf/L00m-Pattern) ausgelagert, mit Konzept (TypeScript-Offline-Web-App
  statt Python, `M0`-Pause pro Schuss, Recherche zu Taster/OLED/Neopixel unter grblHAL und FluidNC). `AGENTS.md`
  verweist jetzt dorthin.
- 19.10.2026: `Firmware/grblHAL-RP2040-fysetc-r4.patch` korrigiert: Die Ersatzwerte für die Homing-Geschwindigkeit
  pro Achse in `grbl/settings.c` standen innerhalb von `#if ENABLE_SPINDLE_LINEARIZATION`, ohne
  `machine_defaults.h` brach der Build ab. Getestet unter Windows (Arm GNU Toolchain 13.2.rel1, Pico SDK 2.1.1):
  alter und neuer Patch mit `machine_defaults.h` ergeben bytegleiche Firmware, ohne die Datei baut der neue Patch
  jetzt durch. Die `.uf2` im Repo bleibt daher unverändert gültig.
- 19.10.2026: Servo am Gerät bestätigt (`M280` funktioniert); Firmware-PDF Kapitel 9 und das Claude-Doc angepasst.
- 19.10.2026: `02 L00m Entwicklungsgenese.pdf` an den Stand angepasst: Status, TR8x8 als verbaute Spindel,
  grblHAL statt Klipper, X/Z statt X/Y, 12-V-/5-V-Schiene mit den Werten aus dem Schaltplan.
- 19.10.2026: Rendering `Bilder/L00m-Render.png` im README eingebunden.
- 19.10.2026: Repo angelegt mit README, AGENTS/CLAUDE, HANDOFF, LICENSE (GPL-3.0 / CERN-OHL-S-2.0 / CC BY-SA 4.0),
  STEP-Export als `CAD/L03m.step.zip`.

## Offene Baustellen

1. Mechanik-Aufbauanleitung schreiben (im Firmware-PDF angekündigt).
2. Weiter-Taster am Rahmen: Cycle-Start-Eingang im Patch belegen (derzeit `CONTROL_ENABLE` = 0; Kandidaten
   PROBE/GPIO25 oder Y-STOP/GPIO12). Gebraucht für die `M0`-Pause pro Schuss aus L00m-Pattern.
3. Schussfarbe an der Maschine anzeigen: Neopixel per `RGB_LED_ENABLE 2` und `M150` (Pin 29 ist im Patch
   vorgesehen; prüfen, ob das Plugin beim Stand `2f5bc4a` enthalten ist). Ein OLED bräuchte ein eigenes Plugin.
4. Sicherheitskonzept umsetzen: Not-Aus-Pilztaster in der 24-V-Leitung.
5. Servo-Versorgung für mehr als 1–2 Servos: separater 5-V-Wandler (MP1584EN / XL4016).
6. Für die PDFs vormerken: Entwicklungsgenese Kapitel 8 beschreibt noch einen Python-Generator; Ablauf in Kapitel 7
   um die `M0`-Pause und den Weiter-Taster ergänzen.
7. Nach dem Probelauf: ESP32-S3-Host als Prototyp am R4 (Option C unten). Erst klären, welche grblHAL-Schnittstelle
   der S3 nutzt (zweiter UART am R4 oder USB-Host) – davon hängt ab, ob GPIO0/1 für Servos frei bleiben.
8. **`M280` wartet nicht auf laufende Fahrten** (am Gerät in Zeitlupe gesehen, 21.10.2026; in den grblHAL-Quellen
   bestätigt): Das PWM-Servo-Plugin (`Plugins_misc/pwm_servo_m280.c`) setzt kein `user_mcode_sync`, der Servo
   schaltet also beim Einlesen, während X noch fährt. `G4` wartet auf den leeren Puffer (Bruchteile gehen,
   50-ms-Schritte). L00m-Pattern setzt deshalb `G4` nach jeder X-Fahrt. Offen: in der Entwicklungsgenese Kapitel 7
   (G-Code-Ablauf) und im Firmware-PDF ergänzen; prüfen, ob der L00m-Patch das Plugin auf Synchronisation umstellen
   soll (dann wäre der Ablauf ohne zusätzliches `G4` sicher).

## Bekannte Probleme

- **Verfahrweg X 100 mm** vs. Konzept bis 240 Kettfäden – vermutlich nur Prototyp-Breite, nicht geklärt.
- Tippfehler „Ausgansposition“ im G-Code-Beispiel der Entwicklungsgenese (Kapitel 7), noch nicht korrigiert (die
  Code-Schrift dort lässt sich nicht passgenau nachsetzen).

## Entscheidungen in der Schwebe

| Frage | Optionen | Stand |
|---|---|---|
| Fadenauswahl ab ~64 Fäden | Servos · Latching-Solenoide · Wähler-Haken nach CMU-Vorbild | offen, Prototyp mit Servo |
| Repo öffentlich machen | ja · privat lassen | privat |
| Mehrere Looms stapeln (bis 4 Fäden pro 2 mm) | je ein Controller pro Loom, Synchronisation offen | Idee |
| Firmware-Zukunft | A: R4 + Web Serial wie jetzt · C: R4/SKR Pico + ESP32-S3 als grblHAL-Host · D: FluidNC-Board hostet L00m-Pattern | **wahrscheinlichster Weg A → C** (Begründung unten); Klipper verworfen |

## Controller-Recherche (21.10.2026)

Ungeprüft am Gerät; Preise grob aus dem Gedächtnis. Gesucht: X + Z1/Z2 mit Squaring, 1–6 Servos, WLAN, Neopixel,
OLED, 1–2 Taster, billig und einfach nachzubauen, 5–10 Jahre Schulbetrieb.

**Weg A → C:**

- **A (jetzt):** R4 mit grblHAL, Web Serial per USB aus L00m-Pattern. Keine neue Hardware; damit den Probelauf
  fertig machen und Mechanik, Squaring und Servo-Takt klären.
- **C (Ziel):** ESP32-S3 als Host vor dem grblHAL-Controller. Der S3 liefert L00m-Pattern per WLAN aus, hält den Job
  und sendet ihn selbst (Tablet darf einschlafen), steuert OLED, Neopixel und Taster. Kein Betriebssystem, keine
  SD-Karte im System, sofort bereit. Zuerst am R4 (Patch bleibt), SKR Pico erst bei mehr als 2–4 Servos.
  - Hardware: ESP32-S3 SuperMini ~6 € (4 MB Flash, 512 KB SRAM; viele Varianten haben zusätzlich 2 MB PSRAM
    (ESP32-S3FH4R2) – beim Kauf prüfen). Reicht für Firmware mit WLAN/HTTP/WebSocket (~1,5 MB) und die Seite
    (`l00m.html` ~150 KB, gzip ~40 KB); OTA-Updates mit zwei App-Partitionen werden bei 4 MB eng. Große Jobs passen
    nicht ins RAM (`rauten-50.gcode` 66 KB, ein großes Gewebe mehrere MB) → microSD-Modul (SPI, ~1 €, 4 Pins) als
    Job- und Musterspeicher. Die SD ist dort nur Datenspeicher, nicht systemkritisch: Firmware startet aus dem
    Flash; fällt die Karte aus, gehen nur Archiv und große Jobs verloren. Pins: UART 2, I²C (OLED) 2, SPI (SD) 4,
    Neopixel 1, Taster 2 – passt.
  - R4 und SKR Pico haben **keinen SD-Slot**; den Controller-SD für den S3 mitzunutzen geht also nicht (wäre über
    grblHAL-YModem ohnehin langsam).
  - Aufwand: eigene S3-Firmware, geschätzt 1–2 Wochen Prototyp, ~1 Monat schulfest; Sende-Logik aus
    `L00m-Pattern/src/connection/grbl.ts` nach C++ portieren. In L00m-Pattern kommt ein Netz-Transport dazu
    (WebSocket zum S3, CSP `connect-src 'self'`). grblHAL-Grenzen bleiben (siehe unten).
- **D (Alternative):** FluidNC-Board hostet L00m-Pattern selbst. FluidNC v4 liefert Dateien aus dem Flash aus (mehrere
  UIs unter `/ui`), WebSocket auf `/`, `/command`, Upload per `/upload`/`/files`/WebDAV, `$SD/Run` arbeitet den Job
  selbst ab, `M0` geht. Wenig Programmierung (Vorlage mit `M67`, Upload/Start in L00m-Pattern), aber nur Boards mit
  freien GPIOs (6x CNC Controller, 6-Pack mit RC-Servo-Modul, S3 mit externen Treibern) – keine verlöteten TMC.
- **Verworfen:** Klipper mit Pi Zero 2 W/Orange Pi (hätte alles fertig, das R4 ist sogar dafür gebaut), weil die
  SD-Karte mit dem Betriebssystem in 5–10 Jahren ausfällt. Klipper-Host auf dem S3: nur Ansätze
  (`justinh-rahb/klipper-micro`: Protokoll und Uhrsync in C, aber keine Motoren/Homing), Monate Arbeit.
  FYSETC E4: kein freier GPIO für Servos (nur GPIO0 und die USB-Konsole RX0/TX0). MKS DLC32: Treiber fehlen,
  kaum Pins.

**FluidNC (v4.1.1):** Fertige Firmware nur für ESP32 und ESP32-S3; RP2040/RP2350 stehen im Quellcode, aber in keinem
Release. Dual-Z mit Squaring geht (`motor0`/`motor1` mit eigenem Endstop). Servos: bis 4 per `M67 E0–E3 Q<Prozent>`
bei 50 Hz plus Servos als Achsen A/B/C; kein `M280`, die Vorlage in L00m-Pattern müsste neu. Kein PCA9685-Treiber;
I²C-Extender (PCA9539/9535) nur ein/aus und im ESP32-Build abgeschaltet, Neopixel (Listener) ebenfalls. Der
UART-Expander (Airedale = STM32F103, Firmware offen in `bdring/PendantsForFluidNC/STM32_Expander`) kann PWM, aber nur
mit 1000 Stufen: bei 50 Hz bleiben 50 Stufen für 1–2 ms (~3,6° bei 180°). Servos brauchen echte GPIOs, die
I2S-Schieberegister-Ausgänge (DLC32, TinyBee) gehen nicht.

- **MKS DLC32 V2.1:** 3 Stepstick-Steckplätze, 3 Endstops – reicht für X + Z1/Z2. Treiber fehlen (+ ~10–15 €),
  TMC-UART vermutlich nicht verdrahtet (Strom per Poti), wenige freie GPIOs. Kostet am Ende etwa so viel wie der E4.
- **FYSETC E4:** 4× TMC2209 mit UART fest verlötet, 12–24 V, 3 Endstops, ESP32 mit WLAN; FluidNC-Config und
  grblHAL-Map vorhanden. Laut Pinbelegungen ist jeder brauchbare GPIO belegt → für L00m ungeeignet.

**S3-Host, Details:** UART zum Controller ist robuster als USB-Host. Fertige Firmware gibt es nicht (ESP3D 3.x:
Brücke mit OLED, USB-Host nur „geplant“).

**Servo-Pins laut Schaltplan** (MOSFET-, Thermistor- und Optokoppler-Pins fallen aus):

| Board | Sicher | Mit S3 über USB statt UART | Fraglich |
|---|---|---|---|
| R4 | GPIO22 (Laser, 3,3 V), GPIO29 (5V-RGB, 5-V-Puffer; dann Neopixel an den S3) | + GPIO0/1 (Pi-Header) | GPIO12 (Y-STOP, 10 kΩ in Reihe) |
| SKR Pico (~20–30 €, 4× TMC2209 UART, grblHAL-Map vorhanden) | GPIO29 (Servo-Header), GPIO20 (Laser; Spindel-PWM umlegen), GPIO3 (Y-STOP) und GPIO22 (Probe; je 100 Ω + 100 nF) | + GPIO0/1 (Pi-Header) | – |

R4: 2 Servos mit UART-Brücke, 4 mit USB. SKR Pico: 4 mit UART-Brücke, 6 mit USB, Neopixel (GPIO24) bleibt frei.
Achtung: GPIO29 am R4 ist auch für den Neopixel vorgesehen (Baustelle 3), GPIO12 Kandidat für den Weiter-Taster
(Baustelle 2) – nicht doppelt verplanen.

**grblHAL-Grenzen:** `M280` höchstens 4 Servos (`N_PWM_SERVOS` im Plugin auf 4 gekappt; anheben = Patch). Servo-Fix
und Board-Map bleiben eigener Patch pro Board. Kein PCA9685-Treiber (nur PCA9654E, ein/aus); ein eigener Treiber über
das Expander-Gerüst wäre möglich, I²C ginge am SKR Pico aber nur auf GPIO0/1 (Standard 26/27 = Thermistoren mit
100 nF). Lohnt erst bei vielen Servos (Fadenauswahl ab ~64 Fäden). Servos am S3 statt am Controller (Sync über
`G4 P0` → `ok`) wäre machbar, aber dann läuft der G-Code nicht mehr ohne den S3.
