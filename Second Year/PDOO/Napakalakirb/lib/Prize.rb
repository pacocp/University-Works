# encoding: UTF-8
#
#   Programación y diseño orientado a objetos
#   Grado en Ingeniería Informática
#
#  Ángela Castro Jimenez
#  Francisco Carrillo Pérez
require_relative 'Monster'
require_relative 'BadConsequence'
module Napakalaki
  class Prize
    attr_accessor :level, :treasures 
  
    def initialize(level,treasures)
      @level = level
      @treasures = treasures
    end

    def self.Prize(l,t)
      new(l,t)
    end
    def getLevel
      return @level
    end
    def getTreasures
      return @treasures
    end
    def to_s 
      "\nTesoros ganados: #{@treasures} \n Niveles ganados: #{@level}"
    end
 
  end
end

