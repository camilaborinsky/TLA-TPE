# Lenguaje DOBBY
#### Teoría de Lenguajes, Automatas y Compiladores : TPE
Creamos el lenguaje *Dobby* para facilitar la programación de ascii art animada para la terminal. Para esto diseñamos tipos de datos y funciones que conforman un lenguaje para manipular figuras y sus interacciones durante su ciclo de vida. 

![](https://i.imgur.com/JeR7tss.jpg)

## Autores
* Camila Borinsky
* Agustin Jerusalinsky
* Agustin Tormakh
## Indice

[toc]

## Compilación y Ejecución

### Compilación del compilador
```
make parser
```

### Compilación de un programa
```
make compile FROM=<origin> TO=<destination>
make compile FROM=tests/jumping.td
make compile FROM=tests/types.td TO=program
```

### Tests
jumping.td : programa de prueba que al compilar y ejecutar dibuja una figura que se puede hacer saltar apretando la barra espaciadora.
strings.td : programa de prueba que va concatenando lo que escribas en el teclado e imprimiendo en pantalla.
echo.td : Lee de STDIN y escribe a STDOUT 
types.td : Imprime en pantalla una instancia o ejemplo de todos los tipos que soporta el lenguaje.
fill.td : si se oprime un nro x entre 0 y 9 se hace un fill de la pantalla de (x*10)%. Es decir si se oprime un 1 se llena un 10% de la pantalla, un 2 un 20%, etc. 


## Idea subyacente y objetivo del lenguaje
La idea del lenguaje como se mencionó brevemente es proveer un ambiente amigable para el desarrollo de pequeñas animaciones en la terminal mediante código.

Los que han lidiado con el interfaces gráficas a bajo nivel sabrán que no es algo simple y por lo general requiere de conocimiento y muchas biblotecas, además de ser un trabajo tedioso. Con nuestro lenguaje se pueden dibujar figuras, simples y complejas (haciendo uso de la union de figuras). A su vez se pueden generar *key listeners* para ejecutar una función al apretarse alguna tecla, e *interval callbacks* para ejecutar una función cada *x* ms. Permitimos también poder elegir en que punto de la pantalla se quiere dibujar, haciendo más fácil la tarea de alinear figuras. 

## Consideraciones realizadas

Nuestro lenguaje cuenta con algunas características propias que nos resulta relevante remarcar.

Sobre la estructura de los programas podemos decir que inicialmente se pueden declarar funciones y variables globales. A partir de la primera sección de código que sea para ejecutarse comienza una sección de código que ya no permite la declaración de nuevas funciones pero si de nuevas variables. 

Otra característica de nuestro lenguaje es que todas las funciones deben finalizar con una sentencia return. No se permite hacer más de una sentencia *return* y nuestra gramática tampoco permite que este en algún lado que no sea la última sentencia de la función. Si el tipo de retorno de la función es de tipo void entonces podrá hacerse:
```
return;
```
al final de la función. 

Más adelante mencionaremos funciones para poder dibujar en pantalla figuras, etc. Haremos uso de coordenadas x, y para situar las figuras y el texto que se quiere ver en pantalla. Estas coordenadas se toman desde la esquina superior izquierda como punto de referencia. 

## Descripción del desarrollo del TP
Para resumir brevemente la realización del trabajo práctico podemos dividir el desarrollo en 4 partes:
#### 1. Pensar el lenguaje y su gramática 
Inicialmente discutimos ideas posibles, así como también pensamos como iban a ser las producciones de nuestra gramática. En esta parte pensamos qué nuevos tipos de datos y funciones introduciríamos para poder brindar el servicio de poder dibujar en la terminal de manera intuitiva. También decidimos que nuestro compilador produciría código en C. Al ser el objetivo de nuestro lenguaje tan distinto a la naturaleza de C nos pareció adecuado, además de que la implementación de las funcionalidades que queríamos proveer nos resultaba más conveniente escribirlo en C. Lógicamente durante el proceso de desarrollo la gramática sufrió varios cambios respecto a como la planteamos inicialmente, debido a bugs y conflictos encontrados además de nuevas features que queríamos agregarle y algunos easter eggs :egg:.

![](https://i.imgur.com/oAVLIUV.jpg)

#### 2. Avanzamos con 2 tareas en paralelo
#### a. Implementación de las nuevas funcionalidades
Por un lado tuvimos que implementar los nuevos tipos y funciones que queríamos que sean de fácil acceso y parte de nuestro lenguaje. Decidimos que nuestro lenguaje no iba a tener punteros sino que ibamos a trabajar directamente con referencias. Esto hace también que el lenguaje sea mucho más seguro de usar y no tan propenso a encontrar Null Pointer Exceptions u otro tipo de excepciones que ocurren a la hora de trabajar directamente con direcciones de memoria. Utilizamos *ncurses* para la implementación de la parte gráfica.

#### b. Diseño del AST e implementación de reglas del archivo.y
Si bien era una opción no contar con un **AST** para generar el código, decidimos que la mejor idea era crear uno ya que esto hace que el lenguaje sea mucho más extensible, mantenible y le da claridad al código. De esta forma delegamos todo el análisis semántico al módulo del árbol. La validez de las operaciones que se quieren realizar, validación de tipos, scopes y demás lo delegamos a este módulo. Lógicamente para armar correctamente el árbol nos apoyamos fuertemente sobre yacc y su posiblidad de asignar reglas respecto a los atributos de cada símbolo. Creamos distintos tipos de nodos para el árbol, cada uno con su funcionalidad semántica asociada. Esto nos permitió también modularizar la generación de código. 

En esta instancia también diseñamos la tabla de símbolos que usamos para guardar referencia de las variables que se van definiendo a lo largo del programa y para hacer la validación de scopes correspondientes. En la tabla de símbolos también viven referencias a las funciones. 

#### 3. Generación de código. 
Una vez planeada la arquitectura del árbol, la implementación de nuevas funcionalidades y teniendo la gramática prácticamente terminada comenzamos con lo que sería la generación de código. Como mencionamos elegimos c como lenguaje de salida. La estructura y el diseño que elegimos para el árbol permitió que pudieramos crear un módulo de generación de código que lidiara con cada tipo de nodo independiente. 

#### 4. Testing y uso
Luego pasamos a la parte de probar nuestro nuevo lenguaje, en busca de errores. Tuvimos que hacer modificaciones a la gramática y se nos fueron ocurriendo también cosas para arreglar y mejorar. 

## Descripción de la gramática
Para la sintaxis de nuestra gramática usamos como inspiración el lenguaje *Typescript* pero estrictamente tipado.

![](https://i.imgur.com/3It6lZv.jpg =700x)


Los tipos que manejamos son:
* int 
* double
* bool
* text
* **dot**
* **rectangle**
* **circle**
* **line**
* **figure**

Es obligatorio el uso de ; para el final de las instrucciones.

Los operadores lógicos son: **not**, **and**, **or**
Los operadores aritméticos son: +, -, *, /
Los operadores relacionales son: >, <, <=, >=, ==, !=

Las declaraciones son de la siguiente forma:
```
let variable_name : variable_type;
```

Las asignaciones son de la forma:
```
variable_name = expression;
```

También permitimos el siguiente tipo de instrucción pero esto solo se puede realizar dentro de un bloque tipo bucle, bloque de control o función. 
```
let variable_name : variable_type = expression;
```

La sintaxis para el bloque de bucle y de control es la siguiente:
```
if(condition){
    code
}

while(condition){
    code
}
```

Las funciones que tenemos para soporte de dibujo en la terminal son:
Esta primera lista para instanciar figuras:
```
rect_init(x, y, width, height);
circ_init(x, y, radius);
line_init(xfirst, yfirst, xsecond, ysecond);
dot_init(x, y);
join(figure1, figure2);
```
donde x e y son coordenadas y hacen referencia a la posición donde se quiere dibujar la figura. Luego width, height y radius están medidos en las unidades de fontsize.

Las funciones para las animaciones de las figuras son:
```
draw(figure);
move_figure(figure, xdestination, ydestination);

set_interval( duration , {
        code;
    }
);
void on_key(int key, , {
        code;
    }
);

```
Las funciones *on_key* y *set_interval* reciben como segundo parámetro una función lambda sin parámetros que indica lo que se realizará durante un intervalo determinado para el primer caso y al oprimir una tecla en el segundo caso. 
Las funciones para leer y escribir de entrada/salida std:
```
cursor(x,y);  
print(text str);
printN(int n);
printD(double d);
printC(int c);
text concat(text s1, text s2);
text append(text s, int c);
```

Una forma equivalente de llamar funciones es la con el uso de ```-->``` de la siguiente forma:
```
draw(figure);
cursor(0,0);
```
```
draw --> figure 
cursor --> 0,0 
```
 
## Dificultades encontradas en el desarrollo del TP
:bulb: Podemos decir que la mayor complicación que tuvimos fue elegir la idea del lenguaje. Es muy dificil al usarlos constantemente pensar en uno nuevo que sea útil pero que además tenga su vuelta de tuerca. Se nos hacía dificil salir de la idea de hacer una librería. Si bien las ideas eran buenas nos resultaba que eran ideas para librerías y no para un nuevo lenguaje per se. 

:bug: Al principio también nos costaba encontrar errores y hacer debugging. El programa tal vez abortaba o no producía el código que queríamos pero nos resultaba dificil encontrar lo que estaba produciendo el error. Como la gramática terminó quedando bastante grande no era viable hacer el seguimiento a mano de la expresión que teníamos. Luego pudimos conectar el gdb al IDE que utilizamos para el desarrollo y simplificó muchísimo la tarea de debugging.



![](https://i.imgur.com/aNA8KU7.jpg)

:deciduous_tree: Otra de las dificultades que tuvimos fue a la hora de diseñar el **AST** (abstract syntax tree) de manera prolija y para que luego lo podamos usar para generar código válido y hacer las validaciones correspondientes. 


## Futuras extensiones
En general las futuras extensiones que encontramos para nuestro lenguaje se basan en las limitaciones que tiene el mismo. 

![](https://i.imgur.com/WFxA9I3.jpg =700x)

:book: Permitir importación de librerías y archivos de nuestro lenguaje. Esto es una propiedad que tienen todos los lenguajes que usamos regularmente y que es muy útil para la reutilización de código. Fortalecería nuestro lenguaje ya que podría tenerse una librería de las figuras más complejas y comportamiento que se usan frecuentemente. Implicaría agregar un módulo nuevo a la gramática con producciones para admitir algo similar a la sentencia *import*. 

:art: Se le puede agregar a nuestro lenguaje mayor soporte para imprimir cadenas de caracteres en pantalla. Es decir podrían proveerse funciones para imprimir en distintos tamaños y colores. Si bien brindamos manera de imprimir a pantalla texto, se puede trabajar bastante sobre la ampliación de esta funcionalidad. 

:triangular_ruler:  Como estudiantes vivimos también la complicación al trabajar con lenguajes que no están pensados para producir interfaces visuales que es muy complicado hacer impresiones en forma tabular sin antes haber perdido horas en que quede bien alineado. Es por esto que estaría bueno agregarle al lenguaje un tipo **table** que permita hacer esto fácilmente y que encapsule los problemas de alineamiento,etc. Si bien tenemos forma de dibujar líneas vendría bastante bien este módulo. 

:wastebasket:  Deberíamos también agregarle al lenguaje un garbage collector.

:black_medium_square: Actualmente un pixel de nuestro programada esta formado por 2 caracteres, lo que involucra una gran pérdida de resolución. Para lograr una mayor resolución y lograr un parecido con *ascii art* deberíamos hacer uso de diferentes caractéres (como *[ ] | / \ L .* etc.) con el fin de adaptar mejor el dibujo final al  programa.





