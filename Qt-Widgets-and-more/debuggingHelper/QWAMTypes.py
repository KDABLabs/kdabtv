# Check http://doc.qt.io/qtcreator/creator-debugging-helpers.html
# for more details or look at qttypes.py, stdtypes.py, boosttypes.py
# for more complex examples.

from dumper import Children, SubItem, UnnamedSubItem, DumperBase
from utils import DisplayFormat, TypeCode
from qttypes import *
import struct
####################### Your code below #######################


### Part 1
def qdump__Foo(d, value):
    i = value["i"].integer()
    j = value["j"].integer()
    d.putValue("[%d,%d]" % (i,j))
   
    d.putExpandable()
    if d.isExpanded():
        with Children(d):
            d.putSubItem('j', value["j"])
            
            # Don't try this at home :-)
            # and the "i" (that is the one in quotes stand for type integer...
            d.putSubItem('i', d.createValue(struct.pack("i",i), d.intType()))
            
            with SubItem(d, "sum"):
                d.putValue(i+j)
                d.putType(d.intType()) # not really needed though

### Part 2
def qdump__MyNameSpace__Foo(d, value):
    d.putValue("Secret!")
    d.putPlainChildren(value)
    
### Part 3
#def qdump__Money(d, value):
#    amount = value["m_amount"].floatingPoint()
#    currency = value["m_currency"].integer()
#    d.putValue("%s %s" % (("EUR" if (currency == 0) else "USD"), amount))
#    d.putPlainChildren(value)

### Part 4
def qdump__Money(d, value):
    str = d.call("@QString", value, "toString")
    d.putStringValue(str)
    d.putPlainChildren(value)  
    
### Part 5
def qdump__FooOrBar(d, value):
    str=d.parseAndEvaluate("fooOrBarToString(*((FooOrBar*)%s))" % value.laddress)
    d.putStringValue(str)
    d.putPlainChildren(value)
    
#### Part 6
def qdump__UserID(d, value):
    employeeID = value.integer()
    str=d.parseAndEvaluate("EmployeeDatabase::instance().lookup(%d)" % employeeID)
    d.putStringValue(str)
 
def qdump__UserIDList(d, value):
    d.createTypedefedType(d.lookupType("int"), "UserID");
    d.formats[d.currentIName] = DisplayFormat.DirectQListStorage
    d.putItem(value.cast("QList<UserID>"))           
