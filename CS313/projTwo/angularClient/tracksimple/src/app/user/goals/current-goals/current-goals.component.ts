import { Component, OnInit, ViewChild, ElementRef } from '@angular/core';

import { Chart } from 'chart.js';
import { UserGoalService } from 'src/app/shared/services/userGoal.service';
import { UserGoal } from 'src/app/shared/models/user-goal.model';
import { Subscription } from 'rxjs';

@Component({
  selector: 'app-current-goals',
  templateUrl: './current-goals.component.html',
  styleUrls: ['./current-goals.component.css']
})
export class CurrentGoalsComponent implements OnInit {
  // Values
  goal: UserGoal;
  dailyCalorieTotalByGram: number;
  currentUserGoalSub: Subscription;

  // Chart Info
  chart: Chart;
  @ViewChild('chart') chartele: ElementRef;

  constructor(private userGoalService: UserGoalService) { }

  ngOnInit() {
    this.initChart();
    this.userGoalService.retrieveCurrentGoal();
    this.goal = this.userGoalService.getCurrentUserGoal();
    this.currentUserGoalSub = this.userGoalService.currentUserGoalChanged.subscribe(result => {
      this.goal = this.userGoalService.getCurrentUserGoal();
      this.dailyCalorieTotalByGram = (this.goal.dailyProtein * this.userGoalService.getProteinCalsPerGram()) +
                                   (this.goal.dailyCarbs  * this.userGoalService.getCarbCalsPerGram()) +
                                   (this.goal.dailyFats * this.userGoalService.getFatCalsPerGram());
      this.updateChart();
    });
    this.dailyCalorieTotalByGram = (this.goal.dailyProtein * this.userGoalService.getProteinCalsPerGram()) +
                                   (this.goal.dailyCarbs  * this.userGoalService.getCarbCalsPerGram()) +
                                   (this.goal.dailyFats * this.userGoalService.getFatCalsPerGram());
    this.updateChart();
  }

  initChart() {
    this.chart = new Chart(this.chartele.nativeElement, {
      type: 'doughnut',
      responsive: true
    });
  }

  updateChart() {

    this.chart.data = {
        datasets: [
          {
            data: [
              this.goal.dailyProtein * this.userGoalService.getProteinCalsPerGram(),
              this.goal.dailyCarbs * this.userGoalService.getCarbCalsPerGram(),
              this.goal.dailyFats * this.userGoalService.getFatCalsPerGram()
            ],
            backgroundColor: ['#3F51B5', '#FF4081', '#F44A3E']
          }
        ],
        labels: ['Protein', 'Carbs', 'Fats']
      },
      this.chart.options = {
      title: {
        display: true,
        text: 'Calorie Breakdown'
      }
    };
    this.chart.update();
  }

}
