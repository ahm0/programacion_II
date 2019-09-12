# Ejercicio Habitaciones
Un prestigioso hotel de la ciudad, que cuenta con 100 habitaciones, desea adquirir un sistema que le permita gestionar la reserva de las mismas. El sistema debe permitir al recepcionista realizar las siguientes acciones:

* Inicializar las habitaciones. Esta operación reinicia el archivo de habitaciones.
* Tomar una reserva. Esta operación marca una habitación como *reservada*
* Liberar una habitación. Esta operación marca una habitación como *libre*
* Listar. Esta operación permite mostrar por pantalla un listado de todas las habitaciones, indicando su estado y en caso de estar reservada, quién la ocupa.

Para realizar la reserva de una habitación se deberán ingresar los datos del cliente, a saber:

1. Nombre y Apellido
1. Edad
1. DNI
1. Correo electrónico
1. Cantidad de días que se va a quedar en el hotel.

El recepcionista deberá preguntar al cliente si quiere que el hotel le asigne una habitación o si prefiere elegir una en particular. Si el cliente está dispuesto a que el hotel le asigne una habitación, se deberá Implementar un algoritmo que permita asignar la primer habitación *libre* que se encuentre. Si por el contrario, el cliente desea elegir una habitación particular, el recepcionista deberá preguntar al cliente el **Id** de la habitación que desea.

Cuando un cliente abandone el hotel, el recepcionista deberá solicitar al cliente el **Id** de la habitación en la que se alojó para marcarla como *libre*.

## Requerimientos no funcionales

1. Implementar la aplicación utilizando un archivo binario.
1. La operación de reserva a partir de un Id de habitación deberá realizarse a través de accesos directos
1. La operación de liberación de una habitación deberá realizarse a través de accesos directos
