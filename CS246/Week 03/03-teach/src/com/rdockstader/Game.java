package com.rdockstader;

import com.google.gson.Gson;
import java.io.*;

public class Game {
    private Player player;

    public Game(Player player) {
        this.player = player;
    }

    public Player getPlayer() {
        return player;
    }

    public void saveGame(String fileName) {
        Gson gson = new Gson();
        try {
            File file = new File(fileName);
            BufferedWriter out = new BufferedWriter(new FileWriter(file));
            String output = gson.toJson(this);
            out.write(output);
            out.close();
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public static Game loadGame(String fileName) {
        try {
            File save = new File(fileName);
            BufferedReader in = new BufferedReader(new FileReader(save));
            Gson gson = new Gson();
            Game g = gson.fromJson(in.readLine(), Game.class);
            System.out.println(g.getPlayer().getName());
            return g;

        } catch (Exception e) {
            System.out.println(e);
        }

        return null;
    }
}
