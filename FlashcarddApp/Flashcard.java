package com.example.flashcardapp;

import java.io.Serializable;

public class Flashcard implements Serializable {
    private String state;
    private String capital;

    public Flashcard(String state, String capital) {
        this.state = state;
        this.capital = capital;
    }

    public String getState() {
        return state;
    }

    public String getCapital() {
        return capital;
    }
}
