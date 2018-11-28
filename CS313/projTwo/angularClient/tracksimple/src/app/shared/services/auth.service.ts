import { Subject } from 'rxjs';
import { Injectable } from '@angular/core';
import { Router } from '@angular/router';
import { HttpClient } from '@angular/common/http';

import { User } from '../models/user.model';
import { AuthData } from '../models/auth-data.model';
import { environment } from '../../../environments/environment';

@Injectable()
export class AuthService {
  private token: string;
  private tokenTimer: any;
  private user: User;

  authChange = new Subject<boolean>();

  constructor(private http: HttpClient, private router: Router) {}

  registerUser(newUser: User) {
    this.user = { ...newUser };
    this.http.post<{message: string, id: string}>(environment.apiUrl + '/user', this.user).subscribe(response => {
      this.user.userId = response.id;
    });

    this.router.navigate(['/login']);
  }

  login(authData: AuthData) {
    this.http.post<{token: string, expiresIn: any, user: User}>(environment.apiUrl + '/user/login', authData).subscribe(result => {
      this.user = result.user;
      this.token = result.token;
      this.setAuthTime(result.expiresIn);
      this.authChange.next(true);
      this.router.navigate(['/dashboard']);
    });
  }

  logout() {
    this.token = null;
    this.user = null;
    clearTimeout(this.tokenTimer);
    this.authChange.next(false);
    this.router.navigate(['/login']);
  }

  getUser() {
    return { ...this.user };
  }

  isAuth() {
    return this.user != null;
  }

  getToken() {
    return this.token;
  }

  private setAuthTime(durationInSeconds: number) {
    this.tokenTimer = setTimeout(() => {
      this.logout();
    }, durationInSeconds * 1000);
  }
}
