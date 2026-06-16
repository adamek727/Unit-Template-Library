#!/usr/bin/env bash
#
# Copyright (C) 2024 Adam Ligocki
# Distributed under MIT licence
#
# Print the CHANGELOG.md section body for a given version, for use as GitHub
# Release notes. The version may carry a leading 'v', so a git tag like
# v2.1.0 can be passed straight through. Leading/trailing blank lines are
# trimmed. Exits non-zero if no matching section exists.
#
# Usage: tools/extract_changelog.sh <version> [changelog-path]

set -euo pipefail

version="${1:?usage: extract_changelog.sh <version> [changelog-path]}"
changelog="${2:-CHANGELOG.md}"
version="${version#v}"

awk -v ver="$version" '
    /^## / {
        if (found) { exit }
        heading = $2
        sub(/^v/, "", heading)
        if (heading == ver) { found = 1; next }
        next
    }
    found { body[++n] = $0 }
    END {
        if (!found) {
            print "extract_changelog: no section for version " ver > "/dev/stderr"
            exit 1
        }
        start = 1
        while (start <= n && body[start] ~ /^[[:space:]]*$/) { start++ }
        end = n
        while (end >= start && body[end] ~ /^[[:space:]]*$/) { end-- }
        for (i = start; i <= end; i++) { print body[i] }
    }
' "$changelog"
