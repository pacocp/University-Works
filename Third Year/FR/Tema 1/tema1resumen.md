#Tema 1: Introducción

###Aclaración
Todo el contenido de estos apuntes viene de las diapositivas de la asignatura FR del profesor José Camacho Páez http://wdb.ugr.es/~josecamacho/ más las notas que he ido tomando en clase.

## Contenido

-  Sistemas de comunicación y redes
- Diseño y estandarización de redes
- Terminología y servicios
- Internet: Arquitectura y direccionamiento
- Cuestiones y ejercicios

###1. Sistemas de comunicación y redes

Hay dos tipos de redes fundamentales: **telefónicas** y **ordenadores**. Todas las redes se dividen en 5 grandes módulos (que se ven ``en la figura 1``). Son 5 módulos ya que la información como sale de la fuente no tiene nada que ver con como sale del transmisor.

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 1/screenshot1.png)
      *Figura 1*

Los mensajes se trozean para no ocupar el ancho de banda. Así se distribuye la carga y no se colapsa en un único usuario. Además si no hay un error no se pierde toda la información.

**Razones para uso de una red de computadores: **
  - Compartir recursos
  - Escalabilidad: Conectar más máquinas en red.
  - Seguridad -> duplicidad: hay que tener cuidado por que las cosas se copien.

**Clasificación**

Las redes tienen distintos dispositivos, retardos...

- Según la **escala**:
   +  *LAN*: red local. Es raro tener una red local con fibra óptica. Ejemplo: oficinas de una empresa.
   + *MAN*
   + *WAN*: redes amplias. Los dispositivos de interconexión en una WAN son más caros que en una LAN.
- Según la **tecnología de transmisión**:
  + *Difusión* (a): red en la que teóricamente todos puedes "escuchar" lo que dice uno. Se puede utilizar criptografía para que se parezca a la *punto a punto*. Ejemplo: comunicaciones por satélite.
  + *Punto a punto* (b),(c): se conectan por cables.


![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 1/screenshot2.png)

**Estructura y elementos de una red**

- *Host*: dispositivos finales de usuario.
- *Subred* = nodos de conmutación + líneas de transmisión. Conmutan la información, de ahí se redirigen a donde sea su destino.

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 1/screenshot3.png)

###2. Diseño y estandarización de redes

Para conectar dos **host** hay que:
- Resolver la parte *hardware* (tarjetas de red...)
- Cuando se envía y cuando se recibe.
- Control de errores.
- Control de flujo (el receptor necesita saber el orden de los paquetes)
- Un **protocolo de comunicación** -> series de reglas que me permiten conocer que me están diciendo.
- Conocer que perfil va a tener la red.
- Tiene que existir un inicio de mensaje, para que el receptor sepa que es un mensaje, y un final, para que el receptor sepa que caba el mensaje.

Las redes tiene diseño **modular**. Son modulares por la simplicidad. La interconexión es complicada en la modularidad y hay duplicación, pero no es tan malo como tener que picar todo el código.

**Modelo OSI**

Modelo de referencia en redes. Es un modelo teórico. La funcionalidad se encuentra en capas:

- **Capa física** : La capa física resuelve todo lo que tiene que ver con la tarjeta de red y más componentes hardware.
- **Capa de enlace** : Se implementa sobre la capa física y resuelve: le pone **cabeceras** a la información(para el inicio y el final de los mensajes), **control de errores** (redundancia) y **control de flujo** (reordenar los mensajes).
- **Capa de red**: Tiene que resolver el encaminamiento(si un paquete va a un sitio debe llegar a ese sitio) y el **control de congestión**.

[Todo el resto ya no entiende si hay red, como si no hubiera nada en medio.]

- **Capa de transporte**: **Control de flujo** y **control de gestión** entre dos host.
- **Capa de sesión**: turno de palabra, cuando habla uno y cuando habla el otro.
- **Capa de presentación**: capa que permite conectar aplicaciones de distinto diseño para hacerlas compatibles (por ejemplo de MACOX y WINDOWS).
- **Capa de aplicación**: cualquier tipo de aplicación que tenemos que se comunica con Internet. Ahí tenemos los protocolos.

**TCP/IP**

Es una arquitectura, no un modelo. Es una arquitectura enteramente software. La *capa física y la capa de enlace* están fuera de esta arquitectura. Esto hace que una red tipo ethernet se pueda conectar con un WIFI por ejemplo. Séase, permite la interoperabilidad entre todos los sistemas.

Ya en **TCP/IP** sólo tenemos tres capas. La *capa de transporte* controla el turno de palabra.Esta capa también tiene el control de congestión, al contrario que en **OSI**. La *capa de red* tiene el encapsulamiento.


![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 1/screenshot4.png)

###3. Terminología y servicios.

**Comunicación OSI**

