<h1 align="center"> desklab Arduino Library </h1>
<p align="center">
<img align="center" src="https://www.ardu-badge.com/badge/desklab.svg?">
<br>
<a href="./README_DE.md">to the english version of this file</a>
</p>

`desklab` ist eine Arduino Bibliothek zur Nutzung mit den Geräten von desklab (www.desk-lab.de). Die Bibliothek kann durch die Arduino-Bibliotheksverwaltung installiert und zusammen mit der Arduino-Entwicklungsumgebung genutzt werden. Obwohl diese Bibliothek speziell zur Nutzung der desklab Geräte entwickelt wurde, kann sie auch für andere Projekte, die einen Atmel-AVR-Mikrocontroller verwenden, benutzt werden.

#### Kompatibilität zu Geräten
  - `desklab Photometer V2`
  - `desklab Photometer V3`

### Entwicklung und Community-Beiträge
Wir freuen uns über Beiträge in Form von Berichten über Probleme (_Issues_) oder Ergänzungen des Programmcodes (_Pull Requests_). Bitte nutze die im folgenden beschriebenen Werkzeuge, um sicherzustellen, dass wir den Code integrieren können. Da diese Bibliothek auf eine spezielle Zielgruppe (Schüler:innen/Lehrkräfte) ausgerichtet ist und die Kompatibilität zu (potentiell bzw. teilweise noch unveröffentlichten) Geräten von desklab erhalten werden muss, ist es möglich, dass noch weitere Anforderungen bestehen, die nicht durch automatische Tests abgedeckt werden können. Daher stehen wir unter <orga@desk-lab.de> oder durch die _Issues_ bei Rückfragen oder für Diskussionen über den besten Weg zur Lösung eines Problems gerne zur Verfügung. Solltest du Änderungen am Code dieser Bibliothek vorschlagen, wird dieser unter derselben MIT Lizenz wie dieses Projekt veröffentlicht werden.

##### Arduino Lint
Installiere `arduino-lint` wie in der [offiziellen arduino-lint Dokumentation](https://arduino.github.io/arduino-lint/latest/installation/) beschrieben. Du solltest `arduino-lint` mit den diesen Optionen nutzen:

```bash
# Launch linting 
arduino-lint --library-manager update --compliance strict
```

##### Unittests & Beispiele
Unittests sind im `/test`-Ordner gespeichert. Bei Änderungen am Programmcode, die durch automatische Tests abgedeckt werden können, sollten diese ergänzt werden. Um die Tests lokal durchführen zu können, muss zuerst `arduino-ci` mit den folgenden Schritten installiert werden:

```bash
# Install test requirements: 
gem install bundler
bundler config set --local path vendor/bundle  # optional
bundler install
```

Für die automatisierten Tests wird die `arduino/compile-sketches`-Action auf GitHub verwendet. Um lokal alle Beispiele zu kompilieren und die Tests durchzuführen, kann aber `arduino-ci` genutzt werden. Mit der Option `--skip-examples-compilation` werden ausschließlich die Tests gestartet und die Beispiele übersprungen.

```bash
# Run the tests and compile examples
bundle exec arduino_ci.rb

# Run the tests 
bundle exec arduino_ci.rb --skip-examples-compilation
```

#### Dokumentation

Zum Erstellen der Dokumentation wird **MkDocs** genutzt. Mit den folgenden befehlen wird MkDocs in einer neuen `conda` Umgebung installiert:

```bash
conda create -n desklab-arduino lib python=3.9
pip install -r requirements.txt
```

Die Dokumentation kann mit dem folgenden Befehlen erstellt werden:

```bash
conda activate desklab-arduino-lib
mkdocs build
```

Die Dokumentation ist online unter [support.desk-lab.de/desklab-arduino-lib](https://support.desk-lab.de/desklab-arduino-lib/build/html/index.html) verfügbar.

### Lizenz

Die `desklab` Bibliothek ist unter der [MIT License](https://opensource.org/licenses/MIT) lizensiert:

> Copyright 2018-2022 desklab gUG (haftungsbeschränkt) <orga@desk-lab.de>  
>
> Permission is hereby granted, free of charge, to any person obtaining a  
> copy of this software and associated documentation files  
> (the "Software"), to deal in the Software without restriction, including  
> without limitation the rights to use, copy, modify, merge, publish,  
> distribute, sublicense, and/or sell copies of the Software, and to  
> permit persons to whom the Software is furnished to do so, subject to  
> the following conditions:  
> 
> The above copyright notice and this permission notice shall be included  
> in all copies or substantial portions of the Software.  
> 
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,  
> EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF  
> MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  
> IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR  
> ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  
> CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION  
> WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE  
