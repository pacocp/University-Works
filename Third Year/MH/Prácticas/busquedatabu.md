# Búsqueda tabú

## Memoria a corto plazo

La búsqueda tabú acepta el mejor de los n mejore la solución actual o no. Genero n y cojo el mejor da igual que lo mejore o no. Con esto salimos de óptimos locales. Con esto podría estar ciclando continuamente.
La lista tabú sirve para no repetir acciones que yo haya hecho en el pasado. Esa memoria sirve para que coja el mejor NO tabú. Así no vuelvo a esas zonas. Me iría a la segunda mejor. Es decir, al mejor no tabú.
Si es mejor que la mejor actual pero no es mejor que la mejor global no la saco de la lista tabú. La lista tabú es un histórico. 

Tenencia tabú -> tiempo que está un atributo en la lista tabú.

Si hago una lista tabú de soluciones tendré N soluciones tabú. La lista de válidas será Espacio-N soluciones válidas cuando tenga la lista llena.

Mala idea lista tabú de soluciones completas. Mejor list tabú de posiciones o movimientos. Cuántas más limitaciones le ponga, a  menos vecinos voy a poder saltar. Restringimos mucho más el vecindario y me voy a vecindarios que aún no he visitado.

Es una lista por donde salen con entrada. El nuevo que entre pisa al uno, y sale por el último.

Generar L vecinos. Cuántos más vecinos meta más se parece a una búsqueda primero mejor y cuantos menos más se parece a un enfriamiento simulado.

 Mejor generar todos los vecinos de un tirón, evaluarlos y ordenarlos de mejor a peor. Con un do-while voy viendo cuál acepto. El candidato es el primero, a no ser que se encuentre dentro de la lista tabú:

 - Si no es tabú lo acepto, y tengo que mirar si es mejor que la solución global.Si es mejor que la global cambio los valores. Y ahora actualizo la lista tabú. Tengo que meter lo que sea que me haya permitido generar esa posición. En el caso de que sea de movimientos meto el movimiento que me permitió llegar ahí.
 - Si es tabú, compruebo el criterio de aspiración. En la práctica comprobamos si es mejor que la mejor solución global. Sólo se comprobaría el primero de la lista tabú. Si lo supera me muevo y lo vuelvo a meter en la lista tabú, si no lo supera pasamos al segundo de la lista de vecinos y así sucesivamente.

### Hasta aquí llegaría la práctica ahora va un extendido

## Memoria a largo plazo

Puede ser mejor que la global ya que estamos cambiando posiciones. Entonces actualmente a lo mejro cambiando esas posiciones de mi solución actual consigo una mejor que la global que tenía.