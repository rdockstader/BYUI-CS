package com.rdockstader;

public class User {
    private String password;
    private String hashedPassword;
    private String salt;

    public User() {
        this.password = new String();
        this.salt = new String();
        this.hashedPassword = new String();
    }

    public User(String password) {
        this.password = password;
        this.salt = new String();
        this.hashedPassword = new String();
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setHashedPassword(String hashedPassword) { this.hashedPassword = hashedPassword;}

    public String getHashedPassword() {
        return hashedPassword;
    }


    public String getSalt() {
        return salt;
    }

    public void setSalt(String salt) {
        this.salt = salt;
    }

}
