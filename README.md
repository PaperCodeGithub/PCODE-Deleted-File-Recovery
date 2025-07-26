# Aspha (Raw Disk Sector Scanner)

A lightweight C-based tool to **recover deleted image files** (like JPG, PNG) directly from raw disk sectors. This utility works by scanning binary data for common **image file headers and footers**, reconstructing lost images without relying on the filesystem.

## 🛠 Features

- 🔍 Scans raw disk sectors for image file signatures
- 🧠 Identifies file boundaries using image header/footer
- 💾 Recovers and reconstructs deleted image files (JPG, PNG, etc.)
- ⚙️ Minimal dependency — pure C implementation
- 🏃 Fast, efficient, and lightweight
- A Basic .txt File recovery logic is also added

## 📦 Supported File Formats

| Format | Header (Hex)         | Footer (Hex)         |
|--------|----------------------|----------------------|
| JPG    | `FF D8`              | `FF D9`              |
| PNG    | `89 50 4E 47 0D 0A`  | `49 45 4E 44 AE 42`  |

(More formats can be added easily by extending the signatures.)

---

## 🚀 Usage

### 1. Build
./Aspha/
```
gcc Aspha.c -o aspha.exe
```
Output .exe is in Aspha folder

### 2. Run
Open aspha.exe

## 📂 Output
Recovered images are stored as:
recovered.jpg

---

## 🧠 How It Works
- Reads raw sectors (blocks) from the disk device
- Scans byte-by-byte for known image file headers
- Once a header is found, starts dumping bytes to a file
- Stops when a matching footer is found
- Saves the recovered file with a sequential name

## ⚠️ Disclaimer
- This tool is for educational and forensic use only.
- Do NOT write to the disk you are recovering from.
- Make sure to work on a cloned disk image when possible.

---

## 👨‍💻 Author
Hi, I’m **Aritra**, the creator behind Paper Code. I’m a passionate developer from India, always experimenting with ideas others hesitate to try — from building new compilers to training intelligent models from scratch.<br>
Email: aritra.paper.code@gmail.com
