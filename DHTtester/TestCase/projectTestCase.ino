# Test Case 1: Normal Operation
Inputs: Temperature = 20°C, Humidity = 50%
Expected Output: Relay remains deactivated.

# Test Case 2: Temperature Threshold Exceeded
Inputs: Temperature = 25°C, Humidity = 50%
Expected Output: Relay activates.

# Test Case 3: Humidity Threshold Exceeded
Inputs: Temperature = 20°C, Humidity = 65%
Expected Output: Relay activates.

# Test Case 4: Both Thresholds Exceeded
Inputs: Temperature = 26°C, Humidity = 70%
Expected Output: Relay activates.

# Test Case 5: Error Handling (Invalid Sensor Readings)
Inputs: NaN for both temperature and humidity readings
Expected Output: Error message "Failed to read from DHT sensor!" is printed.

# Test Case 6: Extreme Temperature
Inputs: Temperature = -10°C, Humidity = 50%
Expected Output: Relay remains deactivated.

# Test Case 7: Extreme Humidity
Inputs: Temperature = 20°C, Humidity = 100%
Expected Output: Relay activates.

# Test Case 8: Boundary Test
Inputs: Temperature = 24°C, Humidity = 60%
Expected Output: Relay remains deactivated.

# Test Case 9: Long Duration Test
Inputs: Varying temperature and humidity readings over an extended period.
Expected Output: Relay activates and deactivates as per threshold conditions.

# Test Case 10: Power Interruption
Inputs: Power interruption during operation, then power restoration.
Expected Output: Code resumes execution, with relay behavior consistent with sensor readings.
