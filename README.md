# captain_sonar_cpp
project captain sonar en c++ utilisant oxygine - SDL - socket.io - Boost

### INSTALLATION:

- faire un clone du repository AVEC les dépendances :

```sh
$ git clone --recurse-submodules https://github.com/ridergoster/captain_sonar_cpp.git
```

- installer la librarie boost :

```sh
$ brew install boost
```

- trouver l'installation de boost sur le disque :

```sh
$ brew info boost
boost: stable 1.64.0 (bottled), HEAD
Collection of portable C++ source libraries
https://www.boost.org/
/usr/local/Cellar/boost/1.64.0_1 (12,628 files, 395.7MB) *
```

- dans XCode, ajouter les configurations suivante dans target->Build Settings
```sh
[chemin de boost]/lib --> Search Paths --> Library Search Paths  
[chemin de boost]/include --> Search Paths --> Header Search Paths  
```

- ajouter les librairies suivantes dans le projet contenue dans le dossier [chemin de boost]/lib (faire un drag-drop sur le projet dans XCode)

```sh
libboost_thread-mt.dylib
libboost_system.dylib
```

### API:

pour utiliser l'API locale:

- se rendre dans le dossier captain_sonar_api

- installer les dépendances de l'API
```sh
$ npm install
```

- démarrer le serveur
```sh
$ node server.js
Listening on {{ PORT }}
```

