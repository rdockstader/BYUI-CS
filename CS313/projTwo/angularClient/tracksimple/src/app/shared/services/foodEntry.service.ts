import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';

import { FoodEntry } from '../models/food-entry.model';

import { environment } from '../../../environments/environment';
import { Router } from '@angular/router';
import { Subject } from 'rxjs';
import { AuthService } from './auth.service';

@Injectable()
export class FoodEntryService {
  private mealOptions: string[] = ['Breakfast', 'Lunch', 'Dinner', 'Snack'];
  private foodEntries: FoodEntry[] = [];
  public foodEntriesChanged = new Subject<FoodEntry[]>();

  constructor (private http: HttpClient, private router: Router, private authService: AuthService) {}

  getMealOptions() {
    return this.mealOptions.slice();
  }

  addFoodEntry(entry: FoodEntry) {
    entry.dateAdded.setHours(0, 0, 0, 0);

    this.http.post<{message: string, id: string}>(environment.apiUrl + '/foodEntry', entry).subscribe(response => {
      entry.FoodEntryID = response.id;
      this.foodEntries.push(entry);
      this.foodEntriesChanged.next(this.foodEntries.slice());
    });
  }

  getFoodEntires(date?: Date) {
    if (!date) {
      date = new Date();
    }
    this.http.get<{message: string,
                  foodEntries: FoodEntry[]}>(environment.apiUrl +
                                                '/foodEntry?user=' +
                                                this.authService.getUserID() +
                                                '&dateAdded=' +
                                                date.toISOString())
    .subscribe(response => {
      this.foodEntries = response.foodEntries;
      this.foodEntriesChanged.next(this.foodEntries.slice());
    });
  }
}
