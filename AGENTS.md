# AGENTS.md – Projektkontext L00m

Dauerhaftes Nachschlagewerk für alle, die an diesem Repo arbeiten (Menschen und KI-Agenten). Der aktuelle
Arbeitsstand steht in `HANDOFF.md`, nicht hier.

## Projektüberblick

L00m ist ein computergesteuerter Jacquard-Webstuhl im Eigenbau für den Schul- und Kunstbetrieb (5–10 Jahre
Einsatz). Ein Servo auf einem X-Schlitten wählt Kettfäden einzeln aus, ein Dual-Z-Hub hebt alle gewählten Fäden
gemeinsam. Dieses Repo enthält die Maschine selbst: Konzept, Entwicklungsgenese, CAD und Renderings. Software und
Firmware liegen in eigenen Repos. Öffentlich ist bisher nur dieses Repo (seit 29.10.2026); die anderen sind in
Entwicklung und bleiben bis zu einem veröffentlichbaren Alpha-Zustand privat. README und LICENSE nennen sie mit Link
und dem Zusatz „in Entwicklung“ (Entscheidung Nutzer 29.10.2026):

| Repo | Inhalt | Braucht von L00m |
|---|---|---|
| [L00m-grblHAL](https://github.com/DeRGiPsKoPf/L00m-grblHAL) | grblHAL-Firmware für den FYSETC R4 (Patch, `.uf2`, Anleitung Flashen & Verkabeln) | Achsen, Verfahrwege, Spindelsteigung, Motoren |
| [L00m-Pattern](https://github.com/DeRGiPsKoPf/L00m-Pattern) | Muster-App: Bild, Zeichnung, Code → G-Code; Maschinenprofile | Fadenabstand, Verfahrwege, Z-Höhen, Ablauf pro Schuss |
| [L00m-Host](https://github.com/DeRGiPsKoPf/L00m-Host) | ESP32-S3 am Loom: WLAN, Auftrag, Anzeige, Taster, mehrere Looms im Takt (geplant) | Einbauort, Versorgung, Platz für die Antenne (Funk zwischen gestapelten Looms) |

## Tech-Stack

- **Mechanik:** 2020-Aluprofil (Nut 6, Blind Joints), MGN9H-Linearführungen, Dual-Z-Trapezgewindespindeln TR8x8
  (8 mm Steigung, `$102=400`) mit 2× NEMA 17 (17HE15-1504S oder 17HS4401), X über GT2-Riemen (20 Zähne)
- **Aktor für die Fadenauswahl:** RC-Servo (getestet MG90, geplant bis 6× SG90)
- **Elektronik:** FYSETC R4 V1.0 (RP2040, 4× TMC2209 fest verlötet) mit grblHAL aus L00m-grblHAL; geplant pro Loom
  ein ESP32-S3 SuperMini (L00m-Host) am UART0 des R4
- **CAD:** Shapr3D (`.shapr`), Export als STEP
- **G-Code:** aus L00m-Pattern; senden per USB (Web Serial, ioSender) oder künftig über L00m-Host

## Architektur

```
01 Konzept & Quellen - Jacquard-Webstuhl.pdf   Recherche: Aktor-Varianten, Skalierung, Quellen
02 L00m Entwicklungsgenese.pdf                 Designentscheidungen Mechanik, Antrieb, Strom, Sicherheit
Bilder/                                        Renderings (im README eingebunden)
CAD/                                           Shapr3D-Projekt, STEP-Export (gezippt)
LICENSES/                                      Lizenzvolltexte (siehe LICENSE.md)
```

Zusammenspiel: Muster (Bild, Zeichnung, PDF, WIF, Code) → L00m-Pattern mit Maschinenprofil → `.gcode` → per USB
(Web Serial oder G-Code-Sender) → grblHAL auf dem R4 (L00m-grblHAL). Geplant: L00m-Pattern → WLAN → L00m-Host
(ESP32-S3) → UART → R4; mehrere Looms per Funk gekoppelt (Koppeln-Knopf, keine Kabel), ein Host gibt den Takt.
Pro Schuss: Z auf Wählhöhe, X fährt Faden für Faden an (`G4` nach jeder X-Fahrt), Servo wählt (`M280 P0 S90`,
`G4 P0.2`, `M280 P0 S0`, `G4 P0.2`), X zurück auf X0, dann hebt Z alle gewählten Fäden (`G1 Z88`), `M0` pausiert zum
Schusseintrag, nach Zyklusstart schließt Z0 das Fach. Ablauf: Entwicklungsgenese Kapitel 7; die G-Code-Vorlage
liegt in L00m-Pattern. Änderungen an Mechanik (Wege, Steigung, Fadenabstand) dort und in L00m-grblHAL mitprüfen.

**Achsen nach Homing:** Nullpunkt am Home-Schalter, Bereich X 0–98 mm, Z 0–88 mm (Verfahrweg − 2 mm Pull-off).
Pinbelegung des R4: L00m-grblHAL, Anleitung Kapitel 10.

## Konventionen

- **Sprache:** Dokumentation und Commit-Nachrichten auf Deutsch.
- **Dateinamen:** Dokumente mit laufender Nummer (`01 …`, `02 …`); Shapr3D-Stände mit Datum `JJJJMMTT`; der
  STEP-Export trägt die Projektversion im Namen (`L03m` = Version 3, so gewollt).
- **Commits:** kurze Betreffzeile auf Deutsch im Imperativ, z. B. „Hubrahmen verstärkt“.
- **Tests:** keine automatisierten Tests; Abnahme am Gerät (Firmware: Checkliste in der Anleitung von L00m-grblHAL,
  Weben: `PROBELAUF.md` in L00m-Pattern).

## Wichtige Befehle

STEP-Export aus Shapr3D zippen (die entpackte `.step` ist per `.gitignore` ausgeschlossen, GitHub nimmt nur bis
100 MB):

```powershell
Compress-Archive -Path CAD\L03m.step -DestinationPath CAD\L03m.step.zip -CompressionLevel Optimal -Force
```

Firmware bauen und flashen: siehe L00m-grblHAL.

## Bekannte Fallstricke und Entscheidungen

- **Holz + LM8UU verworfen** (Anfang Oktober 2026): Toleranzen, Verziehen bei Feuchtigkeit, Textilstaub zerstört
  Kugelbuchsen. Ersetzt durch Aluprofil + MGN9H.
- **Riemen statt Spindel für Z verworfen:** ~110 N Hubkraft (bis 240 Kettfäden), 6-mm-GT2 würde bei 55 N je Seite
  dauerhaft dehnen; Getriebestepper zu teuer. Spindeln nur trocken schmieren (PTFE-Spray oder Graphit), kein Fett –
  Fett + Faserflug verklebt.
- **grblHAL statt Klipper:** keine Makrosprache, daher erzeugt der Muster-Generator alle Servo-Befehle direkt als
  G-Code. Details in L00m-grblHAL.
- **Muster-Generator als eigenes Repo in TypeScript** (Entscheidung 19.10.2026): statt Python + Pillow in diesem
  Repo. Als Offline-Web-App in einer HTML-Datei läuft er ohne Installation auf jedem Gerät; ein eigenes Repo hält die
  CAD-Historie fern und erlaubt eigene Releases. Begründung: `KONZEPT.md` und `AGENTS.md` in L00m-Pattern.
- **Steuerzentrale ESP32-S3 statt FluidNC-Board** (Entscheidung 21./22.10.2026): Ein S3 pro Loom am UART0 des R4.
  Taster, OLED und Neopixel sitzen am S3, nicht am R4. FluidNC-Boards gestrichen, Klipper verworfen (SD-Karte mit
  Betriebssystem). Begründung und Recherche: `KONZEPT.md` in L00m-Host.
- **Firmware in eigenem Repo** (Entscheidung 23.10.2026): L00m-grblHAL mit eigenen Versionen pro `.uf2` und eigener
  Lizenz (GPL); dieses Repo bleibt Mechanik und Dokumentation. Historie der Firmware-Dateien hier bis Commit
  `91e346d`.
- **Sicherheit:** 12 V statt 24 V senkt die Kraft nicht (TMC2209 regelt Strom). StallGuard schützt keine Hände.
  Geplant: Strom so tief, dass 110 N gerade gehoben werden, plus Pilz-Not-Aus, der die 24 V hart trennt.
- **Servo-Strom:** Mehrere Servos am 5-V-Wandler des R4 können einen Brownout auslösen. Für mehr als 1–2 Servos
  eigener Wandler (geplant XL4016) direkt am 24-V-Netzteil, zum R4 nur Signal + eine Masseleitung.
- **STEP wird gezippt versioniert** statt Git LFS (Entscheidung 19.10.2026): kein LFS auf den Rechnern nötig; jede
  neue Version vergrößert aber die Historie um ~45 MB.
- **PDFs und Claude-Docs:** Das Konzept gibt es auch als Claude-Doc, dessen PDF-Export aber anders aussieht (andere
  Seitenaufteilung). Kleine Korrekturen am 19.10.2026 wurden deshalb direkt in die PDFs geschrieben (PyMuPDF, gleiche
  Schriften und Positionen); die Entwicklungsgenese hat keine Doc-Quelle. Am 29.10.2026 ebenso: Statuszeilen,
  Kapitel 1, Kapitel 8 (Absatz neu in Arial) und der Codeblock in Kapitel 7, der dafür komplett in Consolas neu
  gesetzt ist (die Original-Codeschrift ist eine Type3-Schrift und lässt sich nicht nachsetzen).

## Nicht anfassen / Vorsicht bei

- **Lizenz bleibt Open Source** (CERN-OHL-S-2.0 für CAD, CC BY-SA 4.0 für Dokumentation); nicht ändern
  (Entscheidung Nutzer 23.10.2026). Fremde Norm- und Kaufteile im CAD (von GrabCAD, öffentlich lizenziert) sind
  ausgenommen (LICENSE.md); neue Fremdteile dort in die Liste aufnehmen.
- **Repo ist öffentlich:** keine privaten Daten, Zugangsdaten oder vollen Namen einchecken. Die PDFs nennen nur den
  Vornamen. Die anderen L00m-Repos nicht ohne ausdrückliche Ansage öffentlich machen.
- **DIAG-Jumper am R4** müssen gezogen bleiben, sonst melden die Treiber falsche Endstops.
- **Motoren nie unter Spannung an- oder abstecken** (zerstört die fest verlöteten Treiber).
