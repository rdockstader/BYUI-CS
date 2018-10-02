package com.rdockstader;

import java.util.Comparator;
import java.util.Map;

public class SortByFollowers implements Comparator<Map.Entry<String, BYUITweet>> {
    @Override
    public int compare(Map.Entry<String, BYUITweet> o1, Map.Entry<String, BYUITweet> o2) {
        return (o1.getValue().getUser().getFollowers() < o2.getValue().getUser().getFollowers())? 1 : -1;
    }
}
