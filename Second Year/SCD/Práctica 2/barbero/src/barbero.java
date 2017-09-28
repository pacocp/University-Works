/************************************************************
	Francisco Carrillo Pérez                                *
	Sistemas Concurrentes y distribuidos.                   *
	Práctica 2                                             *
************************************************************/

import monitor.* ;
import java.util.Random ;

class Barberia extends AbstractMonitor
{ 
	//int n_clientes;
	boolean cortando = false, acabadeentrar = false;
	private Condition barbero = makeCondition();
	public Condition sala = makeCondition();
	public Condition silla = makeCondition();
// invcado por los clientes para cortarse el pelo
	public void cortarPelo ( )
	{ 
		enter();
		//acabadeentrar = true;
		if(cortando || !sala.isEmpty()) sala.await();
		//acabadeentrar = false;
		cortando = true;
		barbero.signal();
		
		silla.await();
		leave();


	}	
// invocado por el barbero para esperar (si procede) a un nuevo cliente y sentarlo para el corte
	public void siguienteCliente ()
	{ 
		enter();
		if(sala.isEmpty() /*|| acabadeentrar == false*/) barbero.await();
		//System.out.println("Entra el siguiente cliente");
		if(cortando == false){
			sala.signal();
		}
		
		
		leave();




	}
// invocado por el barbero para indicar que ha terminado de cortar el pelo
	public void finCliente ()
	{ 
		enter();
		if(cortando){
			cortando = false;
			silla.signal();
		}
		
		//System.out.println("El barbero ha acabado de cortar el pelo");
		
		
		leave();
	}
}
class aux
{
  static Random genAlea = new Random() ;
  static void dormir_max( int milisecsMax )
  { try
    { Thread.sleep( genAlea.nextInt( milisecsMax ) ) ;
    } 
    catch( InterruptedException e )
    { System.err.println("sleep interumpido en 'aux.dormir_max()'");
    }
  }
}
class Cliente implements Runnable
{ 
	public Thread thr ;
	Barberia barberia;
	int indice;
  	public Cliente(Barberia b,int n)
  	{
  		indice = n;
  		barberia = b;
  		thr = new Thread(this,"Cliente "+ n);
  	}
	public void run ()
	{ 
		while (true) {
		System.out.println(thr.getName()+ " ha entrado en la baberia");
		System.out.println(thr.getName()+ " esperando a pelarse");
		barberia.cortarPelo (); // el cliente espera (si procede) y se corta el pelo
		System.out.println(thr.getName()+ " ha acabado de cortarse el pelo y se va");
		aux.dormir_max( 2000 ); // el cliente esta fuera de la barberia un tiempo
		

		}
	}
}
class Barbero implements Runnable
{ 
	public Thread thr ;
	Barberia barberia;
	public Barbero(Barberia b)
	{
		barberia = b;
		thr = new Thread(this,"Barbero");
	}
	public void run ()
	{ 	
		while (true) {
		System.out.println("El barbero llama al siguiente cliente");
		barberia.siguienteCliente ();
		System.out.println("El barbero empieza a cortar el pelo");
		aux.dormir_max( 2500 ); // el barbero esta cortando el pelo
		System.out.println("El barbero ha acabado de cortar el pelo");
		barberia.finCliente ();
		}
	}
}

class barbero
{
	public static void main( String[] args ) 
	{

		Barberia barberia = new Barberia();
		Barbero barbero = new Barbero(barberia);
		int n = Integer.parseInt(args[0]);
		Cliente [] clientes = new Cliente[n];

		for(int i = 0; i <n ;i++)
		{
			clientes[i] = new Cliente(barberia,i);
		}

		//poner en marcha las hebras
		barbero.thr.start();
		for(int i = 0; i < n; i++) clientes[i].thr.start();

	}
}