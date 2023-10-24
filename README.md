<h1 align="center">42cursus - Minishell</h1>

<p align="center">
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/wengcychan/42cursus-minishell?style=plastic&color=blue&label=C%20language&logo=42"/>
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/wengcychan/42cursus-minishell?style=plastic&color=green&logo=42"/>
</p>

Minishell is a project focused on creating a simple shell, similar to bash. This project provides an opportunity to learn about processes and file descriptors while building a custom command-line interface.

For more projects related to 42cursus, please visit the [hive-42cursus](https://github.com/wengcychan/hive-42cursus.git) repository.

## Introduction

The goal of this project is to create a custom shell, capable of running commands and interacting with the operating system. Minishell will support various shell commands and features.

## Features

- **Command Execution**: Minishell can execute system commands and display the output.
- **Pipelines**: It supports command pipelines.
- **Redirection**: You can redirect input and output for commands.
- **Environment Variables**: Minishell can manage environment variables.
- **Signal Handling**: Minishell effectively manages user interruptions with ctrl-C, provides a graceful exit with ctrl-D, and ignores ctrl-\ signals.
- **Built-in Commands**: Minishell includes essential built-in commands like echo, cd, pwd, export, unset, env, and exit for core shell functionality.
- **Error Handling**: It provides error handling and reporting for invalid commands.

## Usage

To use Minishell program, follow these steps:

1. Clone the repository to your local machine:

   ```bash
   git clone https://github.com/wengcychan/42cursus-minishell.git

2. Compile the program:

   ```bash
	make
	```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; This will generate an executable named `minishell`.

3. Run Minishell:
	
	```bash
	./minishell
	```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Start using your Minishell.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; You can run various commands, use pipelines, and perform redirection as you would in a standard shell.