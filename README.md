# L00m – computergesteuerter Jacquard-Webstuhl

![L00m: CAD-Modell mit Dual-Z-Hub, X-Schlitten mit Servo und Harnisch](Bilder/L00m-Render.png)

L00m ist ein Jacquard-Webstuhl im Eigenbau für den Schul- und Kunstbetrieb. Statt der klassischen
Platinen-Mechanik wählt ein kleiner Aktor (RC-Servo) die Kettfäden einzeln aus, ein zentraler Hub (zwei
Schrittmotoren an Trapezgewindespindeln) hebt alle gewählten Fäden gemeinsam an. Gesteuert wird das Ganze wie ein
3D-Drucker oder eine CNC-Fräse: ein Muster wird in G-Code übersetzt und an einen Controller mit grblHAL geschickt.

Ziel ist eine langlebige, wartungsarme und sichere Maschine (5–10 Jahre Einsatz), die sich mit Teilen aus dem
3D-Druck-Umfeld nachbauen lässt.

## Stand (Oktober 2026)

| Bereich | Stand |
|---|---|
| Konzept & Recherche | fertig, siehe `01 Konzept & Quellen` und `02 L00m Entwicklungsgenese` |
| CAD (Shapr3D) | in Arbeit, Stand 19.10.2026 |
| Elektronik & Firmware | aufgebaut und getestet: grblHAL auf FYSETC R4, X + Dual-Z (TR8x8) mit Squaring, Servo per `M280` |
| Mechanik-Aufbauanleitung | fehlt noch |
| Muster-Generator (Bild → G-Code) | geplant, noch nicht begonnen |
| Sicherheitskonzept (Strombegrenzung, Not-Aus) | geplant, noch nicht umgesetzt |

## Aufbau des Repos

```
01 Konzept & Quellen - Jacquard-Webstuhl.pdf   Aktor-Varianten, Skalierung, Maker-Projekte als Quellen
02 L00m Entwicklungsgenese.pdf                 Mechanik-, Antriebs-, Strom- und Sicherheitsentscheidungen
Bilder/                                        Renderings
CAD/
  Project L00m - 20261019.shapr                Shapr3D-Projekt (Arbeitsdatei)
  L03m.step.zip                                STEP-Export der Baugruppe, Projektversion 3 (gezippt, entpackt 171 MB)
Firmware/
  grblHAL auf FYSETC-R4 - Flashen & Konfiguration.pdf   Anleitung: Flashen, Verkabeln, Einstellungen, Fehlersuche
  grblHAL-FYSETC-R4.uf2                        fertige Firmware zum Draufkopieren
  grblHAL-RP2040-fysetc-r4.patch               Änderungen gegenüber grblHAL (Board-Datei, Servo-Fix, Standardwerte)
  machine_defaults.h                           Maschinenwerte, die $RST=* wiederherstellt
LICENSES/                                      vollständige Lizenztexte
```

## Schnellstart Elektronik

1. Am FYSETC R4 BOOTSEL halten, RST drücken, BOOTSEL loslassen.
2. `Firmware/grblHAL-FYSETC-R4.uf2` auf das Laufwerk `RPI-RP2` ziehen.
3. Mit einem G-Code-Sender (z. B. [ioSender](https://github.com/terjeio/ioSender)) verbinden, `$RST=*` senden,
   mit `$I` prüfen, ob `FYSETC R4 V1.0` gemeldet wird.

Alles Weitere (Verkabelung, Homing, Servo, Firmware selbst bauen) steht in der Firmware-Anleitung im Ordner
`Firmware`.

## Lizenz

Mehrere Lizenzen, je nach Dateiart – Details in [LICENSE.md](LICENSE.md):

- Firmware und Code: **GPL-3.0-or-later** (Pflicht, weil die Firmware auf grblHAL aufbaut)
- CAD-Daten: **CERN-OHL-S-2.0**
- Dokumentation (PDFs, Markdown): **CC BY-SA 4.0**

## Kontakt

Fragen und Ideen bitte über die GitHub-Discussions dieses Repos.
