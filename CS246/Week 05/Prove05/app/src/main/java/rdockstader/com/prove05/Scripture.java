package rdockstader.com.prove05;

import android.os.Parcel;
import android.os.Parcelable;

public class Scripture implements Parcelable {
    private String book;
    private String chapter;
    private String verse;

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel out, int flags) {
        out.writeString(book);
        out.writeString(chapter);
        out.writeString(verse);
    }

    // this is used to regenerate your object. All Parcelables must have a CREATOR that implements these two methods
    public static final Parcelable.Creator<Scripture> CREATOR = new Parcelable.Creator<Scripture>() {
        public Scripture createFromParcel(Parcel in) {
            return new Scripture(in);
        }

        public Scripture[] newArray(int size) {
            return new Scripture[size];
        }
    };

    public Scripture(String book, String chapter, String verse) {
        this.book = book;
        this.chapter = chapter;
        this.verse = verse;
    }

    // example constructor that takes a Parcel and gives you an object populated with it's values
    private Scripture(Parcel in) {
        this.book = in.readString();
        this.chapter = in.readString();
        this.verse = in.readString();
    }

    public String getBook() {
        return book;
    }

    public void setBook(String book) {
        this.book = book;
    }

    public String getChapter() {
        return chapter;
    }

    public void setChapter(String chapter) {
        this.chapter = chapter;
    }

    public String getVerse() {
        return verse;
    }

    public void setVerse(String verse) {
        this.verse = verse;
    }

    @Override
    public String toString() {
        return this.getBook() + ' ' + this.getChapter() + ':' + this.getVerse();
    }
}
