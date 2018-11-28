import { Component, OnInit, OnDestroy } from '@angular/core';
import { MatTableDataSource } from '@angular/material';
import { FoodEntry } from '../../shared/models/food-entry.model';
import { FoodEntryService } from 'src/app/shared/services/foodEntry.service';
import { Subscription } from 'rxjs';
<<<<<<< HEAD
=======
import { FormControl } from '@angular/forms';
>>>>>>> 9bf1cd415a16230a9469968ad413a286853fccc8

@Component({
  selector: 'app-entry-list',
  templateUrl: './entry-list.component.html',
  styleUrls: ['./entry-list.component.css']
})
export class EntryListComponent implements OnInit, OnDestroy {
  entryDate = new FormControl(new Date());
  displayedColumns = ['name', 'calories', 'protein', 'carbs', 'fats'];
  breakfastDataSource = new MatTableDataSource<FoodEntry>();
  lunchDataSource = new MatTableDataSource<FoodEntry>();
  dinnerDataSource = new MatTableDataSource<FoodEntry>();
  snackDataSource = new MatTableDataSource<FoodEntry>();

  foodEntrySub = new Subscription();

  constructor(private foodEntryService: FoodEntryService) { }

  ngOnInit() {
    this.foodEntryService.getFoodEntires();
    this.foodEntrySub = this.foodEntryService.foodEntriesChanged.subscribe(entries => {
      this.buildDataSource(entries.filter(ent => ent.meal === 'Breakfast'), this.breakfastDataSource);
      this.buildDataSource(entries.filter(ent => ent.meal === 'Lunch'), this.lunchDataSource);
      this.buildDataSource(entries.filter(ent => ent.meal === 'Dinner'), this.dinnerDataSource);
      this.buildDataSource(entries.filter(ent => ent.meal === 'Snack'), this.snackDataSource);
    });
    // TODO: figure out how to make it update date without the button
  }

  ngOnDestroy() {
    this.foodEntrySub.unsubscribe();
  }

  onUpdateDate() {
    this.foodEntryService.getFoodEntires(this.entryDate.value);
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

}
