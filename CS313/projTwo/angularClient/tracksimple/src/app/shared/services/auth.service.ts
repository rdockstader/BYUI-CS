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
  private userID: string;

  authChange = new Subject<boolean>();
  userChanged = new Subject<void>();

  constructor(private http: HttpClient, private router: Router) {}

  registerUser(newUser: User) {
    this.user = { ...newUser };
    this.http.post<{message: string, id: string}>(environment.apiUrl + '/user', this.user).subscribe(response => {
      this.user.userId = response.id;
    });

    this.router.navigate(['/login']);
  }

  updateUser(updateduser: User) {
    console.log(updateduser);
    this.http.put<{message: string, user: User}>(environment.apiUrl + '/user/' + this.userID, updateduser).subscribe(response => {
      this.user.firstName = updateduser.firstName;
      this.user.lastName = updateduser.lastName;
      this.user.middleName = updateduser.middleName;
      this.user.heightInInches = updateduser.heightInInches;
      this.user.weightInPounds = updateduser.weightInPounds;
      this.user.goalWeightInPounds = updateduser.goalWeightInPounds;
      this.user.genderAtBirth = updateduser.genderAtBirth;
      this.user.dateOfBirth = updateduser.dateOfBirth;
    });
  }

  login(authData: AuthData) {
    this.http.post<{token: string, expiresIn: any, user: User}>(environment.apiUrl + '/user/login', authData).subscribe(result => {
      this.user = result.user;
      this.userID = this.user.userId;
      this.token = result.token;
      this.setAuthTime(result.expiresIn);
      this.authChange.next(true);
      this.saveAuthData(this.token, new Date(new Date().getTime() + result.expiresIn * 1000), this.userID);
      this.router.navigate(['/dashboard']);
    });
  }

  logout() {
    this.token = null;
    this.user = null;
    clearTimeout(this.tokenTimer);
    this.authChange.next(false);
    this.clearAuthData();
    this.router.navigate(['/login']);
  }

  getUser() {
    return { ...this.user };
  }

  getUserID() {
    return this.userID;
  }

  isAuth() {
    return this.token != null;
  }

  getToken() {
    return this.token;
  }

  autoAuthUser() {
    const authInfo = this.getAuthData();
    if (!authInfo) {
      return;
    }
    const now = new Date();
    const expiresIn = authInfo.expirationDate.getTime() - now.getTime();
    if (expiresIn > 0) {
      this.token = authInfo.token;
      this.userID = authInfo.userId;
      this.setAuthTime(expiresIn / 1000);
      this.authChange.next(true);
      this.http.get<{message: String, user: User}>(environment.apiUrl + '/user/' + authInfo.userId).subscribe(result => {
        this.user = result.user;
        this.userChanged.next();
      });
    }
  }

  private saveAuthData(token: string, expirationDate: Date, userId: string) {
    localStorage.setItem('token', token);
    localStorage.setItem('expiration', expirationDate.toISOString());
    localStorage.setItem('currentUserId', userId);
  }

  private clearAuthData() {
    localStorage.removeItem('token');
    localStorage.removeItem('expiration');
    localStorage.removeItem('currentUserId');
  }

  private getAuthData() {
    const token = localStorage.getItem('token');
    const expirationDate = localStorage.getItem('expiration');
    const userId: string = localStorage.getItem('currentUserId');
    if (!token || !expirationDate) {
      return;
    }

    return {
      token: token,
      expirationDate: new Date(expirationDate),
      userId: userId
    };
  }

  private setAuthTime(durationInSeconds: number) {
    this.tokenTimer = setTimeout(() => {
      this.logout();
    }, durationInSeconds * 1000);
  }
}
