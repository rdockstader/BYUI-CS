import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations' ;
import { FlexLayoutModule } from '@angular/flex-layout';
import { ReactiveFormsModule, FormsModule } from '@angular/forms';

import { AppComponent } from './app.component';
import { AppRoutingModule } from './app-routing.module';
import { MaterialModule } from './material.module';

import { SignupComponent } from './auth/signup/signup.component';
import { LoginComponent } from './auth/login/login.component';
import { FoodEntryComponent } from './food-entry/food-entry.component';
import { NewEntryComponent } from './food-entry/new-entry/new-entry.component';
import { WelcomeComponent } from './welcome/welcome.component';
import { HeaderComponent } from './navigation/header/header.component';
import { SidenavListComponent } from './navigation/sidenav-list/sidenav-list.component';
import { EntryListComponent } from './food-entry/entry-list/entry-list.component';

import { AuthService } from './shared/services/auth.service';
import { HTTP_INTERCEPTORS, HttpClientModule } from '@angular/common/http';
import { AuthInterceptor } from './shared/auth-interceptor';
import { FoodEntryService } from './shared/services/foodEntry.service';
import { SettingsComponent } from './user/settings/settings.component';
import { GoalsComponent } from './user/goals/goals.component';
import { CurrentGoalsComponent } from './user/goals/current-goals/current-goals.component';
import { NewGoalsComponent } from './user/goals/new-goals/new-goals.component';
import { UserGoalService } from './shared/services/userGoal.service';



@NgModule({
  declarations: [
    AppComponent,
    SignupComponent,
    LoginComponent,
    FoodEntryComponent,
    NewEntryComponent,
    WelcomeComponent,
    HeaderComponent,
    SidenavListComponent,
    EntryListComponent,
    SettingsComponent,
    GoalsComponent,
    CurrentGoalsComponent,
    NewGoalsComponent
  ],
  imports: [
    BrowserModule,
    BrowserAnimationsModule,
    MaterialModule,
    AppRoutingModule,
    FlexLayoutModule,
    FormsModule,
    ReactiveFormsModule,
    HttpClientModule
  ],
  providers: [
    AuthService,
    FoodEntryService,
    UserGoalService,
    {provide: HTTP_INTERCEPTORS, useClass: AuthInterceptor, multi: true}
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
