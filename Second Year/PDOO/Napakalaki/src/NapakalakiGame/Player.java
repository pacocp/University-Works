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

public class Player {
   private boolean dead = true;
   private String name;
   private int level;
   
   private ArrayList<Treasure> visibleTreasures = new ArrayList();
   private ArrayList<Treasure> hiddenTreasures = new ArrayList();
   private BadConsequence pendingBadConsequence = new BadConsequence();
   
   public Player(String miname){
       name = miname;
       level = 1;
   }

   public Player(Player p)
   {
       this.name = p.name;
       this.dead = p.dead;
       this.level = p.level;
       
       
   }
   public void bringTolife(){
       dead = false;        
   }
   public boolean getDeath()
   {
       return dead;
   }
   //Devuelve el nivel de combate del jugador, que viene dado por su nivel más 
    //los bonus que le proporcionan los tesoros que tenga equipados, según las 
    //reglas del juego.
     public int getCombatLevel(){
         boolean tiene = false;
         int levelfinal=level;
         for(Treasure t: visibleTreasures){
             if(t.getType()==TreasureKind.NECKLACE){
                tiene = true;
             }
         }
         
         for(Treasure t: visibleTreasures){
             if(tiene){
                 levelfinal=levelfinal+ t.getMaxBonus();
             }
             else{
                 levelfinal=levelfinal+ t.getMinBonus();
             }
         
         }
         return levelfinal;      
     
     }        
   
   public void incrementLevels(int I){
      level = level + I;
   }
   
   public void decrementLevels(int I){
       if(level<=I)
           level=1;
       else
        level = level - I;
   }
   
   public void setPendingBadConsequence(BadConsequence b){
      pendingBadConsequence = b;
   }
   
   //Cambia el estado de jugador a muerto si no tiene ni tesoros visibles ni 
    //ocultos, modificandon el correspondiente atributo.
   public void dieIfNoTreasures() {
      if(visibleTreasures.size() <= 0 && hiddenTreasures.size() <= 0){
          dead = true;
      }
   }
   
   //Si el jugador tiene equipado el tesoro tipo NECKLACE, se lo pasa al CardDealer y lo
   //elimina de sus tesoros visibles.
   public void discardNecklaceVisible() {
         for (Treasure t : this.visibleTreasures) {
 
            if (t.getType() == TreasureKind.NECKLACE) {
 
                //Le pasamos el tesoro al CardDealer
                CardDealer cd = CardDealer.getInstance();
                cd.giveTreasuresBack(t);
 
                //Lo eliminamos de nuestros tesoros visibles (equipados)
                visibleTreasures.remove(t);
 
                //Salimos del bucle
                break;
            }
         }
   }
  
   
   public void die() {
       this.setLevels(1);
       CardDealer dealer = CardDealer.getInstance();
       for(Treasure t:visibleTreasures)
       {
           dealer.giveTreasuresBack(t);
       }
       visibleTreasures.clear();
       for(Treasure t: hiddenTreasures)
       {
           dealer.giveTreasuresBack(t);
       }
       hiddenTreasures.clear();
       this.dieIfNoTreasures();
       
   }
   
   // Calcula y devuelve los niveles que puede comprar el jugador con la lista t de tesoros.
   protected int computeGoldCoinsValue( ArrayList<Treasure> t) {
        int suma = 0;
        for(Treasure tr: t){
            suma = suma + tr.getGoldCoins();
        }
        return suma%1000;
   }
   
 
   public boolean canBuyLevels(int l){
       return this.level+l<10;

   }                         
   
   
   public void applyPrize(Monster currentMonster){
       int nLevels =  currentMonster.getLevelsGained();
       this.incrementLevels(nLevels);
       int nTreasures = currentMonster.getTreasuresGained();
       if(nTreasures >0)
       {
           CardDealer dealer = CardDealer.getInstance();
           int i;
           for(i = 1; i <= nTreasures;i++)
           {
               Treasure treasure = dealer.nextTreasure();
               hiddenTreasures.add(treasure);
           }
       }
   }
   
   
   public void applyBadConsequence(BadConsequence bad){
       int nLevels = bad.getLevels();
       this.decrementLevels(nLevels);
       BadConsequence pendingBad = bad.adjustToFitTreasureLists(visibleTreasures, hiddenTreasures);
       setPendingBadConsequence(pendingBad);
   }
   public BadConsequence getPendingBadConsequence()
   {
       return pendingBadConsequence;
   }
    private boolean isTreasureKindInUse(TreasureKind type) {
        boolean result = false;
        for (Treasure tv : this.visibleTreasures) {
 
            if (type.equals(tv.getType())) {
 
                result = true;
                break;
 
            }
 
        }
        return result;
    }
   //Comprueba si el tesoro (t) se puede pasar de oculto a visible, 
    //según las reglas del juego
   public boolean canMakeTreasureVisible(Treasure t){
       if(t.getType()==TreasureKind.ONEHAND){
           int cont=0;
           for(Treasure tr: visibleTreasures){
               if(tr.getType()==TreasureKind.ONEHAND)
                   cont++;
               if(tr.getType()==TreasureKind.BOTHHAND)
                   return false;
           }
       
       }
       else if (t.getType()==TreasureKind.BOTHHAND){
           for(Treasure tr: visibleTreasures){
               if(tr.getType()==TreasureKind.ONEHAND || tr.getType()==TreasureKind.BOTHHAND)
                   return false;
           }
       }
        else{
           for(Treasure tr: visibleTreasures){
               if(tr.getType()==t.getType())
                   return false;
           }
       }
       return true;
       
    }

   
   public int howManyVisibleTreasures(TreasureKind tkind){
       int contador = 0;
       for(int i = 0; i < visibleTreasures.size();i++){
          Treasure t;
          t = visibleTreasures.get(i);
          if(t.getType() == tkind){
              contador++;
          }
        }
       return contador;     
    }
   
