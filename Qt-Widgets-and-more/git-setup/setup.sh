#! /bin/bash

echo "Welcome to the QWAM setup script."


# ========== copy hooks
if [ ! -e "git-setup/hooks" ]; then
  echo "Sorry, you need to run this from the topmost directory in your repos"
  exit -1
fi

echo -n "First I'll delete the old .git/hooks directory. Press Ctrl+c to stop me."
read dummy

rm -rf .git/hooks

echo -n "Next I'll copy all files from git-setup/hooks to .git/hooks. Press Ctrl+c to stop me."
read dummy

# ========== Copy hook's
cp -i -a git-setup/hooks .git
chmod -R +x .git/hooks


# ========= Setup commit template
echo -e "\n\nNext I will setup so you use the commit template, that means I'll run:"
echo "  git config --local commit.template git-config/commit-template"
echo -n "Press Ctrl+c to stop me"
read dummy
 
git config --local commit.template git-setup/commit-template
 
echo "Over and out"
