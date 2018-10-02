package com.rdockstader;

import java.util.ArrayList;
import java.util.List;

public class VacationCalculator {

    public static void main(String[] args) {
	    VacationCalculator vc = new VacationCalculator();

	    float japanCost = vc.calculateVacationCost(Destination.Japan, 1);

        System.out.println("Cost: " + japanCost);

    }

    public float calculateVacationCost(Destination dest, int numberOfDays) {
        ArrayList<Expense> expenses = new ArrayList<Expense>();
        expenses.add(new Cruise(dest));
        expenses.add(new Dining(dest, numberOfDays));
        expenses.add(new Lodging(dest, numberOfDays));

        return tallyExpenses(expenses);
    }

    float tallyExpenses(List<Expense> expenses) {
        float total = 0f;
        for (Expense e: expenses) {
            total += e.getCost();
        }

        return total;
    }
}
