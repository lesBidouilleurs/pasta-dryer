# pasta-dryer
Projet pour rendre programmable un séchoir à pâtes avec Arduino

**Fonctionnement de départ :** Le séchoir actuel permet de définir une température et un taux d'humidité à atteindre pendant un temps donné.

**Problématique :** Ce fonctionnement impose la présence de quelqu'un pour changer ces valeurs et relancer les cycles.

**Objectif :** automatiser ces cycles.

## Description d'un cycle
Un cycle se compose d'un temps de séchage, d'une pause, puis d'un temps de refroidissement.

- **ventilation** : Maintenir un taux d'humidité et une température pendant X minutes.
- **pause** : On coupe tout pendant X minutes.
- **refroidissement** : Maintenir un taux d'humidité et une température pendant X minutes.

## Description du séchoir
Le séchoir est composé d'une résistance de chauffage, de deux ventilateurs (l'un d'eux peut changer de sens), d'un capteur d'hygrométrie et d'un capteur de température.

## Choix techniques
Nous ne souhaitons pas supprimer le fonctionnement d'origine et permettre de faire fonctionner en parallele l'ancienne partie commande et la nouvelle.

Nous utilisons un aurduino Uno, et quatre relais qui permettront de commander la partie puissance présente a l'origine dans le séchoir. Actuellement nous faisons le choix de ne pas utiliser les capteurs d'origine mais d'utiliser un DHT22 (AM2302).
