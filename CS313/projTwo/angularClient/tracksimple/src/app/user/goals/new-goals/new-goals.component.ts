import { Component, OnInit, OnDestroy } from '@angular/core';
import { FormGroup, FormControl, Validators } from '@angular/forms';
import { Subscription } from 'rxjs';

import { UserGoal } from 'src/app/shared/models/user-goal.model';
import { UserGoalService } from 'src/app/shared/services/userGoal.service';

@Component({
  selector: 'app-new-goals',
  templateUrl: './new-goals.component.html',
  styleUrls: ['./new-goals.component.css']
})
export class NewGoalsComponent implements OnInit, OnDestroy {
  goalForm: FormGroup;
  userGoal: UserGoal;
  userGoalSub: Subscription;

  dailyCalorieTotalByGram = 0;

  constructor(private userGoalService: UserGoalService) { }

  ngOnInit() {
    this.userGoalService.retrieveCurrentGoal();
    this.userGoal = this.userGoalService.getCurrentUserGoal();
    this.initForm();
    this.updateCalorieTotal();
    this.userGoalSub = this.userGoalService.currentUserGoalChanged.subscribe(result => {
      this.userGoal = this.userGoalService.getCurrentUserGoal();
      this.initForm();
      this.updateCalorieTotal();
    });
  }

  ngOnDestroy() {

  }

  updateCalorieTotal() {
    this.dailyCalorieTotalByGram = (this.goalForm.value['protein'] * this.userGoalService.getProteinCalsPerGram()) +
                                   (this.goalForm.value['carbs'] * this.userGoalService.getCarbCalsPerGram()) +
                                   (this.goalForm.value['fats'] * this.userGoalService.getFatCalsPerGram());
  }

  initForm() {
    let calories = null;
    let protein = null;
    let carbs = null;
    let fats = null;

    if (this.userGoal) {
      calories = this.userGoal.dailyCalories;
      protein = this.userGoal.dailyProtein;
      carbs = this.userGoal.dailyCarbs;
      fats = this.userGoal.dailyFats;
    }

    this.goalForm = new FormGroup({
      'calories': new FormControl(calories, Validators.compose([Validators.required, Validators.min(0)])),
      'protein': new FormControl(protein, Validators.min(0)),
      'carbs': new FormControl(carbs, Validators.min(0)),
      'fats': new FormControl(fats, Validators.min(0))
    });
  }

  onSubmit() {
    this.userGoalService.updateCurrentGoal({
      dailyCalories: this.goalForm.value['calories'],
      dailyProtein: this.goalForm.value['protein'],
      dailyCarbs: this.goalForm.value['carbs'],
      dailyFats: this.goalForm.value['fats']
    });
  }

  formIsInvalid() {
    if (this.goalForm.valid && this.dailyCalorieTotalByGram <= this.goalForm.value['calories']) {
      return false;
    }

    return true;
  }

}
