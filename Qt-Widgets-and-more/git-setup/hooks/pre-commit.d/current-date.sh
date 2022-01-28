matches=$(git diff --cached | grep -E '^\+.*?QDate::currentDate()')

if [ "$matches" != "" ]
then
        echo "-----------------------------------------------------------------------"
        echo "Please replace QDate::currentDate() with DateUtils::today()"
        echo "This allows for unit testing code involving dates"
        echo "Please fix it before committing."
        echo "  ${matches}"
        echo "If you really really need to commit it, then run git commit using the --no-verify switch"
        exit 1
fi
