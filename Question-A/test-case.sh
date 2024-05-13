#!/bin/bash

# Filename for the test file
test_filename="plaintext.txt"

# Create or clear the file
> "$test_filename"

# Add different types of content to the file

# 1. Plain ASCII text
echo "Simple ASCII text for basic input." >> "$test_filename"

# 2. Numeric characters
echo "1234567890" >> "$test_filename"

# 3. Special characters
echo "!@#$%^&*()_+-=[]{}|;:',.<>/?~" >> "$test_filename"

# 4. Extended characters including accents
echo "Üñîçødé characters with accents: é, ñ, ö, ü." >> "$test_filename"

# 5. A long paragraph with spaces
cat <<EOF >> "$test_filename"
This is a longer block of text that is intended to test the encryption and decryption 
processes across multiple lines of input. It includes various punctuation marks and 
special characters to enhance the complexity of the test case. Testing how encryption 
algorithms handle different types of text input is crucial for ensuring robustness.
EOF

# 6. Binary-like content (simulated)
echo "0101010101 1010101010 11110000 00001111" >> "$test_filename"

# 7. Base64-like content
echo "TWFueSBkYXRhIGVuY3J5cHRpb24gYW5kIGRlY3J5cHRpb24gdGVzdHM=" >> "$test_filename"

# 8. JSON-like content
echo '{"name": "John Doe", "age": 30, "city": "New York"}' >> "$test_filename"

# 9. XML-like content
echo '<root><child name="value"/></root>' >> "$test_filename"

# Display information about the created file
echo "Test file created with various content types: $test_filename"
ls -l "$test_filename"
