package com.rdockstader;

import com.google.gson.annotations.SerializedName;

public class User {
    private String name;
    @SerializedName("followers_count")
    private int followers;

    public User(String name, int followers) {
        this.name = name;
        this.followers = followers;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getFollowers() {
        return followers;
    }

    public void setFollowers(int followers) {
        this.followers = followers;
    }
}
