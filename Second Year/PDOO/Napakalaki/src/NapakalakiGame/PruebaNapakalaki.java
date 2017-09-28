/*  
 *  Programación y diseño orientado a objetos
 *  Grado en Ingeniería Informática
 * 
 *  
 *
 *  Angela Castro Jiménez
 *  Francisco Carrillo Pérez
 */
package NapakalakiGame;
import java.util.ArrayList;
import java.util.Arrays;


public class PruebaNapakalaki {

    /**
     * @param args the command line arguments
     */
     public static void main(String args[]){
        
        
       
        
        
        //PRUEBAS CONSULTA CARTAS
        
            //Mostrar los monstruos con un nivel superior a 10
            /*
                for(Monster m : monstruos){
                    if(m.getCombatLevel() >= 10){
                        System.out.println(m.getName());
                    }
                }
            */ 
        
            //Mostrar los monstruos que tengan un mal rollo que solo
            // implique perdida de niveles
            /*
                BadConsequence mal = new BadConsequence();
                for(Monster m : monstruos){
                    mal = m.getMalrollo();
                    if((mal.getLevelsPerdidos() > 0) && (mal.getnHiddenPerdidos() == 0) && (mal.getnVisiblePerdidos() == 0)){
                        System.out.println(m.getName());
                    }
                }
            */
        
            //Mostrar los monstruos que su buen rollo indique una ganancia de niveles superior a 1
            
//                Prize prem = new Prize();
//                for (Monster m : monstruos){
//                    prem = m.getPrize();
//                    if(prem.GetLevel() > 1){
//                    System.out.println(m.getName());
//                    }
//                }
               
    }
    
}
