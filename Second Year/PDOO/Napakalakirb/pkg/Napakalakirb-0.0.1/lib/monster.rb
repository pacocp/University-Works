# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Napakalaki
  require_relative 'bad_consequence.rb'
  require_relative 'Prize.rb'

class Monster
    attr_accessor :name, :combatLevel, :premio, :malrollo
    
  def initialize (name, combatLevel, premio, malrollo)
    @name = name
    @combatLevel = combatLevel
    @premio = premio
    @malrollo = malrollo
  end
  
  
  
    def to_s 
      "Nombre: #{@name} \n Nivel: #{@combatLevels} \n Premio: #{@premio.to_s}
      \n Mal rollo #{@malrollo.to_s}"
  end

 
  def gain_levels
    @malrollo.levels > 0 
  end
end
end
