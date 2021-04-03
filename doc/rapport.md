# Rapport TP Fitts

## 1. Donner une critique de l'interface fournie et du programme QT associé

- La formule mathématique n'apparait pas à l'écran

- Le titre des groupe box n'est pas assez visible

## 2. Rendre plus conforme au modèle MVC

**Pour l'instant :**

- Le Modèle construit la Vue qui construit le Contrôleur

- Toutes les Vues sont regroupées dans une seule classe

- Les classes sont toutes `friend` entre elles, elles devrait utiliser `getteurs` et `setteurs`

**Les changements à opérer :**

- Le Contrôleur devrait être instancié en premier avec un Modèle puis seulement après le Contrôleur instancie une Vue.

- Les trois Vues devraient être séparées :
  
  - Vue des paramètres
  
  - Vue expérimentale
  
  - Vue résultat (graphique)

- Les classes ne doivent plus être `friend` entre elles.

- Les classes doivent utiliser des accesseurs pour récupérer les données.
