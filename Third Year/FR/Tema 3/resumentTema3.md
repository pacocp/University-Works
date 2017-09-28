#Tema 3: Capa de Transporte en Internet

###Aclaración
Todo el contenido de estos apuntes viene de las diapositivas de la asignatura FR del profesor José Camacho Páez http://wdb.ugr.es/~josecamacho/ más las notas que he ido tomando en clase.

## Contenido

- 1.Introducción
- 2.Protocolo de datagrama de usuario(UDP)
- 3. Protocolo de control de transmisión(TCP)
  - 3.1 Multiplexación/demultiplexación
  - 3.2 Control de conexión
  - 3.3 Control de errores y de flujo
  - 3.4 Control de congestión
- Extensiones TCP

###1. Introducción

**UDP** -> solo utiliza los puertos.
**TCP** -> tiene todo lo que se implementa en la capa de transporte .
Control de conexión significa que se necesita que haya un inicio de conexión y un fin de conexión.

Funciones y servicios de la capa de transporte:
- Comunicacion *extremo a extremo* (end to end).
- *Multiplexación/demultiplexacíón* de aplicaciones -> puerto.

Protocolo UDP:
- *Multiplexación/demultiplexación* de aplicaciones.
- Servicio *no orientado a conexión,no fiable*.

Protocolo TCP:
- *Multiplexación/demultiplexación* de aplicaciones.
- Servicio *orientado a conexión,fiable*: Control de *errores y de flujo*. Control de la *conexión*. Control de *congestión*.

###2. Protocolo de datagrama de usuario(UDP)

**User Datagram Protocol (UDP)**

Funcionalidad "*best effort*":
- Servicio *no orientado a conexión*.
- Servicio *no fiable*.
- *No* hay garantías de *entrega ordenada*.
- *No* hay *control de congestión*: entrega tan rápida como se pueda.
- *Multiplexación/demultiplexación*: transportar las TPDU al proceso correcto

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura1.png)

**Longitud UDP** nos da el valor de la cabecera + el payload.

**payload** -> donde tenemos toda la información de la capa de aplicación.
**comprobación(checksum)** -> nos permite comprobar ciertas cosas. En la comprobación se meten las IP para que se compruebe que si ha ocurrido algún error de que ese paquete no iba dirigido a ti.

El checksum se calcula en UCP, en TCP, es el complemento a 1 de la la suma complemento a 1 de las palabras de 16 bits.

**Multiplexación/demultiplexación**: transportar las TPDU al proceso correcto.

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura2.png)

UDP se usa frecuentemente para **aplicaciones multimedia**: tolerantes a fallos y sensibles a retardos.

Cada segmento UDP se **encapsula** en un datagrama IP.

###3. Protocol de control de transmisión(TCP)

**Características del "Transmission Control Protocol"**

- Servicio *orientado a conexión*.["Hand-shaking"]
- *Entrega ordenada*.
- *Full-duplex* : se recibe y se envía en el mismo canal.
- Mecanismo de control de flujo y detección y recuperación de errores:
    - confirmaciones positicas (*ACKs*) y acumulativas: paquetes de control que confirman la correcta llegada. Esto se combina con temporizadores, si se agota y no hay confirmación se vuelve a enviar.
    - incorporación de confirmaciones("*piggybacking*"): se intenta maximizar el número de paquetes que se envían de control.
    - *timeouts* adaptables.
    - *Ventanas* adaptables : puedo utilizarlas para enviar varios segmentos, y cuando los han confirmado todos, envío otro pack de segmentos.
- Mecanismo de control de congestión.
- *Servicio fiable* : control de congestión y control de flujo.

#LA CABECERA DE TCP SUELE CAER EN EL EXÁMEN

TDPU TCP = **Segmento TCP**:

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura3.png)

- *Número de secuencia* : por donde veo lo que yo he enviado.
- *Reservado* : para investigación.
- *UAPRSF* : campo de flags. Se mira para conmprobar el resto de los campos.
- *Puntero de datos urgentes* : permite diferenciar en el **payload** los datos que merecen más prioridad que otros.

El campo de opciones es variable, muchas veces en el comienzo de una comunicación se utilizan para negociar ciertos campos de la comunicación.

*Multiplexación/demultiplexación* de aplicaciones:

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura4.png)

La "conexión TCP" se identifica por: puerto e IP origen y puerto e IP destino (y opcionalmente el protocolo).

**Control de la conexión**

El intercambio de información tiene **tres fases**:
- *1º paquete* : se le pone el flag de sincronización a 1. El nº de secuencia se inicializará a un número pseudoaleatorio y se manda. Este llega a un puerto del servidor.
- *2º paquete* : devuelve ACK = 1. Como tenemos conexión full-duplex el servidor también pone el SYN = 1 e inicializa el nº de secuencia a este número pseudoaleatrio. El acuse se pone a x +- 1.
- *3º paquete* : secuencia = X + 1; acuse = Y + 1.; ACK = 1. Cierre de la conexión ( liberar recursos).

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura5.png)

*Cierre de la conexión, liberación de recursos*

El que quiere desconectar manda un segmento con el flag FIN=1. Cuando el segmento llega al otro confirma, si quiere, y pone también el flag FIN=1 y lo mandará. Y finalmente se confirma ese segmento.
El siguiente segmento será con Y+1.
Espera cin el temporizador ya que puede que no todos los paquetes hayan llegado, ni que el otro haya cerrado, por lo tanto se queda un ratito escuchando por si acaso.

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura6.png)

*Control de conexión. Números de secuencia*

