import { Component, OnInit } from '@angular/core';
import { FormGroup, FormControl, Validators } from '@angular/forms';
import { AuthService } from 'src/app/shared/services/auth.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {
  isLoading = false;
  loginForm: FormGroup;
  constructor(private authService: AuthService) { }

  ngOnInit() {
    this.isLoading = true;
    this.initForm();
    this.isLoading = false;
  }

  onSubmit() {
    if (!this.loginForm.invalid) {
      this.isLoading = true;
      this.authService.login({
        email: this.loginForm.value.email,
        password: this.loginForm.value.password
      });
    }
  }

  private initForm() {

    const email = '';
    const password = '';
    this.loginForm = new FormGroup({
      'email': new FormControl(email, Validators.compose([Validators.email, Validators.required])),
      'password': new FormControl(password, Validators.compose([Validators.required])),
    });

  }

}
