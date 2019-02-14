import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Subject } from 'rxjs';

import { UserGoal } from '../models/user-goal.model';
import { environment } from '../../../environments/environment';


@Injectable()
export class UserGoalService {
  // constants
  private FAT_CALS_PER_GRAM = 9;
  private PROTEIN_CALS_PER_GRAM = 4;
  private CARB_CALS_PER_GRAM = 4;
  // Vars
  private currentUserGoal: UserGoal;
  currentUserGoalChanged = new Subject<void>();

  constructor(private http: HttpClient) {}

  getCurrentUserGoal() {
    return { ...this.currentUserGoal };
  }

  getFatCalsPerGram() {
    return this.FAT_CALS_PER_GRAM;
  }
  getProteinCalsPerGram() {
    return this.PROTEIN_CALS_PER_GRAM;
  }
  getCarbCalsPerGram() {
    return this.CARB_CALS_PER_GRAM;
  }


  retrieveCurrentGoal() {
    this.http.get<{message: string, userGoal: UserGoal}>(environment.apiUrl + '/userGoal').subscribe(response => {
      console.log(response.userGoal);
      this.currentUserGoal = response.userGoal;
      this.currentUserGoalChanged.next();
    });
  }

  updateCurrentGoal(newGoal: UserGoal) {
    this.http.post<{message: string, id: string}>(environment.apiUrl + '/userGoal', newGoal).subscribe(response => {
      this.currentUserGoal = newGoal;
      this.currentUserGoalChanged.next();
    });
  }

}
