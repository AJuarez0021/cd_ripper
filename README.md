# CD Ripper

A Windows desktop application for extracting audio tracks from CDs and converting them to WAV or MP3 format. Built with native C++ using the Win32 API and the BASS audio library.

---

## Features

- Automatic detection of CD-ROM drives (up to 10 drives)
- Built-in audio player with:
  - Play, pause, and stop controls
  - Previous / next track navigation
  - Volume, pan, and speed sliders
  - Real-time audio level meters
- Extract CDA tracks to **WAV** format
- Convert CDA tracks to **MP3** using the LAME encoder
- Batch processing (multi-track selection)
- Album metadata editing (artist, album, year, genre)
- Configuration persistence via `config.ini`
- Activity logging to `audio_converter.log`

---

## Tech Stack

| Component      | Details                        |
|----------------|--------------------------------|
| Language       | C++                            |
| Platform       | Win32 API (native Windows)     |
| Compiler       | Visual C++ 6.0                 |
| Audio / CD     | BASS Audio Library             |
| MP3 Encoding   | LAME MP3 Encoder               |
| UI Controls    | Windows Common Controls        |

---

## Requirements

### To build
- Visual C++ 6.0
- Windows SDK

### To run
- Windows 98 / 2000 / XP or later
- The following DLL files in the same directory as the executable:
  - `bass.dll`
  - `basscd.dll`
  - `lame_enc.dll`
- A CD-ROM drive with an audio disc inserted

---

## Building

1. Open `CDRipper.dsw` in Visual C++ 6.0.
2. Select the desired configuration:
   - **CDRipper - Win32 Release** (optimized)
   - **CDRipper - Win32 Debug** (with debug symbols)
3. Go to **Build → Rebuild All**.
4. The executable is generated in the `Release/` or `Debug/` folder.

---

## Usage

1. Place the DLL files (`bass.dll`, `basscd.dll`, `lame_enc.dll`) next to the executable.
2. Insert an audio CD into the drive.
3. Run `CDRipper.exe`.
4. Select the CD drive from the dropdown.
5. Choose the tracks to extract from the list.
6. Select the output folder for WAV or MP3 files.
7. Start the extraction or conversion from the **Action** menu or toolbar.

---

## Configuration

The `config.ini` file is created automatically in the application directory and stores:

- Last used MP3 output folder
- Last used WAV output folder
- Preferred output format
- Selected CD drive

The log file is written to:
```
{Windows Directory}\audio_converter.log
```

---

## Project Structure

```
cd_ripper/
├── WinMain.cpp           # Application entry point
├── CApplication.h/cpp    # Main application class (UI and state)
├── CPanel.h/cpp          # CD player panel
├── CAudioConverter.h/cpp # Audio conversion logic
├── CCda.h/cpp            # CD handling via BASS library
├── CListView.h/cpp       # Track list control
├── CToolBar.h/cpp        # Toolbar
├── CStatusBar.h/cpp      # Status bar
├── CProgressBar.h/cpp    # Progress bars
├── CWnd.h/cpp            # Base window class
├── CBrowse.h/cpp         # Folder browser dialog
├── Resource.rc           # Application resources
├── resource.h            # Resource ID definitions
├── CDRipper.dsp          # MSVC 6.0 project file
├── CDRipper.dsw          # MSVC 6.0 workspace file
└── config.ini            # Runtime configuration (auto-generated)
```

---

## External Dependencies

| Library  | File            | Purpose                            |
|----------|-----------------|------------------------------------|
| BASS     | `bass.dll`      | Audio playback and CD handling     |
| BASS CD  | `basscd.dll`    | CD-specific audio functions        |
| LAME     | `lame_enc.dll`  | MP3 encoding                       |

---

## Notes

- This project uses raw Win32 API without MFC or any other framework, keeping the executable lightweight.
- Legacy project built with Visual C++ 6.0 (1998); may require adjustments to compile with modern MSVC versions.
