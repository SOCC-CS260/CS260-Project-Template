# CS-260 Project Template

Welcome to the CS-260 Project Tempalte. This repository is set up to work with GitHub Codespaces, providing you with a powerful, customizable, and scalable cloud development environment.

## Repository Structure

- `.devcontainer`: Contains the configuration files that specify the operating system and other configurations for the virtual machine (docker contaier if you know what that is) that VS Code is running in on the cloud. You shoud never need to modify files in this directory.
- `.github`: Contains GitHub-specific configurations including workflows for automated testing and grading. The `classroom` directory contains autograding settings, and the `workflows` directory defines how tests are run on GitHub. You should never need to modify files in this directory.
- `.vscode`: Contains the configurations for VS Code itself. The `launch.json` and `tasks.json` files tell VS Code what to do when you click the "play"/launch button. You should never need to modify files in this directory.
- `app/`: Contains the `main.cpp` file, which is where you will put the code for your app (except for the class files).
- `build/`: This directory will contain the executable files (aka binaries) and any intermediate files created by the compiler (e.g. object .obj files). The executables (.out) files are the fully compiled programs you can run on your computer. The ones here are specifically compiled to run on linux, which is what the codespaces environment is running in. You should not need to modify the files in this directory.
- `include/`: Stores all the header `.h` files for the project's classes.
- `resources/`: A directory for example code, files that are useful for manual testing, etc.
- `src/`: Houses the source or implementation `.cpp` files for our chess game classes.
- `test/`: Contains automated test files using the doctest framework. You should never need to modify files in this directory, but it may be useful to study the the unit tests.

## Using Codespaces

Here's how to get started:

1. **Open Your Codespace**: Navigate to the main page of this GitHub repository and click on the green Code button. Select Open with Codespaces and then New codespace.
2. **Build and Run the App**: Use the `Run and Debug` feature in the sidebar, select `Build & Run App (CS 260)` from the dropdown at the top, and then click the green play button to compile and run the main application. Alternatively you can us the `Build & Run` button in the taskbar at the bottom of the screen.
3. **Run Unit Tests**: Similarly, select `Run Unit Tests (CS 260)` from the dropdown and click the green play button to execute the unit tests. Alternatively you can us the `Run Tests` button in the taskbar at the bottom of the screen. You can use the Testing tab in the sidebar to see the results of the tests.
4. If you want to run your codespace locally, it's easy! Check out [these instructions](https://docs.github.com/en/codespaces/developing-in-a-codespace/using-github-codespaces-in-visual-studio-code).

## Working on the Lab

- Develop your classes in the corresponding files under the `src/` and `include/` directories.
- When you fininsh implementing a class, run the unit tests. If you get errors you can troubleshoot by studying unit test code in the `test/unit_tests.cpp` file to figure out what it was trying to do.
- Commit and push your changes to the repository regularly.
- Note that neigher the app nor the unit tests will compile until you at least implement the Square class (since the provided Chess class uses Square objects which are not yet defined)
- When finished, make sure the manual test code in the `resources` directory works as expected


## Happy Coding!

I hope you find this lab both challenging and enjoyable. Good luck!

