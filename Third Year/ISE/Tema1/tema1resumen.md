# Tema 1
## Introducción a la ingeniería de servidores

###Aclaración
Todo el contenido de estos apuntes viene de las diapositivas de la asignatura ISE del profesor Héctor Pomares Cintas http://www.ugr.es/~hector/ más las notas que he ido tomando en clase.
###Contenido
-     Concepto de sistema informático
-     Clasificación de sistemas informáticos
-     Fundamentos de Ingeniería de Servidores
-     Comparación  de conjunta de  prestaciones y coste
-      Límites en la mejora del tiempo de respuesta : Ley de Amdahl


- - -

###1.Concepto de Sistema Informático

*Sistema informático*

-  Conjunto de elementos **hardware**, **software** y **humanware** interrelacionados entre si que permite almacenar y procesar información.

      -  **Hardware**: conjunto de componentes físicos que forman el sistema informático: procesadores, memoria, almacenamiento externo, cables, etc.
      -  **Software**: conjunto de componentes lógicos que forman el sistema informático: sistema operativo y aplicaciones.
      -  **Humanware**: conjunto de recursos humanos. EN nuestro caso, personal técnico que crea y mantiene el sistema(administradores, analistas, programadores, operarios, etc.) y los usuarios que lo utilizan.



 - - -


###2.Clasificación de Sistemas Informáticos

- Los Sistemas Informáticos pueden clasificarse según numerosos criterios. Por supuesto las clasificaciones no son estancas y es común encontrar sistemas híbridos que no encajen en una única categoría.
- Ejemplos de clasificación:

     - **Según el nivel de paralelismo de su arquitectura**: SISD,SIMD,MIS o MIMD
     - **Según su uso**: De uso general o de uso específico
     - **Según la arquitectura de servicio**: Sistema aislado, arquitectura cliente-servidor, arquitectura de n capas o arquitectura cliente-cola-cliente


**Clasificación. Paralelismo Arquitectura**

-   Según el paralelismo de su arquitectura:
     - SISD: Single Instruction Single Data.
     - SIMD: Single Instruction Multiple Data.
     - MISD: Multiple Instruction SIngle Data.
     - MIMD: Multiple Instruction Multiple Data.


![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot1.png)


-   **SISD**: Single Instruction Single Data
     -  Una arquitectura en la que un solo procesador, un uniprocesador, ejecuta un flujo de instrucciones, para operar sobre un ´unico flujo de datos.
     -  Una única unidad de control despacha las instrucciones a una única unidad de procesamiento(UP)
     -  Se corresponde con la arquitectura von Neumann.

-  **SIMD**: Single Instruction Multiple Data(procesadores vectoriales)
    -  Arquitectura empleada para conseguir paralelismos a nivel de datos.
    -  Instrucciones que aplican una misma operación sobre varios conjuntos de datos.
    -  Ejemplo: repertorio de instrucciones 3DNow! de AMD, y SSE de Intel.

-   **MISD**: Multiple Instruction Single Data
    -  Arquitectura de computación paralela donde muchas unidades funcionales reaizan diferentes operaciones sobre los mismos datos.
    -  Por ejemplo : Redes Neuronales.

-    **MIMD**: Multiple Instruction Multiple Data
     -  Mayor paralelismo posible
     -  Tienen un número de procesadores que funcionan independientemente. En cualquier momento, cualquier procesador puede ejecutar diferentes instrucciones sobre distintos datos.
     -  Pueden tener memoria compartida o distribuida.

**Clasificación: Según su uso**

-   Según su uso, un sistema informático puede considerarse:
	-  De uso general, como los computadores personales (PC) que son utilizados por un usuario para ejecutar muy diversas aplicaciones. Ej: PC de sobremesa, PC portátil.
	-  De uso específico. Ej: Sistemas empotrados, servidores.

**Clasificación. Uso específico**

-  **Sistemas empotrados(embedded systems)**
	-  Sistemas informáticos acoplados a otro dispositivo o aparato, diseñados para realizar una o algunas funciones dedicadas, frecuentemente con fuertes restriciones de coste, consumo y tiempo de respuesta (sistemas de tiempo real).
	-  Suelen estar formados por un microcontrolador, memoria y una amplia gama de interfaces de comunicación.
	-  Ejemplo: un taxímetro, un sistema de control de acceso...

