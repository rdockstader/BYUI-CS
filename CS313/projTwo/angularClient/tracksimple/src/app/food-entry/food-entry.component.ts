import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-food-entry',
  templateUrl: './food-entry.component.html',
  styleUrls: ['./food-entry.component.css']
})
export class FoodEntryComponent implements OnInit {
  selectedTab = 0;

  constructor() { }

  ngOnInit() {
  }

  toggleTab(tabNum: number) {
    this.selectedTab = tabNum;
  }

}
