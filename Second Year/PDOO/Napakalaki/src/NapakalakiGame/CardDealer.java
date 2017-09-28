/*  
 *  Programación y diseño orientado a objetos
 *  Grado en Ingeniería Informática
 * 
 *  
 *
 *  Angela Castro Jiménez
 *  Francisco Carrillo Pérez
 */
package NapakalakiGame;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class CardDealer {
    
    private ArrayList<Monster> unusedMonsters = new ArrayList();
    private ArrayList<Monster> usedMonsters = new ArrayList();
    
    private ArrayList<Treasure> unusedTreasures = new ArrayList();
    private ArrayList<Treasure> usedTreasures = new ArrayList();
    
    private ArrayList<Cultist> unusedCultists = new ArrayList();
     private ArrayList<Cultist> usedCultists = new ArrayList();
    
    private static final CardDealer instance = new CardDealer();
    
    private  CardDealer(){}
    
    public static CardDealer getInstance(){
        return instance;
    }
    
    private void initTreasureCardDeck(){
        
        unusedTreasures.add(new Treasure("¡Si mi amo!", 0, 4, 7, TreasureKind.HELMET));
        unusedTreasures.add(new Treasure("Botas de investigacion", 600, 3, 4, TreasureKind.SHOE));
        unusedTreasures.add(new Treasure("Capucha de Cthulhu", 500, 3, 5, TreasureKind.HELMET));
        unusedTreasures.add(new Treasure("A prueba de babas", 400, 2, 5, TreasureKind.ARMOR));
        unusedTreasures.add(new Treasure("Botas de lluvia acida", 800, 1, 1, TreasureKind.BOTHHAND));
        unusedTreasures.add(new Treasure("Casco Minero", 400, 2, 4, TreasureKind.HELMET));
        unusedTreasures.add(new Treasure("Ametralladora Thompson", 600, 4, 8, TreasureKind.BOTHHAND));
        unusedTreasures.add(new Treasure("Camiseta de la UGR", 100, 1, 7, TreasureKind.ARMOR));
        unusedTreasures.add(new Treasure("Clavo de rail ferroviario", 400, 3, 6, TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Cuchillo de sushi arcano", 300, 2, 3, TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Fez alopodo", 700, 3, 5, TreasureKind.HELMET));
        unusedTreasures.add(new Treasure("Hacha prehistorica", 500, 2, 5, TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("El aparato de Pr.Tesla", 900, 4, 8, TreasureKind.ARMOR));
        unusedTreasures.add(new Treasure("Gaita", 500, 4, 5, TreasureKind.BOTHHAND));
        unusedTreasures.add(new Treasure("Insecticida", 300, 2, 3, TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Escopeta de 3 cañones", 700, 4, 6, TreasureKind.BOTHHAND));
        unusedTreasures.add(new Treasure("Garabato Mistico", 300, 2, 2, TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("La fuerza de Mr.T", 1000, 0, 0, TreasureKind.NECKLACE));
        unusedTreasures.add(new Treasure("La rebeca metalica", 400, 2, 3, TreasureKind.ARMOR));
        unusedTreasures.add(new Treasure("Mazo de los antiguos", 200, 3, 4, TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Necro-playboycon", 300, 3, 5, TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Lanzallamas", 800, 4, 8, TreasureKind.BOTHHAND));
        unusedTreasures.add(new Treasure("Necro-comicon", 100, 1, 1, TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Necronomicon", 800, 5, 7, TreasureKind.BOTHHAND));
        unusedTreasures.add(new Treasure("Linterna a 2 manos", 400, 3, 6, TreasureKind.BOTHHAND));
        unusedTreasures.add(new Treasure("Necro-gnomicon", 200, 2, 4, TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Necrotelecom", 300, 2, 3, TreasureKind.HELMET));
        unusedTreasures.add(new Treasure("Porra preternatural", 200, 2, 3, TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Tentaculo de pega", 200, 0, 1, TreasureKind.HELMET));
        unusedTreasures.add(new Treasure("Zapato deja-amigos", 500, 0, 1, TreasureKind.SHOE));
        unusedTreasures.add(new Treasure("Shogulador", 600, 1, 1, TreasureKind.BOTHHAND));
        unusedTreasures.add(new Treasure("Varita de atizamiento", 400, 3, 4, TreasureKind.ONEHAND));
        this.shuffleTreasures();
    }
    
    private void initMonsterCardDeck(){
        
        //El rey rosa
        BadConsequence malrollo = new BadConsequence("Pierdes 5 niveles "
        + "y 3 tesoros visibles", 5, 3, 0);
        Prize prize = new Prize(4,2);
        unusedMonsters.add(new Monster("El rey de rosa", 13, malrollo, prize));
      
        
        //Byajhees de bonanza
        BadConsequence malrollo1 = new BadConsequence("Pierdes tu armadura visible y "
        + "otra oculta", 0, new ArrayList(Arrays.asList(TreasureKind.ARMOR)), 
        new ArrayList(Arrays.asList(TreasureKind.ARMOR)));
        Prize prize1 = new Prize(2,1);
        unusedMonsters.add(new Monster("Byajhees de bonanza", 8, malrollo1, prize1));
        
        
        //Chibithulhu
        BadConsequence malrollo2 = new BadConsequence("Embobado con el lindo primigenenio"
        + "te descargas de tu casco visible", 0, new ArrayList(Arrays.asList(TreasureKind.HELMET)),
        new ArrayList());
        Prize prize2 = new Prize(1,1);
        unusedMonsters.add(new Monster("Chibithulhu", 2, malrollo2, prize2));

        
        //El Sopor de Dunwich
        BadConsequence malrollo3 = new BadConsequence("El primordial bostezo contagioso, "
        + "pierdes el calzado visible", 5, new ArrayList(Arrays.asList(TreasureKind.SHOE)),
        new ArrayList());
        Prize prize3 = new Prize(1,1);
        unusedMonsters.add(new Monster("El Sopor de Dunwich", 2, malrollo3, prize3));
        
        
        //Angeles de la noche ibicenca
        BadConsequence malrollo4 = new BadConsequence("Te atrapan para llevarte de fiesta"
        + "y te dejan caer en mitad del vuelo, descarta una mano visible y una oculta",
        0, new ArrayList(Arrays.asList(TreasureKind.ONEHAND)),
        new ArrayList(Arrays.asList(TreasureKind.ONEHAND)));
        Prize prize4 = new Prize(4,1);
        unusedMonsters.add(new Monster("Angeles de la noche ibicenca", 14, malrollo4, prize4));
      
        
        //La que redacta en las tinieblas
        BadConsequence malrollo5 = new BadConsequence("Toses los pulmones y pierdes 2 niveles",
        2,0,0);
        Prize prize5 = new Prize(1,1);
       unusedMonsters.add(new Monster("La que redacta en las tinieblas", 2, malrollo5, prize5));

        
        //El gorrón en el umbral
        BadConsequence malrollo6 = new BadConsequence("Pierdes todos tus tesoros visibles",
        0, 6, 0);
        Prize prize6 = new Prize(3,1);
        unusedMonsters.add(new Monster("El gorrón en el umbral", 10, malrollo6, prize6));
      
        
        //H.P Munchcraft
        BadConsequence malrollo7 = new BadConsequence("Pierdes la armadura visible",
        0, new ArrayList(Arrays.asList(TreasureKind.ARMOR)), new ArrayList());
        Prize prize7 = new Prize(2,1);
        unusedMonsters.add(new Monster("H.P Munchcraft", 6, malrollo7, prize7));
        
        
        //Bichgooth
        BadConsequence malrollo8 = new BadConsequence("Sientes bichos debajo de la ropa"
        + ". Descarta la armadura visible", 0,
        new ArrayList(Arrays.asList(TreasureKind.ARMOR)), new ArrayList());
        Prize prize8 = new Prize(1,1);
        unusedMonsters.add(new Monster("Bichgooth", 2, malrollo8, prize8));
      
        
        //Los Hondos
        Boolean muerto = true;
        BadConsequence malrollo9 = new BadConsequence("Estos monstruos resultan bastante "
        + "superficiales y te aburren mortalmente. Estas muerto", muerto );
        Prize prize9 = new Prize(2,1);
        unusedMonsters.add(new Monster("Los Hondos", 8, malrollo9, prize9));
       
        
        //Semillas Cthulhu
        BadConsequence malrollo10 = new BadConsequence("Pierdes dos niveles y dos tesoros"
        + "ocultos", 2, 0, 2);
        Prize prize10 = new Prize(2,1);
        unusedMonsters.add(new Monster("Semillas Cthulhu", 4, malrollo10, prize10));
        
        
        //Dameargo
        BadConsequence malrollo11 = new BadConsequence("Te intentas escaquear."
        + " Pierdes una mano visible",0,
        new ArrayList(Arrays.asList(TreasureKind.ONEHAND)), new ArrayList());
        Prize prize11 = new Prize(2,1);
        unusedMonsters.add(new Monster("Dameargo", 1, malrollo11, prize11));
        
        
        //Pollipólipo volante
        BadConsequence malrollo12 = new BadConsequence("Da mucho asquito."
        + "Pierdes tres niveles", 3, 0, 0);
        Prize prize12 = new Prize(1,1);
        unusedMonsters.add(new Monster("Pollipólipo volante", 3, malrollo12, prize12));
        
    
        //YskhtihyssgGoth
        BadConsequence malrollo13 = new BadConsequence("No le hace gracia que pronuncies mal"
        + "su nombre.Estas muerto", muerto);
        Prize prize13 = new Prize(3,1);
        unusedMonsters.add(new Monster("YskhtihyssgGoth", 12, malrollo13, prize13));
      
        
        //Familia feliz
        BadConsequence malrollo14 = new BadConsequence("La familia te atrapa. estás muerto",
        muerto);
        Prize prize14 = new Prize(4,1);
        unusedMonsters.add(new Monster("Familia feliz", 1, malrollo14, prize14));
       
        
        //Roboggoth
        BadConsequence malrollo15 = new BadConsequence("La quinta directiva primaria te obliga"
        + "a perder 2 niveles y un tesoro 2 manos visibles", 2,
        new ArrayList(Arrays.asList(TreasureKind.BOTHHAND)), new ArrayList());
        Prize prize15 = new Prize(2,1);
        unusedMonsters.add(new Monster("Roboggoth", 8, malrollo15, prize15));
       
        
        //El espía
        BadConsequence malrollo16 = new BadConsequence("Te asusta la noche.Pierdes un casco"
        + "visible", 0, new ArrayList(Arrays.asList(TreasureKind.HELMET)), new ArrayList());
        Prize prize16 = new Prize(1,1);
        unusedMonsters.add(new Monster("El espía", 5, malrollo16, prize16));
        
        
        //El Lenguas
        BadConsequence malrollo17 = new BadConsequence("menudo susto te llevas.Pierdes 2 niveles"
        + "y 5 tesoros visibles", 2, 5, 0);
        Prize prize17 = new Prize(1,1);
        unusedMonsters.add(new Monster("El Lenguas", 20, malrollo17, prize17));
        
        
        //Bicéfalo
        BadConsequence malrollo18 = new BadConsequence("Te faltan manos para tanta cabeza"
        + "Pieres tres niveles y tus tesoros visibles de las manos", 3,
        new ArrayList(Arrays.asList(TreasureKind.ONEHAND,TreasureKind.BOTHHAND)), new ArrayList());
        Prize prize18 = new Prize(1,1);
        unusedMonsters.add(new Monster("Bicéfalo", 20, malrollo18, prize18));
        
        //El impronunciable
        BadConsequence malrollo19 = new BadConsequence("Pierdes una mano visible, -2 contra sectarios", 0,
        new ArrayList(Arrays.asList(TreasureKind.ONEHAND)), new ArrayList());
        Prize prize19 = new Prize(3,1);
        unusedMonsters.add(new Monster("El mal indecible impronunciable", 10, malrollo19, prize19,-2));
        
        BadConsequence malrollo20 = new BadConsequence("Pierdes tus tesoros visibles. Jajaja. +2 contra sectarios", 0,
        new ArrayList(Arrays.asList(TreasureKind.ONEHAND)), new ArrayList());
        Prize prize20 = new Prize(2,1);
        unusedMonsters.add(new Monster("Testigos Oculares", 6, malrollo20, prize20,2));
        
        BadConsequence malrollo21 = new BadConsequence("Hoy no es tu día de suerte,mueres. +4 contra sectarios", true);
        Prize prize21 = new Prize(2,5);
        unusedMonsters.add(new Monster("El gran cthulhu", 20, malrollo21, prize21,4));
        
        BadConsequence malrollo22 = new BadConsequence("Tu gobierno te recorta dos niveles. -2 contra sectarios",2,0,0);
        Prize prize22 = new Prize(2,1);
        unusedMonsters.add(new Monster("Serpiente Político", 8, malrollo22, prize22,-2));
        
         
        BadConsequence malrollo23 = new BadConsequence("Pierdes tu casco y tu armadura visible. +5 contra sectarios"
                ,0,new ArrayList(Arrays.asList(TreasureKind.ARMOR,TreasureKind.HELMET)),
        new ArrayList(Arrays.asList(TreasureKind.ONEHAND,TreasureKind.BOTHHAND)));
        Prize prize23 = new Prize(1,1);
        unusedMonsters.add(new Monster("Felpuggoth", 2, malrollo23, prize23,5));
        
        BadConsequence malrollo24 = new BadConsequence("Pierdes 2 niveles. -4 contra sectarios",2,0,0);
        Prize prize24 = new Prize(4,2);
        unusedMonsters.add(new Monster("Shoggoth", 16, malrollo24, prize24,-4));
        
        BadConsequence malrollo25 = new BadConsequence("Pintalabios negro. Pierdes 2 niveles. +3 contra sectarios",2,0,0);
        Prize prize25 = new Prize(1,1);
        unusedMonsters.add(new Monster("Lolitagooth", 2, malrollo25, prize25, 3));
        
        this.shuffleMonsters();
    }
    
    
     private void initCultistCardDeck(){
        
        unusedCultists.add(new Cultist("Sectario", 1,"01"));
        unusedCultists.add(new Cultist("Sectario", 1,"02"));
        unusedCultists.add(new Cultist("Sectario", 1,"03"));
        unusedCultists.add(new Cultist("Sectario", 1,"04"));
        unusedCultists.add(new Cultist("Sectario", 2,"05"));
        unusedCultists.add(new Cultist("Sectario", 2,"06"));
 
        this.shuffleCultists();
    }
    private void shuffleTreasures(){
       Collections.shuffle(this.unusedTreasures);
    }
    
    private void shuffleMonsters(){
       Collections.shuffle(this.unusedMonsters);
    }
    
    private void shuffleCultists()
    {
        Collections.shuffle(this.unusedCultists);
    }
    
    
    
    public Treasure nextTreasure(){
    //Comprobamos si tenemos cartas en el mazo
        if (this.unusedTreasures.isEmpty()) {
 
            //Recorremos las cartas descartadas
            for (Treasure t: this.usedTreasures) {
                //Las agregamos al mazo sin usar
                this.unusedTreasures.add(t);
            }
 
            //Las barajamos
            this.shuffleTreasures();
 
            //Limpiamos el mazo de descartes
            this.usedTreasures.clear();
 
        }
 
        //Obtengo la primera carta del mazo
        Treasure t = this.unusedTreasures.get(0);
 
        //La agregamos al mazo de descartes
        this.usedTreasures.add(t);
 
        //La eliminamos del mazo
        this.unusedTreasures.remove(t);
 
        //Devolvemos la carta
        return t;
    }
    
  
   public Monster nextMonster(){
       //Comprobamos si tenemos cartas en el mazo
        if (this.unusedMonsters.isEmpty()) {
 
            //Recorremos las cartas descartadas
            for (Monster m: this.usedMonsters) {
                //Las agregamos al mazo sin usar
                this.unusedMonsters.add(m);
            }
 
            //Las barajamos
            this.shuffleMonsters();
 
            //Limpiamos el mazo de descartes
            this.usedMonsters.clear();
 
        }
 
        //Obtengo la primera carta del mazo
        Monster m = this.unusedMonsters.get(0);
 
        //La eliminamos del mazo
        this.unusedMonsters.remove(m);
 
        //Devolvemos la carta
        return m;
   }
    
   public Cultist nextCultist()
   {
       //Comprobamos si tenemos cartas en el mazo
        if (this.unusedCultists.isEmpty()) {
 
            //Recorremos las cartas descartadas
            for (Cultist m: this.usedCultists) {
                //Las agregamos al mazo sin usar
                this.unusedCultists.add(m);
            }
 
            //Las barajamos
            this.shuffleCultists();
 
            //Limpiamos el mazo de descartes
            this.usedCultists.clear();
 
        }
 
        //Obtengo la primera carta del mazo
        Cultist m = this.unusedCultists.get(0);
 
        //La eliminamos del mazo
        this.unusedCultists.remove(m);
 
        //Devolvemos la carta
        return m;
   }
   
    public void giveTreasuresBack(Treasure t){
       usedTreasures.add(t);
    }
    
    public void giveMonsterBack(Monster m){
       usedMonsters.add(m);
    }
    //EXAMEN
    public Treasure changeTreasure(Treasure t)
    {
        Treasure nuevo = nextTreasure();
        giveTreasuresBack(t);
        return nuevo;
    }
    //FIN EXAMEN
    
    public void initCards(){
     this.initTreasureCardDeck();
     this.initMonsterCardDeck();
     this.initCultistCardDeck();
    }
    
    
    
}
