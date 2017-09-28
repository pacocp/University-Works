# encoding: UTF-8
#
#   Programación y diseño orientado a objetos
#   Grado en Ingeniería Informática
#
#  Ángela Castro Jimenez
#  Francisco Carrillo Pérez
module Napakalaki
  require_relative 'BadConsequence.rb'
  require_relative 'Prize.rb'
  require_relative 'dice'
  
  require_relative 'card_dealer'
  require_relative 'TreasureKind'
  
#  require 'singleton'

class Player
#    include Singleton 
    attr_accessor :name, :dead,:level, :pendingBadConsequence,:visibleTreasures,:hiddenTreasures
    
     
      
#  private_class_method :new
   
    
   def initialize (name)
     if(name.class.eql?(String))
      @name = name
      @dead = true
      @level = 1
      @hiddenTreasures = Array.new
      @visibleTreasures = Array.new
      @pendingBadConsequence = BadConsequence.newLevelNumberOfTreasures("", 0, 0, 0)
     
     else
     @name = name.name
     @dead = name.dead
     @level = name.level
     @pendingBadConsequence = name.pendingBadConsequence
     @visibleTreasures = name.visibleTreasures
     @hiddenTreasures = name.hiddenTreasures
     end
   end
   
   def oponent_Level(m)
      return m.getBasicValue
  end
  
   def should_convert
    dice=Dice.instance
    return dice.nextNumber==6
  end
  
   def to_s
      "#{@name}\n Level: #{@level}\n"
  end
   def bringTolife()
     @dead = false
   end
   
   def incrementLevels(i)
       @level = @level + i
   end
   
   def decrementLevels (i)
     @level = @level - i
   end
   
   def dieIfNoTreasures()
       if (@visibleTreasures.size <= 0 && @hiddenTreasures.size <= 0)
            @dead = true
       end
   end
#  //Devuelve el nivel de combate del jugador, que viene dado por su nivel más 
#    //los bonus que le proporcionan los tesoros que tenga equipados, según las 
#    //reglas del juego.
   def getCombatLevel()
      tiene = false
      levelfinal = @level
      @visibleTreasures.each{|t|
        if t.type == TreasureKind::NECKLACE
          tiene = true
        end
      }
       @visibleTreasures.each{|t|
         if tiene
           levelfinal = levelfinal + t.getMaxBonus()
         else
           levelfinal = levelfinal + t.getMinBonus()
         end
       }
       
      return levelfinal
   end
   def incrementLevels(aumento)
      @level = @level + aumento
   end
   
   def decrementLevels(decremento)
     @level = @level - decremento
   end
#Si el jugador tiene equipado el tesoro tipo NECKLACE, se lo pasa al CardDealer y lo
#elimina de sus tesoros visibles. 
   def discardNecklaceIfVisible()
       collar = false;
      for i in 0..@visibleTreasures.size()-1
        if collar then
          break
        end
        if (@visibleTreasures.at(i).type().to_s == "[:NECKLACE]")
          collar = true
          tesoro = @visibleTreasures.at(i)
          CardDealer.instance.giveTreasureBack(tesoro)
          @visibleTreasures.delete(tesoro)
          @pendingBadConsequence.substractVisibleTreasure(tesoro) 
          dielfNoTreasures
        end
      end
        end
 
      
      
   


   def die()
     @level = 1
     dealer = CardDealer.instance
     @visibleTreasures.each{|t|
       dealer.giveTreasureBack(t);
       
     }
     
     @hiddenTreasures.each{|t|
       dealer.giveTreasureBack(t);
       
     }
     @visibleTreasures.clear
     @hiddenTreasures.clear
     dieIfNoTreasures
     
     
   end


   def computeGoldCoinsValue(t)
     suma = 0
     t.each{ |tr|
        suma = suma + tr.getGoldCoins
     }
     
     return suma
     
   end

   def  canBuyLevels(i)
      puedecomprar = false
      sumamonedas = 0
      
     @visibleTreasures.each{ |t|
       sumamonedas = sumamonedas + t.getGoldCoins
       if(sumamonedas >= i*1000)
         puedecomprar = true
       end
     }
     if (puedecomprar)
        return puedecomprar
     
     else
       @hiddenTreasures.each{ |t|
         sumamonedas = sumamonedas + t.getGoldCoins
       if(sumamonedas >= i*1000)
         puedecomprar = true
       end
       }
       return puedecomprar
   
    end
   
  end
  
 
   def applyPrize(currentMonster)

    nLevels = currentMonster.getLevelsGained()
    incrementLevels(nLevels)
    nTreasures = currentMonster.getTreasuresGained
        
      if(nTreasures > 0)
        dealer = CardDealer.instance
        for i in 0..(nTreasures-1)
          t = dealer.nextTreasure
          @hiddenTreasures << t
        end
    end
   end


   def applyBadConsequence(bad)
     nLevels = bad.getLevels
     decrementLevels(nLevels)
     pendingBad = bad.adjustToFitTreasureLists(@visibleTreasures, @hiddenTreasures)
     setPendingBadConsequence(pendingBad)
   end


   
   def canMakeTreasureVisible(treasure)
     isWearable=false;
      tipo=treasure.getType.to_s
      contador=howManyVisibleTreasures(tipo)
      
      if(tipo.eql?("[:ONEHAND]") && contador<2 && howManyVisibleTreasures("[:BOTHHAND]")==0)
        isWearable=true
      elsif(tipo.eql?("[:BOTHHAND]") && contador==0 && howManyVisibleTreasures("[:ONEHAND]")==0)
        isWearable=true
      elsif(tipo!="[:BOTHHAND]" && tipo!="[:ONEHAND]" && contador==0)
        isWearable=true
      end
      
      return isWearable 
   
    end
    
   


   def howManyVisibleTreasures(tKind)
     contador = 0
     @visibleTreasures.each{ |t|
       if(t.getType == tKind)
         contador = contador + 1
       end
     }
     return contador
   end
   
   def isDead()
      @dead
   end
   
