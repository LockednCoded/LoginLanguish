# LockednCoded

![CMake Workflow Status](https://github.com/LockednCoded/LoginLanguish/actions/workflows/cmake.yml/badge.svg)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/77e352dbe59a454fae44f44b10b5218b)](https://app.codacy.com/gh/LockednCoded/LoginLanguish/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
[![CodeDocs Badge](https://codedocs.xyz/LockednCoded/LoginLanguish.svg)](https://codedocs.xyz/LockednCoded/LoginLanguish/)
[![CodeScene general](https://codescene.io/images/analyzed-by-codescene-badge.svg)](https://codescene.io/projects/43160)
[![CodeScene Code Health](https://codescene.io/projects/43160/status-badges/code-health)](https://codescene.io/projects/43160)
[![CodeScene System Mastery](https://codescene.io/projects/43160/status-badges/system-mastery)](https://codescene.io/projects/43160)
[![codecov](https://codecov.io/gh/LockednCoded/LoginLanguish/graph/badge.svg?token=1LN5G3NIQY)](https://codecov.io/gh/LockednCoded/LoginLanguish)

Members:

- Cameron Bruce 4476706
- Jack Searle 6178637
- Finn O'Neill 7143491
- Jeb Nicholson 4509896

## Building from source

**Prerequisites:**

- CMake
- node/npm

### 1. Clone the repo

```
git clone https://github.com/LockednCoded/LoginLanguish.git
cd LoginLanguish
```

### 2. Build the project

Configuring, building and debugging can be done using VSCode tasks. This is the simplest option.

**Configuring:**
In the cmake configure step, vcpkg will be downloaded and used to install dependencies. This may take a while.


Configure for debugging:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

Configure for release:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

**Building:**

```bash
cmake --build build
```

**Running tests:**

```bash
ctest --test-dir build
```
