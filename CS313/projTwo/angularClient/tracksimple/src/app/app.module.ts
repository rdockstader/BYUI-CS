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
import { CurrentEntriesComponent } from './foodEntry/current-entries/current-entries.component';
import { NewEntryComponent } from './foodEntry/new-entry/new-entry.component';
import { PreviousEntriesComponent } from './foodEntry/previous-entries/previous-entries.component';
import { WelcomeComponent } from './welcome/welcome.component';



@NgModule({
  declarations: [
    AppComponent,
    SignupComponent,
    LoginComponent,
    FoodEntryComponent,
    CurrentEntriesComponent,
    NewEntryComponent,
    PreviousEntriesComponent,
    WelcomeComponent
  ],
  imports: [
    BrowserModule,
    BrowserAnimationsModule,
    MaterialModule,
    AppRoutingModule,
    FlexLayoutModule,
    FormsModule,
    ReactiveFormsModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
