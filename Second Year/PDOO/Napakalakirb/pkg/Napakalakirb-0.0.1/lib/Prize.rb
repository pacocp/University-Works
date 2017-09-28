# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Napakalaki
class Prize
  attr_accessor :level, :treasures 
  def initialize(level,treasures)
   @level = level
   @treasures = treasures
  end
  
  def self.premvacio()
    new(0,0)
  end
  
  
  def to_s 
    "Tesoros ganados: #{@treasure} \n Niveles ganados: #{@levels}"
  end
  
    
  end
  end

