---
hide:
  - toc
---

# API (Dokumentation der Funktionen)

## encode
##### Beschreibung
Die Funktion codiert einen Buchstaben, wandelt ihn also in eine Bitfolge (7 Bit) um.

##### Syntax
```C++
encode(x)
```

##### Parameter 
x: Buchstabe im Datentyp `char`.

##### Rückgabewert
Eine Bitfolge vom Datentyp `byte8_t`.

##### Beispiele
```C++
byte8_t bitsequence;
bitsequence = encode('H');
display(bitsequence); // Das Display zeigt '10010000'
```

## decode
##### Beschreibung
Die Funktion decodiert eine Bitfolge, wandelt sie also in einen Buchstaben um.

##### Syntax
```C++
decode(x)
```

##### Parameter
x: Bitfolge vom Datentyp `byte8_t`.

##### Rückgabewert
Ein Buchstabe vom Datentyp `char`.

##### Beispiele
```C++
byte8_t bitsequence;
bitsequence = encode('H');
char output;
output = decode (bitsequence);
display(output); // Das Display zeigt 'H'
```
