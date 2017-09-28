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

public class Monster implements Card {
    private String name;
    private int combatLevel;
    private int levelChangedAgainstCultistPlayer;
    private Prize prize = new Prize();
    private BadConsequence badConsequence = new BadConsequence();
    
    private String tipo;
    
    public Monster(){
        name = "";
        combatLevel = 0;
        
    }
     
    public Monster(String n, int l){
        name = n;
        combatLevel = l;
    }

    public Monster(String n, int l, BadConsequence b, Prize p){
        name = n;
        combatLevel = l;
        badConsequence = b;
        prize = p;
        
    }
    
    public Monster(String n, int l, BadConsequence b, Prize p, int levels){
        name = n;
        combatLevel = l;
        badConsequence = b;
        prize = p;
        levelChangedAgainstCultistPlayer = levels;
        
    }
    
    public String getTipo(){
        return tipo;
    }
    
    public String getName(){
        return name;
    }
    
    public int getCombatLevel(){
        return combatLevel;  
    }
    
    public Prize getPrize(){
         return prize;
    }
    
    public BadConsequence getBadConsequence(){
         return badConsequence;
    }
    
    public int getLevelsGained(){
        return prize.getLevels();
        
    }
    
     public int getTreasuresGained(){
        return prize.getTreasures();
    }
    
    public boolean kills(){
        return badConsequence.myBadConsequenceIsDeath();
    }
     
     private int levelChangedAgainstCultistPlayer()
     {
         return levelChangedAgainstCultistPlayer;
     }
     
     @Override
     public int getBasicValue()
     {
         return combatLevel;
         
     }
    
    @Override
    public int getSpecialValue() {
        return this.getCombatLevel() + this.levelChangedAgainstCultistPlayer();
    }
    
    public String toString(){
        return "Nombre: "+name
                +".\nNivel: " + Integer.toString(combatLevel)
                +".\nPremio: " + prize.toString()
                +"\n"+ badConsequence.toString();
        }
    
    
        
   
    }
    /*PRUEBA
        public static void main(String args[]){
          Prize prize = new Prize(4,2);
          BadConsequence malrollo = new BadConsequence("Pierdes 5 niveles", 5, 0, 0);
          Monster monstruo = new Monster("El monstruo de prueba", 5, malrollo, prize);
          
           System.out.println(monstruo.getName());
           System.out.println(monstruo.getCombatLevel()); 
           System.out.println(monstruo.getPrize()); 
           System.out.println(monstruo.getMalrollo()); 
           System.out.println(monstruo.toString());    
}
        }*/
     

