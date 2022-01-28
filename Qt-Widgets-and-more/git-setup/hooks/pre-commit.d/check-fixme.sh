matches=$(git diff --cached | grep -E '\+.*?FIXME|TODO')

if [ "$matches" != "" ]
then
        echo "-----------------------------------------------------------------------"
        echo "'FIXME' or 'TODO' tag is detected."
        echo "If they are supposed to live longer, please replace them with a PENDING"
        echo "Example: PENDING(Jesper) Fix blah blah, See LOCV-1234"
        echo "Please fix it before committing."
        echo "  ${matches}"
        echo "If you really really need to commit it, then run git commit using the --no-verify switch"
        exit 1
fi
