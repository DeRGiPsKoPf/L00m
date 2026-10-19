# Lizenzen

Copyright © 2026 DeRGiPsKoPf

Dieses Repo enthält Software, Hardware-Konstruktionsdaten und Dokumentation. Jede Dateiart steht unter der dazu
passenden freien Lizenz. Alle drei sind Copyleft-Lizenzen: Wer etwas davon verändert und weitergibt, muss die
Änderungen unter derselben Lizenz weitergeben.

| Dateien | Lizenz | Volltext |
|---|---|---|
| `Firmware/grblHAL-RP2040-fysetc-r4.patch`, `Firmware/machine_defaults.h`, `Firmware/grblHAL-FYSETC-R4.uf2`, künftiger Code (z. B. Muster-Generator) | GNU General Public License v3.0 oder später (`GPL-3.0-or-later`) | [LICENSES/GPL-3.0-or-later.txt](LICENSES/GPL-3.0-or-later.txt) |
| `CAD/` (Shapr3D, STEP, STL) | CERN Open Hardware Licence Version 2 – Strongly Reciprocal (`CERN-OHL-S-2.0`) | [LICENSES/CERN-OHL-S-2.0.txt](LICENSES/CERN-OHL-S-2.0.txt) |
| Dokumentation: PDFs, Bilder in `Bilder/`, `README.md`, `AGENTS.md`, `CLAUDE.md`, `HANDOFF.md`, `LICENSE.md` | Creative Commons Namensnennung – Weitergabe unter gleichen Bedingungen 4.0 International (`CC-BY-SA-4.0`) | [LICENSES/CC-BY-SA-4.0.txt](LICENSES/CC-BY-SA-4.0.txt) |

Namensnennung bei CC BY-SA und CERN-OHL-S: „L00m – DeRGiPsKoPf“ mit Link auf dieses Repo.

## Warum die Firmware GPL-3.0 sein muss

Die Firmware ist eine Änderung von [grblHAL](https://github.com/grblHAL) (Treiber
[grblHAL/RP2040](https://github.com/grblHAL/RP2040), Commit `2f5bc4a`), das unter GPL-3.0-or-later steht. Der Patch
und die daraus gebaute `.uf2` sind abgeleitete Werke und stehen deshalb ebenfalls unter GPL-3.0-or-later. Die `.uf2`
enthält außerdem Teile des [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) (BSD-3-Clause, mit der
GPL vereinbar).

Der zugehörige Quellcode der `.uf2` besteht aus grblHAL/RP2040 im Stand `2f5bc4a` plus
`Firmware/grblHAL-RP2040-fysetc-r4.patch`; die Build-Anleitung steht in der Firmware-Anleitung (Kapitel 11).

## Marken

Markennamen (FYSETC, Raspberry Pi, Voron, Shapr3D usw.) gehören ihren Inhabern.