-  **Servidores**
	-  Son computadores que, formando parte de una red, proporcionan servicios a otros computadores denomidas clientes.
	-  Dependiendo del rol que sumen dentro de una red podemos distinguir:
	    -  **Servidores dedicados**: son aquellos que le dedican toda su potencia a administrar los recursos de la red, ed decir, a atender las solicitudes de procesamiento de los clientes.
	    -  **Servidores no dedicados**: son aquellos que no dedican toda su potencia a los clientes, si no también pueden jugar el rol de estaciones de trabajo al procesar solicitudes de un usuario local.
	-  Un servidor no es necesariamente una máquina de última generación de grandes prestaciones: un servidor puede ser desde un computador de gama baja (coste bajo) hasta un gran cluster de computadores.

-   **Cluster de computadores**

	-  Asociaciones de computadores de modo que pueden ser percibidos externamente como un único sistema.

-  Algunos tipos de servidores:
	-  **Servidor de archivos**
	-  **Servidor Web**
	-  **Servidor de base de datos**
	-  **Servidor de transacciones**
	-  **Servidor de impresión**
	-  **Servidor de correo**

**Clasificación. Arquitectura de servicio**

-   Según la arquitectura de servicio:
	-  Sistema aislado
	-  Arquitectura cliente-servidor
	-  Arquitectura de n capas
	-  Arquitectura Cliente-Cola-CLiente

-  **Sistema aislado**
	- Sistema computacional que no interactúa con otros sistemas.
	- Arquitectura monolítica en la que no existe distribución de a información.
	- Ej: computadores personales.

-	**Arquitectura cliente-servidor**
	- Es un modelo de aplicación distribuida en el que las tareas se reparte entre los proveedores de recursos o servicios, llamados servidores, y los demandantes, llamados clientes.
	- Suele tener dos tipos de nodos en la red: los clientes(temitentes de solicitudes), los servidores (receptores de solicitudes).

-	**Arquitectura de n capas**
	- Es una arquitectura cliente/servidor que tiene n tipos de nodos en la red.
	- Mejora la distribución de carga entre los diversos servidores. Es más escalable.
	- Pone más carga en la red.
	- Difícil de programar y administrar.
	- Ejemplo: arquitectura de 3 capas es una aruitectura cliente/servidor que tiene tres tipos de nodos en la red: clientes que interctúan con los usuarios finales, servidores de aplicación que procesas los datos para los clientes y servidores de bases de datps quie almacenan/buscan/gestionan los datos para los servidores de aplicación.

-	**Arquitectura Cliente-Cola-Cliente**
	-  Habilita a todos los clientes para desempeñar tareas semejantes interactuando cooperativamente para realizar una actividad distribuida, mientras que el servidor actúa como una cola que va capturando las peticiones de los clientes y sincronizando el funcionamiento del sistema.
	-  La arquitectura P2P se basa en el conceltp ·Cliente-Cola-Cliente".
	-  Aplicaciones: Intercambio y búsqueda de ficheros, sistemas de telefonía por internet.


###3. Fundamentos de Ingeniería de Servidores.

-	**Diseño, configuración y evaluación de un Servidor**
	- Requisitos funcionales: Prestaciones, Disponibilidad, Seguridad, Fiabilidad, Mantenimiento, Coste, Escalabilidad, Extensibilidad...
	- Compontentes físicos y lógicos: Placa Base, Memoria, Microprocesador, Fuente de alimentación, Periféricos (E/S, Almacenamiento), Sistema Operativo, Middleware, Aplicaciones, COnexciones de red, Cableado, Refrigeración local...

-	**Disponibilidad (Availability)**
	- Un servidor está disponible si se encuentra en estado operativo.
	- **Tiempo de inactividad** (Downtime): cantidad de tiempo en el que el sistema no está disponible.
	- Tiempo de inactividad planificado: es usualmente el resultado de un evente lógico o de gestión iniciado.
	- TIempo de inactividad no planificado: surge de un evento físico tales como fallos en el hardware, anomalías ambientales o fallos software -> tolencia a fallos.
	- Algunas sugerencias: sistemas redundantes de alimentación, configuraciones RAID, sistemas de red redundantes, sistemas distribuidos, reemplazo en caliente de componentes.

-	**Fiabilidad (Reliability)**
	- Un sistema es fiable cuando se desarrolla su actividad sin presencia de erros. **MTBF** (Mean Time Between Failures): teimpo medio que tiene un sistema entre dos fallos consecutivos. Soluciones: uso de sumas de comprobación (checksums) para la detección de fallos, retransmisión de mensajes/datos, replicación de datos...

-	**Seguridad**
	- Un servidor debe ser seguro ante: la incursión de individuos no autorizados, la corrupción o alteración no autorizada de datos, las interferencias que impidan el acceso a los recursos.
	- Soluciones: autenticación segura de usuarios, encriptación de datos, cortafuegos (firewalls), mecanismos de prevención de ataques de denegación de servicio.

