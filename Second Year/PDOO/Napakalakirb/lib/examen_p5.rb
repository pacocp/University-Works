# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative'player'
class ExamenP5
  def initialize
    
  end
  def self.principal
     p1 = Player.new
     p2 = Player.new
     c = Cultist.new
     
     cultistp1= Cultist.new(p1,c)
     
    cultistp1.addHiddenTreasureExam(Treasure.new("Clavo de rail ferroviario", 400, 3, 6, TreasureKind::ONEHAND))
    p2.addHiddenTreasureExam(Treasure.new("Clavo de rail ferroviario", 400, 3, 6, TreasureKind::ONEHAND))
    
    cultistp1.addHiddenTreasureExam(Treasure.new("Capucha de Cthulhu", 500, 3, 5, TreasureKind::HELMET))
    p2.addHiddenTreasureExam(Treasure.new("Capucha de Cthulhu", 500, 3, 5, TreasureKind::HELMET))
     
    cultistp1.addHiddenTreasureExam(Treasure.new("Cuchillo de sushi arcano", 300, 2, 3, TreasureKind::ONEHAND))
    p2.addHiddenTreasureExam(Treasure.new("Cuchillo de sushi arcano", 300, 2, 3, TreasureKind::ONEHAND))
    
    cultistp1.addHiddenTreasureExam(Treasure.new("Tentaculo de pega", 200, 0, 1, TreasureKind::HELMET))
    p2.addHiddenTreasureExam(Treasure.new("Tentaculo de pega", 200, 0, 1, TreasureKind::HELMET))
    
    cultistp1.addHiddenTreasureExam(Treasure.new("Linterna a 2 manos", 400, 3, 6, TreasureKind::BOTHHAND))
    p2.addHiddenTreasureExam(Treasure.new("Linterna a 2 manos", 400, 3, 6, TreasureKind::BOTHHAND))
    
    hiddenTreasuresp1 = cultistp1.getHiddenTreasures
    hiddenTreasuresp2 = p2.getHiddenTreasures
    
    hiddenTreasuresp1.each { |t|
    
      if cultistp1.canMakeTreasureVisible(t)
        cultistp1.makeTreasureVisible
      end
     
    }
    
    hiddenTreasuresp2.each { |t|
    
      if p2.canMakeTreasureVisible(t)
        p2.makeTreasureVisible
      end
     
    }
    
    hiddenTreasuresp1 = cultistp1.getHiddenTreasures
    hiddenTreasuresp2 = p2.getHiddenTreasures
    visibleTreasuresp1 = cultistp1.getVisibleTreasures
    visibleTreasuresp2 = p2.getVisibleTreasures
    
    hiddenTreasuresp1.each { |t|
    
      puts t.to_s
     
    }
    
     hiddenTreasuresp2.each { |t|
    
      puts t.to_s
     
    }
    
     visibleTreasuresp1.each { |t|
    
      puts t.to_s
     
    }
    
     visibleTreasuresp2.each { |t|
    
      puts t.to_s
     
    }
    
    levelcombatp1 = cultistp1.combat_level
    levelcombatp2 = p1.getCombatLevel
    
    puts levelcombatp1
    puts levelcombatp2
    
    cultistp2= Cultist.new(p2,c)
    
    levelcombatp1 = cultistp1.combat_level
    levelcombatp2 = cultistp2.combat_level
    
    puts levelcombatp1
    puts levelcombatp2
    
    listatesorosv = Array.new
    listatesorosh = Array.new
    listatesorosv << TreasureKind::ONEHAND
    listatesorosv << TreasureKind::SHOE
    listatesorosv << TreasureKind::SHOE
    listatesorosv << TreasureKind::BOTHHAND
    listatesorosv << TreasureKInd::ARMOR
    listatesorosv << TreasureKind::ONEHAND
    listatesorosv << TreasureKind::BOTHHAND
    
    listatesorosh << TreasureKind::ONEHAND
    listatesorosh << TreasureKind::SHOE
    listatesorosh << TreasureKind::SHOE
    listatesorosh << TreasureKind::BOTHHAND
    listatesorosh << TreasureKInd::ARMOR
    listatesorosh << TreasureKind::ONEHAND
    listatesorosh << TreasureKind::BOTHHAND
    malrollo = BadConsequence.new("mi mal rollo",0,0,0,false,listatesorosh,listatesorosv)
    
    v = Array.new
    v << TreasureKind::ONEHAND
    v << TreasureKind::SHOE
    
    h = Array.new
    h << TreasureKind::SHOE
    h << TreasureKind::HELMET
    
    malrollo.adjustToFitTreasureLists(v, h)
    
    puts malrollo.to_s
    
    v = malrollo.getSpecificVisibleTreasures()
    h = malrollo.getSpecificHiddenTreasures()
    
    v.each{ |t|
      
      puts t
      
    }
    
    h.each{ |t|
      
      puts t
      
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
     
    
    
     
  end
end
