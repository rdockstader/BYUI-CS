package com.rdockstader;

import sun.reflect.annotation.ExceptionProxy;

import java.util.Scanner;

public class Test {
    private static Scanner in = new Scanner(System.in);

    public static void main(String[] args) throws Exception {
        System.out.println("Input a Password");
	    String password = in.nextLine();
	    User user = new User(password);
	    boolean passwordIsValid = false;

        while(!passwordIsValid) {
            try {
                System.out.println("password: " + user.getPassword() + " salt: " + user.getSalt() + " hash: " + user.getHashedPassword());
                NSALoginController.hashUserPassword(user);
                passwordIsValid = true;
            } catch(WeakPasswordException e) {
                System.out.println("Password Error: " + e.getMessage());
                passwordIsValid = false;
                System.out.println("Input a Password");
                password = in.nextLine();
                user.setPassword(password);
            } catch(Exception e) {
                System.out.println("Error getting hash!");
            }
        }

        System.out.println("password: " + user.getPassword() + " salt: " + user.getSalt() + " hash: " + user.getHashedPassword());
        System.out.println("Input a Password to verify");
        String verifyPassword = in.nextLine();
        user.setPassword((verifyPassword));
        try {
            if(NSALoginController.verifyPassword(user)) {
                System.out.println("Hmm. Checks Out.");
            } else {
                System.out.println("Bad password! Turn on the alerts and sirens!");
            }
        } catch(Exception e) {
            // do nothing
        }


    }
}
