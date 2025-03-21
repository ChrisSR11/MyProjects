package com.example.flashcardapp;


import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;
import java.util.ArrayList;


public class MainActivity extends AppCompatActivity {


    private Button startButton;
    private Button settingsButton;
    private TextView welcomeTextView;
    private TextView gamesPlayedTextView;
    private TextView currentDifficultyTextView;
    private TextView correctAnswersTextView; // TextView for correct answers
    private TextView wrongAnswersTextView; // TextView for wrong answers
    private ArrayList<Flashcard> flashcards;

    private TextView results;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        startButton = findViewById(R.id.startButton);
        settingsButton = findViewById(R.id.settingsButton);
        welcomeTextView = findViewById(R.id.welcomeTextView);
        gamesPlayedTextView = findViewById(R.id.gamesPlayedTextView);
        currentDifficultyTextView = findViewById(R.id.currentDifficultyTextView);
        correctAnswersTextView = findViewById(R.id.correctAnswersTextView); // Initialize correct answers TextView
        wrongAnswersTextView = findViewById(R.id.wrongAnswersTextView); // Initialize wrong answers TextView
        results = findViewById(R.id.totalScoreTextView);

        SharedPreferences sharedPreferences = getSharedPreferences("FlashcardAppPrefs", Context.MODE_PRIVATE);


        // Load and display player name
        String playerName = sharedPreferences.getString("playerName", "Player");
        welcomeTextView.setText("Welcome, " + playerName + "!");


        // Load and display games played
        int gamesPlayed = sharedPreferences.getInt("gamesPlayed", 0);
        gamesPlayedTextView.setText("Games Played: " + gamesPlayed);


        // Load and display current difficulty
        int numberOfFlashcards = sharedPreferences.getInt("numberOfFlashcards", 5); // Default is 5 (Easy)
        String difficulty = getDifficultyFromNumberOfFlashcards(numberOfFlashcards);
        currentDifficultyTextView.setText("Current Difficulty: " + difficulty);


        // Initialize flashcards
        flashcards = new ArrayList<>();
        flashcards.add(new Flashcard("Alabama", "Montgomery"));
        flashcards.add(new Flashcard("Alaska", "Juneau"));
        flashcards.add(new Flashcard("Arizona", "Phoenix"));
        flashcards.add(new Flashcard("Arkansas", "Little Rock"));
        flashcards.add(new Flashcard("California", "Sacramento"));
        flashcards.add(new Flashcard("Colorado", "Denver"));
        flashcards.add(new Flashcard("Connecticut", "Hartford"));
        flashcards.add(new Flashcard("Delaware", "Dover"));
        flashcards.add(new Flashcard("Florida", "Tallahassee"));
        flashcards.add(new Flashcard("Georgia", "Atlanta"));
        flashcards.add(new Flashcard("Hawaii", "Honolulu"));
        flashcards.add(new Flashcard("Idaho", "Boise"));
        flashcards.add(new Flashcard("Illinois", "Springfield"));
        flashcards.add(new Flashcard("Indiana", "Indianapolis"));
        flashcards.add(new Flashcard("Iowa", "Des Moines"));
        flashcards.add(new Flashcard("Kansas", "Topeka"));
        flashcards.add(new Flashcard("Kentucky", "Frankfort"));
        flashcards.add(new Flashcard("Louisiana", "Baton Rouge"));
        flashcards.add(new Flashcard("Maine", "Augusta"));
        flashcards.add(new Flashcard("Maryland", "Annapolis"));
        flashcards.add(new Flashcard("Massachusetts", "Boston"));
        flashcards.add(new Flashcard("Michigan", "Lansing"));
        flashcards.add(new Flashcard("Minnesota", "Saint Paul"));
        flashcards.add(new Flashcard("Mississippi", "Jackson"));
        flashcards.add(new Flashcard("Missouri", "Jefferson City"));
        flashcards.add(new Flashcard("Montana", "Helena"));
        flashcards.add(new Flashcard("Nebraska", "Lincoln"));
        flashcards.add(new Flashcard("Nevada", "Carson City"));
        flashcards.add(new Flashcard("New Hampshire", "Concord"));
        flashcards.add(new Flashcard("New Jersey", "Trenton"));
        flashcards.add(new Flashcard("New Mexico", "Santa Fe"));
        flashcards.add(new Flashcard("New York", "Albany"));
        flashcards.add(new Flashcard("North Carolina", "Raleigh"));
        flashcards.add(new Flashcard("North Dakota", "Bismarck"));
        flashcards.add(new Flashcard("Ohio", "Columbus"));
        flashcards.add(new Flashcard("Oklahoma", "Oklahoma City"));
        flashcards.add(new Flashcard("Oregon", "Salem"));
        flashcards.add(new Flashcard("Pennsylvania", "Harrisburg"));
        flashcards.add(new Flashcard("Rhode Island", "Providence"));
        flashcards.add(new Flashcard("South Carolina", "Columbia"));
        flashcards.add(new Flashcard("South Dakota", "Pierre"));
        flashcards.add(new Flashcard("Tennessee", "Nashville"));
        flashcards.add(new Flashcard("Texas", "Austin"));
        flashcards.add(new Flashcard("Utah", "Salt Lake City"));
        flashcards.add(new Flashcard("Vermont", "Montpelier"));
        flashcards.add(new Flashcard("Virginia", "Richmond"));
        flashcards.add(new Flashcard("Washington", "Olympia"));
        flashcards.add(new Flashcard("West Virginia", "Charleston"));
        flashcards.add(new Flashcard("Wisconsin", "Madison"));
        flashcards.add(new Flashcard("Wyoming", "Cheyenne"));


