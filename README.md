# LockednCoded

![CMake Workflow Status](https://github.com/LockednCoded/LoginLanguish/actions/workflows/cmake.yml/badge.svg)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/77e352dbe59a454fae44f44b10b5218b)](https://app.codacy.com/gh/LockednCoded/LoginLanguish/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
[![CodeDocs Badge](https://codedocs.xyz/LockednCoded/LoginLanguish.svg)](https://codedocs.xyz/LockednCoded/LoginLanguish/)
[![CodeScene general](https://codescene.io/images/analyzed-by-codescene-badge.svg)](https://codescene.io/projects/43160)
[![CodeScene Code Health](https://codescene.io/projects/43160/status-badges/code-health)](https://codescene.io/projects/43160)
[![CodeScene System Mastery](https://codescene.io/projects/43160/status-badges/system-mastery)](https://codescene.io/projects/43160)
[![CodeScene Missed Goals](https://codescene.io/projects/43160/status-badges/missed-goals)](https://codescene.io/projects/43160)

  
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
git clone https://github.com/LockednCoded/LoginLanguish.git && \
cd LoginLanguish
```

### 2. Build the project

Configuring, building and debugging can be done using VSCode tasks. This is the simplest option. 

**Configuring:**
```bash
cmake -B build
```

**Building:**
```bash
cmake --build build --clean-first
```
