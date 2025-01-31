# Philosophers

## // INTRO

* Voici le Milestone 3, le projet : Philosophers
* En cours.

## /. HELP

* Voir le pdf de Philosophers qui explique parfaitement le projet.

* Les deux cas à éviter sont:

Les deadlock (pas celui de Valo):
```c
// Attente de mutex_b
void    function1()
{
    pthread_mutex_lock(&mutex_a);
    pthread_mutex_lock(&mutex_b);
    x = 5;
    pthread_mutex_unlock(&mutex_b);
    pthread_mutex_unlock(&mutex_a);
}

// Attente de mutex (déja verrouillé par function1).
void    function2()
{
    pthread_mutex_lock(&mutex_b);
    pthread_mutex_lock(&mutex_a);
    x = 10;
    pthread_mutex_unlock(&mutex_a);
    pthread_mutex_unlock(&mutex_b);
}
```
* Les data races:
```c
// x est protégé par mutex_a.
void function1() {
    pthread_mutex_lock(&mutex_a);
    x = 5;
    pthread_mutex_unlock(&mutex_a);
}

// x est protégé par mutex_b (alors qu'il est déjà protégé par mutex_a).
void function2() {
    pthread_mutex_lock(&mutex_b);
    x = 10;
    pthread_mutex_unlock(&mutex_b);
}
```
* La règle est qu'il ne faut protégé des variables que par un même mutex.

##	/: EOF

Modifié le 2 Janvier 2025 par Juste.
