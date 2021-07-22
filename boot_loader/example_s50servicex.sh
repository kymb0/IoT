#!/bin/sh
#

case "$1" in
  start)
        /var/servicex &
        [ $? = 0 ] && echo "OK" || echo "FAIL"
        ;;
  stop)
        /var/servicex &
        [ $? = 0 ] && echo "OK" || echo "FAIL"
        ;;
  restart|reload)
        "$0" stop
        "$0" start
        ;;
  *)
        echo "Usage: $0 {start|stop|restart}"
        exit 1
esac

exit $?
