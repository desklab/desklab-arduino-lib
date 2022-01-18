---
hide:
  - toc
---

# API (Dokumentation der Funktionen)

### encode
##### Beschreibung
Die Funktion codiert einen Buchstaben, wandelt ihn also in eine Bitfolge (7 Bit) um.

##### Syntax
```
encode(x)
```

##### Parameter 
x: Buchstabe im Datentyp char.

##### Rückgabewert
Eine Bitfolge vom Datentyp byte8_t.

##### Beispiele
````
byte8_t bitsequence;
bitsequence = encode('H');
display(bitsequence); // Das Display zeigt '10010000'

