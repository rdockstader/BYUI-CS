import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { CurrentGoalsComponent } from './current-goals.component';

describe('CurrentGoalsComponent', () => {
  let component: CurrentGoalsComponent;
  let fixture: ComponentFixture<CurrentGoalsComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ CurrentGoalsComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(CurrentGoalsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
