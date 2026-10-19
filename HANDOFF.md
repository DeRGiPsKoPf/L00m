# Handoff – aktueller Arbeitsstand

**Aktualisiert:** 19. Oktober 2026 · Branch `main`

## Aktuelles Ziel

Prototyp mit X + Dual-Z + einem Servo mechanisch fertig aufbauen und die erste Fachbildung per G-Code testen.

## Letzter Stand

- 19.10.2026: Repo angelegt (vorher nur lokaler Ordner `Project L00m`). Neu: `README.md`, `AGENTS.md`, `CLAUDE.md`,
  `HANDOFF.md`, `LICENSE.md`, `LICENSES/`, `.gitignore`, `.gitattributes`. STEP-Export als `CAD/L03m.step.zip`.
- 19.10.2026: Firmware fertig und am Gerät getestet: X, Dual-Z mit Squaring, Homing, Soft-Limits
  (`Firmware/grblHAL-FYSETC-R4.uf2`, `Firmware/machine_defaults.h`, Patch). Anleitung als PDF in `Firmware/`.
- 19.10.2026: CAD-Stand `CAD/Project L00m - 20261019.shapr`, STEP-Export `L03m.step`.
- Konzept- und Entscheidungsdokumente `01 …` und `02 …` (Stand 19.10.2026).

## Offene Baustellen

1. Servo-Korrektur der Firmware am Gerät bestätigen (`M280 P0 S90`; laut Firmware-PDF Kapitel 9 noch nicht geprüft).
2. Hubkraft prüfen: Hebt Z die ~110 N mit dem eingebauten Motorstrom (500 mA)? Das Sicherheitskonzept nennt
   0,6–0,8 A. Danach `$140`–`$142` und `machine_defaults.h` festlegen.
3. Mechanik-Aufbauanleitung schreiben (im Firmware-PDF angekündigt).
4. Muster-Generator in Python (Bild/Matrix → G-Code) beginnen.
5. Sicherheitskonzept umsetzen: Not-Aus-Pilztaster in der 24-V-Leitung, Strombegrenzung einstellen.
6. Servo-Versorgung für mehr als 1–2 Servos: separater 5-V-Wandler (MP1584EN / XL4016).

## Bekannte Probleme

- **Spindelsteigung widersprüchlich:** Entwicklungsgenese nennt TR8x4 als Präferenz, die Firmware rechnet mit 8 mm
  Steigung (`$102=400`, TR8x8). Bei TR8x4 wäre `$102=800`. Welche Spindel verbaut ist: weiß ich nicht.
- **Veraltete Stellen in `02 L00m Entwicklungsgenese.pdf`:** Tabelle Kapitel 3 spricht beim TR8x8 vom
  „Klipper-Controller“ (Firmware ist grblHAL); Kapitel 8 nennt X/Y-Befehle, die Maschine hat X/Z.
- **5-V-Schiene:** Entwicklungsgenese nennt ~3 A (kurz 5 A), Firmware-PDF 5 A (Spitze 6 A). Firmware-PDF ist aus dem
  Schaltplan berechnet, vermutlich die genauere Angabe.
- **Verfahrweg X 100 mm** vs. Konzept bis 240 Kettfäden – vermutlich nur Prototyp-Breite, nicht geklärt.
- **Patch, `grbl/settings.c`:** Die Ersatz-Defines für die Homing-Geschwindigkeiten pro Achse stehen innerhalb von
  `#if ENABLE_SPINDLE_LINEARIZATION`. Ohne `machine_defaults.h` (und ohne Spindel-Linearisierung) fehlen sie
  vermutlich und der Build bricht ab – entgegen der Aussage im Firmware-PDF. Nicht geprüft.
- **Pinout-Grafik von FYSETC** im Firmware-PDF hat keine Lizenz; vor einer öffentlichen Freigabe klären oder ersetzen.

## Entscheidungen in der Schwebe

| Frage | Optionen | Stand |
|---|---|---|
| Spindel für Z | TR8x4 (mehr Kraft, sanfter) · TR8x8 (Standard, günstiger) | offen, Firmware auf TR8x8 |
| Fadenauswahl ab ~64 Fäden | Servos · Latching-Solenoide · Wähler-Haken nach CMU-Vorbild | offen, Prototyp mit Servo |
| Repo öffentlich machen | ja (vorher FYSETC-Grafik klären) · privat lassen | privat |
