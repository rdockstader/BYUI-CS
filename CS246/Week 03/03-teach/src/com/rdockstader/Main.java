package com.rdockstader;


public class Main {

    public static void main(String[] args) {
        Player player = new Player("Gandolf", 100, 150, 100000);

        player.addEquipment("Sword");
        player.addEquipment("shield");

        Game game = new Game(player);

        game.saveGame("saved-game.txt");

        Game loadedGame = Game.loadGame("saved-game.txt");

        System.out.println("Same Players? " +  game.getPlayer().toString().equals(loadedGame.getPlayer().toString()));


    }
}
