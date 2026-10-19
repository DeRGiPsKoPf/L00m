# AGENTS.md – Projektkontext L00m

Dauerhaftes Nachschlagewerk für alle, die an diesem Repo arbeiten (Menschen und KI-Agenten). Der aktuelle
Arbeitsstand steht in `HANDOFF.md`, nicht hier.

## Projektüberblick

L00m ist ein computergesteuerter Jacquard-Webstuhl im Eigenbau für den Schul- und Kunstbetrieb (5–10 Jahre
Einsatz). Ein Servo auf einem X-Schlitten wählt Kettfäden einzeln aus, ein Dual-Z-Hub hebt alle gewählten Fäden
gemeinsam. Gesteuert wird per G-Code über grblHAL; ein geplanter Python-Muster-Generator übersetzt Bilder in G-Code.

## Tech-Stack

- **Controller:** FYSETC R4 V1.0 (RP2040, 4× TMC2209 fest verlötet, UART-Modus, 0,22-Ω-Messwiderstände)
- **Firmware:** grblHAL, Treiber [grblHAL/RP2040](https://github.com/grblHAL/RP2040) Commit `2f5bc4a` + eigener Patch.
  Gebaut mit Pico SDK 2.1.1, arm-none-eabi-gcc 13.2, CMake + Ninja (Linux/WSL)
- **Mechanik:** 2020-Aluprofil (Nut 6, Blind Joints), MGN9H-Linearführungen, Dual-Z-Trapezgewindespindeln mit
  2× NEMA 17 (17HE15-1504S oder 17HS4401), X über GT2-Riemen (20 Zähne)
- **Aktor für die Fadenauswahl:** RC-Servo (getestet MG90, geplant bis 6× SG90) per `M280 P0 S<Winkel>`
- **CAD:** Shapr3D (`.shapr`), Export als STEP und STL
- **G-Code-Sender:** ioSender (Windows), alternativ gSender, CNCjs, UGS
- **Muster-Generator (geplant):** Python + Pillow

## Architektur

```
01 Konzept & Quellen - Jacquard-Webstuhl.pdf   Recherche: Aktor-Varianten, Skalierung, Quellen
02 L00m Entwicklungsgenese.pdf                 Designentscheidungen Mechanik, Antrieb, Strom, Sicherheit
CAD/                                           Shapr3D-Projekt, STEP-Export (gezippt)
Firmware/                                      Anleitung (PDF), fertige .uf2, Patch, machine_defaults.h
LICENSES/                                      Lizenzvolltexte (siehe LICENSE.md)
```

Zusammenspiel: Muster (Bild/Matrix) → Muster-Generator → `.gcode` → G-Code-Sender (USB) → grblHAL auf dem R4.
Pro Schuss: Z auf Wählhöhe, X fährt Faden für Faden an, Servo wählt (`M280 P0 S90`, `G4 P0.2`, `M280 P0 S0`),
dann hebt Z alle gewählten Fäden (`G1 Z90`), danach Z0 schließt das Fach. Ablauf: Entwicklungsgenese Kapitel 7.

**Pinbelegung (grblHAL):** X = MOTOR-X, Z1 = MOTOR-Z, Z2 = MOTOR-E (ganged + auto-squared), Y-Treiber frei.
Endstops X-STOP, Z-STOP, E-STOP (= Z2). Servo am Laser-Stecker (GPIO22). Vollständig: Firmware-PDF Kapitel 10.

**Achsen nach Homing:** Nullpunkt am Home-Schalter, Bereich X 0–98 mm, Z 0–88 mm (Verfahrweg − 2 mm Pull-off).

## Konventionen

- **Sprache:** Dokumentation und Commit-Nachrichten auf Deutsch. Code-Kommentare in der Firmware auf Englisch
  (wie grblHAL upstream).
- **Dateinamen:** Dokumente mit laufender Nummer (`01 …`, `02 …`); CAD-Stände mit Datum `JJJJMMTT`.
- **Firmware-Änderungen** nur über den Patch: grblHAL/RP2040 auf `2f5bc4a` auschecken, Patch anwenden, ändern, neuen
  Patch mit `git diff` erzeugen. `machine_defaults.h` liegt zusätzlich einzeln in `Firmware/` und muss mit der
  Fassung im Patch übereinstimmen.
- **Getestete Werte** stehen in `machine_defaults.h` und in der Firmware-Anleitung Kapitel 7 („Endkonfiguration“).
  Beide gemeinsam ändern.
- **Commits:** kurze Betreffzeile auf Deutsch im Imperativ, z. B. „Servo-Pulsbreiten an MG90 angepasst“.
- **Tests:** keine automatisierten Tests; Hardware-Abnahme nach der Checkliste „Geschafft, wenn“ im Firmware-PDF.

## Wichtige Befehle

STEP-Export aus Shapr3D zippen (die entpackte `.step` ist per `.gitignore` ausgeschlossen, GitHub nimmt nur bis
100 MB):

```powershell
Compress-Archive -Path CAD\L03m.step -DestinationPath CAD\L03m.step.zip -CompressionLevel Optimal -Force
```

Firmware bauen (Linux/WSL, Werkzeuge siehe Firmware-PDF Kapitel 11):

```bash
git clone https://github.com/grblHAL/RP2040.git && cd RP2040
git checkout 2f5bc4a && git submodule update --init --recursive
git apply ../grblHAL-RP2040-fysetc-r4.patch
mkdir build && cd build && cmake -G Ninja -DPICO_BOARD=pico .. && ninja   # → build/grblHAL.uf2
```

Am Gerät: `$I` (Board/Optionen), `$+` (alle Einstellungen; `$$` geht in diesem Build nicht), `$RST=*`
(Standardwerte laden), `$LIM` (Endstops), `$H` / `$HZ` / `$HX` (Homing), `M280 P0 S90` (Servo).

## Bekannte Fallstricke und Entscheidungen

- **Holz + LM8UU verworfen** (Anfang Oktober 2026): Toleranzen, Verziehen bei Feuchtigkeit, Textilstaub zerstört
  Kugelbuchsen. Ersetzt durch Aluprofil + MGN9H.
- **Riemen statt Spindel für Z verworfen:** ~110 N Hubkraft (bis 240 Kettfäden), 6-mm-GT2 würde bei 55 N je Seite
  dauerhaft dehnen; Getriebestepper zu teuer. Spindeln nur trocken schmieren (PTFE-Spray oder Graphit), kein Fett –
  Fett + Faserflug verklebt.
- **grblHAL statt Klipper:** keine Makrosprache, daher erzeugt der Muster-Generator alle Servo-Befehle direkt als
  G-Code.
- **Motorstrom:** maximal 958 mA (0,22-Ω-Messwiderstände); grblHAL rechnet sonst mit 0,11 Ω, daher
  `TRINAMIC_R_SENSE 220` im Patch. Z2 übernimmt Strom und Mikroschritte von Z.
- **Sicherheit:** 12 V statt 24 V senkt die Kraft nicht (TMC2209 regelt Strom). StallGuard schützt keine Hände.
  Geplant: Strom so tief, dass 110 N gerade gehoben werden, plus Pilz-Not-Aus, der die 24 V hart trennt.
- **Servo-Strom:** Mehrere Servos am 5-V-Wandler des R4 können einen Brownout auslösen. Für mehr als 1–2 Servos
  eigener Wandler (geplant XL4016) direkt am 24-V-Netzteil, zum R4 nur Signal + eine Masseleitung.
- **Servo-Fix im Patch:** grblHAL ab Commit `947338d` reserviert den PWM-Kanal beim Start (`M280` → `error:39`), und
  50 Hz passen bei 200 MHz nicht in den 16-Bit-Zähler. Beides behebt der Patch in `ioports_analog.c`.
- **STEP wird gezippt versioniert** statt Git LFS (Entscheidung 19.10.2026): kein LFS auf den Rechnern nötig; jede
  neue Version vergrößert aber die Historie um ~45 MB.
- **Hard-Limits aus (`$21=0`):** der unbelegte Y-Eingang meldet „ausgelöst“ und würde sofort Alarm geben.

## Nicht anfassen / Vorsicht bei

- **Commit `2f5bc4a` von grblHAL/RP2040** nicht ohne Not wechseln – der Patch passt nicht automatisch auf neuere
  Stände.
- **DIAG-Jumper am R4** müssen gezogen bleiben, sonst melden die Treiber falsche Endstops.
- **FAN2 nicht belegen:** GPIO22 ist auch das Servo-Signal.
- **Motoren nie unter Spannung an- oder abstecken** (zerstört die fest verlöteten Treiber).
- **Pinout-Grafik von FYSETC** im Firmware-PDF ist Fremdmaterial ohne Lizenz (siehe `LICENSE.md`).
