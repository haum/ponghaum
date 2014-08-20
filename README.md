# PongHaum

## Qu'est-ce que c'est ?

Ce dépôt contient les sources de ponghaum, le pong 1D réalisé par le HAUM (http://haum.org/)

## Arduino

### Présentation

Le système utilise 150 leds en bande commandées par la bibliothèque FastLED et deux boutons. Les détails du système est/sera présent sur le site du HAUM.

### Compilation

Lorsque le dépôt est cloné, il faut penser à charger les submodules pour avoir les dépendances permettant de construire le programme pour Arduino.

```
git submodule init
git submodule update
```

Puis utiliser le Makefile pour Arduino :

```
make -f Makefile.arduino
```

## Émulateur

### Contôles

Les boutons sont émulés par des touches de calvier :

 - Flèche Gauche ou touche Q sur clavier AZERTY = bouton 1
 - Flèche Droite ou touche D sur clavier AZERTY = bouton 2

Une touche permet aussi de quitter l'émulateur :

 - Échap = Quitter l'émulateur

Les leds sont émulés par des pixels dans une fenêtre.

Les caractères envoyés sur la liaison série sont redirigés vers la sortie standard du programme.

### Raison d'être

Les sources contiennent un émulateur pour le développement et tests sur PC.

Celui-ci permet d'essayer différents programmes sans avoir accès au système électronique, en cours de construction lors de la création du dépôt.
Il faut néanmoins garder en tête que la cible principale est un microcontrôleur 8 bits avec assez peu de mémoire vive.

### Compilation

Un Makefile permet de construire l'émulateur PC :

```
make -f Makefile.pc
```

Les dépendances sont seulement pthread et SDL2.


## Arduino

Les boutons sons reliés aux entrées 2 et 3 de l'Arduino (définit dans le fichier hmi/hmi_manager.cpp ouvert)
Le bandeau de LEDs est relier a l'Arduino par la sortie 10 (definit dans le meme fichier)

### compilation de la version Arduino

Il faut installer le Makefile générique Arduino https://github.com/sudar/Arduino-Makefile 
Il faut ensuite ajuster le fichier Makefile.arduino en fonction de votre installation et de votre modèle d'Arduino

La compilation du projet se fait par :

```
make -f Makefile.arduino
```

le téléchargement dans l'Arduino:

```
make -f Makefile.arduino upload
```

have fun :)

## Licence

Le projet est fourni sous licence MIT.

C'est une licence libre qui vous permet par exemple :
 - de le copier,
 - de l'étudier,
 - de l'adapter à vos besoins,
 - de le redistribuer

Nous vous encourageons vivement à forker et partager !
