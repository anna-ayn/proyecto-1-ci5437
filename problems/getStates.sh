#!/usr/bin/bash

# Tener los estados evaluados de los resultados de las pruebas de A* e IDA* en un archivo
# y mostrarlas en consola seprando los estados evaluados de A* e IDA* con un salto de linea
# Uso: ./getStates.sh <archivo>

# Si no se proporciona un archivo, se muestra un mensaje de error
if [ $# -eq 0 ]; then
    echo "Uso: ./getStates.sh <archivo>"
    exit 1
fi

# Se obtienen los estados evaluados de los resultados de las pruebas de A* e IDA* en un archivo
# Las lineas que contienen los estados evaluados son las que contienen la palabra son con el formato:
# Estado inicial: 16 10 4 9 14 6 13 3 5 15 8 0 7 2 1 12 11 (El estado en si puede tener cualquier formato)

# Tambien, el archivo muestra primero los estados evaluados de A* y luego las de IDA*. En el formato:
# A*
# Linea con informacion innecesaria
# Estado inicial: 16 10 4 9 14 6 13 3 5 15 8 0 7 2 1 12 11 (El estado en si puede tener cualquier formato)
# IDA*
# Linea con informacion innecesaria
# Estado inicial: 16 10 4 9 14 6 13 3 5 15 8 0 7 2 1 12 11 (El estado en si puede tener cualquier formato)

# Obtenemos el numero de linea que dice IDA*
lineaIDA=$(grep -n "IDA\*" $1 | cut -d: -f1)
lineas=$(wc -l $1 | cut -d" " -f1)

# Obtenemos los estados evaluados de A* y las mostramos en consola
echo "A*"
head -n $(($lineaIDA-1)) $1 | grep "Estado inicial" | cut -d" " -f3-
# Revisamos si la ultima prueba de A* fue exitosa. Para eso comparamos el numero de estados iniciales con el numero de estados evaluados
# Si el numero de estados iniciales es igual al numero de estados evaluados, entonces la prueba fue exitosa
# Si no, entonces la prueba no fue exitosa
# Obtenemos el numero de estados iniciales
estadosIniciales=$(head -n $(($lineaIDA-1)) $1 | grep "Estado inicial" | wc -l)
# Obtenemos el numero de estados evaluados
# Para obtener el numero de estados evaluados, buscamos las lineas que contienen "Estado objetivo encontrado" o "Tiempo de ejecución excedido"
# Si la linea contiene "Estado objetivo encontrado" o "Tiempo de ejecución excedido", entonces la linea contiene un estado evaluado
estadosEvaluados=$(head -n $(($lineaIDA-1)) $1 | grep -E "Estado objetivo encontrado|Tiempo de ejecución excedido" | wc -l)
# Comparamos los numeros, si son distintos, imprimimos "El ultimo estado mato el proceso". En caso contrario, no imprimimos nada
if [ $estadosIniciales -ne $estadosEvaluados ]; then
    echo "El ultimo estado mato el proceso"
fi

# Obtenemos los estados evaluados de IDA* y las mostramos en consola
echo "IDA*"
tail -n $(($lineas-$lineaIDA)) $1 | grep "Estado inicial" | cut -d" " -f3-
# Revisamos si la ultima prueba de IDA* fue exitosa. Para eso comparamos el numero de estados iniciales con el numero de estados evaluados
# Si el numero de estados iniciales es igual al numero de estados evaluados, entonces la prueba fue exitosa
# Si no, entonces la prueba no fue exitosa
# Obtenemos el numero de estados iniciales
estadosIniciales=$(tail -n $(($lineas-$lineaIDA)) $1 | grep "Estado inicial" | wc -l)
# Obtenemos el numero de estados evaluados
# Para obtener el numero de estados evaluados, buscamos las lineas que contienen "Estado objetivo encontrado" o "Tiempo de ejecución excedido"
# Si la linea contiene "Estado objetivo encontrado" o "Tiempo de ejecución excedido", entonces la linea contiene un estado evaluado
estadosEvaluados=$(tail -n $(($lineas-$lineaIDA)) $1 | grep -E "Estado objetivo encontrado|Tiempo de ejecución excedido" | wc -l)
# Comparamos los numeros, si son distintos, imprimimos "El ultimo estado mato el proceso". En caso contrario, no imprimimos nada
if [ $estadosIniciales -ne $estadosEvaluados ]; then
    echo "El ultimo estado mato el proceso"
fi
