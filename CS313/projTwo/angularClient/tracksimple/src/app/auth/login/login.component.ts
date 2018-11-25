import { Component, OnInit } from '@angular/core';
import { FormGroup, FormControl, Validators } from '@angular/forms';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {
  sigunupForm: FormGroup;
  constructor() { }

  ngOnInit() {
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
    this.sigunupForm = new FormGroup({
      'email': new FormControl(email, Validators.compose([Validators.email, Validators.required])),
      'password': new FormControl(password, Validators.compose([Validators.required])),
    });

  }

}
