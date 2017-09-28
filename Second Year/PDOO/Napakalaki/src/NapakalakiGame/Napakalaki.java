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
import java.util.Random;

public class Napakalaki {
    public Player  currentPlayer = new Player("");
    public ArrayList<Player> players = new ArrayList();
    
    public CardDealer dealer = CardDealer.getInstance();
    public Monster currentMonster = new Monster();
    
    private static final Napakalaki instance = new Napakalaki();
    
    private Napakalaki(){};
    
    private void initPlayers(ArrayList<String> names){
          for(String m:names){
              players.add(new Player(m));
          }
          
          Random rnd = new Random();
          int  nextIndex = rnd.nextInt(names.size());
          currentPlayer = players.get(nextIndex);
    }
    
    private Player nextPlayer(){
          int nextIndex;
        Player nextPlayer;
 
        //Obtenemos el numero total de jugadores
        int totalPlayers = this.players.size();
 
        //Si no está definido el jugador actual es porque es la primera vez
        if (this.currentPlayer == null) {
 
            //Creamos un objeto Random
            Random rnd = new Random();
 
            //Obtenemos un numero aleatorio con tope el índice maximo del 
            //numero de jugadores
            nextIndex = rnd.nextInt(totalPlayers);
 
        } else {
 
            //Obtenemos el índice del jugador actual
            int currentPlayerIndex = this.players.indexOf(this.currentPlayer);
 
            if (currentPlayerIndex == totalPlayers - 1) {
                //Si es el último seleccionamos el primero
                nextIndex = 0;
 
            } else {
                //En caso contrario seleccionamos el siguiente
                nextIndex = currentPlayerIndex + 1;
            }
 
        }
 
        //Obtenemos el jugador correspondiente al índice aleatorio
        nextPlayer = this.players.get(nextIndex);
 
        //Establecemos el siguiente jugador
        this.currentPlayer = nextPlayer;
 
        return this.currentPlayer;
          
    }
    
    public boolean nextTurnAllowed(){
      if(currentPlayer.validState()){
          return true;
      }
      else{
          return false;
      }
    }
    
    
    public static Napakalaki getInstance(){
        return instance;
    }
    
    public CombatResult developCombat(){
        CombatResult combatresult = currentPlayer.combat(currentMonster); 
        //Comprobamos si el resultado es LoseAndConvert
        if (combatresult == CombatResult.LoseAndConvert) {

            //Obtenemos una carta de cultista
            Cultist cl = this.dealer.nextCultist();

            //Creamos un nuevo cultista
            CultistPlayer clPlayer = new CultistPlayer(this.currentPlayer, cl);

            //Obrenemos el indice del currentplayer por sustituirlo por el cultista
            int currentPlayerIndex = this.players.indexOf(this.currentPlayer);

            //Sustituimos el cultista
            this.players.set(currentPlayerIndex, clPlayer);

            this.currentPlayer = clPlayer;
        }
        dealer.giveMonsterBack(currentMonster);
        return combatresult;
    }
    
    public void discardVisibleTreasures(ArrayList<Treasure> treasures){
        for(Treasure t: treasures){
           currentPlayer.discardVisibleTreasure(t);
           dealer.giveTreasuresBack(t);
        }
    }
   
    public void discardHiddenTreasures(ArrayList<Treasure> treasures){
        for(Treasure t: treasures){
           currentPlayer.discardHiddenTreasure(t);
           dealer.giveTreasuresBack(t);
        }
    
    }
    
    public void makeTreasuresVisible(ArrayList<Treasure> treasures){
        for(Treasure t:treasures){
            currentPlayer.makeTreasureVisible(t);
        }
    }
    
    public boolean buyLevels(ArrayList<Treasure> visible, ArrayList<Treasure> hidden){
        
        boolean canl = currentPlayer.buyLevels(visible,hidden);
        return canl;
    }
    
    public void initGame(ArrayList<String> names){
        this.initPlayers(names);
        dealer.initCards();
        this.nextTurn();
    }
    
    public Player getCurrentPlayer(){
        return currentPlayer;
    }
    
    public Monster getCurrentMonster(){
        return currentMonster;
    }
    
   
    public boolean nextTurn(){
        boolean stateOK = this.nextTurnAllowed();
        if(stateOK){
            currentMonster = dealer.nextMonster();
            currentPlayer = this.nextPlayer();
            boolean dead = currentPlayer.isDead();
            if(dead){
                currentPlayer.initTreasures(); 
            }
        }
        return stateOK;
    }
    
    public boolean endOfGame(CombatResult result){
     if(result == CombatResult.WinAndWinGame )
     {
         return true;
     }
     else
     {
         return false;
     }
    }
}

