package com.rdockstader;


public class Main {

    public static void main(String[] args) {
        final String name = "Gondolf";
        int health = 100;
        int mana = 150;
        int gold = 100000;

        Player player = new Player(name, health, mana, gold);

        player.addEquipment("Sword");
        player.addEquipment("shield");

        Game game = new Game(player);

        game.saveGame("saved-game.txt");

        Game loadedGame = Game.loadGame("saved-game.txt");

        System.out.println("Same Players? " +  game.getPlayer().toString().equals(loadedGame.getPlayer().toString()));
    }
}
