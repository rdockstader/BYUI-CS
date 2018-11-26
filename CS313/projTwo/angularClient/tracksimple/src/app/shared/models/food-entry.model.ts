export interface FoodEntry {
  FoodEntryID: string;
  user?: string;
  meal: 'Breakfast' | 'Lunch' | 'Dinner' | 'Snack';
  name: string;
  calories: number;
  protein?: number;
  carbs?: number;
  fats?: number;
  dateAdded: Date;
}
