import { Component, OnInit } from '@angular/core';
import { FormGroup, FormControl, Validators } from '@angular/forms';
import { AuthService } from 'src/app/shared/services/auth.service';

@Component({
  selector: 'app-signup',
  templateUrl: './signup.component.html',
  styleUrls: ['./signup.component.css']
})
export class SignupComponent implements OnInit {
  isLoading = false;
  sigunupForm: FormGroup;
  PASSWORD_MIN_LENGTH = 8;
  MAX_DATE: Date;

  constructor(private authService: AuthService) { }

  ngOnInit() {
    this.isLoading = true;
    this.MAX_DATE = new Date();
    this.MAX_DATE.setFullYear(this.MAX_DATE.getFullYear() - 18);
    this.initForm();
    this.isLoading = false;
  }

  onSubmit() {
    this.isLoading = true;
    if (!this.sigunupForm.invalid) {
      this.authService.registerUser({
        userId: null,
        email: this.sigunupForm.value.email,
        password: this.sigunupForm.value.password,
        firstName: this.sigunupForm.value.firstName,
        lastName: this.sigunupForm.value.lastName,
        middleName: this.sigunupForm.value.middleName,
        heightInInches: this.sigunupForm.value.heightInInches,
        weightInPounds: this.sigunupForm.value.weightInPounds,
        goalWeightInPounds: this.sigunupForm.value.goalWeightInPounds,
        genderAtBirth: this.sigunupForm.value.gender,
        dateOfBirth: this.sigunupForm.value.dateOfBirth
      });
    }
  }

  private initForm() {

    const email = '';
    const password = '';
    const firstName = '';
    const lastName = '';
    const middleName = '';
    const heightInInches = '';
    const weightInPounds = '';
    const goalWeightInPounds = '';
    const gender = '';
    const dateOfBirth = '';
    const agree = '';

    this.sigunupForm = new FormGroup({
      'email': new FormControl(email, Validators.compose([Validators.email, Validators.required])),
      'password': new FormControl(password, Validators.compose([Validators.required, Validators.minLength(this.PASSWORD_MIN_LENGTH)])),
      'firstName': new FormControl(firstName, Validators.required),
      'middleName': new FormControl(middleName),
      'lastName': new FormControl(lastName, Validators.required),
      'heightInInches': new FormControl(heightInInches, Validators.compose([Validators.required, Validators.min(1)])),
      'weightInPounds': new FormControl(weightInPounds, Validators.compose([Validators.required, Validators.min(1)])),
      'goalWeightInPounds': new FormControl(goalWeightInPounds, Validators.compose([Validators.required, Validators.min(1)])),
      'gender': new FormControl(gender, Validators.compose([Validators.required])),
      'dateOfBirth': new FormControl(dateOfBirth, Validators.compose([Validators.required])),
      'agree' : new FormControl(agree, Validators.required)
    });

  }

}
