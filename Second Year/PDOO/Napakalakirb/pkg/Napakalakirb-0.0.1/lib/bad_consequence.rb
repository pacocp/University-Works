# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Napakalaki
class BadConsequence
  attr_accessor :text, :levels, :nVisible, :nHidden, :death
  @specificHiddenTreasures = Array.new
  @specificVisibleTreasures = Array.new
  private_class_method :new
  
  def initialize(text,levels,nVisible,nHidden,death,specificHiddenTreasures,specificVisibleTreasures)
    @text = text
    @levels = levels
    @nVisible = nVisible
    @nHidden = nHidden
    @death = death
    @specificHiddenTreasures = specificHiddenTreasures
    @specificVisibleTreasures = specificVisibleTreasures
  end
  
  def self.NuevaBadC()
    new(0,0,0,0,0,[],[]) 
  end
  
  def self.NewDeath (text)  
      new(text, 0, 0, 0,true, [], [])
  end
  
  def self.newLevelSpecificTreasures(text,levels,nVisible,nHidden)
    new(text,levels,0,0,0,nVisible,nHidden)
  end
  def self.newLevelNumberOfTreasures(text,levels,nVisible,nHidden)
    new(text,levels,nVisible,nHidden,0,[],[])
  end
  
    
  def to_s 
    "Mal rollo: #{@text} \n Niveles: #{@levels} \n Num. Tesoros Visibles: #{@nVisible}
      \n Num. Tesoros Ocultos: #{@nHidden} \n Muerte: #{@death}"
  end
  
end
end