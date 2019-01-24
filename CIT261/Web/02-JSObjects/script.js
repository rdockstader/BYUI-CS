/*****************************/
/****iNITIALIZE CLASS VARS****/
/*****************************/

// Creature (base class)
function Creature(name, health, type) { 
    this.name = name;
    this.currentHealth = health;
    this.isAlive = true;
    this.level = 1;
    this.maxHealth = health;
    this.type = type;
}
// Weapon (base class)
function Weapon(name, damage, range) {
    this.name = name;
    this.damage = damage;
    this.range = range;
}

// Hero (calls creature)
function Hero(name, health, type) {
    Creature.call(this, name, health, type);
    this.experience = 0;
    
}

// Villian (calls creature)
function Villian(name, health, type) {
    Creature.call(this, name, health, type);
}

// Warrior (calls hero)
function Warrior(name) {
    Hero.call(this, name, 20, "Warrior");   
    this.weapon = new Weapon("Basic Sword", 1, 1);
} 

// Mage (calls hero)
function Mage(name) {
    Hero.call(this, name, 10, "Mage");
    this.weapon = new Weapon("Basic Staff", 2, 5);
}

// Healer (calls hero)
function Healer(name) {
    Hero.call(this, name, 5, "Healer"); 
    this.weapon = new Weapon("Healer's Staff", 2, 5);
}

// WIldBoar (calls villian)
function WildBoar() {
    Villian.call(this, "Wild Boar", 5, "Wild Boar");
}

/***********************/
/****LINK PROTOTYPES****/
/***********************/
// Hero inherits from Creature
Hero.prototype = Object.create(Creature.prototype);
// Villian inherits from Creature
Villian.prototype = Object.create(Creature.prototype);
// Warrior inherits from Hero
Warrior.prototype = Object.create(Hero.prototype);
// Mage inherits from Hero
Mage.prototype = Object.create(Hero.prototype);
// Healer inherits from Hero
Healer.prototype = Object.create(Hero.prototype);
// Wild Boar inherits from Villian
WildBoar.prototype = Object.create(Villian.prototype);

/***********************/
/****CLASS FUNCTIONS****/
/***********************/

// Creature
Creature.prototype.takeDamage = function (damage) {
    this.currentHealth -= damage;
    if(this.currentHealth <= 0) {
        this.currentHealth = 0
        this.isAlive = false;
    }
}

Creature.prototype.getHealed = function (healingDone) {
    this.currentHealth += healingDone;
    if(this.currentHealth > this.maxHealth) {
        this.currentHealth = this.maxHealth;
    }
}

Creature.prototype.res = function () {
    this.currentHealth = this.maxHealth/2;
    this.isAlive = true;
    
}

// Hero
Hero.prototype.greet = function () {
    return this.name + ' says hello.';
}

// Warrior
Warrior.prototype.attack = function(creature) {
    creature.takeDamage(this.weapon.damage);
}

// Mage
Mage.prototype.cast = function(creature) {
    creature.takeDamage(this.weapon.damage);
}

// Healer
Healer.prototype.heal = function(creature) {
    creature.getHealed(this.weapon.damage);
}

// Wild Board
WildBoar.prototype.charge = function(creature) {
    creature.takeDamage(1);
}

/***********************/
/*******GAME VARS*******/
/***********************/

var heros = [];
var villians = [];
var gameStarted = false;

/***********************/
/****-GAME FUNCTIONS****/
/***********************/

onAddHero = function() {
    var name = document.getElementById("hero-name").value;
    var type = document.getElementById("hero-type").value;
    var errorMessageEle = document.getElementById("hero-add-error-message");
    if(validateHeroName(name) == null) {
        if(type === "w") {
            heros.push(new Warrior(name));
        } else if (type === "m") {
            heros.push(new Mage(name));
        } else {
            heros.push(new Healer(name));
        }
        refreshHeroTable();
        errorMessageEle.innerHTML = "";
        errorMessageEle.classList.add("hidden");
    } else {
        errorMessageEle.classList.remove("hidden");
        errorMessageEle.innerHTML = "Hero Already Exists!";
    }
}

