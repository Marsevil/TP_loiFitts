# Rapport TP Fitts

## 1. Donner une critique de l'interface fournie et du programme QT associé

- On ne voit pas la formule

- Le titre des groupe box n'est pas assez visible

## 2. Rendre plus conforme au modèle MVC

**Pour l'instant :**

- Le Model construit la vue qui construit le contrôleur

- Toutes les vues sont regroupé dans une seule classe

- Les classes sont toutes `friend` entre elles, elles devrait utiliser `getteurs` et `setteurs`

**Les changements à opéré :**

- Le contrôleur devrait être instancier en premier avec un modèle puis seulement après le contrôleur instancie une vue.

- Les trois vues devrait être séparé :
  
  - vue des paramètres
  
  - vue expérimentale
  
  - vue résultat (graphique)

- Les classes ne doivent plus être `friend` entre elles.

- Les classes doivent utiliser des accesseurs pour récupérer les données.
