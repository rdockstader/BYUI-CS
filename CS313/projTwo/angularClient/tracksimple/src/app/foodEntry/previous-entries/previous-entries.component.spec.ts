import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { PreviousEntriesComponent } from './previous-entries.component';

describe('PreviousEntriesComponent', () => {
  let component: PreviousEntriesComponent;
  let fixture: ComponentFixture<PreviousEntriesComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ PreviousEntriesComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(PreviousEntriesComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
