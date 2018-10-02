package com.rdockstader;

public class Dining implements Expense {
    private float cost;

    Dining(Destination dest, int numberOfDays) {
        this.cost = 0;
        calculateCost(dest, numberOfDays);
    }

    private void calculateCost(Destination dest, int numberOfDays) {
        cost = getCostPerDay(dest) * numberOfDays;
    }

    private float getCostPerDay(Destination dest) {
        if(dest == Destination.Mexico) {
            return 10f;
        } else if (dest == Destination.Europe) {
            return 20f;
        } else if(dest == Destination.Japan) {
            return 30f;
        }
        return 0;
    }

    public float getCost() {
        return this.cost;
    }
}
