import { Component, OnInit } from '@angular/core';
import { FormGroup, FormControl, Validators } from '@angular/forms';

@Component({
  selector: 'app-signup',
  templateUrl: './signup.component.html',
  styleUrls: ['./signup.component.css']
})
export class SignupComponent implements OnInit {
  sigunupForm: FormGroup;
  PASSWORD_MIN_LENGTH = 8;
  MAX_DATE: Date;

  constructor() { }

  ngOnInit() {
    this.MAX_DATE = new Date();
    this.MAX_DATE.setFullYear(this.MAX_DATE.getFullYear() - 18);
    this.initForm();
  }

  onSubmit() {
    if (!this.sigunupForm.invalid) {
      console.log(this.sigunupForm.value);
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
      'dateOfBirth': new FormControl(dateOfBirth, Validators.compose([Validators.required])),
      'agree' : new FormControl(agree, Validators.required)
    });

  }

}
