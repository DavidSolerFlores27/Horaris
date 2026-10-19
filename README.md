# Generador d'Horaris i Combinador d'Assignatures

**Autor:** David Soler Flores  
**Codi UdG:** u6106247  

---

## Introducció

Aquest programa cerca totes les combinacions de grups de teoria, pràctiques i problemes mitjançant l'algorisme de **backtracking** per tal d'evitar solapaments horaris.

A més, identifica la millor solució basant-se en la **minimització del temps buit entre classes** (finestres).

- **Entrada:** Es realitza per teclat (es recomana redirigir un fitxer de text amb el format especificat).
- **Eixida:** Mostra totes les solucions trobades i el nombre total de combinacions. Si no n'hi ha cap, mostrarà:  
  `TOTAL SOLUCIONS: 0`

>  **Atenció amb els espais:** Compte amb els espais en blanc al final dels noms. No és el mateix `"Assignatura 1"` que `"Assignatura 1 "`.

---

##  Conceptes Clau

###  Solució
Es considera solució qualsevol combinació de grups d'assignatures on cap classe es solapi en l'horari. Una solució inclou les assignatures seleccionades amb els seus respectius grups.

###  Classes
Cada assignatura pot compondre's de 3 tipus de classes: **Teoria**, **Pràctiques** i **Problemes**.
- **Teoria:** És l'única tipologia que, per a un mateix grup, pot disposar de més d'una sessió a la setmana.
- **Pràctiques i Problemes:** Si s'escull un grup, només té assignat un dia i una hora concrets per setmana.

###  Classes Obligatòries
Si hi ha assignatures de diferents cursos o moltes incompatibilitats, pot ser que no existeixi cap combinació sense solapaments. Per això, es pot marcar quina classe és obligatòria (`1`) o no (`0`).

| Valor | Descripció |
| :---: | :--- |
| `1` | **Obligatòria** |
| `0` | **No obligatòria** |

> **Nota:** Si una classe no és obligatòria i coincideix amb una altra que sí que ho és, s'inserirà igualment. Per aquest motiu el programa mostra totes les opcions possibles perquè l'usuari decideixi.

###  Setmanes A / B
Algunes classes de pràctiques o problemes no s'imparteixen totes les setmanes:
- **`A`**: La classe només s'imparteix a la setmana A.
- **`B`**: La classe només s'imparteix a la setmana B.
- **`AB`**: La classe s'imparteix totes les setmanes.

*(Dues classes el mateix dia i hora però en setmanes diferents **no** es consideren solapament).*

###  Restriccions de Grups
Si una assignatura està dividida en diferents parts (per exemple, *Física* i *Electrònica*) però cal matricular-se al mateix grup, es poden tractar com a assignatures independents afegint **restriccions de grup**.

>  **Important:** En el fitxer d'entrada, la relació ha de ser **simètrica**. Si l'Assignatura A requereix coincidir amb la B, l'Assignatura B també ha d'incloure la restricció vers la A. En cas de no compartir cap grup en comú, l'algorisme no trobarà cap solució.



### Límits i Descansos

####  Límits Horaris
Indiquen al programa les franges horàries on **no** es volen tenir classes (per exemple, no començar abans de les 11:00h). Per defecte, tots els dies estan limitats de `00:00` a `23:59`.

####  Descansos
Es pot especificar una franja horària (per exemple, de dinar) i una duració mínima. El programa buscarà dins d'aquest interval un espai buit per a cada dia que compleixi la duració indicada.

---

##  Format del Fitxer d'Entrada

### Esquema General

