# encoding: UTF-8
#
#   Programación y diseño orientado a objetos
#   Grado en Ingeniería Informática
#
#  Ángela Castro Jimenez
#  Francisco Carrillo Pérez

module Napakalaki
  
require_relative'Card'
class Treasure < Card
  attr_accessor :name,:goldCoins,:minBonus,:maxBonus,:type
  def initialize(name,goldCoins,minBonus,maxBonus,type)
        @name = name
        @goldCoins = goldCoins
        @minBonus = minBonus
        @maxBonus = maxBonus
        @type = type
        
  end
  
  def self.Treasure(n,g,min,max,t)
    new(n,g,min,max,t)
  end
  
  def getName()
     @name
  end
  def getGoldCoins()
    @goldCoins
  end
  
 def getMinBonus()
   @minBonus
 end
 
 def getMaxBonus()
   @maxBonus
 end
 
 def getType()
     @type
 end
 def to_s
      "#{@name}. GoldCoins: #{@goldCoins}. Minbonus #{@minBonus}. MaxBonus #{@maxBonus}. Type #{@type}"
    end
end

 def basic_value
        return getMinBonus;
    end

    def special_value
      return getMaxBonus;
    end
end