validateHeroName = function(name) {
    return heros.find((ele) => {
        return ele.name == name;
        
    })
}
                  
refreshHeroTable = function() {
    var tableHtml = '<thead><tr>';
    tableHtml += '<th>Name</th>';
    tableHtml += '<th>Type</th>';
    tableHtml += '<th>Health</th>';
    tableHtml += '<th>Max Health</th>';
    tableHtml += '<th>Exp</th>';
    tableHtml += '<th>Level</th>';
    tableHtml += '</tr></thead><tbody>';
    var rowNum = 0;
    heros.forEach((ele) => {
        tableHtml += '<tr>';
        tableHtml += '<td>' + ele.name + '</td>';
        tableHtml += '<td>' + ele.type + '</td>';
        tableHtml += '<td>' + ele.currentHealth + '</td>';
        tableHtml += '<td>' + ele.maxHealth + '</td>';
        tableHtml += '<td>' + ele.experience + '</td>';
        tableHtml += '<td>' + ele.level + '</td>';
        tableHtml += '</tr>';
        rowNum++;
    })
    tableHtml += '</tbody>'
    
    document.getElementById("hero-table").innerHTML = tableHtml;
}

refreshVillianTable = function() {
    var tableHtml = '<thead><tr>';
    tableHtml += '<th>Name</th>';
    tableHtml += '<th>Type</th>';
    tableHtml += '<th>Health</th>';
    tableHtml += '<th>Max Health</th>';
    tableHtml += '<th>Level</th>';
    tableHtml += '</tr></thead><tbody>';
    var rowNum = 0;
    villians.forEach((ele) => {
        tableHtml += '<tr>';
        tableHtml += '<td>' + ele.name + '</td>';
        tableHtml += '<td>' + ele.type + '</td>';
        tableHtml += '<td>' + ele.currentHealth + '</td>';
        tableHtml += '<td>' + ele.maxHealth + '</td>';
        tableHtml += '<td>' + ele.level + '</td>';
        tableHtml += '</tr>';
        rowNum++;
    })
    tableHtml += '</tbody>'
    
    document.getElementById("villian-table").innerHTML = tableHtml;
}

startGame = function() {
    for(var i = 0 ; i < 10; i++) {
        villians.push(new WildBoar());
    }
    refreshVillianTable();
    gameStarted = true;
    document.getElementById("start-game-btn").classList.add("hidden");
    document.getElementById("add-hero-btn").classList.add("hidden");
    document.getElementById("play-round-btn").classList.remove("hidden");
}


playRound = function() {
    var heroIndex = 0;
    var villianIndex = 0;
    var heroToAttack = heros[heroIndex];
    var villianToAttack = villians[villianIndex];

    heros.forEach(function(element) {
        if(element.isAlive) {
            while(villianToAttack.currentHealth <= 0 && villianIndex < villians.length-1) {
                villianIndex = villianIndex + 1;
                villianToAttack = villians[villianIndex];
            }
            if(villianToAttack.currentHealth > 0) {
                if(element.type === "Warrior") {
                    element.attack(villianToAttack);
                } else if (element.type === "Mage") {
                    element.cast(villianToAttack);
                }
                
            }
        }
    });

    villians.forEach(function(element) {
        if(element.isAlive) {
            while(heroToAttack.currentHealth <= 0 && heroIndex < heros.length-1) {
                heroIndex = heroIndex + 1;
                heroToAttack = heros[heroIndex];
            }
            if(heroToAttack.currentHealth > 0) {
                if(element.type === "Wild Boar") {
                    element.charge(heroToAttack);
                } 
            }
        }
    });
    
    if(heroIndex == heros.length-1 && !heroToAttack.isAlive) {
        alert("you lose!!!");
        document.getElementById("play-round-btn").classList.add("hidden");
    }

    if(villianIndex == villians.length-1 && !villianToAttack.isAlive) {
        alert("Winna Winna Chicken Dinna!!");
            document.getElementById("play-round-btn").classList.add("hidden");
    }


    refreshHeroTable();
    refreshVillianTable();
}





























