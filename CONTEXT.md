# 🛡️ PROJET : C-Bootcamp (SISR)

## 🎯 Objectif Mensuel
Créer un outil de démonstration technique type "Ransomware Local" (XOR Encrypter) pour comprendre la gestion bas niveau de la mémoire et des fichiers.

## ⚙️ Stack Technique
* **OS Dev :** Linux (WSL/Native)
* **Langage :** C (Standard C99/C11)
* **Compilation Cible :** Windows (via MinGW-w64)
* **Contraintes :** Pas de bibliothèques haut niveau inutiles, gestion manuelle de la mémoire.

## 📅 Progression
* [x] Semaine 1 : Compréhension des types et pointeurs.
* [ ] Semaine 1 : Outil "Binary Probe" (Hexdumper basique avec fopen/fseek).
* [ ] Semaine 2 : API Windows & Processus.
* [ ] Semaine 3 : Algorithme de chiffrement XOR.
* [ ] Semaine 4 : Assemblage final.

## 📝 État Actuel
Je suis en train de coder le `main.c` pour l'exercice "Seeker". Je dois utiliser `fseek` et `ftell` pour récupérer la taille d'un fichier binaire sans le lire entièrement.

## 🧠 Acquis & Règles (Ne pas répéter)
1. **Règle d'Or :** Ne jamais me donner la solution complète. Donne-moi des indices ou la logique. Je veux coder moi-même ("Hard Way").
2. **Mémoire :** J'ai compris pourquoi `unsigned char` est obligatoire pour le binaire (problème du signe -1 vs 255).
3. **Sécurité :** Toujours vérifier les retours de `fopen` et `malloc`.
4. **Style :** Pas de `scanf` (%s), utilisation de `fgets` ou lecture binaire stricte.
5. **Dette technique :** Je dois encore maîtriser parfaitement l'arithmétique de pointeurs.