# Linux system re-setup

Qt Creator has a few Linux tips, which requires some system setup. 
In case you reinstall your linux and the changes get lost, here are the highlights.

## GDB cache
[Speeding up the Start-up of GDB](https://www.youtube.com/watch?v=2e2MGZKSvBY&list=PL6CJYn40gN6gf-G-o6syFwGrtq3kItEqI&index=38)

1. Check that your ~/.gdbinit file holds this line:
   > set index-cache on
2. Check your crontab is setup to clean out old cache entries
   * Run crontab -e and check you have a line similar to this:
   > 0 15 * * * find ~/.cache/gdb -name "*.gdb-index" -type f -atime +30 -delete
   
   
