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

public class Treasure implements Card{
    private String name;
    private int goldCoins;
    private int minBonus;
    private int maxBonus;
    private TreasureKind type;
    
    public Treasure (String n, int g,int min, int max, TreasureKind t){
        name = n;
        goldCoins = g;
        minBonus = min;
        maxBonus = max;
        type= t;
    }
    
    public String getName(){
        return name;
    }
    
    public int getGoldCoins(){
        return goldCoins;
    }
    
    public int getMinBonus(){
        return minBonus;
    }
    
    public int getMaxBonus(){
        return maxBonus;
    }
    
    public TreasureKind getType(){
        return type;
    }
    
     public String toString(){
        return "Nombre: "+name
                +".\nMonedas: " + Integer.toString(goldCoins)
                +".\nBonus Minimo: " +minBonus
                +"\nBonus Maximo"+ maxBonus
                +"\nTipo de Tesoro: "+ type;
        }
     
     @Override
     public int getBasicValue(){
         return this.getMinBonus();
     }
    
     @Override
     public int getSpecialValue(){
         return this.getMaxBonus();
     }
}
