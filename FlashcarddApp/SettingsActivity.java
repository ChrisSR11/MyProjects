package com.example.flashcardapp;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;

public class SettingsActivity extends AppCompatActivity {

    private Spinner difficultySpinner;
    private EditText playerNameEditText;
    private Button saveSettingsButton;
    private Button resetSettingsButton;

    private SharedPreferences sharedPreferences;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        difficultySpinner = findViewById(R.id.difficultySpinner);
        playerNameEditText = findViewById(R.id.playerNameEditText);
        saveSettingsButton = findViewById(R.id.saveSettingsButton);
        resetSettingsButton = findViewById(R.id.resetSettingsButton);

        // Initialize SharedPreferences
        sharedPreferences = getSharedPreferences("FlashcardAppPrefs", Context.MODE_PRIVATE);

        // Set up the Spinner with difficulty options
        setupDifficultySpinner();

        // Load saved preferences
        loadPreferences();

        // Save settings when the save button is clicked
        saveSettingsButton.setOnClickListener(v -> savePreferences());

        // Reset settings when the reset button is clicked
        resetSettingsButton.setOnClickListener(v -> resetPreferences());
    }

    private void setupDifficultySpinner() {
        // Define the difficulty options and their corresponding number of cards
        String[] difficultyOptions = {"Easy (5 cards)", "Medium (10 cards)", "Hard (15 cards)"};
        ArrayAdapter<String> adapter = new ArrayAdapter<>(this, android.R.layout.simple_spinner_item, difficultyOptions);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        difficultySpinner.setAdapter(adapter);
    }

    private void loadPreferences() {
        int numberOfFlashcards = sharedPreferences.getInt("numberOfFlashcards", 5);
        String playerName = sharedPreferences.getString("playerName", "");

        // Set the Spinner selection based on the saved number of flashcards
        if (numberOfFlashcards == 5) {
            difficultySpinner.setSelection(0); // Easy
        } else if (numberOfFlashcards == 10) {
            difficultySpinner.setSelection(1); // Medium
        } else if (numberOfFlashcards == 15) {
            difficultySpinner.setSelection(2); // Hard
        }

        playerNameEditText.setText(playerName);
    }

    private void savePreferences() {
        String playerName = playerNameEditText.getText().toString().trim();
        if (playerName.isEmpty()) {
            playerName = "Player"; // Default player name
        }

        // Get the selected difficulty and map it to the number of flashcards
        String selectedDifficulty = difficultySpinner.getSelectedItem().toString();
        int numberOfFlashcards;

        switch (selectedDifficulty) {
            case "Easy (5 cards)":
                numberOfFlashcards = 5;
                break;
            case "Medium (10 cards)":
                numberOfFlashcards = 10;
                break;
            case "Hard (15 cards)":
                numberOfFlashcards = 15;
                break;
            default:
                numberOfFlashcards = 5; // Default to Easy
                break;
        }

        // Save preferences
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putInt("numberOfFlashcards", numberOfFlashcards);
        editor.putString("playerName", playerName);
        editor.apply();

        Toast.makeText(this, "Settings saved!", Toast.LENGTH_SHORT).show();

        // Return to MainActivity
        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
    }

    private void resetPreferences() {
        // Reset to default values
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putInt("numberOfFlashcards", 5); // Default to Easy (5 cards)
        editor.putString("playerName", "Player"); // Default player name
        editor.apply();

        // Update the UI to reflect the reset values
        difficultySpinner.setSelection(0); // Set Spinner to Easy
        playerNameEditText.setText("Player");

        Toast.makeText(this, "Settings reset to default!", Toast.LENGTH_SHORT).show();
    }
}