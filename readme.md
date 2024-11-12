# Proyecto: Nombre de tu proyecto
Escribe aquí un overview general de tu proyecto

## Descripción del avance 1
https://github.com/famchiyaque/Proyecto-Avance-1

## Descripción del avance 2
https://github.com/famchiyaque/Simulador-Sportsbook-NFL

### Cambios sobre el primer avance
Cada avance fue hecho por aparte. Cada uno tiene su descripcion en su propio read.me

## Descripción del avance 3
Este programa simula el mapa de una ciudad y segun la posicion del usuario y su destino,
ofrece la ruta mas corta para llegar utilizando el algoritmo BFS. El usuario puede seguir 
ahi, ir de un lugar a otro, y ver el resultado de la ruta optima siempre en un archivo
que se genera cada vez 'ruta.txt'.
Refriése a la imagen que viene en esta carpeta, que es un diagrama de este ciudad imaginaria
'Neoland'. Verifique también que las respuestas dadas por el programa realmente son correctas
con ese diagrama.
Este programa es un prototipo, y podría implementarse en una ciudad muchísima más grande.
Solo habría que agregar más detalle a los archivos de conexiones y nombres.

### Cambios sobre el segundo avance
El segundo avance y este son separados.

## Instrucciones para compilar el avance de proyecto
Ejecuta el siguiente comando en la terminal:

`g++ -std=c++11 main.cpp`  

## Instrucciones para ejecutar el avance de proyecto
Ejecuta el siguiente comando en la terminal:

`./a.exe`, o como se llame el archivo generado a partir del comando anterior  

## Descripción de las entradas del avance de proyecto
Este programa empieza leyengo un archivo con todas las conexiones que tiene esta ciudad, 
es decir cuales lugares estan conectados con cuales otros (hay una conexion entre el estadio 
y el parque central). 
Luego lee un archivo de todos los lugares, y los coloca en un vector para uso en el futuro.
El programa le muestra al usuario, que empieza en el lugar 0, su casa, todos los lugares de la
ciudad y le pide un destino. De ahi llama el algoritmo para determinar la mejor ruta.

## Descripción de las salidas del avance de proyecto
Al ingresar el destino, el programa genera un nuevo archivo 'ruta.txt' y ahi escribe los pasos
a seguir para llegar al destino desde el lugar actual del usuario, siempre la ruta mas corta.

## Desarrollo de competencias

### SICT0301: Evalúa los componentes
#### Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.
(Esto viene del avance 1, que otra vez no tiene que ver con este programa)
Para este programa, el método de ordenamiento elegido es el merge sort, debido a que entre selection sort, insertion sort, y merge sort, es el más rápido de los 3 en promedio, y en su peor caso (caso que más le puede costar al algoritmo en términos de tiempo). Tiene un tiempo de complejidad fijo de O(n log(n)) siempre, solo al costo de ocupar doble el espacio de memoria que los otros 2, que, para este proyecto, no es un problema. Los otros dos tienen como promedio un tiempo de complejidad de O(n^2), que para este caso podría funcionar como el dataset es pequeño pero para las buenas prácticas, utilizaremos el método más rapido.

#### Hace un análisis de complejidad correcto y completo de todas las estructuras de datos y cada uno de sus usos en el programa.
(Esto viene del avance 2, no este programa)
Aquí hago uso de la estructura más sencilla para guardar datos que es el vector, e inicializo 3 al inicio
del programa, cada uno que servirá de otra cosa:
    vector<string> bet_lines = {""}; n = cantidad de apuestas disponibles
        - push_back() para guardar las apuestas dadas en el primer archivo: O(1) en promedio
        - accedimiento de cada elemento para una lectura completa para la interfaz al usuario: O(n) (pero es necesario)
    vector<Bet> user_bets; n = cantidad de apuestas creadas por el usuario
        - utiliza push_back(Bet) de los bets creados: O(1) en promedio
        - accedimiento para hacer cálculos finales a cada elemento: O(n)
    vector<int> bet_results = {0}; n = cantidad de resultados de las apuestas
        - push_back() durante lectura O(1)
        - accedimiento directo para comparar resultados con apuestas O(1)

    Parlay parlay = Parlay(); **Una lista ligada**
        - inicialización: O(1)
        - undoBet(): O(1)
        - addBet(): O(1)
        - gradeParlay(): O(n) n = cantidad de apuestas en el parlay

