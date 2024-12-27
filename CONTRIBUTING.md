# Contributing

I am delighted that you would like to contribute to the “SimpleReplace” project.

Here are a few guidelines to make this easier for you.

## Passive contribution (report bugs, suggestions for improvement)
Even if you don't want to program yourself, you can contribute to the project, for example by reporting bugs or suggesting improvements.
- Check [Issues](https://github.com/ma7t3/SimpleReplace/issues) first to see if someone else has already reported the same bug.
- If not, [simply create an issue](https://github.com/ma7t3/SimpleReplace/issues/new/choose) and describe your bug or suggestion in as much detail as possible.

## Active contribution (fix bugs, implement functions)
You are also welcome to actively contribute to the project by writing new code yourself or improving the existing code and thus fixing bugs, adding functions or similar.
- Simply fork this repository and clone it to your device.
- Compile the translation files (`*.ts`) into qm files (using `lrelease` in the Qt console)
- Now the whole project should compile successfully.

## Branch rules
Please use the branches as follows:
- The `main` branch is the production branch. It should contain a fully stable version of the software at all times.   
  **Never commit directly to the main-branch**!
- The `develop` branch is the main development branch. Minor changes or fixes may be committed directly to the development branch.
- If you plan to make larger changes consisting of several commits, create a feature-branch or bugfix-branch for this purpose. As soon as the feature is ready, you can create a pull request to merge the feature branch into development.
- **Note:** Even if you commit directly to ´development´, your changes must be merged from your forked branch to the dev branch of the project repository via pull request.
- Before you start programming a new feature or fixing a bug, create a corresponding issue (if it does not already exist) and inform them that you are working on this issue so that there are no conflicts.

### Branch naming
- The branches `main` and `develop` are long-lived and should not be renamed.
- For a feature branch, use the function provided by GitHub in an issue. Simply click on “Create a branch” and then fetch it to your device.   
  ![image](https://github.com/user-attachments/assets/46bab94c-73ae-4e07-99f8-3203f20a023f)
- These feature branches are always named according to the scheme `<Issue-ID>-<Issue-Title>`.

### Other branches
- The `translations` branch is used to update the translations (*.ts files). It remains permanently, is updated by a merge from the `develp` branch and merged back into `develop` after the translations have been updated.
