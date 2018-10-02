package com.rdockstader;

public class Lodging implements Expense {
    private float cost;

    Lodging(Destination dest, int numberOfNights) {
        float costPerDay = getCostPerDay(dest);
        calculateCost(dest, numberOfNights);

    }

    private void calculateCost(Destination dest, int numberOfDays) {
        this.cost = getCostPerDay(dest) * numberOfDays;
        this.cost += getHotelTaxSurcharge(dest, this.cost);
    }

    private float getCostPerDay(Destination dest) {
        if(dest == Destination.Mexico) {
            return 100f;
        } else if (dest == Destination.Europe) {
            return 200f;
        } else if(dest == Destination.Japan) {
            return 300f;
        }
        return 0;
    }

    private float getHotelTaxSurcharge(Destination dest, float amount) {
        if(dest == Destination.Europe) {
            return .1f * amount;
        } else if (dest == Destination.Japan) {
            return .3f * amount;
        }
        return 0;
    }

    public float getCost() {
        return this.cost;
    }
}
