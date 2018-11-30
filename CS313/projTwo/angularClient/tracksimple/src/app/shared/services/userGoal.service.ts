import { UserGoal } from '../models/user-goal.model';
import { Subject } from 'rxjs';

export class UserGoalService {
  // constants
  private FAT_CALS_PER_GRAM = 9;
  private PROTEIN_CALS_PER_GRAM = 4;
  private CARB_CALS_PER_GRAM = 4;
  // Vars
  private currentUserGoal: UserGoal;
  currentUserGoalChanged = new Subject<void>();

  constructor() {}

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
    this.currentUserGoal = {dailyCalories: 2000, dailyProtein: 100, dailyCarbs: 100, dailyFats: 100};
    this.currentUserGoalChanged.next();
  }

  updateCurrentGoal(newGoal: UserGoal) {
    this.currentUserGoal = newGoal;
    this.currentUserGoalChanged.next();
  }

}
