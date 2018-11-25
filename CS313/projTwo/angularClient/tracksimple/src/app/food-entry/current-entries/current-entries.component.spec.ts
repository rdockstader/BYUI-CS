import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { CurrentEntriesComponent } from './current-entries.component';

describe('CurrentEntriesComponent', () => {
  let component: CurrentEntriesComponent;
  let fixture: ComponentFixture<CurrentEntriesComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ CurrentEntriesComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(CurrentEntriesComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
