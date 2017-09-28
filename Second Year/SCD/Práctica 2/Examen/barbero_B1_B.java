import monitor.* ;
import java.util.Random ;

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


class Barberia extends AbstractMonitor
{
   int num_clientes = 0;  //numero de clientes dentro de la barberia
      
   Condition clientesEnEspera, // cola donde esperan los clientes hasta que el barbero pueda cortarles el pelo
             clienteEnCorte, // cola donde espera el cliente al que el barbero le está cortando el pelo
             barberoDormido ; // cola donde espera el barbero mientras duerme
             
   public Barberia()
   {
      clientesEnEspera = makeCondition() ;
      clienteEnCorte = makeCondition() ;
      barberoDormido  = makeCondition() ;
   }
   
   // invocado por las hebras de clientes para entrar en la barberia y 
   // después esperar hasta que el barbero les ha cortado el pelo
   
   public void cortarPelo()
   {
      enter() ;
      
      System.out.print(Thread.currentThread().getName()+" llega a la barberia, comprueba si el barbero está ocupado : ");
      num_clientes++;
      
      if ( num_clientes > 1 ) // si el barbero está pelando o a punto de pelar a otro cliente
      {  
	 System.out.println("barbero ocupado, cliente espera.");
         clientesEnEspera.await() ; // esperar con el resto de clientes
      }
      else // si el barbero no está pelando (está dormido o a punto de hacerlo)
      {   
	 System.out.println("barbero durmiendo, va a despertarlo.");
         barberoDormido.signal() ; // despertar al barbero
      }
      System.out.println(Thread.currentThread().getName()+" comienza a cortarse el pelo.");

      clienteEnCorte.await() ; // esperar a que el barbero indique que ha terminado de cortarme el pelo

      System.out.println(Thread.currentThread().getName()+" ha terminado de cortarse el pelo, abandona la barbería.");
      
      leave() ;
   }
   
   // invocado por la hebra de barbero para esperar a que llegue un 
   // cliente
   public void siguienteCliente()
   {
      enter() ;
      System.out.print(Thread.currentThread().getName()+" mira a ver si hay un cliente: ");
      
      if ( num_clientes == 0 ) // si no hay clientes en la barberia
      {
         System.out.println("no hay, se pone a dormir.");
         barberoDormido.await() ; // dormir esperando a que llege uno y me despierte
      }
      else // sí hay clientes en la sala de espera
      {  
         System.out.println("sí hay, va a despertar a uno.");
         clientesEnEspera.signal() ; // despertar a uno de ellos para cortarle el pelo
      } 
       
      System.out.println(Thread.currentThread().getName()+" comienza a cortar el pelo");
      
      leave() ;
   }
   
   // invocado por la hebra de barbero para señalar que ha acabado con
   // el cliente con el que estaba
   public void finCliente()
   {
      enter() ;
      System.out.println("barbero finaliza corte de pelo, indicará al cliente que salga");
      num_clientes--;  //cliente va a salir de la barberia
      clienteEnCorte.signal() ; // indicar al cliente que he terminado de cortarle el pelo
      leave() ;	   
   }
}

class Cliente implements Runnable
{
   Barberia      barberia ;
   public Thread thr ;
   static int    contador = 0 ;
   
   public Cliente( Barberia p_barberia )
   {
 
      contador++ ;
      
      barberia = p_barberia ;
      thr    = new Thread(this,"cliente "+contador);
      
      System.out.println("creando hebra '"+thr.getName()+"'"); 
   }
   
   public void run()
   {
	  System.out.println("comienza '"+thr.getName()+"'");
	   
      while( true )
      {
		  barberia.cortarPelo() ;
		  aux.dormir_max( 1000 );
	  }
   }
}

//----------------------------------------------------------------------

class Barbero implements Runnable
{
   Barberia       barberia ;
   public Thread  thr ;
   
   public Barbero( Barberia p_barberia )
   {
      assert p_barberia != null ;
      
      barberia = p_barberia ;
      thr    = new Thread(this,"barbero");
      
      System.out.println("creando hebra '"+thr.getName()+"'"); 
   }
   
   public void run()
   {
	  
	  System.out.println("comienza '"+thr.getName()+"'");
	 
      while( true )
      {
		  barberia.siguienteCliente() ;
		  aux.dormir_max( 500 );
		  barberia.finCliente() ;
	  }
   }
}

class barbero_B1_B
{
  
	public static void main( String args[] )
	{
	       int num_hebras_cliente = 3;

		System.out.println("comienza simulación de barbería.");
		
		Barberia  barberia = new Barberia() ;
		Barbero   barbero  = new Barbero(barberia);
		Cliente[] cliente  = new Cliente[num_hebras_cliente] ;
		
		for( int i = 0 ; i < num_hebras_cliente ; i++ )
			cliente[i] = new Cliente(barberia) ;

		barbero.thr.start();
		for( int i = 0 ; i < num_hebras_cliente ; i++ )
			cliente[i].thr.start();


	}
}
