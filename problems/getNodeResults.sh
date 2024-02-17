#!/usr/bin/bash

# Tener los nodos de los resultados de las pruebas de A* e IDA* en un archivo
# y mostrarlas en consola seprando los nodos de A* e IDA* con un salto de linea
# Uso: ./getNodeResults.sh <archivo>

# Si no se proporciona un archivo, se muestra un mensaje de error
if [ $# -eq 0 ]; then
    echo "Uso: ./getNodeResults.sh <archivo>"
    exit 1
fi

# Se obtienen los nodos de los resultados de las pruebas de A* e IDA* en un archivo
# Las lineas que contienen los nodos son las que contienen la palabra son con el formato:
# Estado objetivo encontrado con distancia 14, nodos expandidos 3547754, tiempo 5.704468 segundos.
# Estado objetivo encontrado con distancia 14, nodos expandidos 3547754, tiempo 5.704468 segundos.

# Tambien, el archivo muestra primero los nodos de A* y luego las de IDA*. En el formato:
# A*
# Linea con informacion innecesaria
# Estado objetivo encontrado con distancia 14, nodos expandidos 3547754, tiempo 5.704468 segundos.
# IDA*
# Linea con informacion innecesaria
# Estado objetivo encontrado con distancia 14, nodos expandidos 3547754, tiempo 5.704468 segundos.

# Obtenemos el numero de linea que dice IDA*
lineaIDA=$(grep -n "IDA\*" $1 | cut -d: -f1)
lineas=$(wc -l $1 | cut -d" " -f1)

# Obtenemos los nodos de A* y las mostramos en consola (Recordamos eliminar la "," de los nodos)
echo "A*"
head -n $(($lineaIDA-1)) $1 | grep "Estado objetivo encontrado con distancia" | cut -d" " -f9 | tr -d ","
# Revisamos si la ultima prueba de A* fue exitosa. Para eso comparamos el numero de estados iniciales con el numero de estados evaluados
# Si el numero de estados iniciales es igual al numero de estados evaluados, entonces la prueba fue exitosa
# Si no, entonces la prueba no fue exitosa
# Obtenemos el numero de estados iniciales
estadosIniciales=$(head -n $(($lineaIDA-1)) $1 | grep "Estado inicial" | wc -l)
# Obtenemos el numero de estados evaluados
estadosEvaluados=$(head -n $(($lineaIDA-1)) $1 | grep "Estado objetivo encontrado" | wc -l)
# Comparamos los numeros, si son distintos, imprimimos "Estado no exitoso". En caso contrario, no imprimimos nada
if [ $estadosIniciales -ne $estadosEvaluados ]; then
    echo "Estado no exitoso"
fi

# Obtenemos los nodos de IDA* y las mostramos en consola
echo "IDA*"
tail -n $(($lineas-$lineaIDA-1)) $1 | grep "Estado objetivo encontrado con distancia" | cut -d" " -f9 | tr -d ","
# Revisamos si la ultima prueba de IDA* fue exitosa. Para eso comparamos el numero de estados iniciales con el numero de estados evaluados
# Si el numero de estados iniciales es igual al numero de estados evaluados, entonces la prueba fue exitosa
# Si no, entonces la prueba no fue exitosa
# Obtenemos el numero de estados iniciales
estadosIniciales=$(tail -n $(($lineas-$lineaIDA-1)) $1 | grep "Estado inicial" | wc -l)
# Obtenemos el numero de estados evaluados
estadosEvaluados=$(tail -n $(($lineas-$lineaIDA-1)) $1 | grep "Estado objetivo encontrado" | wc -l)
# Comparamos los numeros, si son distintos, imprimimos "Estado no exitoso". En caso contrario, no imprimimos nada
if [ $estadosIniciales -ne $estadosEvaluados ]; then
    echo "Estado no exitoso"
fi
