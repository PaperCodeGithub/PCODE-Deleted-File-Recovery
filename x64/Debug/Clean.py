with open("C:\\1. Projects\\Social Media\\Deleted File Recover\\Aspha\\x64\\Debug\\recovered_S.txt", "rb") as f:
    raw = f.read()


# Keep readable ASCII plus tabs, newlines, and carriage return
clean = ''.join(chr(b) for b in raw if 32 <= b <= 126 or b in (9, 10, 13))

with open("cleaned_hi.txt", "w", encoding="utf-8") as out:
    out.write(clean)

print("✅ Cleaned content written to cleaned_hi.txt")
