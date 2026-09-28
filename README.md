# GrabText

GrabText is a lightweight desktop application that allows you to select any region of your screen and extract the text contained in it.

The recognized text is automatically copied to the clipboard, making it easy to extract text from images, applications, websites, documents, and other content displayed on your screen.

## Features

* Support for multiple languages
* Download additional language data directly from the application
* Windows 7+ and macOS 10.13+
* Lightweight Qt5/C++ application

## Screenshot

<img width="183" height="191" alt="GrabText-screenshot" src="https://github.com/user-attachments/assets/5911e297-ebee-472d-8baf-3bb8c107eb50" />

## How it works

1. Open GrabText.
2. Choose the language of the text you want to copy.
3. If it's your first time using it, download new languages by clicking ```Add Language```.
4. Start a screen capture by clicking ```GrabText!```.
5. Select the area containing the text you want to extract.
6. The recognized text is copied to the clipboard.

## OCR Engine

GrabText uses [Tesseract OCR](https://github.com/tesseract-ocr/tesseract) to recognize text.

## Supported Languages

GrabText uses Tesseract's `.traineddata` language files.

GrabText supports every language that Tesseract supports, it will download new languages directly from [Tessdata](https://github.com/tesseract-ocr/tessdata), allowing you to install only the languages you need.

Language data is stored separately from the application.  
```Windows``` will store in ```~/AppData/Roaming/GrabText/languages```.  
```macOS``` will store in ```~/Library/Application Support/GrabText/languages```.

## Platforms

GrabText is designed to support:

* macOS
* Linux (Coming soon)
* Windows

## Technologies

GrabText is built using:

* **C++**
* **Qt 5**
* **CMake**
* **Tesseract OCR**
* **Leptonica**

## Building

### Requirements

* C++ compiler with C++17 support
* CMake
* Qt 5
* Tesseract OCR
* Leptonica
* pkg-config

Clone the repository:

```bash
git clone https://github.com/dev-gseven/GrabText.git
cd GrabText
```

Create a build directory:

```bash
mkdir build
cd build
```

Configure the project:

```bash
cmake ..
```

Build:

```bash
cmake --build .
```

## License

This project is under GPL3 License.

## Author

Developed by **dev-gseven**.

---

If you find GrabText useful, consider giving the project a ⭐ on GitHub.