-	**Escalabilidad (o escalabilidad horizontal)**
	- Un servidor es escalable si sus prestaciones pueden aumentar significativamente ante un incremento **significativo** de su carga.
	- Soluciones (muchas interrelacionadas): cloud computing, clusters de computadores, virtualización, grid computing, distribución de carga, storage area networks (SAN), arquitecturas distribuidas.

- 	**Extensibilidad-expansibilidad**
	- Hace referencia a la facilidad que ofrece el sistema para aumentar sus características o recursos locales.
	- Soluciones: uso de SO modulares de código abierto. Uso de interfaces de E/S estándar.
	- EL uso de sistemas abiertos también repercute en que el coste de los componentes añadidos suele ser menor así como los gastos de mantenimiento debido a la mayor facilidad de elección de proveedores.

-	**Mantenimiento**
	- Hace referencia a todas las acciones que tienen como objetivo prolongar el funcionamioento correcto del sistema.
	- Es importante que el servidor sea fácil de mantener. Por ejemplo, facilidad de actualizar el SO, aplicaciones, servicios, drivers, etc.

-	**Coste**
	- Un diseño que sea asequible y se ajuste al presupuesto: coste hardware, coste software, coste actualizaciones hw/sw, cosye personal, coste proveedores de red, coste alquiler local, coste consumo eléctrico tanto del hardware como de la refrigeración: **Eficiencia energética**


-	**Eficiencia Energética**
	- Uso eficiente de los recursos computacionales minimizando el coste energético, cuidando el impacto ambiental y observando deberes sociales.
	- ¿Por qué preocuparse por la eficiencia energética?: Reducir costes, mayor vida útil de los componentes, preservar el medio ambiente.
	- Soluciones: Ajuste automátio del consumo de potencia de los componentes electrónicos según la carga. Free cooling: utilización de bajas temperatura exteriores para la refrigeración gratuita, consolidación de servidores.

-	**Prestaciones**
	- Medida o cuantificación de la velocidad con la que se realia una determinada cantidad de trabajo (carga)
	- **Prestaciones del servidos con respecto al tiempo**: El servidor que realiza la misma cantidad de trabajo (carga) en el menor tiempo es el que mejor prestaciones tiene.
	-  Maginitudes medibles con respecto a índices de prestaciones: tiempo que tarda un componente o el sistema en realizar una tarea, número de trabajos realizados por algún componente o por el sistema completo por unidad de tiempo, porcentaje de toiempo que se está usando cada componente (utilización).
	-  **Medidas fundamentales de prestaciones de un servidor**
	    -   **Tiempo de respuesta** o ** latencia**: tiempo total desde que se solicita una tarea al servidor o a un comonente del mismo y la finalización de la misma.
	    -   **Productividad** o **ancho de banda**: cantidad de trabajo(carga) realizado por el servidor o por un componente del mismo por unidad de tiempo.


![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot2.png)

![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot3.png)


###4. Comparación Conjunta de Prestaciones y Coste

**Comparación de prestaciones**

- Debemos ejecutar los programas reales (o los más parecidos a los programas reales) para evaluar el rendimiento de un sistema
- El computador más rápido es aquel que ejecuta el programa(o el conjunto de programas) en el tiempo más corto.
- En este contexto, a la ganancia en prestaciones de un computador con respecto a otro se conoce como aceleración o ganancia en velocidad (speedup).

**Tiempos de ejecución mayores/menores**

- Sea tA = tiempo de ejecución de un determinado programa en la máquina A(idem para tB).
	- tA es tA/tB veces tB. **EJEMPLO**: tA = 10s, tB=5s -> tA es 2 veces tB (el doble).
	- Igualmente, el ejemplo anterior: tB es 0.5 veces tA (la mitad).
- El **cambio relativo** de tA con respecto de tB viene dado por:

  ![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot4.png)
  - En el ejemplo anterior, el **cambio relativo** de tA con respecto a tB es 1(100%).
  - Igualmente, el cambio relativo de tB con respecto a tA sería -0.50(-50%).
- Uso del lenguaje "común" en el ejemplo anterior:
  - tA es un 100% **mayor que** tB.
  - tB es un 50% **menor que** tA.
  - tA es 2 veces **mayor que** tB(UNA VEZ MAYOR QUIERE DECIR IGUALES).
  - tB es 2 veces **menor que** tA.
- No sólo se comparan tiempos. También se pueden comparar productividades,costos...Pero lo normal es que se haga con velocidades.

**¿Qué máquina es más "rápida"? Speedup**

