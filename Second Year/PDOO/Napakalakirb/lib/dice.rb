# encoding: UTF-8
#
#   Programación y diseño orientado a objetos
#   Grado en Ingeniería Informática
#
#  Ángela Castro Jimenez
#  Francisco Carrillo Pérez
module Napakalaki
  require 'singleton'

class Dice
  include Singleton
  @@instance=nil
    
    def self.getInstance
      return @@instance
    end
   def nextNumber
      return 1 + rand(6)
    end
  
  
end
end
