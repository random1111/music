------------------1st--------------------------------------
function insert()
{
	echo "Enter name"
	read name
	echo "Enter a phone number as XXXXXXXXXX: "
        read phno
 	pat="^[0-9]{10}$"
        while [[ ! $phno =~ $pat ]]
    	do
    	echo "Please enter a phone number as XXXXXXXX: "
    	read phno
	done
	echo "Enter Address"
	read addr
	echo "$1 | $name | $phno | $addr">>$filename
	echo "Record is inserted"
	return
}
function modify()
{
	grep -v -w $1 $filename>$filename1
	echo "Enter the new name"
	read name
	echo "Enter a phone number as XXXXXXXXXX: "
        read phno
 	pat="^[0-9]{10}$"
        while [[ ! $phno =~ $pat ]]
    	do
    	echo "Please enter a phone number as XXXXXXXXXX: "
    	read phno
	done
	echo "Enter the new address"
	read addr
	echo "$1 | $name | $phno | $addr">>$filename1
	cat $filename1>$filename
	echo "Record is modified"
	return
}
function delete()
{
	grep -v -w $1 $filename>$filename1
	cat $filename1>$filename
	echo "Record is deleted"
	return
}
clear
echo "Enter the filename"
read filename
filename1=temp.db
if [ -f $filename ]
then
	echo "File already exist"
else
	echo "SNO | Name | PhNo | Addr">$filename
	echo "File is created"
fi

for((;;))
	do
		echo "1.Insert a record"
		echo "2.View Address Book"
		echo "3.Modify a record"
		echo "4.Delete a record"
		echo "5.Exit"
		read ch
		case $ch in
		1) while [ true ]
			do
				echo "Enter Serial No"
				read sn
				if ( grep -w $sn $filename )
				then
					echo "Record already exist"
				else
					insert $sn
					break
				fi
			done ;;
		2) cat $filename ;;
		3) echo "Enter Serial no"
		   read sn
		   if ( grep -w $sn $filename )
		   then
		  	 modify $sn
		   else
			echo "Record not found"
		   fi ;;
		4) echo "Enter Serial no to be deleted"
		   read sn
		   if ( grep -w $sn $filename )
		   then
		   	delete $sn
		   else
		   	echo "Record not found"
		   fi ;;
 		5)exit
		esac
	done

