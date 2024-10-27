# Remotif.AI - Advanced Patient Management System
A remote health monitoring system using IoT that integrates sensors for vital sign tracking and machine learning for health predictions. Features include real-time monitoring, a health chatbot, and a collaborative platform for patients and doctors.
Remotif.AI is a comprehensive healthcare management system designed to streamline operations and improve patient care. It features an intuitive interface for managing appointments, patient records, doctor information, and administrative tasks, leveraging advanced AI technologies for enhanced patient monitoring.

## Table of Contents

- [Directory Structure](#directory-structure)
- [Steps to Run the Chatbot](#steps-to-run-the-chatbot)
- [Steps to Run the Frontend](#steps-to-run-the-frontend)
- [Hardware Setup](#hardware-setup)
- [ML Model Codes](#ml-model-codes)
- [Technologies Used](#technologies-used)

## Directory Structure

```
remotif.ai
│
├── Backend                  # Backend code for handling API requests
├── Chatbot                  # Chatbot functionality using OpenAI API
├── Code for Hardware        # Arduino/ESP32 code for hardware components
├── Dataset                  # Dataset used for training and evaluation
├── Frontend                 # Frontend code built with React.js
├── ML models                # Machine learning models for predictive analytics
└── node_modules             # Node.js modules for frontend dependencies
    ├── package-lock.json
    └── package.json
```

## Steps to Run the Chatbot

1. **Install the required libraries:**

   Open your terminal and run:

   ```bash
   pip install -r requirements.txt
   ```

2. **Enter your OpenAI API key in the `.env` file:**

   Create a `.env` file in the root directory with the following content:

   ```plaintext
   OPENAI_API_KEY = 'xxxxxxxxxxxxxxxxxxxxxxxxxxx'
   ```

3. **Run `vector_db.py` to create embeddings and store them in the Chroma vector database:**

   Execute the following command in your terminal:

   ```bash
   python Chatbot/vector_db.py
   ```

   * This script will generate embeddings and store them in the `chroma_db` folder.

4. **Once the embeddings are stored, start the application by running `app.py`:**

   ```bash
   python Chatbot/app.py
   ```

   * This will use Flask to handle requests, running on the local server at `http://127.0.0.1:5501/`.

## Steps to Run the Frontend

The Remotif.AI frontend is a React-based application designed for easy navigation across devices.

### Features
- **User-friendly Interface:** Clean and responsive design.
- **Appointment Management:** Schedule and manage patient appointments.
- **Patient Records:** Maintain detailed patient information.
- **Doctor Directory:** Access a list of doctors and their specialties.
- **Administrative Tools:** Secure admin panel for system oversight.
- **Responsive Design:** Optimized for desktop and mobile.

### Pages
- **Home:** Welcome page with quick access to key features.
- **Appointments:** Manage patient appointments.
- **Patients:** Add and manage patient records.
- **Doctors:** View and manage doctor information.
- **Admin:** Secure login for administrative tasks.

### Setup and Installation

1. **Clone the repository:**

   ```bash
   git clone https://github.com/Keerthivasan-Venkitajalam/remotif.ai
   ```

2. **Navigate to the project directory:**

   ```bash
   cd remotif.ai
   cd Frontend
   ```

3. **Install dependencies:**

   ```bash
   npm install
   ```

4. **Run the development server:**

   ```bash
   npm run dev
   ```

   * Access the frontend at `http://localhost:3000`.

## Hardware Setup

## Hardware Setup

The hardware setup for Remotif.AI involves various components that enable data collection, patient monitoring, and communication with the system. Below is a list of essential components used in this project:

### Components Used

1. **Microcontroller:**
   - **Arduino Nano 33 IoT**: 
     - This compact board features built-in WiFi and Bluetooth capabilities, making it ideal for IoT applications. It is used for collecting data from sensors and transmitting it to the backend.

2. **Sensors:**
   - **ECG Sensor (e.g., AD8232)**: 
     - Monitors the electrical activity of the heart, capturing ECG signals for heart health analysis.
   - **Temperature Sensor (MLX90614)**: 
     - Provides accurate, non-contact temperature readings for monitoring patient body temperature.
   - **Heart Rate Sensor (e.g., MAX30100)**: 
     - Measures heart rate and oxygen saturation levels, essential for patient monitoring.

3. **Power Supply:**
   - **USB Power Supply**: 
     - The Arduino Nano 33 IoT can be powered through a USB cable connected to a computer or an external USB power source.

### Steps to Upload the INO Code:

1. **Open Arduino IDE.**
2. **Connect your Arduino Nano 33 IoT to your computer.**
3. **Select the correct board (Arduino Nano 33 IoT) and port from the Tools menu.**
4. **Open the `.ino` file from the `Code for Hardware` directory.**
5. **Upload the code to the microcontroller.**

### Additional Considerations

- **Wiring and Connections**: Ensure that all sensors are correctly wired to the Arduino Nano 33 IoT according to the pin configuration specified in your `.ino` code. Refer to each sensor's datasheet for detailed wiring instructions.
- **Libraries**: Install the required libraries in Arduino IDE to interface with the sensors and modules effectively. For example, libraries for the ECG sensor, MLX90614 temperature sensor, and display module.

This hardware setup enables effective data collection and communication for patient monitoring, forming a crucial part of the Remotif.AI system.


## ML Model Codes

The `ML models` directory contains Jupyter Notebooks for training and predicting health conditions using machine learning algorithms. To run these notebooks, follow these steps:

1. **Install Jupyter Notebook (if not already installed):**

   ```bash
   pip install notebook
   ```

2. **Navigate to the ML models directory:**

   ```bash
   cd ML models
   ```

3. **Start Jupyter Notebook:**

   ```bash
   jupyter notebook
   ```

4. **Open the respective `.ipynb` file to train or evaluate your model.**

   * Ensure that all dependencies mentioned in the notebooks are installed. You can install additional libraries using:

   ```bash
   pip install <library_name>
   ```

## Technologies Used

- **Frontend:** React.js, JavaScript (ES6+), HTML5, CSS3
- **Backend:** Flask
- **Database:** Chroma (for embeddings)
- **Machine Learning:** Python libraries (e.g., scikit-learn, TensorFlow)
- **APIs:** OpenAI API for chatbot functionalities
- **Other Tools:** Font Awesome for icons, jsPDF for PDF report generation

---