Yo creo que cumplo con esta competencia porque en **ningún lugar en mi programa, si fueras a hacer más grandes los archivos o si un usuario creara mil apuestas y/o un parlay de 10,000 apuestas, existiría un proceso/algoritmo que tenga una complejidad de tiempo peor a O(n)**. 
De hecho cuando iba a programar la parte de evaluar las apuestas, iba a hacer un for loop añadido que
correría por cada apuesta, sacar el nombre del jugador, y iterar por todo el archivo hasta encontrar 
la línea correspondiente, pero eso sería muy tardado a gran escala. Por eso creé el vector de 
resultados, que itera por el archivo de resultados solamente una vez, y luego las apuestas pueden
acceder a las resultados por su index con O(1).

#### Hace un análisis de complejidad correcto y completo para todos los demás componentes del programa y determina la complejidad final del programa.
1. La Inicialización:  O(n) n = # de lugares en la ciudad
explicación a fondo
2. El Algoritmo BFS:  O(n + log(n)) n = # de lugares en la ciudad
explicación a fondo
3. En su Totalidad:  O(2n + log(n))

Este programa, al ser por aparte de mis otros, no trae mucho que analizar porque solo tiene una función, 
que es crear la ciudad y luego encontrar rutas. Pero entre todos los avances, estos son los tiempos de
complejidad de cada uno:
1. Bingo NFL (ordenamiento y búsqueda): O(n log(n) + log(n))
2. Simulador Sportsbook NFL (lista ligada, vector): O(n)
3. Waze Chaffa (queues, BFS): O(2n + log(n))


### SICT0302: Toma decisiones
#### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.
(Del avance 1)
Ya que los vectores están ordenados, el programa itera por los valores del vector de guesses del usuario, y para cada valor utiliza el método de búsqueda binaria en el vector de los puntajes finales reales para ver si el guess del usuario fue correcto y determinar el score total del usuario. Necesita 3/5 mínimo para ganar.
Igual que antes, este método de búsqueda es para optimizar el programa en términos del tiempo. La búsqueda secuencial normal tiene un a complejidad de tiempo de O(n) (n siendo el número de elementos del vector), mientras que la búsqueda binaria tiene una complejidad de tiempo de O(log(n)).

#### Selecciona una estructura de datos adecuada al problema y la usa correctamente.
Lo que buscaba era una manera de proporcionar la opción de 'undo' en la creación del parlay, igual como
los casos en la vida real que usan listas ligadas. La lista ligada en este programa, o parlay, es una lista
de tipo stack, porque la última apuesta que entra, es la que se elimina al llamar en 'undoBet' función.
Last In First Out. El 'undoBet' es como un 'pop', donde el pop saca el último element en agregarse.
El problema con las listas es la iteración/búsqueda de elementos, pero en este caso la
búsqueda no era necesaria, y la iteración solamente se ocupa al terminar las apuestas y para 
evaluar cada apuesta del parlay y ver que cada una salió bien para que el usuario pueda ganar. En ese caso,
la iteración de O(n) es necesario.

### SICT0303: Implementa acciones científicas
#### Implementa mecanismos para consultar información de las estructras correctos.
El accedimiento a las esctructuras de datos en este programa, que son vectores y una lista ligada, siempre
son optimizadas. La iteración de la lista ligada tiene O(n), y es necesario al evaluarse. Luego durante esa 
evaluación, el vector de resultados proporciona la información para evaluar cada apuesta y siempre se le 
accede con un index y por lo tanto O(1).

#### Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.
Utilizando ifstream, se leen los archivos línea por línea y las carga en vectores para que el programa más adelante pueda acceder a la información de forma inmediata con un index O(1).

### Implementa mecanismos de escritura de archivos para guardar los datos de las estructuras de manera correcta
Este último programa, mi avance 3, al completar el algoritmo de econtrar la ruta, genera un archivo
para el usuario y ahí escribe línea por línea el camino más corto para el usuario. Es funcional.