#   Aun no implementado
   def getHiddenTreasures()
     @hiddenTreasures
   end

#   Aun no implementado
   def getVisibleTreasures()
     @visibleTreasures
   end
   
def getName
  return @name
end


    def combat(m)
    myLevel = getCombatLevel
    monsterLevel = m.getCombatLevel
        
    if(myLevel > monsterLevel)
      applyPrize(m);
      if(Napakalaki.instance.currentPlayer.level >= 10)
          combatResult = CombatResult::WINANDWINGAME
      else
          combatResult = CombatResult::WIN
      end
    else
      escape = Dice.instance().nextNumber()
        if(escape < 5)
          amIDead = m.kills
          if(amIDead)
              die
              combatResult = CombatResult::LOSEANDDIE
          elsif should_convert then
                    
            combatResult = CombatReesult::LOSEANDCONVERT
          else
            combatResult = CombatResult::LOSE
            bad = m.getBadConsequence
            applyBadConsequence(bad)
          end
        else
          combatResult = CombatResult::LOSEANDESCAPE
        end
    end
    discardNecklaceIfVisible
     return combatResult
  end

   def isTreasureKindInUse(type) 
 
      result = false
      @visibleTreasures.each { |tv|
        if type == tv.type then
 
          result = true
          break
          end
 
      }
 
      
      return result
         
    end

   def makeTreasureVisible(t)
     canl = canMakeTreasureVisible(t)
     if canl
       @visibleTreasures << t
       @hiddenTreasures.delete(t)
     end
    
   end
  
   def discardVisibleTreasure(t)
      @visibleTreasures.delete(t)
      @pendingBadConsequence.substractVisibleTreasure(t) 
      dielfNoTreasures
   end


   def discardHiddenTreasure(t)
     @hiddenTreasures.delete(t)
      @pendingBadConsequence.substractHiddenTreasure(t)
      dieIfNoTreasures 
   end


   def buyLevels(visible,hidden)
     levelsMayBought = computeGoldCoinsValue(visible)
     levelsMayBought = levelsMayBought + computeGoldCoinsValue(hidden)
     levels = levelsMayBought / 1000
     canl = canBuyLevels(levels)
     if canl
       incrementLevels(levels)
     end
    
     dealer = CardDealer.instance
     visible.each{|t|
       dealer.giveTreasureBack(t)
       @visibleTreasures.delete(t)
       
     }
     hidden.each{|t|
       dealer.giveTreasureBack(t)
       @hiddenTreasures.delete(t)
       
     }
     return canl;
   end

   
  def validState
    if(@pendingBadConsequence.isEmpty && @hiddenTreasures.size <= 4)
      return true
    else
      return false
    end
  end


  def initTreasures()
    dealer = CardDealer.instance
    dice = Dice.instance
    bringTolife
    treasure = dealer.nextTreasure
    @hiddenTreasures << treasure
    number = dice.nextNumber
    if number > 1
       treasure = dealer.nextTreasure
       @hiddenTreasures << treasure
    end
    if number == 6
      treasure = dealer.nextTreasure
      @hiddenTreasures << treasure
      
    end
  end

  def hasVisibleTreasures()
    if(@visibleTreasures.size > 0)
      return true
    else
      return false
    end
  end
  
   #EXAMEN
   def addHiddenTreasureExamen(t)
      @hiddenTreasures << t
   end
   #FIN EXAMEN
end
 


end

