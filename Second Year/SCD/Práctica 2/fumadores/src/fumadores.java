/************************************************************
	Francisco Carrillo Pérez                                *
	Sistemas Concurrentes y distribuidos.                   *
	Práctica 2                                             *
************************************************************/


import monitor.* ;
import java.util.Random ;
class Estanco extends AbstractMonitor
{ 

	
	private boolean enlamesa = false;
	private Condition estanquero = makeCondition();
	private Condition [] fumador=new Condition[3];
	public Estanco(){
		for(int i=0; i<3; i++){
			fumador[i] = makeCondition();
	}
	}

	// invocado por cada fumador, indicando su ingrediente o numero
	public void obtenerIngrediente( int miIngrediente )
	{ 
		enter();
		if(miIngrediente == 0)
		{
			if(enlamesa == false) fumador[2].await();

			System.out.println("Fumador1 coge su ingrediente");
			enlamesa = false;
			estanquero.signal();
			
		}
		if(miIngrediente == 1)
		{
			if(enlamesa == false) fumador[1].await();
			System.out.println("Fumador2 coge su ingrediente");
			enlamesa = false;
			estanquero.signal();
			
		}
		if(miIngrediente == 2)
		{
			if(enlamesa == false) fumador[0].await();
			System.out.println("Fumador3 coge su ingrediente");
			enlamesa = false;
			estanquero.signal();
			
		}
		leave();



	}
	// invocado por el estanquero, indicando el ingrediente que pone
	public void ponerIngrediente( int ingrediente )
	{ 
		enter();
		enlamesa = true;
		 //papel--->0; tabaco ---->1 ; cerillas ---->2
		if(ingrediente == 0)
		{
			System.out.println("Poniendo en la mesa papel");
			
			fumador[2].signal();
			
		}
		if(ingrediente == 1)
		{
			System.out.println("Poniendo en la mesa tabaco");
			
			fumador[1].signal();
			
		}
		if(ingrediente == 2)
		{
			System.out.println("Poniendo en la mesa cerillas");
			
			fumador[0].signal();
			
		}
		leave();

	
	}
	// invocado por el estanquero
	public void esperarRecogidaIngrediente()
	{ 
		enter();
		if(enlamesa) estanquero.await();
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

class Fumador implements Runnable
{
	int miIngrediente;
	private Estanco estanco;
	public Thread thr ;

 	
	public Fumador( int p_miIngrediente, Estanco est,int i )
	{ 
		estanco = est;
		miIngrediente = p_miIngrediente;
		thr   = new Thread(this,"Fumador "+i);

	}
	public void run()
	{
		while ( true )
		{ 
			estanco.obtenerIngrediente( miIngrediente );
			System.out.println(thr.getName()+ " fumando");
			aux.dormir_max( 2000 );
			System.out.println(thr.getName()+ " ha acabado de fumar");
		}
	}
}

class Estanquero implements Runnable
{ 
	public Thread thr ;
	private Estanco estanco;
	public Estanquero(Estanco est)
	{
		estanco = est;
		thr = new Thread(this,"Estanquero");
	}
	public void run()
	{ 
		int ingrediente ;
		while (true)
		{
			ingrediente = (int) (Math.random () * 3.0); // 0,1 o 2
			estanco.ponerIngrediente( ingrediente );
			estanco.esperarRecogidaIngrediente() ;
		}
	}
}

class fumadores
{
	public static void main( String[] args ) 
	{
		Estanco estanco = new Estanco();
		Estanquero estanquero = new Estanquero(estanco);
		Fumador[] fumadores = new Fumador[3];

		for(int i = 0; i < 3;i++)
		{
			fumadores[i] = new Fumador(i,estanco,i+1);
		}

		//poner en marcha las hebras
		estanquero.thr.start();
		for(int i = 0; i < fumadores.length; i++) fumadores[i].thr.start();

	}
}

