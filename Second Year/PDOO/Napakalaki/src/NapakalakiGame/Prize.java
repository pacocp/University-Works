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


public class Prize {
    
    private int level;
    private int treasures;
    
    public Prize (){
      level = 0;
      treasures =0; 
    }
    
    public Prize (int t, int l) {
        treasures = t;
        level = l;
    }
    
    public int getTreasures(){
        return treasures;
    }
    
    public int getLevels(){
        return level;
    }
    
    public String toString(){
        return "Tesoros = "+Integer.toString(treasures)+". Niveles = " + Integer.toString(level)+".";   
    }

    
   /* PRUEBA 
        public static void main(String args[]){
           Prize premio = new Prize (2,4);
           System.out.println(premio.GetLevel());
           System.out.println(premio.GetTreasures()); 
           System.out.println(premio.toString());
        } */
}
