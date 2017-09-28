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



public class CultistPlayer extends Player{
        
    private static int totalCultistPlayer = 0;
    Cultist myCultistCard;
    public CultistPlayer(Player p, Cultist c)
    {
        super(p);
        myCultistCard = c;
        totalCultistPlayer++;
        
        
    }

    public static int  getTotalCultistPlayer(){
        return totalCultistPlayer;
    }  
    
    
    @Override
    protected boolean shouldConvert()
    {
        //Siempre devuelve false
        return false;
    }
    
    @Override
    protected int getOponentLevel(Monster m)
    {
         return m.getSpecialValue();
    }
    
    @Override
    public int getCombatLevel() {

        return super.getCombatLevel() + this.myCultistCard.getSpecialValue();

    }
    
    @Override
    protected int computeGoldCoinsValue(ArrayList<Treasure> treasures) {
        
        return super.computeGoldCoinsValue(treasures) * 2;
    }
    
    public Cultist getCultistCard() {
    
        return this.myCultistCard;
    }
    
    //EXAMEN
    public void changeTreasure(Treasure t)
    {
        super.changeTreasure(t);
        
    } 
    //FIN EXAMEN
}
