import os
import sys

# Папки, которые игнорируем
IGNORE_DIRS = {
    ".git", ".github", ".vs", ".vscode", ".idea",
    "build", "out", "bin", "obj", "cmake-build-debug", "cmake-build-release",
    "node_modules", "__pycache__", ".cache", "vendor", "third_party", "external"
}

# Расширения/имена файлов, которые игнорируем (бинарники, кэш и т.п.)
IGNORE_EXT = {
    ".exe", ".dll", ".so", ".dylib", ".o", ".obj", ".a", ".lib",
    ".png", ".jpg", ".jpeg", ".gif", ".bmp", ".ico", ".svg",
    ".zip", ".tar", ".gz", ".7z", ".rar",
    ".pdf", ".doc", ".docx", ".xls", ".xlsx",
    ".pyc", ".pyo", ".pdb", ".ilk", ".exp",
    ".db", ".sqlite", ".sqlite3",
    ".lock"
}

IGNORE_FILES = {"dump.txt", ".DS_Store", "Thumbs.db"}

# Максимальный размер файла (в байтах) — чтобы не тянуть гигантов
MAX_FILE_SIZE = 512 * 1024  # 512 KB


def should_skip_dir(name):
    return name in IGNORE_DIRS or name.startswith(".")


def should_skip_file(name):
    if name in IGNORE_FILES:
        return True
    _, ext = os.path.splitext(name)
    if ext.lower() in IGNORE_EXT:
        return True
    return False


def is_text_file(path):
    try:
        with open(path, "rb") as f:
            chunk = f.read(1024)
        if b"\x00" in chunk:
            return False
        chunk.decode("utf-8")
        return True
    except Exception:
        return False


def dump_project(root, output):
    root = os.path.abspath(root)
    with open(output, "w", encoding="utf-8") as out:
        for dirpath, dirnames, filenames in os.walk(root):
            # фильтруем директории на месте
            dirnames[:] = [d for d in dirnames if not should_skip_dir(d)]

            for fname in sorted(filenames):
                if should_skip_file(fname):
                    continue
                full = os.path.join(dirpath, fname)
                rel = os.path.relpath(full, root).replace("\\", "/")

                try:
                    size = os.path.getsize(full)
                except OSError:
                    continue
                if size > MAX_FILE_SIZE:
                    out.write(f"\n===== FILE: {rel} (SKIPPED, {size} bytes) =====\n")
                    continue
                if not is_text_file(full):
                    out.write(f"\n===== FILE: {rel} (BINARY, skipped) =====\n")
                    continue

                out.write(f"\n===== FILE: {rel} =====\n")
                try:
                    with open(full, "r", encoding="utf-8", errors="replace") as f:
                        out.write(f.read())
                except Exception as e:
                    out.write(f"[read error: {e}]\n")
                out.write("\n")


if __name__ == "__main__":
    root = sys.argv[1] if len(sys.argv) > 1 else "."
    output = sys.argv[2] if len(sys.argv) > 2 else "dump.txt"
    dump_project(root, output)
    print(f"Готово: {output}")