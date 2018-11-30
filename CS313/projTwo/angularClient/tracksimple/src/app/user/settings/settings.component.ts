import { Component, OnInit, OnDestroy } from '@angular/core';
import { FormGroup, FormControl, Validators } from '@angular/forms';
import { AuthService } from 'src/app/shared/services/auth.service';
import { User } from 'src/app/shared/models/user.model';
import { Subscription } from 'rxjs';

@Component({
  selector: 'app-settings',
  templateUrl: './settings.component.html',
  styleUrls: ['./settings.component.css']
})
export class SettingsComponent implements OnInit, OnDestroy {
  userSettingForm: FormGroup;
  user: User;
  userChangedSub: Subscription;
  MAX_DATE: Date;

  constructor(private authService: AuthService) { }

  ngOnInit() {
    this.MAX_DATE = new Date();
    this.MAX_DATE.setFullYear(this.MAX_DATE.getFullYear() - 18);
    this.user = this.authService.getUser();
    this.initForm();
    this.userChangedSub = this.authService.userChanged.subscribe(result => {
      this.user = this.authService.getUser();
      this.initForm();
    });
  }

  ngOnDestroy() {
    this.userChangedSub.unsubscribe();
  }

  onSubmit() {
    this.authService.updateUser({
      userId: null,
      email: null,
      password: null,
      firstName: this.userSettingForm.value.firstName,
      lastName: this.userSettingForm.value.lastName,
      middleName: this.userSettingForm.value.middleName,
      heightInInches: this.userSettingForm.value.heightInInches,
      weightInPounds: this.userSettingForm.value.weightInPounds,
      goalWeightInPounds: this.userSettingForm.value.goalWeightInPounds,
      genderAtBirth: this.userSettingForm.value.gender,
      dateOfBirth: this.userSettingForm.value.dateOfBirth
    });
  }

  private initForm() {
    let firstName = '';
    let lastName = '';
    let middleName = '';
    let heightInInches = 0;
    let weightInPounds = 0;
    let goalWeightInPounds = 0;
    let gender = '';
    let dateOfBirth = new Date();

    if (this.user) {
      firstName = this.user.firstName;
      lastName = this.user.lastName;
      middleName = this.user.middleName;
      heightInInches = this.user.heightInInches;
      weightInPounds = this.user.weightInPounds;
      goalWeightInPounds = this.user.goalWeightInPounds;
      gender = this.user.genderAtBirth;
      dateOfBirth = this.user.dateOfBirth;
    }

    this.userSettingForm = new FormGroup({
      'firstName': new FormControl(firstName, Validators.required),
      'middleName': new FormControl(middleName),
      'lastName': new FormControl(lastName, Validators.required),
      'heightInInches': new FormControl(heightInInches, Validators.compose([Validators.required, Validators.min(1)])),
      'weightInPounds': new FormControl(weightInPounds, Validators.compose([Validators.required, Validators.min(1)])),
      'goalWeightInPounds': new FormControl(goalWeightInPounds, Validators.compose([Validators.required, Validators.min(1)])),
      'gender': new FormControl(gender, Validators.compose([Validators.required])),
      'dateOfBirth': new FormControl(dateOfBirth, Validators.compose([Validators.required]))
    });

  }

}
