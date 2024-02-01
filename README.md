# Objetivo

El objetivo del proyecto es aprender sobre el modelo de espacio de estados y sobre
los diferentes algoritmos de b&uacute;squeda heur&iacute;stica. No s&oacute;lo se
evaluar&aacute; la correctitud de la implementaci&oacute;n; es importante que los
algoritmos sean eficientes y puedan resolver los problemas propuestos en los
tiempos estipulados. Tambi&eacute;n es importante su &aacute;nalisis de resultados en el informe.

Para el proyecto se usará el lenguaje declarativo PSVN, con su conjunto de herramientas y documentación que será
entregada a los estudiantes. **Se recomienda leer detenidamente los ejemplos, instrucciones y herramientas que vienen
incluidas**, recuerde que todo lo que se incluye es para facilitar el trabajo en el proyecto.

Será necesario utilizar C o C++ para trabajar con el API de PSVN y la implementación
de algoritmos de búsqueda, para lo cuál también se incluyen ejemplos.

# Problemas

Consideramos los siguientes problemas:

* N-puzzles: 15-puzzle y 24-puzzle
* Cubo de Rubik: 3x3x3
* Top spin: 12-4, 14-4, y 17-4
* Torre de Hanoi con 4 astas: 12, 14, y 18 discos

Se requiere que incluya representaciones en PSVN para cada uno de los dominios. Para los N-Puzzle, es útil revisar las lecciones incluidas,
pues encontrará ejemplos muy similares que ayudarán a realizar sus representaciones.

En el caso de los demás problemas, encontrará representaciones incluídas junto a PSVN, o en su defecto generadores para las mismas. Debe
leer la información incluída para entender cómo funcionan estas representaciones.

Debe incluir como parte de la entrega las representaciones en PSVN utilizadas para cada problema, así como una **breve** explicación

# &Aacute;rboles de b&uacute;squeda

Estudiar los &aacute;rboles de b&uacute;squeda y su factor de ramificaci&oacute;n sin
eliminaci&oacute;n de duplicados y con eliminaci&oacute;n parcial de duplicados (poda de ancestros).
Se deben crear tablas para cada problema donde se reporte el n&uacute;mero de estados
a cada profundidad en el &aacute;rbol de b&uacute;squeda a partir del estado objetivo,
hasta la profundidad m&aacute;xima que se alcance en 15 minutos de ejecuci&oacute;n.

Puede utilizar el código incluído con PSVN como ayuda para calcular esto.

# Heur&iacute;sticas

Se deben implementar heur&iacute;sticas PDBs para cada problema. Para los n-puzzles
las PDBs deben ser aditivas. Para los otros problemas, se toma el m&aacute;ximo de
varias PDBs. Leer el paper "Additive Pattern Databases" de Felner et al. que se
incluye, y el paper sobre el Cubo de Rubik. Para el Cubo de Rubik, las PDBs 
est&aacute;ndar pueden tomar demasiado espacio; en ese caso, se pueden crear mas
PDBs de menor tama&ntilde;o.

En la documentación de PSVN hay secciones indicando como elaborar PDBs utilizando el lenguaje,
así como ejemplos de ello. Deben incluir todos los archivos que utilicen para generarlos.

# Algoritmos informados

Estudiar la b&uacute;squeda de *soluciones &oacute;ptimas* con algoritmos informados.
Buscar soluciones para las instancias dadas en cada problema utilizando los algoritmos:
A* con eliminaci&oacute;n retardada de duplicados (DDD) e IDA* con eliminaci&oacute;n
parcial de duplicados. Para las heur&iacute;sticas en cada problema:
* N-puzzles: distancia Manhattan (15-puzzle) y diferentes additive PDBs (15- y 24-puzzle)
* Cubo de Rubik: max de corner PDB y 2 edge PDBs (si son demasiado grandes, dividirlas en varias PDBs peque&ntilde;as)
* Top Spin: max de diferents PDBs
* Torre de Hanoi con 4 astas: max de diferentes PDBs

El tiempo m&aacute;ximo de ejecuci&oacute;n lo deciden ustedes seg&uacute;n los
recursos que tengan a su disposici&oacute;n. Para A*, no permitan que el programa
utilice memoria virtual (paginaci&oacute;n sobre disco) ya que posiblemente correr&aacute; extremadamente
lento y no podr&aacute;n resolver el problema (y la m&aacute;quina se les "congelar&aacute;").

# Casos de prueba

Se entregan casos de prueba para los n-puzzles y para el Cubo de Rubik. Para los
problemas restantes deben generar casos de prueba con el programa global/generator.cc
que se entrega en la distribuci&oacute;n de PSVN. Leer el programa para entenderlo
y poder ejecutarlo. Se deben generar casos de prueba f&aacute;ciles y dif&iacute;ciles.

Deben entregar su implementación de la solución junto a un informe que explique las decisiones tomadas y los resultados de sus ejecuciones.


