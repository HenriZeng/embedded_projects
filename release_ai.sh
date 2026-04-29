#!/bin/bash
set -e

export PATH="$HOME/.npm-global/bin:/opt/homebrew/bin:/usr/local/bin:$PATH"

if ! command -v codex >/dev/null 2>&1; then
  echo "Error: codex command not found. Install it with: npm install -g @openai/codex"
  exit 1
fi

PROJECT_NAME="$1"

if [ -z "$PROJECT_NAME" ]; then
  echo "Usage: ./release_ai.sh <project_name>"
  exit 1
fi

echo "=================================="
echo "AI Release: $PROJECT_NAME"
echo "=================================="

# 读取 prompt 模板并替换变量
PROMPT=$(sed "s/{{PROJECT_NAME}}/$PROJECT_NAME/g" .ai/readme_update.prompt)

echo "Running Codex..."

codex exec \
  --sandbox workspace-write \
  "$PROMPT"

echo ""
echo "Git diff:"
git status

git add "$PROJECT_NAME/README.md"

git commit -m "docs: update $PROJECT_NAME README (AI)"

git push

echo ""
echo "Release done."
