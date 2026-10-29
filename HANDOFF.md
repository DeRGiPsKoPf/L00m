# Handoff – aktueller Arbeitsstand

**Aktualisiert:** 29. Oktober 2026 · Branch `main`

## Aktuelles Ziel

Prototyp mit X + Dual-Z + einem Servo mechanisch fertig aufbauen und die erste Fachbildung per G-Code testen
(Probelauf mit L00m-Pattern per USB).

## Letzter Stand

- 29.10.2026: **Repo öffentlich gemacht.** Vorher ganzes Repo
  samt Historie geprüft: keine Zugangsdaten, keine E-Mail-Adressen, kein voller Name. L00m-grblHAL, L00m-Pattern
  und L00m-Host sind in Entwicklung und bleiben bis zu einem veröffentlichbaren Alpha-Zustand privat; README und
  LICENSE nennen sie mit Link und dem Zusatz „in Entwicklung“.
  README hat einen Sicherheitshinweis (Prototyp, kein geprüftes Gerät). LICENSE.md nimmt jetzt fremde Norm- und
  Kaufteile im CAD (Motoren, Servo, MGN9H, Endschalter, Pulleys, Kupplungen, Lager; alle von GrabCAD, öffentlich
  lizenziert) von der CERN-OHL-S aus.
- 29.10.2026: **PDFs korrigiert** (PyMuPDF): Datum in beiden Statuszeilen deutsch (19.10.2026); Entwicklungsgenese
  mit Status „Elektronik & Firmware aufgebaut und getestet“, „auf einem … Kinematik-System“ (Kap. 1), Codeblock in
  Kap. 7 komplett in Consolas neu gesetzt („Ausgangsposition“, `G1 Z88`, `M0`-Pause statt „<warten auf weiteren
  Input>“), Kap. 8 neu: beschreibt jetzt L00m-Pattern (TypeScript-Offline-Web-App) statt des Python-Skripts.
  Die Tabelle in Kap. 5 war korrekt (RP2040 an der 5-V-Schiene), dort nichts geändert.
- 23.10.2026: **Gestapelte Looms per Funk statt Kabel** (Entscheidung, Details L00m-Host `KONZEPT.md`): Die S3
  koppeln sich per ESP-NOW über einen Koppeln-Knopf; RS-485 und Micro-Fit-Buchsen entfallen. Für die Mechanik heißt
  das: kein Kabelweg zwischen den Looms, aber ein Einbauort mit freier Sicht für die Antenne.
- 23.10.2026: **Repos neu geordnet.** Die Firmware (`Firmware/`: Patch, `.uf2`, `machine_defaults.h`, Anleitung)
  liegt jetzt im eigenen Repo [L00m-grblHAL](https://github.com/DeRGiPsKoPf/L00m-grblHAL) (GPL), mit den
  Firmware-Punkten und der Servo-Pin-Tabelle aus diesem HANDOFF. Neu ist außerdem
  [L00m-Host](https://github.com/DeRGiPsKoPf/L00m-Host) (ESP32-S3 pro Loom, proprietär), dorthin ist die
  Controller-Recherche vom 21.10. gezogen (`KONZEPT.md`, Anhang). L00m-Pattern ist proprietär. Dieses Repo enthält
  nur noch Mechanik, CAD und Dokumentation (CERN-OHL-S-2.0, CC BY-SA 4.0; `LICENSES/GPL-3.0-or-later.txt` entfernt).
  README, AGENTS und LICENSE verweisen auf alle drei Repos (Tabelle „Zusammenspiel der Repos“); in AGENTS `G1 Z90` →
  `Z88` und der Ablauf pro Schuss auf den Stand der Vorlage gebracht.
- 22.10.2026: Entscheidungen (Details L00m-Host `KONZEPT.md` Abschnitt 2): Weg A → C, FluidNC-Board (D) gestrichen;
  jeder Loom bekommt einen S3 am UART0 des R4 (GPIO0/1); der Host gibt den Takt, jeder S3 webt seinen Loom selbst;
  Taster, OLED und Neopixel am S3. (Die Verbindung zwischen den Looms war zuerst RS-485, seit 23.10. Funk.)
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
4. Einbau des ESP32-S3 (L00m-Host) am Loom planen: Gehäuse, Weiter- und Koppeln-Taster erreichbar, OLED sichtbar;
   die Antenne trägt auch die Verbindung zu gestapelten Looms, also nicht hinter Metall oder neben den Motoren
   (Details L00m-Host `KONZEPT.md` Abschnitt 4).
5. Für die PDFs vormerken: Entwicklungsgenese Kapitel 7 fehlt noch `G4` nach X-Fahrt und Schwenk; die Repos
   L00m-grblHAL und L00m-Host werden im PDF noch nicht erwähnt (L00m-Pattern seit 29.10. in Kapitel 8).
6. L00m-grblHAL, L00m-Pattern und L00m-Host im Alpha-Zustand veröffentlichen; dann „in Entwicklung“ in README und
   LICENSE entfernen.
7. **Hubmagnet statt Servo** (Nutzer, 29.10.2026): 24 V, 0,3 A, 5 N auf 10 mm, schneller und einfacher als der Servo.
   Anschluss am Heizausgang bzw. (zweiter) am Heizbett-Ausgang des Controllers (R4, SKR Pico), bis 2 Stück, später
   evtl. mehr. Freilaufdiode antiparallel direkt am Magneten (Kathode an +24 V), Schottky z. B. SS34 oder 1N5819
   (mindestens 1 A, 40 V). Prüfen: Einschaltdauer (ED) des Magneten, falls er während der `M0`-Pause an bleibt
   (Erwärmung); Abfallzeit mit Diode (die Diode verlangsamt das Loslassen etwas). Punkt 3 (Servo-Versorgung) entfällt
   damit voraussichtlich. Firmware: L00m-grblHAL HANDOFF Punkt 6; Vorlage: L00m-Pattern.

## Bekannte Probleme

- **Verfahrweg X 100 mm** vs. Konzept bis 240 Kettfäden – vermutlich nur Prototyp-Breite, nicht geklärt.

## Entscheidungen in der Schwebe

| Frage | Optionen | Stand |
|---|---|---|
| Fadenauswahl ab ~64 Fäden | Servos · Latching-Solenoide · Wähler-Haken nach CMU-Vorbild | offen, Prototyp mit Servo |
| ~~Repo öffentlich machen~~ | – | entschieden 29.10.2026: L00m öffentlich, die anderen drei bis zum Alpha-Zustand privat |
| ~~Firmware in eigenes Repo~~ | – | entschieden 23.10.2026: L00m-grblHAL |
| ~~Mehrere Looms stapeln~~ | – | entschieden 22.10.2026: je ein Controller + S3 pro Loom, Takt vom Host (L00m-Host); seit 23.10. per Funk gekoppelt |
| ~~Firmware-Zukunft~~ | – | entschieden 22.10.2026: Weg A → C (S3 als Host vor grblHAL), D gestrichen, Klipper verworfen |