   public boolean isDead(){
       return dead;
   }
   
   
  public ArrayList<Treasure> getHiddenTreasures(){
     
       
       return hiddenTreasures;
  }
   
   
   public ArrayList<Treasure> getVisibleTreasures(){
       
       return visibleTreasures;
   }
   
   
  public CombatResult combat(Monster m){
      CombatResult combatResult;
      
      int myLevels = this.getCombatLevel();
      int monsterlevel = this.getOponentLevel(m);
      if(myLevels > monsterlevel){
          this.applyPrize(m);
          if(this.level >=10){
              combatResult = CombatResult.WinAndWinGame;
          }
          else{
              combatResult = CombatResult.Win;
          }
      }
       else{
          Dice dice = Dice.getInstance();
          int escape = dice.nextNumber();
          if(escape<5){
              boolean amIDead = m.kills();
              if(amIDead == true) {
                  this.die();
                  combatResult=CombatResult.LoseAndDie;
              }
              else {
                  boolean should = this.shouldConvert();
                  if(should)
                  {
                      combatResult=CombatResult.LoseAndConvert;
                  }
                  else
                  {
                       BadConsequence bad = m.getBadConsequence();
                       combatResult=CombatResult.Lose;
                       this.applyBadConsequence(bad);
                  }
                 
              }
          }
          else{
              combatResult=CombatResult.LoseAndEscape;
          }
        }
      
      this.discardNecklaceVisible();
      return combatResult;
  }
   
  
   public void makeTreasureVisible(Treasure t) {
       boolean canl = this.canMakeTreasureVisible(t);
       if(canl)
       {
           visibleTreasures.add(t);
           hiddenTreasures.remove(t);
       }
   }
  
   public void discardVisibleTreasure(Treasure t) {
       visibleTreasures.remove(t);
       if((pendingBadConsequence != null) && (!pendingBadConsequence.isEmpty())){
           pendingBadConsequence.substractVisibleTreasure(t);
       }
       this.dieIfNoTreasures();
       
   }
   
   
  public void discardHiddenTreasure(Treasure t){
      hiddenTreasures.remove(t);
      if((pendingBadConsequence != null) && (!pendingBadConsequence.isEmpty())){
          pendingBadConsequence.substractHiddenTreasure(t);
      }
      this.dieIfNoTreasures();
  }
   
   
   public boolean buyLevels(ArrayList<Treasure> visible,ArrayList<Treasure> hidden){
        float levelsMayBought=computeGoldCoinsValue(visible);
        levelsMayBought+=computeGoldCoinsValue(hidden);
        int levels=(int)levelsMayBought/1000;
        boolean canI=canBuyLevels(levels);
        if(canI)
            incrementLevels(levels);
        visibleTreasures.removeAll(visible);
        hiddenTreasures.removeAll(hidden);
        CardDealer dealer=CardDealer.getInstance();
        for(Treasure t:visible)
            dealer.giveTreasuresBack(t);
        for(Treasure t:hidden)
            dealer.giveTreasuresBack(t);
        return canI;
       
   }
   
   public boolean validState(){
     return (pendingBadConsequence.isEmpty() &&  hiddenTreasures.size() <= 4);
   }
   
   
   public void initTreasures() {
       CardDealer dealer = CardDealer.getInstance();
       Dice dice = Dice.getInstance();
       this.bringTolife();
       Treasure treasure = dealer.nextTreasure();
       hiddenTreasures.add(treasure);
       int number = dice.nextNumber();
       if(number  > 1)
       {
           treasure = dealer.nextTreasure();
           hiddenTreasures.add(treasure);
       }
       if(number == 6)
       {
           treasure = dealer.nextTreasure();
           hiddenTreasures.add(treasure);
       }
   }
   
   public boolean hasVisibleTreasures(){
     return(visibleTreasures.size() > 0);
   }
   
   public int getLevels(){
       return level;
   }
   
   public void setLevels(int i)
   {
       level = i;
   }
   
   public String getName()
   {
       return name;
   }
 
   
   protected boolean shouldConvert()
    {
        Dice dice = Dice.getInstance();
        int escape = dice.nextNumber();
        
        return (escape == 6);
       
    }
    
   protected int getOponentLevel(Monster m)
    {
        return m.getCombatLevel();
    }
   
   //EXAMEN
     public void changeTreasure(Treasure t)
    {
        CardDealer dealer = CardDealer.getInstance();
        Treasure treasure = dealer.nextTreasure();
        hiddenTreasures.remove(t);
        hiddenTreasures.add(treasure);
        
        
    }
     //FIN EXAMEN
  public String toString(){
        return "Nombre: "+name
                +" \nNivel del jugador " + Integer.toString(level)
                +"\nNivel de combate: "+ Integer.toString(getCombatLevel());
     }
}

