package com.rdockstader;

import com.google.gson.Gson;
import twitter4j.*;
import twitter4j.conf.ConfigurationBuilder;

import java.util.*;

public class TweetLoader {
    private Twitter twitter;

    private void configureKeys() {

        ConfigurationBuilder cb = new ConfigurationBuilder();

        final String consumerKey = "";
        final String consumerSecret = "";
        final String accessToken = "";
        final String accessTokenSecret = "";

        cb.setDebugEnabled(true)
                .setOAuthConsumerKey(consumerKey)
                .setOAuthConsumerSecret(consumerSecret)
                .setOAuthAccessToken(accessToken)
                .setOAuthAccessTokenSecret(accessTokenSecret)
                .setJSONStoreEnabled(true);


        TwitterFactory tf = new TwitterFactory(cb.build());
        this.twitter = tf.getInstance();

    }

    public TweetLoader() {
        configureKeys();
    }

    public Map<String, BYUITweet> retrieveTweetsWithHashTag(String hashtag) {
        Gson gson = new Gson();
        Map<String, BYUITweet> tweetMap =  new HashMap<String, BYUITweet>();
        try {
            Query query = new Query("#byui");
            List<Status> tweets = this.twitter.search(query).getTweets();
            for(Status s: tweets) {
                BYUITweet tweet = gson.fromJson(TwitterObjectFactory.getRawJSON(s), BYUITweet.class);
                tweetMap.put(tweet.getUser().getName(), tweet);
            }
        } catch (Exception e) {
            System.out.println(new Date() +  ": [ERROR] - " + e);
        }
        return tweetMap;
    }
}















