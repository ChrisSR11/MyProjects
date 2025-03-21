package com.example.flashcardapp;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Random;
import java.util.Set;

public class QuizActivity extends AppCompatActivity {

    private TextView questionTextView;
    private TextView questionCountTextView;
    private ListView answerListView;
    private ArrayAdapter<String> adapter;
    private ArrayList<Flashcard> flashcards; // Quiz flashcards
    private ArrayList<Flashcard> allFlashcards; // All 50 states flashcards
    private int currentFlashcardIndex = 0;
    private List<String> answerChoices;
    private int totalQuestions;

    // Statistics
    private int correctAnswers = 0;
    private int wrongAnswers = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_quiz);

        questionTextView = findViewById(R.id.questionTextView);
        questionCountTextView = findViewById(R.id.questionCountTextView);
        answerListView = findViewById(R.id.answerListView);

        // Retrieve all flashcards from the Intent
        allFlashcards = (ArrayList<Flashcard>) getIntent().getSerializableExtra("flashcardsData");

        // Clone the full list for quiz flashcards (to avoid modifying the original list)
        flashcards = new ArrayList<>(allFlashcards);

        // Load quiz settings from SharedPreferences
        SharedPreferences sharedPreferences = getSharedPreferences("FlashcardAppPrefs", Context.MODE_PRIVATE);
        totalQuestions = sharedPreferences.getInt("numberOfFlashcards", 5);

        // Shuffle flashcards to get random questions
        Collections.shuffle(flashcards);

        // Limit quiz questions based on user preference
        if (flashcards.size() > totalQuestions) {
            flashcards = new ArrayList<>(flashcards.subList(0, totalQuestions));
        }

        // Load the first question
        loadNextQuestion();

        // Handle answer selection
        answerListView.setOnItemClickListener((parent, view, position, id) -> checkAnswer(answerChoices.get(position)));
    }

    private void loadNextQuestion() {
        if (currentFlashcardIndex < flashcards.size()) {
            Flashcard flashcard = flashcards.get(currentFlashcardIndex);

            // Display question
            questionTextView.setText("What is the capital of " + flashcard.getState());
            questionCountTextView.setText("Question " + (currentFlashcardIndex + 1) + " of " + totalQuestions);

            // Generate answer choices from all 50 states
            answerChoices = getRandomChoices(flashcard.getCapital());
            adapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, answerChoices);
            answerListView.setAdapter(adapter);
        }
    }

    private List<String> getRandomChoices(String correctAnswer) {
        Set<String> choices = new HashSet<>();
        choices.add(correctAnswer); // Add correct answer first

        Random random = new Random();

        // Keep adding random capitals until we have 4 unique answers
        while (choices.size() < 4) {
            String randomCapital = allFlashcards.get(random.nextInt(allFlashcards.size())).getCapital();
            choices.add(randomCapital);
        }

        // Convert to list and shuffle
        List<String> choiceList = new ArrayList<>(choices);
        Collections.shuffle(choiceList);
        return choiceList;
    }

    private void checkAnswer(String selectedAnswer) {
        if (selectedAnswer.equals(flashcards.get(currentFlashcardIndex).getCapital())) {
            correctAnswers++; // Increase correct answer count
        } else {
            wrongAnswers++; // Increase wrong answer count
        }

        currentFlashcardIndex++;
        if (currentFlashcardIndex < flashcards.size()) {
            loadNextQuestion();
        } else {
            showStatistics();
        }
    }

    private void showStatistics() {
        // Create an Intent to return to MainActivity
        Intent intent = new Intent(QuizActivity.this, MainActivity.class);
        intent.putExtra("correctAnswers", correctAnswers); // Pass correct answers
        intent.putExtra("wrongAnswers", wrongAnswers); // Pass wrong answers
        intent.putExtra("totalQuestions", flashcards.size());
        startActivity(intent);
        finish(); // Close QuizActivity so the user doesn't come back to the quiz
    }
}
