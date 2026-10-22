@AGENTS.md

# Hinweise für Claude Code

- Der Projektkontext steht in `AGENTS.md` (oben eingebunden), der Arbeitsstand in `HANDOFF.md`. Zu Beginn jeder
  Sitzung beide lesen.
- Am Ende einer Sitzung nur `HANDOFF.md` aktualisieren; `AGENTS.md` nur bei grundsätzlichen Änderungen
  (Architektur, Konventionen, Stack). Änderungen an beiden vor dem Commit zeigen.
- Die PDFs sind die eigentlichen Projektdokumente. Neue Erkenntnisse, die dort hineingehören, als offenen Punkt in
  `HANDOFF.md` notieren, statt sie nur in Markdown festzuhalten.
- Erkenntnisse zur Firmware gehören ins Repo [L00m-grblHAL](https://github.com/DeRGiPsKoPf/L00m-grblHAL), zur App
  nach [L00m-Pattern](https://github.com/DeRGiPsKoPf/L00m-Pattern), zur Steuerzentrale am Loom nach
  [L00m-Host](https://github.com/DeRGiPsKoPf/L00m-Host): dort als offenen Punkt in dessen `HANDOFF.md` notieren.
  Änderungen an der Mechanik (Wege, Steigung, Fadenabstand) betreffen Profile in L00m-Pattern und Standardwerte in
  L00m-grblHAL.
