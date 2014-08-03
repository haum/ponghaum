# PongHaum

## Qu'est-ce que c'est ?

Ce dépôt contient les sources de ponghaum, le pong 1D réalisé par le HAUM (http://haum.org/)

## Émulateur

### Contôles

Les boutons sont émulés par des touches de calvier :

 - Flèche Gauche = bouton 1
 - Flèche Droite = bouton 2

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

## Licence

Le projet est fourni sous licence MIT.

C'est une licence libre qui vous permet par exemple :
 - de le copier,
 - de l'étudier,
 - de l'adapter à vos besoins,
 - de le redistribuer

Nous vous encourageons vivement à forker et partager !
