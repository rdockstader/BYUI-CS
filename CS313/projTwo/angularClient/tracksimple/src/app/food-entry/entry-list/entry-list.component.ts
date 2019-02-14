import { Component, OnInit, OnDestroy, ViewChild, ElementRef } from '@angular/core';
import { MatTableDataSource } from '@angular/material';
import { FoodEntry } from '../../shared/models/food-entry.model';
import { FoodEntryService } from 'src/app/shared/services/foodEntry.service';
import { Subscription } from 'rxjs';
import { UserGoalService } from 'src/app/shared/services/userGoal.service';
import { UserGoal } from 'src/app/shared/models/user-goal.model';

@Component({
  selector: 'app-entry-list',
  templateUrl: './entry-list.component.html',
  styleUrls: ['./entry-list.component.css']
})
export class EntryListComponent implements OnInit, OnDestroy {
  @ViewChild('date') dateInput: ElementRef;
  entryDate = new Date();
  displayedColumns = ['name', 'calories', 'protein', 'carbs', 'fats'];
  breakfastDataSource = new MatTableDataSource<FoodEntry>();
  lunchDataSource = new MatTableDataSource<FoodEntry>();
  dinnerDataSource = new MatTableDataSource<FoodEntry>();
  snackDataSource = new MatTableDataSource<FoodEntry>();

  totalCalories: number;
  totalProtein: number;
  totalCarbs: number;
  totalFats: number;
  goal: UserGoal;

  calValue = 0;
  protValue = 0;
  carbValue = 0;
  fatValue = 0;

  foodEntrySub = new Subscription();
  userGoalSub = new Subscription();

  constructor(private foodEntryService: FoodEntryService, private userGoalService: UserGoalService) { }

  ngOnInit() {
    this.foodEntryService.getFoodEntires();
    this.foodEntrySub = this.foodEntryService.foodEntriesChanged.subscribe(entries => {
      this.buildDataSource(entries.filter(ent => ent.meal === 'Breakfast'), this.breakfastDataSource);
      this.buildDataSource(entries.filter(ent => ent.meal === 'Lunch'), this.lunchDataSource);
      this.buildDataSource(entries.filter(ent => ent.meal === 'Dinner'), this.dinnerDataSource);
      this.buildDataSource(entries.filter(ent => ent.meal === 'Snack'), this.snackDataSource);
      this.getDailyTotals(entries);
      this.setValues();
    });

    this.userGoalService.retrieveCurrentGoal();
    this.goal = this.userGoalService.getCurrentUserGoal();
    this.setValues();
    this.userGoalSub = this.userGoalService.currentUserGoalChanged.subscribe(result => {
      this.goal = this.userGoalService.getCurrentUserGoal();
      this.setValues();
    });
  }

  ngOnDestroy() {
    this.foodEntrySub.unsubscribe();
  }
  onNextDate() {
    console.log();
    this.entryDate.setDate(this.entryDate.getDate() + 1);
    this.onDateChanged();
  }

  onPreviousDate() {
    this.entryDate.setDate(this.entryDate.getDate() - 1);
    this.onDateChanged();
  }

  onDateChanged() {
    this.dateInput.nativeElement.value = (this.entryDate.getMonth() + 1) +
                                          '/' + this.entryDate.getDate() +
                                          '/' + this.entryDate.getFullYear();
    this.foodEntryService.getFoodEntires(this.entryDate);
  }

  private setValues() {
    this.calValue = this.totalCalories / this.goal.dailyCalories * 100 ;
    this.protValue = this.totalProtein / this.goal.dailyProtein * 100;
    this.carbValue = this.totalCarbs / this.goal.dailyCarbs * 100;
    this.fatValue = this.totalFats / this.goal.dailyFats * 100;
  }

  private buildDataSource(entries: FoodEntry[], dataSource: MatTableDataSource<FoodEntry>) {
    entries.push(this.buildTotalEntry(entries));
    dataSource.data = entries;
  }

  private buildTotalEntry(entries: FoodEntry[]) {
    let totalCals = 0;
    let totalProt = 0;
    let totalCarb = 0;
    let totalFat = 0;
    entries.forEach(entry => {
      totalCals += entry.calories;
      totalProt += entry.protein;
      totalCarb += entry.carbs;
      totalFat += entry.fats;
    });

    return {FoodEntryID: null,
                        meal: null,
                        user: null,
                        name: 'Total',
                        calories: totalCals,
                        protein: totalProt,
                        carbs: totalCarb,
                        fats: totalFat,
                        dateAdded: null};
  }

  private getDailyTotals(entries: FoodEntry[]) {
    let totalCals = 0;
    let totalProt = 0;
    let totalCarb = 0;
    let totalFat = 0;
    entries.forEach(entry => {
      totalCals += entry.calories;
      totalProt += entry.protein;
      totalCarb += entry.carbs;
      totalFat += entry.fats;
    });

    this.totalCalories = totalCals;
    this.totalProtein = totalProt;
    this.totalCarbs = totalCarb;
    this.totalFats = totalFat;
  }

}
