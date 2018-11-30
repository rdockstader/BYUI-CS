import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { NewGoalsComponent } from './new-goals.component';

describe('NewGoalsComponent', () => {
  let component: NewGoalsComponent;
  let fixture: ComponentFixture<NewGoalsComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ NewGoalsComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(NewGoalsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