- Sea tA=tiempo de ejecución de un determinado programa en la máquina A (idem para tB).
- La "velocidad" de la máquina A para ejecutar dicho programa será inversamente proporcional a tA: vA=D/tA(siendo D la distancia recorrida por la máquina = cómputo realizado). Igualmente vB=D/tB, donde hemos utilizado la misma distancia "D" ya que han realizado la misma cantidad de cómputo (el mismo programa).
- Para ese programa, se define la ganancia en velocidad (speedup o aceleración) de la máquina A con respecto a la máquina B como:
  ![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot5.png)
- El *cambio relativo* de vA con respecto a vB viene dado por:
  ![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot6.png)

- Siempre la más grande arriba para que de por encima de 1.
**¿Qué máquina es más "rápida"? Ejemplo**

- Supongamos que, para un determinado programa, tA=36s y tB=45s.
- En ese caso, la ganancia en velocidad(=speedup) de la máquina A con respecto a la máquina B sería:
![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot7.png)
- El cambio relativo de vA con respecto a Vb viene dado por:
![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot8.png)
- Usando el lenguaje "común" diremos que para ese programa:
  - La máquina A es 1.25 veces **más rápida que** la B (Si la ganancia de velocidad = 1 significa "misma velocidad")
  - La máquina A es un 25% **más rápida que** la B.
- Igualmente:
  - La máquina B es (Sa(B)-1=36/45 -1 = -0.2) un 20% **más lenta** que A.

**Relación prestaciones/coste**

- Supongamos que, siguiendo el ejemplp anterior:
  - El computador A cuesta 625 euros.
  - El computafor B cuesta 550 euros.
- El computador A es 625/550 = 1.14 veces **más caro que** el B (un 14% más caro).
- ¿Cuál ofrece mejor relación prestaciones/coste para nuestro programa?
![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot9.png)
- En este caso, el computador A presenta una relación más alta que el B (1.1 veces mayor = un 10% mayor) para nuestro programa y sería el que, en ausencia de otra información, compraríamos.
- En otros ejemplos, las prestaciones se pueden medir de forma distinta: speedups, productividades, índices SPEC, etc.
- El que tenga la relación prestaciones/coste **más alta** es la que se coge.

###5.Límites en la mejora del tiempo de respuesta

**Mejora del Tiempo de Respuesta**

- La mejora del **tiempo de respuesta** ( en nuestro caso, tiempo de ejecución de un proceso) no es *ilimitada*.
  - Hay que saber hacia dónde dirigir los esfuerzos de optimización.
- La mejora de cualquier sistema usando un componente más rápido depende de la fracción de tiempo que éste se utilice.
- Discusión preliminar:
  - Un sistema tade un tiempo Toriginal en ejecutar un proceso/programa.
  - Mejoramos el sistema reemplazando uno de sus componentes por otro k veces más rápido.
  - Este componente se utilizaba durante una fracción f del tiempo Toriginal.
  - ¿Cuál es la ganancia en prestaciones (*speedup*) del sistema para ese programa?

**Tiempo original vs tiempo mejorado**

![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot10.png)

**Ley de Amdahl(1967)**

- ¿Cuál es la ganancia en velocidad S (speedup) del sistema después de mejorar **k** veces un componente?

![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot11.png)

- Casos particulares de la Ley
  - Si f=0 -> S=1: no hay ninguna mejora en el sistema
  - Si f=1 -> S=k: el sistema mejora igual que el componente


**Ejemplo de cálculo**

- La utilización de un disco curo es del 60% para un programa dado.
- ¿En cuánto aumentará el rendimiento del sistema si se duplica la velocidad del disco (k=2)?

![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot12.png)
![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot13.png)
![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot14.png)
![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot15.png)
![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot16.png)
![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot17.png)

- Ganancia máxima que se puede conseguir actuando solo sobre el disco:

![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot18.png)

**Análisis: relación entre S,f y k**

![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot19.png)

**Generalización de la ley de Amdahl**

Se puede generalizar la Ley de Amdahl. Cada recurso se mejora k veces. La ecuación sería la parte no mejorada + los distintos recursos mejorados k veces cada uno ( las k pueden ser distintas).

![](/run/media/pacocp/Nuevo vol/3 año/ISE/Tema1/screenshot21.png)

**Algunas reflexiones finales**

- Una mejora es más efectiva cuanto más grande es la fracción de tiempo en que ésta se aplica.
- Para mejorar un sistema complejo hay que optimizar los elementos que se utilicen durante la mayor parte del tiempo (caso común).
- Con la ley de Amdahl podemos estimar la ganancia en velocidad (speedup) de la ejecución de **un único trabajo** en un sistema después de mejorar **k** veces un componente, s decir,su tiempo de respuesta óptimo en ausencia de otros trabajos.
