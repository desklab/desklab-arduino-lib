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

## parity
##### Beschreibung
Die Funktion parity erzeugt ein Paritätsbit zu einer gegebenen Bitfolge, hängt es an die Bitfolge an und gibt diese dann zurück.

##### Syntax
```C++
parity(x)
```

##### Parameter
x: eine Bitfolge vom Datentyp byte8_t.

##### Rückgabewerte
Eine Bitfolge vom Datentyp byte8_t.

##### Beispiele
```C++
byte8_t bitsequence;
bitsequence = encode('H');
bitsequence = parity(bitsequence);
display(bitsequence); // Das Display zeigt '10010000'
```

## check
##### Beschreibung
Die Funktion check kontrolliert die Parität einer Bitfolge. Sie liefert eine 1, falls die Parität stimmt und eine 0, falls die Parität nicht stimmt.

##### Syntax
```C++
check(x)
```

##### Parameter
x: eine Bitfolge vom Datentyp byte8_t.

##### Rückgabewerte
true, falls die die Parität stimmt. false, falls ein Fehler festgestellt wurde und die Parität nicht stimmt. Datentyp bool.

##### Beispiele
```C++
byte8_t bitsequence;
bitsequence = encode('H');
bitsequence = parity(bitsequence);
bool result;
result = check(bitsequence);
display(result); // Das Display zeigt 'T'
```