# encoding: UTF-8
#
#   Programación y diseño orientado a objetos
#   Grado en Ingeniería Informática
#
#  Ángela Castro Jimenez
#  Francisco Carrillo Pérez
module Napakalaki
require_relative 'Prize'
require_relative 'BadConsequence'
require_relative 'player'
  class Monster < Card
      attr_accessor :name, :combatLevel, :badConsequence,:prize,:levelChangeAgainstCultistPlayer

    def initialize (name, combatLevel, badConsequence,prize,levels)
      @name = name
      @combatLevel = combatLevel
      @prize = prize
      @badConsequence = badConsequence
      @levelChangeAgainstCultistPlayer = levels
      
    end
    
    
    def getLevelsGained()
      return @prize.getLevel
    end
    
    def getTreasuresGained()
      return @prize.getTreasures
    end
    
    def kills()
      return @badConsequence.myBadConsequenceIsDeath
    end
    def getCombatLevel
     @combatLevel
   end
   def getBadConsequence
      return @badConsequence
   end
    def to_s 
        "Nombre: #{@name} \n Nivel: #{@combatLevel} \n Premio: #{@prize.to_s}
        \n Mal rollo: #{@badConsequence.to_s}"
    end

    def basic_value
        return getCombatlevel;
    end

    def special_value
      return @combatLevel + @levelChangeAgainstCultistPlayer;
    end

    
  end
end
