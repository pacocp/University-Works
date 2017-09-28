# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative 'Card'

module Napakalaki
  
  class Cultist < Card
    
    
    attr_accessor :name, :gained_levels

    
    def initialize(gained_levels)
      @name = "Sectario"
      @gained_levels = gained_levels

    end
    
   
    def basic_value
        return @gained_levels;
    end

    def special_value
      return basic_value * CultistPlayer.total_cultist_players;
    end
    
   
    def to_s
      return " Nombre: #{@name} Tipo: #{@type}"
    end

  end
  
end