- Campo de 32 bits : 2^32 valores. Cuando en un flujo TCP se agotan los valores se da la vuelta.
- Inicialización(#secuencia = ISN)
    -  Empieza en el *ISN*(Initial Sequence Number), elegido por el sistema.
    - Para el ISN, el estándar sugiere utilizar un contador entero incrementado en 1 cada 4 microsegundos aproximadamente.
    - El ISN no se inicializa a 0 para evitar confluencias de flujos.
    - Protege de coincidencias, pero no de sabotajes.

- **Número de secuencia** aumenta el número de bytes en el payload.
- Incremento (#secuencia = #secuencia + Nbytes)
  - Se incrementa según los bytes de carga útil (payload).
  - Los flags *SYN* y *FIN* incrementan en 1 el número de secuencia.

Cuando se conecta:

\#secuencia = x -> se obtiene del ISN. Se saca por como aumenta el contador cada 4 microsegundos.

Cuando se desconecta:

\#secuencia = x -> la x por a que empezó más todos los bytes que se han transferido.

Lo mismo para la Y. Se acaba en el número de secuencia + 1 por el flag FIN.

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura7.png)

**Control de errores y de flujo**

Hacen reducir la velocidad.
*Control de errores*: esquema ARQ con confirmaciones positivas y acumulativas.
Campos involucrados:
- Campo secuencia: offset (en bytes) dentro del mensaje.
- Campo acuse: número de byte esperado en el receptor.
- Bit A (ACK) del campo de control.
- Campo comprobación: checksum de todo el segmento y uso de pseudo-cabecera.

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura8.png)

Escenarios de retransmisión:

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura9.png)
El segundo es una ventana de dos segmentos. Vuelve a enviar el ACK = 120 porque este contiene el ACK = 100, ya que son acumulativos.
Generación de ACKs:
![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura10.png)

*¿Cómo estimar los timeouts?*
- Mayor que el tiempo de ida y vuelta (RTT).
- Si es demasiado pequeño: timeouts prematuros.
- Si es demasiado grande: reacción lenta a pérdida de segmentos.
- Para situaciones cambiantes la mejor solución es la adaptable, es decir, dependiendo de cómo esté la red.

Las condiciones de una red son cambiantes. Si la red cambiantes. Si la red cambia un temporizador que me vale ahora puede ser que no valga en 10 minutos. Necesito adaptarme a la red lo más rápido posible.

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura11.png)
![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura12.png)

*Control de flujo*: sirve para no saturar al receptor. Aunque a la ve que hace eso controla la recepción en orden de paquetes.
No se manda un segmento cada vez, es decir, por cada segmento no esperamos al ACK, creamos ventanas. COn las ventanas enviamos más de un segmento a la vez. Así reducimos el tiempo muerto y aumentamos el tiempo activo.
Las confirmaciones son por paquete, ya que si no tendría que volver a enviar la ventana completa, y aumentaría el tiempo muerto otra vez.
El control de flujo de TCP es un sistema crediticio, con esto se intenta no saturar al receptor. Con los créditos que nos da, nos indica cuánto le podemos enviar. Esto lo da el parámetro window. Tiene relación con la comunicación de B a A.
Lo que dice el parámetro window es lo que queda libre de ese buffer de recepción. La parte libre se denomina ventana ofertada. Así se evita un buffer overflow.
![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura13.png)
![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura14.png)

Cuando ese mensaje llega al emisor, se coge el parámetro window y se restan los bytes en tránsito.

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura15.png)

Podemos observar como se llena el buffer del receptor y el cliente queda bloqueado, hasta que el receptor envía un ACK duplicado con el mismo ACK number con el windows que queda libre.
En el three-way handshake si dice el tamaño de buffer que se usa.
Normalmente el buffer se va a atomizar mucho, y se van a enviar segmentos muy pequeños. Esto hace que la proporción de cabeceras con las de datos sea muy descompasada.

Para ello tenemos la ventana optimista, donde si tengo una buena sincronización con el receptor, dejámos de considerar los bytes en tránsito y así reducimos el tamaño de la ventana.
Una solución por parte del receptor sería que no te envíe su ventana hasta que tenga suficiente tamaño.
Con los datos urgentes tiene sentido en el receptor, este se salta la cola de recepción y los envía a la capa de aplicación directamente.
Cuando una información tiene que enviarse se pone el bit P (PSH) a 1 para que el receptor lo trate como datos urgentes. Se utiliza más que la anterior.

*Control de congestión:* Trabaja en colaboración con el control de errores y de flujo. Mismo objetivo que el de flujo pero aquí cambia el agente.
No hay nadie que diga que la red está congestionada, tengo que darme cuenta. Una forma de ver si hay congestión, es ver si se ha perdido ACK. Si se excede el timeout significa que seguramente la red está congestionada.
TCP Tahoe -> inicializa la ventana de congestión a un maximun segment size. Además, inicialmente voy a estar en un estado que se llama inicio lento, que consiste en empezar con un segmento de ventana pequeño y aumentarlo exponencialmente.

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura16.png)
![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura17.png)

Si la seguimos aumentando podemos cagarla, creamos un umbral donde empieza a crecer de forma lineal. Por cada vez que recibo la ventana completa, aumento un MSS(va aumentando de uno en uno).

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura18.png)

*Combinación de CTrl de flujo y congestión:*
![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura19.png)
En cada momento sabes el window y no puedes enviar más de lo que te diga, así el control de congestión se eleva y al final cogemos la ventana más restrictiva.

###4.Extensiones TCP.


- TCP se define con múltiples *sabores*.
- Los diferentes sabores no afectan a la *interoperabilidad* dentre extremos.
- Desde cualquier versión de Linux con kernel mayor que la 2.6.19 se usa por defecto *TCP CuBIC*

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 3/figura20.png)
