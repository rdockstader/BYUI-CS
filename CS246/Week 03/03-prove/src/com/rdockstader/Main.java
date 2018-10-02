package com.rdockstader;


import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;

public class Main {

    public static void main(String[] args) {

        TweetLoader tweetLoader = new TweetLoader();

        Map<String, BYUITweet> tweetMap = tweetLoader.retrieveTweetsWithHashTag("#byui");

        // STRETCH CHALLENGE

        List<Map.Entry<String, BYUITweet>> sortedMap = new ArrayList<Map.Entry<String, BYUITweet>>(tweetMap.size());

        sortedMap.addAll(tweetMap.entrySet());

        Collections.sort(sortedMap, new SortByFollowers());

        for(Map.Entry<String, BYUITweet> tweet: sortedMap) {
            System.out.println(tweet.getValue().toString());
        }

        // END STRETCH CHALLENGE

        /*for(Map.Entry<String, BYUITweet> tweet: tweetMap.entrySet()) {
            System.out.println(tweet.getValue().toString());
        }*/
    }
}
