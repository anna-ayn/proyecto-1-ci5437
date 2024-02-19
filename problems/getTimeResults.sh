#!/usr/bin/bash

# Tener los tiempos de los resultados de las pruebas de A* e IDA* en un archivo
# y mostrarlas en consola seprando los tiempos de A* e IDA* con un salto de linea
# Uso: ./getTimeResults.sh <archivo>

# Si no se proporciona un archivo, se muestra un mensaje de error
if [ $# -eq 0 ]; then
    echo "Uso: ./getTimeResults.sh <archivo>"
    exit 1
fi

# Se obtienen los tiempos de los resultados de las pruebas de A* e IDA* en un archivo
# Las lineas que contienen los tiempos son las que contienen la palabra son con el formato:
# Estado objetivo encontrado con distancia 14, nodos expandidos 3547754, tiempo 5.704468 segundos.
# Estado objetivo encontrado con distancia 14, nodos expandidos 3547754, tiempo 5.704468 segundos.
# Si excedieron el tiempo limite, se muestra el mensaje la linea tiene el formato:
# Tiempo de ejecución excedido

# Tambien, el archivo muestra primero los tiempos de A* y luego las de IDA*. En el formato:
# A*
# Linea con informacion innecesaria
# Estado objetivo encontrado con distancia 14, nodos expandidos 3547754, tiempo 5.704468 segundos.
# Linea con informacion innecesaria
# Tiempo de ejecución excedido
# IDA*
# Linea con informacion innecesaria
# Estado objetivo encontrado con distancia 14, nodos expandidos 3547754, tiempo 5.704468 segundos.
# Linea con informacion innecesaria
# Tiempo de ejecución excedido

# Obtenemos el numero de linea que dice IDA*
lineaIDA=$(grep -n "IDA\*" $1 | cut -d: -f1)
lineas=$(wc -l $1 | cut -d" " -f1)

# Obtenemos los tiempos de A* y las mostramos en consola
echo "A*"
# El grep busca las lineas que contienen "Estado objetivo encontrado con distancia" o "Tiempo de ejecución excedido". (flag -E para usar expresiones regulares)
# Es decir, cumplen la expresion regular "Estado objetivo encontrado con distancia" o "Tiempo de ejecución excedido"
# Expresion regular: "Estado objetivo encontrado con distancia|Tiempo de ejecución excedido"
# El sed elimina la parte de la linea que no es el tiempo (flag -n para no imprimir las lineas por defecto, p para imprimir la linea actual)
# El cut obtiene el tiempo (flag -d para especificar el delimitador y -f para especificar el campo)
head -n $(($lineaIDA-1)) $1 | grep -E "Estado objetivo encontrado con distancia|Tiempo de ejecución excedido" > getTimeResults.tmp
# Iteramos sobre las lineas del archivo temporal
while read linea; do
    # Si la linea contiene "Estado objetivo encontrado con distancia", entonces obtenemos el tiempo y se cambia el "." por ","
    if echo $linea | grep -q "Estado objetivo encontrado con distancia"; then
        echo $linea | cut -d" " -f11 | tr . ,
    # Si la linea contiene "Tiempo de ejecución excedido", entonces imprimimos el mensaje
    else
        echo "Tiempo de ejecución excedido"
    fi
done < getTimeResults.tmp

# Revisamos si la ultima prueba de A* fue exitosa. Para eso comparamos el numero de estados iniciales con el numero de estados evaluados
# Si el numero de estados iniciales es igual al numero de estados evaluados, entonces la prueba fue exitosa
# Si no, entonces la prueba no fue exitosa
# Obtenemos el numero de estados iniciales
estadosIniciales=$(head -n $(($lineaIDA-1)) $1 | grep "Estado inicial" | wc -l)
# Obtenemos el numero de estados evaluados
estadosEvaluados=$(head -n $(($lineaIDA-1)) $1 | grep -E "Estado objetivo encontrado con distancia|Tiempo de ejecución excedido" | wc -l)
# Comparamos los numeros, si son distintos, imprimimos "El ultimo estado mato el proceso". En caso contrario, no imprimimos nada
if [ $estadosIniciales -ne $estadosEvaluados ]; then
    echo "El ultimo estado mato el proceso"
fi

# Obtenemos los tiempos de IDA* y las mostramos en consola
echo "IDA*"
tail -n $(($lineas-$lineaIDA)) $1 | grep -E "Estado objetivo encontrado con distancia|Tiempo de ejecución excedido" > getTimeResults.tmp
# Iteramos sobre las lineas del archivo temporal
while read linea; do
    # Si la linea contiene "Estado objetivo encontrado con distancia", entonces obtenemos el tiempo y se cambia el "." por ","
    if echo $linea | grep -q "Estado objetivo encontrado con distancia"; then
        echo $linea | cut -d" " -f11 | tr . ,
    # Si la linea contiene "Tiempo de ejecución excedido", entonces imprimimos el mensaje
    else
        echo "Tiempo de ejecución excedido"
    fi
done < getTimeResults.tmp

# Revisamos si la ultima prueba de IDA* fue exitosa. Para eso comparamos el numero de estados iniciales con el numero de estados evaluados
# Si el numero de estados iniciales es igual al numero de estados evaluados, entonces la prueba fue exitosa
# Si no, entonces la prueba no fue exitosa
# Obtenemos el numero de estados iniciales
estadosIniciales=$(tail -n $(($lineas-$lineaIDA)) $1 | grep "Estado inicial" | wc -l)
# Obtenemos el numero de estados evaluados
estadosEvaluados=$(tail -n $(($lineas-$lineaIDA)) $1 | grep -E "Estado objetivo encontrado con distancia|Tiempo de ejecución excedido" | wc -l)
# Comparamos los numeros, si son distintos, imprimimos "El ultimo estado mato el proceso". En caso contrario, no imprimimos nada
if [ $estadosIniciales -ne $estadosEvaluados ]; then
    echo "El ultimo estado mato el proceso"
fi

# Eliminamos el archivo temporal
rm getTimeResults.tmp