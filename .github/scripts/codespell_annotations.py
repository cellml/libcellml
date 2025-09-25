import argparse
import subprocess
import re
import sys


def _parse_args():
    parser = argparse.ArgumentParser(description="Runs codespell and creates GitHub annotations for any errors found.")
    parser.add_argument(
        "--exclude-file",
        type=str,
        help="Path to a file containing exclude patterns for codespell."
    )

    parser.add_argument(
        "--dictionary",
        action='append',
        type=str,
        help="Path to a file containing custom spelling corrections for codespell or '-' for default dictionary."
    )
    parser.add_argument(
        "--skip",
        type=str,
        help="Comma-separated list of files/folders to skip for codespell."
    )

    return parser.parse_args()


def run_codespell_and_create_annotations(args):
    """
    Runs codespell with provided arguments and formats its output as GitHub annotations.
    """
    command = ["codespell", ".", "--quiet-level", "3"]
    if args.exclude_file:
        command.extend(["--exclude-file", args.exclude_file])
    if args.skip:
        command.extend(["--skip", args.skip])
    if args.dictionary:
        for dict_path in args.dictionary:
            command.extend(["--dictionary", dict_path])

    print(f"Running command: {' '.join(command)}")

    # Execute the command
    result = subprocess.run(command, capture_output=True, text=True)

    # If codespell printed anything, it means there are errors
    if result.stdout:
        errors_output = result.stdout.strip()

        error_pattern = re.compile(r"^(.*):(\d+): (\w+) ==> (.*)$")

        print("Spelling errors found. Creating annotations...")
        error_count = 0
        for line in errors_output.split('\n'):
            match = error_pattern.match(line)
            if match:
                file_path, line_num, wrong_word, suggestion = match.groups()
                # This is the magic line that creates the annotation in GitHub
                title="Spelling error"
                message = f"{wrong_word} -> {suggestion}"
                if file_path.startswith("./"):
                    file_path = file_path[2:]
                print(f"::error file={file_path},line={line_num},title={title}::{message}")
                error_count += 1

        if error_count > 0:
            sys.exit(1)
    else:
        print("✅ No spelling errors found.")


if __name__ == "__main__":
    run_codespell_and_create_annotations(_parse_args())
