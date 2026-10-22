# Handoff – aktueller Arbeitsstand

**Aktualisiert:** 23. Oktober 2026 · Branch `main`

## Aktuelles Ziel

Prototyp mit X + Dual-Z + einem Servo mechanisch fertig aufbauen und die erste Fachbildung per G-Code testen
(Probelauf mit L00m-Pattern per USB).

## Letzter Stand

- 23.10.2026: **Repos neu geordnet.** Die Firmware (`Firmware/`: Patch, `.uf2`, `machine_defaults.h`, Anleitung)
  liegt jetzt im eigenen Repo [L00m-grblHAL](https://github.com/DeRGiPsKoPf/L00m-grblHAL) (GPL), mit den
  Firmware-Punkten und der Servo-Pin-Tabelle aus diesem HANDOFF. Neu ist außerdem
  [L00m-Host](https://github.com/DeRGiPsKoPf/L00m-Host) (ESP32-S3 pro Loom, proprietär), dorthin ist die
  Controller-Recherche vom 21.10. gezogen (`KONZEPT.md`, Anhang). L00m-Pattern ist proprietär. Dieses Repo enthält
  nur noch Mechanik, CAD und Dokumentation (CERN-OHL-S-2.0, CC BY-SA 4.0; `LICENSES/GPL-3.0-or-later.txt` entfernt).
  README, AGENTS und LICENSE verweisen auf alle drei Repos (Tabelle „Zusammenspiel der Repos“); in AGENTS `G1 Z90` →
  `Z88` und der Ablauf pro Schuss auf den Stand der Vorlage gebracht.
- 22.10.2026: Entscheidungen (Details L00m-Host `KONZEPT.md` Abschnitt 2): Weg A → C, FluidNC-Board (D) gestrichen;
  jeder Loom bekommt einen S3 am UART0 des R4 (GPIO0/1), zwei Steckplätze für weitere Looms per RS-485; der Host gibt
  den Takt, jeder S3 webt seinen Loom selbst; Taster, OLED und Neopixel am S3.
- 21.10.2026: Erster Servo-Test mit L00m-Pattern am Gerät: `M280` läuft der X-Fahrt voraus (jetzt offener Punkt in
  L00m-grblHAL).
- 19.10.2026: Muster-Generator in das eigene Repo L00m-Pattern ausgelagert (TypeScript-Offline-Web-App statt
  Python, `M0`-Pause pro Schuss).
- 19.10.2026: Firmware-Patch korrigiert und unter Windows gebaut (Details jetzt in L00m-grblHAL); Servo am Gerät
  bestätigt.
- 19.10.2026: `02 L00m Entwicklungsgenese.pdf` an den Stand angepasst: Status, TR8x8 als verbaute Spindel,
  grblHAL statt Klipper, X/Z statt X/Y, 12-V-/5-V-Schiene mit den Werten aus dem Schaltplan.
- 19.10.2026: Repo angelegt mit README, AGENTS/CLAUDE, HANDOFF, LICENSE, STEP-Export als `CAD/L03m.step.zip`,
  Rendering im README.

## Offene Baustellen

1. Mechanik-Aufbauanleitung schreiben (in der Firmware-Anleitung angekündigt, die jetzt in L00m-grblHAL liegt).
2. Sicherheitskonzept umsetzen: Not-Aus-Pilztaster in der 24-V-Leitung.
3. Servo-Versorgung für mehr als 1–2 Servos: separater 5-V-Wandler (MP1584EN / XL4016).
4. Einbau des ESP32-S3 (L00m-Host) am Loom planen: Gehäuse, Antenne nicht hinter Metall oder neben den Motoren,
   Micro-Fit-3.0-Buchsen für die Verbindung zu gestapelten Looms (Details L00m-Host `KONZEPT.md` Abschnitt 4).
5. Für die PDFs vormerken: Entwicklungsgenese Kapitel 8 beschreibt noch einen Python-Generator; Kapitel 7 um die
   `M0`-Pause, `G4` nach X-Fahrt und Schwenk und den Hub auf Z88 statt `G1 Z90` ergänzen; Repos L00m-grblHAL,
   L00m-Pattern und L00m-Host erwähnen.

## Bekannte Probleme

- **Verfahrweg X 100 mm** vs. Konzept bis 240 Kettfäden – vermutlich nur Prototyp-Breite, nicht geklärt.
- Tippfehler „Ausgansposition“ im G-Code-Beispiel der Entwicklungsgenese (Kapitel 7), noch nicht korrigiert (die
  Code-Schrift dort lässt sich nicht passgenau nachsetzen).
- Entwicklungsgenese Kapitel 7 nennt noch `G1 Z90`; die Soft-Limits erlauben nur Z 0–88 (siehe Baustelle 5).

## Entscheidungen in der Schwebe

| Frage | Optionen | Stand |
|---|---|---|
| Fadenauswahl ab ~64 Fäden | Servos · Latching-Solenoide · Wähler-Haken nach CMU-Vorbild | offen, Prototyp mit Servo |
| Repo öffentlich machen | ja · privat lassen | privat |
| ~~Firmware in eigenes Repo~~ | – | entschieden 23.10.2026: L00m-grblHAL |
| ~~Mehrere Looms stapeln~~ | – | entschieden 22.10.2026: je ein Controller + S3 pro Loom, Takt vom Host (L00m-Host) |
| ~~Firmware-Zukunft~~ | – | entschieden 22.10.2026: Weg A → C (S3 als Host vor grblHAL), D gestrichen, Klipper verworfen |
