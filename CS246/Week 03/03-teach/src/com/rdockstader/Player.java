package com.rdockstader;

import java.util.ArrayList;
import java.util.List;

public class Player {
    private String name;
    private int health;
    private int mana;
    private int gold;
    private List<String> equipment;

    public Player(String name, int health, int mana, int gold) {
        this.name = name;
        this.health = health;
        this.mana = mana;
        this.gold = gold;
        this.equipment = new ArrayList<String>();
    }

    public void addEquipment(String item) {
        this.equipment.add(item);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getHealth() {
        return health;
    }

    public void setHealth(int health) {
        this.health = health;
    }

    public int getMana() {
        return mana;
    }

    public void setMana(int mana) {
        this.mana = mana;
    }

    public int getGold() {
        return gold;
    }

    public void setGold(int gold) {
        this.gold = gold;
    }

    public String toString() {
        String output = "name: " + this.getName() + " Health: " + this.getHealth() + " Mana: " + this.getMana() + " Gold: " + this.getGold() + " Equipment: ";

        for(String item: equipment) {
            output += item + " ";
        }

        return output;
    }
}