        // Start button click listener
        startButton.setOnClickListener(v -> {
            // Increment the games played counter
            int updatedGamesPlayed = gamesPlayed + 1;
            sharedPreferences.edit().putInt("gamesPlayed", updatedGamesPlayed).apply();


            // Start the QuizActivity
            Intent intent = new Intent(MainActivity.this, QuizActivity.class);
            intent.putExtra("flashcardsData", flashcards);
            startActivity(intent);
        });


        // Settings button click listener
        settingsButton.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, SettingsActivity.class);
            startActivity(intent);
        });


        // Check for quiz results from QuizActivity
        Intent intent = getIntent();
        if (intent != null) {
            int correctAnswers = intent.getIntExtra("correctAnswers", 0);
            int wrongAnswers = intent.getIntExtra("wrongAnswers", 0);
            int totalQuestions = intent.getIntExtra("totalQuestions",1);
            double totalScore = ((double) correctAnswers / totalQuestions) * 100;

            // Update the TextViews with quiz results
            correctAnswersTextView.setText("Correct Answers: " + correctAnswers);
            wrongAnswersTextView.setText("Wrong Answers: " + wrongAnswers);
            results.setText("Total Score: " + totalScore + "%");
        }
    }


    @Override
    protected void onResume() {
        super.onResume();
        SharedPreferences sharedPreferences = getSharedPreferences("FlashcardAppPrefs", Context.MODE_PRIVATE);


        // Update player name
        String playerName = sharedPreferences.getString("playerName", "Player");
        welcomeTextView.setText("Welcome, " + playerName + "!");


        // Update games played
        int gamesPlayed = sharedPreferences.getInt("gamesPlayed", 0);
        gamesPlayedTextView.setText("Games Played: " + gamesPlayed);


        // Update current difficulty
        int numberOfFlashcards = sharedPreferences.getInt("numberOfFlashcards", 5); // Default is 5 (Easy)
        String difficulty = getDifficultyFromNumberOfFlashcards(numberOfFlashcards);
        currentDifficultyTextView.setText("Current Difficulty: " + difficulty);
    }


    // Helper method to map number of flashcards to difficulty level
    private String getDifficultyFromNumberOfFlashcards(int numberOfFlashcards) {
        switch (numberOfFlashcards) {
            case 5:
                return "Easy";
            case 10:
                return "Medium";
            case 15:
                return "Hard";
            default:
                return "Easy"; // Default to Easy
        }
    }
}



