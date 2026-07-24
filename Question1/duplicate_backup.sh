#!/bin/bash

SUBMISSIONS="submissions"
BACKUP="backup"
REPORT="report.txt"
ERROR_LOG="error.log"

mkdir -p "$BACKUP"

processed=0
duplicates=0
backedup=0

for file in "$SUBMISSIONS"/*; do
    if [ -f "$file" ]; then
        processed=$((processed+1))

        filename=$(basename "$file")

        if [ -f "$BACKUP/$filename" ]; then
            cmp -s "$file" "$BACKUP/$filename"
            if [ $? -eq 0 ]; then
                duplicates=$((duplicates+1))
            else
                cp "$file" "$BACKUP/${filename}_copy" 2>>"$ERROR_LOG"
                backedup=$((backedup+1))
            fi
        else
            cp "$file" "$BACKUP/" 2>>"$ERROR_LOG"
            backedup=$((backedup+1))
        fi
    fi
done

echo "Files Processed : $processed" > "$REPORT"
echo "Duplicate Files : $duplicates" >> "$REPORT"
echo "Files Backed Up : $backedup" >> "$REPORT"

echo "Report generated successfully."
