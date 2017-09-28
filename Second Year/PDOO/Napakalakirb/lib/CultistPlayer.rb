# encoding: UTF-8
#
#   Programación y diseño orientado a objetos
#   Grado en Ingeniería Informática
#
#  Ángela Castro Jimenez
#  Francisco Carrillo Pérez



module Napakalaki
  require_relative 'Treasure'
  require_relative 'Monster'
  require_relative 'TreasureKind'
  require_relative 'combat_result'
  require_relative 'dice'
  require_relative 'Napakalaki'
  require_relative 'player'
  class CultistPlayer < Player
  
    attr_accessor :my_cultist_card
    
    @@total_cultist_players = 0
  
    #Constructor (lo hacemos así porque si no falla)
    def initialize(player, cultist)

      super(player.name)
      
      copy_constructor(player)

      @my_cultist_card = cultist
      @@total_cultist_players += 1 #Incrementamos el contador de cultistPlayers

    end
  

    #Métodos
    def combat_level
      
      #En ruby super es una llamada al metodo padre, asi que lo asignamos
      #a una variable y le sumamos el special_value
      lvl = super
      
      lvl += @my_cultist_card.special_value

      return lvl 

    end

    def should_convert

      #Siempre devuelve false
      return false

    end

    def oponent_level(monster) 

      return monster.special_value

    end

    def compute_gold_coins_value(treasures)
        
      #Devolvemos el valor
      return super.compute_gold_coins_value(treasures) * 2
      
    end
    
    def self.total_cultist_players
      return @@total_cultist_players
    end
  end
end