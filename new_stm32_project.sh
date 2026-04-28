#!/usr/bin/env bash

set -euo pipefail

TEMPLATE_REPO="/Users/henri/git/stm32-template-f103rb-base"
WORKSPACE_DIR="/Users/henri/STM32CubeIDE/workspace_2.1.1"
TEMPLATE_PROJECT_NAME="stm32_template"
TEMPLATE_IOC_NAME="${TEMPLATE_PROJECT_NAME}.ioc"

usage() {
  cat <<EOF
Usage:
  $(basename "$0") <new_project_name>

Example:
  $(basename "$0") motor_driver

This script will:
  1. Copy the template repository from:
     ${TEMPLATE_REPO}
  2. Create a new project under:
     ${WORKSPACE_DIR}/<new_project_name>
  3. Remove copied Git-related files from the new project
  4. Rename ${TEMPLATE_IOC_NAME} to <new_project_name>.ioc
  5. Replace template project name references in the new .ioc and README.md
EOF
}

fail() {
  echo "Error: $*" >&2
  exit 1
}

if [[ $# -ne 1 ]]; then
  usage
  exit 1
fi

NEW_PROJECT_NAME="$1"
TARGET_DIR="${WORKSPACE_DIR}/${NEW_PROJECT_NAME}"
NEW_IOC_NAME="${NEW_PROJECT_NAME}.ioc"
SOURCE_IOC_PATH="${TEMPLATE_REPO}/${TEMPLATE_IOC_NAME}"
TARGET_IOC_PATH="${TARGET_DIR}/${NEW_IOC_NAME}"
TARGET_README_PATH="${TARGET_DIR}/README.md"

if [[ ! "$NEW_PROJECT_NAME" =~ ^[A-Za-z0-9_-]+$ ]]; then
  fail "project name must contain only letters, numbers, '_' or '-'"
fi

[[ -d "${TEMPLATE_REPO}" ]] || fail "template repository not found: ${TEMPLATE_REPO}"
[[ -d "${WORKSPACE_DIR}" ]] || fail "workspace directory not found: ${WORKSPACE_DIR}"
[[ -f "${SOURCE_IOC_PATH}" ]] || fail "template IOC file not found: ${SOURCE_IOC_PATH}"
[[ ! -e "${TARGET_DIR}" ]] || fail "target directory already exists: ${TARGET_DIR}"

cp -R "${TEMPLATE_REPO}" "${TARGET_DIR}"
rm -rf "${TARGET_DIR}/.git"
rm -f "${TARGET_DIR}/.gitignore"

mv "${TARGET_DIR}/${TEMPLATE_IOC_NAME}" "${TARGET_IOC_PATH}"

if [[ -f "${TARGET_IOC_PATH}" ]]; then
  perl -0pi -e "s/\Q${TEMPLATE_PROJECT_NAME}\E/${NEW_PROJECT_NAME}/g" "${TARGET_IOC_PATH}"
fi

if [[ -f "${TARGET_README_PATH}" ]]; then
  perl -0pi -e "s/\Q${TEMPLATE_IOC_NAME}\E/${NEW_IOC_NAME}/g; s/\Q${TEMPLATE_PROJECT_NAME}\E/${NEW_PROJECT_NAME}/g" "${TARGET_README_PATH}"
fi

if [[ -f "${TARGET_DIR}/RENAME_PROJECT.md" ]]; then
  perl -0pi -e "s/\Q${TEMPLATE_IOC_NAME}\E/${NEW_IOC_NAME}/g; s/\Q${TEMPLATE_PROJECT_NAME}\E/${NEW_PROJECT_NAME}/g" "${TARGET_DIR}/RENAME_PROJECT.md"
fi

cat <<EOF
Project created:
  ${TARGET_DIR}

Updated:
  - folder name
  - ${NEW_IOC_NAME}
  - removed copied .git and .gitignore
  - README.md project name references
  - RENAME_PROJECT.md project name references

Next steps:
  1. Open ${NEW_IOC_NAME} in STM32CubeIDE or STM32CubeMX
  2. Confirm the Project Name is ${NEW_PROJECT_NAME}
  3. Regenerate STM32CubeIDE project files
  4. Build the project
EOF
