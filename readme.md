# Netlist Viewer
***
## Description
Projet de 1ère année de master semestre 1 de l'UE Modelisation objet pour la conception de circuit.
Le but étant de concevoir en C++ / Qt un logiciel de visualisateur de netlist prenant en source des descriptions en xml de circuit numérique et de les afficher.

## Configuration
```sh
cd NetlistViewer/build
cmake ../src
make install
./NetlistViewer
```
## Résultat 

Schéma transistors porte logique OR à deux entrées : 
![plot](./images/or2.png?raw=true "OR gate")

Schéma d'un halfadder (1 bit)
![plot](./images/halfadder.png?raw=true "halfadder")

Schéma d'un fulladder (1 bit)
![plot](./images/fulladder.png?raw=true "fulladder")