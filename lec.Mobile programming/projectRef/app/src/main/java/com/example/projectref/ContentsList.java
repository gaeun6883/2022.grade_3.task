package com.example.projectref;

import java.util.ArrayList;

public class ContentsList {
    String name;
    int remaining_time_limit;

    public ContentsList(String name, int remaining_time_limit){
        this.name=name;
        this.remaining_time_limit=remaining_time_limit;
    }

    String getFirst(){
        return name;
    }
    int getSecond(){
        return remaining_time_limit;
    }
}
