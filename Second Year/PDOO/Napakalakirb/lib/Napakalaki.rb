# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

 require 'singleton'
 require_relative 'BadConsequence'
require_relative 'Treasure'
require_relative 'dice'
require_relative 'combat_result'
require_relative 'player'
require_relative 'card_dealer'
require_relative 'TreasureKind'
require_relative 'Monster'
require_relative 'Prize'
module Napakalaki
 class Napakalaki
      include Singleton
      
      attr_reader :currentPlayer,:players,:dealer,:currentMonster,:indexCurrentPlayer
  
      def initialize
          @currentPlayer=nil
          @indexCurrentPlayer = -1
          @players=Array.new
          @dealer=CardDealer.instance
          @currentMonster=nil
      end
      
      def initPlayers(names)
        names.each{ |n|
          @players << Player.new(n)
          
        }
        
      end
  
       def nextPlayer
         #Si es la primera vez, se elige aleatoriamente
        if(@currentPlayer == nil)
          @indexCurrentPlayer = rand(@players.size)
         @currentPlayer = @players[@indexCurrentPlayer]
       else
         #Siguiente jugador, sin ser la primera vez
          @indexCurrentPlayer += 1
          @currentPlayer = @players[(@indexCurrentPlayer)%@players.size]
      end

        return @currentPlayer
      end
       
       def nextTurnAllowed
         
         if @currentPlayer.validState
           return true
         else
           return false
         end
       end
        
       def developCombat
         combatresult = @currentPlayer.combat(@currentMonster)
        @dealer.giveMonsterBack(@currentMonster)
        if combatresult == CombatResult::LOSEANDCONVERT
          c=@dealer.nextCultist
          cP=CultistPlayer.new(@currentPlayer,c)
          @currentPlayer=cP
          @players[@currentPlayerIndex] = cP
        end
         return combatresult
       end
  
       def discardVisibleTreasures(treasures)
         treasures.each{|t|
           @currentPlayer.discardVisibleTreasure(t)
           @dealer.getTreasuresBack(t)
           
         }
       end
       
       def discardHiddenTreasures(treasures)
           treasures.each{|t|
             @currentPlayer.discardHiddenTreasure(t)
             @dealer.getTreasureBack(t)
           }
       end
#  
       def makeTreasuresVisible(treasures)
         treasures.each{|t|
           @currentPlayer.makeTreasureVisible(t)
           
         }
       end
       
       def buyLevels(visible, hidden)
         canl = @currentPlayer.buyLevels(visible,hidden)
         return canl
       end
       
       def initGame(players)
         initPlayers(players)
         CardDealer.instance.initCards
         nextTurn
       end
       
      
       def getCurrentMonster()
         @currentMonster
       end
       
       def  nextTurn
         if(currentPlayer == nil)
            stateOk = true
        else
          stateOk = nextTurnAllowed
        end
         if(stateOk)
          @currentMonster = CardDealer.instance.nextMonster
          @currentPlayer = nextPlayer
          dead = @currentPlayer.isDead
          @currentPlayer.initTreasures if (dead)
        end
          return stateOk   
       end
       
       def endOfGame(result)
         if result == CombatResult::WINANDWIN
           return true
         else
           return false
           
         end
       end
      def getCurrentPlayer
          return @currentPlayer
      end
end
end

 
