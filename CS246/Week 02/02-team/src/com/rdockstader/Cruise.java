package com.rdockstader;

import sun.security.krb5.internal.crypto.Des;

public class Cruise implements Expense {
    private float cost;

    Cruise(Destination destination) {
        if(destination == Destination.Mexico) {
            this.cost = 1000.00f;
        } else if (destination == Destination.Europe) {
            this.cost = 2000.00f;
        } else if (destination == Destination.Japan) {
            this.cost = 3000.00f;
        } else {
            this.cost = -1;
        }
    }

    public float getCost() {
        return cost;
    }
}
