# PenGuard - Gestionnaire de Mots de Passe

PenGuard est un gestionnaire de mots de passe simple et sécurisé développé en C++ avec la bibliothèque GTKmm. En plus de stocker vos mots de passe en toute sécurité, PenGuard propose également une fonction de génération d'identifiants aléatoires pour renforcer la sécurité de vos comptes en ligne.

## Fonctionnalités

- **Stockage sécurisé des mots de passe :** PenGuard utilise une encryption robuste (AES) pour garantir la sécurité de vos informations sensibles.
  
- **Génération d'identifiants aléatoires :** Créez des identifiants forts et aléatoires pour renforcer la sécurité de vos comptes en ligne.

- **Interface utilisateur conviviale :** L'interface graphique intuitive, basée sur GTKmm, facilite la gestion de vos mots de passe.

## Captures d'écran

![Capture d'écran 1](/src/assets/screenshots/login.png)
*écran de connexion*

![Capture d'écran 2](/src/assets/screenshots/logged.png)
*page d'acceuil affichant tout les mot de passe de votre compte*

## Prérequis

- **GTKmm :** Assurez-vous d'avoir GTKmm installé sur votre système. Vous pouvez le télécharger [ici](https://www.gtkmm.org/).

- **mysql-lib-dev** Assurez-vous d'avoir mysql-lib et mysql installé sur votre système. Vous pouvez le télécharger avec cette commande :
```bash
sudo apt install libmysqlcppconn-dev
```

- **crypto++** Assurez-vous d'avoir Crypto++ sur votre système. Vous pouvez le télécharger avec cette commande :
```bash
sudo apt-get install libcrypto++-dev
```
 
- **Compilateur C++ :** Un compilateur C++ compatible C++11 est nécessaire. Vous pouvez utiliser GCC, Clang, ou tout autre compilateur compatible.

## Compilation et exécution

1. Clonez le dépôt Git :

```bash
git clone https://github.com/votre_utilisateur/PenGuard.git
cd PenGuard
make run
```

## Contributions

Les contributions sont les bienvenues ! Si vous souhaitez contribuer à PenGuard, veuillez soumettre une demande d'extraction (pull request) avec vos modifications.

## Licence

Ce projet est sous licence MIT.
