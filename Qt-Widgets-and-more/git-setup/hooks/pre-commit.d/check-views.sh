matches=$(git diff --cached '***.ui' | grep -E '^\+.*class="(QTableView|QTreeView)"')

if [ -n "$matches" ]
then
        echo "-----------------------------------------------------------------------"
        echo "It seems like you are creating instances of QTableView or QTreeView in .ui files"
        echo "Please use KDVTableView and KDVTreeView in their place."
        echo "Please fix it before committing."
        echo "  ${matches}"
        echo "If you really really need to commit it, then run git commit using the --no-verify switch"
        exit 1
fi
