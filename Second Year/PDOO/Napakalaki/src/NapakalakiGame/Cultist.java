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


public   class Cultist implements Card {
       private String name;
       private int gainedLevels;
       public Cultist(String n,int g,String i)
       {
           name = n;
           gainedLevels = g;
       }
       
    @Override
    public int getBasicValue() {
        return this.gainedLevels;
    }

    @Override
    public int getSpecialValue() {
        return this.getBasicValue() * CultistPlayer.getTotalCultistPlayer();
                
    }

    
}