Las capas en **OSI** son software. Los procesos dentro de cada capa los llamamos **entidades**. Las entidades son las que tienen que compartir información. Los nodos de interconexión, sólo necesitan hasta la capa de red. Todos los protocolos suelen tener cabeceras. En la cabecera de la *capa de red* encontramos la dirección de destino.
La imagen de abajo nos dice cómo se realiza la comunicación realmente. Para TCP/IP es exactamente igual.

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 1/screenshot5.png)

Dentro de la cabecera encontramos información redundante para la funcionalidad de la capa.
La **comunicación vertical y horizontal** es que haya una diferencia entre el flujo de bits y la comunicación real persé.El **flujo de información** va en sentido descendente.
En **subred** solo mira las tres capas de abajo. Los nodos de la subred no entienden nada de **capa de transporte** hacia arriba.
En **TCP/IP** tendríamos el esquema con solo: Aplicación, Transporte, Red, Enlace y Física.

**Terminología**

- **Capa proveedora de proveedora/usuaria de servicio:** la capa de arriba siempre es usuaria y la de abajo proveedora.
![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 1/screenshot6.png)
(A la izquierda está la cabecera y a la derecha los datos en la imagen)
- **Protocolo:** es un lenguaje con normas con las que se pueden comunicar dos entidades.
- **Arquitectura de red:** (TCP/IP)
- **Pila de protocolos:** conjunto de protocolos que tiene una arquitectura de red.
- **SAP(Service Access Point):** valor específico que te permite acceder a servicios de la capa inferior. Ej: Si tenemos un móvil y una red de telefonía el SAP sería el número de teléfono.
- **SDU**
- **PDU**

**Retardos en la comunicación**

Es muy difícil estimar el comportamiento de Internet. Según el retardo podemos crear los protolos. Se considera el retardo a partir de que ha salido a la red. La figura se llama **diagrama de tiempos**.
![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 1/screenshot7.png)
Hay 3 tipos de retardo:
- **Retardo de transmisión:** tiempo que tardamos en transmitir un paquete. Esto significa ponerlo en la red.
![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 1/screenshot8.png)
- **Retardo de propagación:** lo que tarda cada bit en recorrer el cable.
![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 1/screenshot9.png)
- **Retardo de procesamiento interno:** retardo que tiene el paquete dentro del dispositivo. A este le afecta la congestión de la red, cualquier funcionalidad que tenga que ver con las capas inferiores.

El retardo de transmisión es lo que hace que la fibra óptica sea mejor que los cables de otro tipo.

**Servicios**

Diferenciamos:
- **Servicios orientados a conexión:** hay un inicio de conexión antes de empezar el servicio. Ej: Llamada telefónica. Se transmite un paquete llamado de control, que es el que pide la conexión, y el receptor envía otro paquete diciendo que acepta la conexión. Lo negativo es que tiene un retardo, lo positivo es la seguridad.
- **No orientado a conexión(NOC):** se usa cuando se necesita alta velocidad o necesitamos que llegue a tiempo.
- **Confirmado(fiable):** por cada paquete que se envía, hay que confirmarlo. Como antes, esto supone un retardo. Aquí prima la fiablidad al tiempo.
- **No confirmado(no fiable)**

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 1/screenshot10.png)
![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 1/screenshot11.png)

###4. Internet: Arquitectura y direccionamiento

Internet es una conexión de un montón de redes. No todas esas redes son de la misma naturaleza. Cambian dependiendo de donde te encuentres.

Topología jerárquica:
- Intranet: donde están los host.
- Red de acceso del ISP: red que te ofrecen, se van contratando unas u otras. Las principales diferencias entre su tecnología:
  -   xDSL: tecnología a la que pertenece ADSL.
  -   RDSI: más adaptada a multimedia.
  -   FITH: fibra óptica hasta tu casa.
- Redes troncales: ISP con distinta tecnología.

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 1/screenshot12.png)

**Direccionamiento**

Necesitamos poder direccionar. En capa de aplicación, necesitamos el nombre del dominio. La dirección IP(tiene distintas naturalezas) y puertos(para poder establecer contacto con el exterior).
Cada servicio tiene que estar en un puerto distinto. EL nombre de dominio y el IP identifican máquinas. Los puertos son como las puertas de los procesos.
En cuanto a IP tenemos:
- IP públicas: sólo pueden direccionar a un dispositivo. Cuestan dinero. Son unívocas, como número de teléfono.
- IP privadas: hay una "centralita" que es universal y que todos compartimos. Con esto podemos conectar un montón de ordenadores, en un solo router.

Tiene una serie de rasgos reservados:
![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 1/screenshot13.png)

La primera es para muchísimos dispositivos, la segunda para un nivel intermedio y la tercera para unos pocos dispositivos, como por ejemplo tu casa.

![](/run/media/pacocp/Nuevo vol/3 año/FR/Tema 1/screenshot14.png)
