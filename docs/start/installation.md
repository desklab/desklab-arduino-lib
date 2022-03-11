---
hide:
  - toc
---

# Installation

In diesem Artikel wird beschrieben, wie die Geräte von desklab zusammen mit der Arduino-Entwicklungsumgebung und der bereitgestellten Software-Bibliothek programmiert werden können.

Bei Fragen oder Problemen, auf die Sie in den Hilfe-Artikeln dieser Seite keine Lösung finden, können Sie uns gerne über das Kontaktformular auf unserer [Homepage](www.desk-lab.de) kontaktieren.

### Übersicht

1. Installation des Mikrocontroller-Treibers
2. Installation der Arduino Entwicklungsumgebung
3. Installation der benötigten Bibliotheken
4. Upload eines Beispiel-Programms


### 1. Mikrocontroller-Treiber: Download & Installation

Um den in den Geräten der desklab gUG verbauten Mikrocontroller mit der Arduino-Entwicklungsumgebung programmieren zu können, benötigen Sie den Treiber CH341SER. Die zur Installation benötigten Dateien können Sie von unserer Homepage herunterladen. Sie benötigen dazu die Login-Daten, die Sie zusammen mit der Lieferung oder per E-Mail erhalten haben.

Führen Sie zur Installation des Treibers die folgenden Schritte durch:

1. Trennen Sie per USB angeschlossene desklab-Geräte von Ihrem Computer.
2. Laden Sie die Installationsdatei mc_treiber_CH341SER.zip ([Downloadlink](https://desk-lab.de/documents/66/mc-treiber_CH341SER.zip))von unserer Website herunter.
3. Speichern und Entpacken Sie die heruntergeladene Datei.
4. Führen Sie die Datei "Setup.exe" aus.
5. Wählen Sie im darauf erscheinenden Dialogfenster “Install” aus und befolgen Sie eventuell erscheinende Mitteilungen.


### 2. Arduino IDE (Entwicklungsumgebung): Download & Installation

Wir empfehlen, die aktuellste von Arduino® zur Verfügung gestellte Version der Entwicklungsumgebung zu installieren. Die zur Installation benötigte(n) Datei(en) können unter [www.arduino.cc/en/Main/Software](https://www.arduino.cc/en/Main/Software) heruntergeladen werden. Befolgen Sie zur Installation die dort beschriebenen Schritte. 

Die Kompatibilität der desklab-Bibliothek (s.u.) mit allen Versionen der Arduino Entwicklungsumgebung seit Version 1.8.6 (Release 2018) wird von uns getestet und sichergestellt. Falls Sie eine nicht unterstützte Version der Arduino-Entwicklungsumgebung nutzen, können bei der Nutzung der Funktionen der desklab-Bibliothek Probleme und Fehler auftreten.


### 3. Arduino Bibliotheken

In der desklab Arduino Bibliothek werden Funktionen zur Nutzung und Programmierung der Geräte der desklab gUG bereitgestellt. Die Bibliothek kann in der Bibliotheksverwaltung der Arduino-Entwicklungsumgebung installiert werden. Führen Sie zur Installation der Arduino-Bibliothek die folgenden Schritte durch:

1. Trennen Sie per USB angeschlossene desklab-Geräte von IhremComputer.
2. Öffnen Sie die Arduino-Entwicklungsumgebung.
3. Öffnen Sie die Bibliotheksverwaltung über die Menüleiste der Entwicklungsumgebung.
4. Suchen Sie nach 'desklab' und installieren Sie die neueste Version der Bibliothek.


### 4. Upload eines Beispiel-Programms

In der desklab Arduino Bibliothek sind mehrere Beispielprogramme enthalten, mit denen unter anderem das Photometer zur Messung der optischen Dichte genutzt werden kann.

Um zu testen, ob alle Schritte erfolgreich durchgeführt wurden, kann ein Beispielprogramm auf den Mikrocontroller geladen werden. Dazu muss die Arduino IDE gestartet und der Mikrocontroller per USB Kabel angeschlossen werden.

Nach dem Start der Arduino IDE sollte zum Test ein Beispiel-Sketch der Bibliothek kompiliert und auf den Mikrocontroller geladen werden. Nach wenigen Sekunden sollte der Upload auf den Mikrocontroller abgeschlossen sein und das Programm wird automatisch gestartet.