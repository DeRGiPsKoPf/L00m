# Handoff – aktueller Arbeitsstand

**Aktualisiert:** 19. Oktober 2026 · Branch `main`

## Aktuelles Ziel

Prototyp mit X + Dual-Z + einem Servo mechanisch fertig aufbauen und die erste Fachbildung per G-Code testen.

## Letzter Stand

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
2. Muster-Generator in Python (Bild/Matrix → G-Code) beginnen.
3. Sicherheitskonzept umsetzen: Not-Aus-Pilztaster in der 24-V-Leitung.
4. Servo-Versorgung für mehr als 1–2 Servos: separater 5-V-Wandler (MP1584EN / XL4016).

## Bekannte Probleme

- **Verfahrweg X 100 mm** vs. Konzept bis 240 Kettfäden – vermutlich nur Prototyp-Breite, nicht geklärt.
- Tippfehler „Ausgansposition“ im G-Code-Beispiel der Entwicklungsgenese (Kapitel 7), noch nicht korrigiert (die
  Code-Schrift dort lässt sich nicht passgenau nachsetzen).

## Entscheidungen in der Schwebe

| Frage | Optionen | Stand |
|---|---|---|
| Fadenauswahl ab ~64 Fäden | Servos · Latching-Solenoide · Wähler-Haken nach CMU-Vorbild | offen, Prototyp mit Servo |
| Repo öffentlich machen | ja · privat lassen | privat |