```text
[Numero d'assignatures]
[Nom Assignatura 1]
[Grups teoria] [Hores teoria setmanals] [Obligatòria: 0/1]
[Grup] [Dia] [Hora inici] [Hora fi]
...
[Nombre de restriccions de teoria]
[Nom Assignatura amb qui ha de coincidir]
...
[Opcions pràctica] [Obligatòria: 0/1]
[Grup] [Dia] [Hora inici] [Hora fi] [Setmana: A/B/AB]
...
[Nombre de restriccions de pràctiques]
...
[Opcions problemes] [Obligatòria: 0/1]
[Grup] [Dia] [Hora inici] [Hora fi] [Setmana: A/B/AB]
...
[Nombre de restriccions de problemes]
...
[Nombre de grups de límits horaris]
[Nombre de dies afectats]
[Dies afectats...]
[Hora mínima] [Hora màxima]
...
[Descans: 0/1]
[Hora mínima descans]
[Hora màxima descans]
[Duració mínima (minuts)]
```
---
### Exemple Completa d'Entrada (info.txt)
```text
3                                   // Indica que hi ha 3 assignatures
Assignatura 1                       // Nom de l'assignatura (pot contenir espais)
2 2 1                               // [2] Dos grups de teoria. [2] Dos classes per setmana. [1] És obligatòria
1 Dilluns 8 00 10 00                // [1] Grup de teoria 1. [Dilluns] Es fa la classe al dilluns. [10 00] i [12 00] Hora inici i fi
1 Dimarts 10 00 12 00
2 Dilluns 10 00 12 00
2 Dimecres 8 00 10 00
0                                   // [0] No té restriccions de grup de teoria
3 1                                 // [3] tres grups de pràctiques disponibles [1] Obligatòria
1 Dilluns 16 30 17 30 A             // [1] Grup 1 de pràctques. [Dilluns] Dia de la setmana. [16 30] i [17 30] Hora inici i fi. [A] Setmana A 
2 Dimarts 16 30 17 30 B
6 Dilluns 16 30 17 30 B
2                                   // [2] Hi han dos assignatures que els seus grups de pràctica han de coincidir
Assignatura 2
Assignatura 3                       
2 0                                 // [2] Dos grups de teoria disponibles. [0] No obligatòria (es pot solapar amb alguna altra obligatòria)
1 Divendres 8 00 9 00 AB
2 Divendres 9 00 10 00 AB
1
Assignatura 2                       // [Assignatura 2] El grup de problemes ha de coincidir 
Assignatura 2                      // Nom de l'assignatura 2. És la següent. No hi han espais entre una assignatura i una altra.
1 1 1
1 Dimarts 8 00 9 30 
0
2 1                                   // [2] Té dos grups de pràctiques. Encara que en l'assignatura 1 tingui 3 i tingui aquesta assignatura com a restricció, només es necessita un grup en comú perquè pugui trobar una solució
1 Dilluns 16 30 17 30 A
2 Dimarts 16 30 17 30 B
2
Assignatura 1
Assignatura 3
1 0
1 Divendres 8 00 9 00 AB
1 
Assignatura 1
Assignatura 3                       // Nom de la següent assignatura. 
1 2 1
1 Dimecres 9 00 11 00 
1 Dijous 10 00 12 00
0
2 1
4 Dimarts 8 00 9 00 AB
1 Dilluns 16 30 17 30 A
2 
Assignatura 1
Assignatura 2
0                                  // [0] No té problemes. No cal afegir res més.
2                                 // [2] Té dos grups amb limits diferents de 00:00 a 23:59
1                                // [1] Afecta a un dia en concret
Dimarts                           
8 00                              // Hora minima del dimarts 
17 00                             // Hora màxima del dimarts   
2
Dijous
Divendres 
9 00
19 00
1                                  // [1] Hi ha un descans indicant
13 00                              // Hora minima del descans
15 00                               // Hora màxima
30                                  // Duració minima de 30 min
```

---
## Compilació i execució

Per compilar i executar el programa, s'ha de situar en la carpeta /Programa i accedir a la terminal. 
        
### Compilació del codi:
     g++ -o main *.cpp

### Execució I (per pantalla):
    ./main < info.txt
    
### Execució II (guardar en fitxer):
    ./main < info.txt > resultat.txt
