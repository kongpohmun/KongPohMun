var n= document.getElementById("name");//save the user form input UserName as Var n
var e = document.getElementById("occupa");//save user form input
var seq=1;//for autogenerate sequence no as UserID
function save() //save() for UserID
{
temp=seq++;
localStorage.setItem("1234567890asdAghjybdefvf2222cc",temp)
document.getElementById("idno").value=localStorage.getItem("1234567890asdAghjybdefvf2222cc");
return seq;
}

 function addRow() //add user form input to new row in table
 {  
       var table = document.getElementById("dataTable");  //transfer table var from "dataTable"
       var rowCount = table.rows.length;//assign the no of table rows value   
       var row = table.insertRow(rowCount);  
       //Column 1  
       var cell1 = row.insertCell(0);  
      cell1.innerHTML=rowCount+1;//set column value
       //Column 2    
       var cell2 = row.insertCell(1);  
       cell2.innerHTML = n.value;  //set column value
       //Column 3  
       var cell3 = row.insertCell(2);  
       cell3.innerHTML=e.value;//set column value
   }  

   function sortTable() //sorting 
   {
    var table, rows, switching, i, x, y, shouldSwitch;
    table = document.getElementById("dataTable");
    switching=true;
    /*Make a loop that will continue until
    no switching has been done:*/
    while (switching) {
      //start by saying: no switching is done:
      switching = false;
      rows = table.rows;
      /*Loop through all table rows (except the
      first, which contains table headers):*/
      for (i = 0; i < (rows.length + 1); i++) 
      {
        //start by saying there should be no switching:
        shouldSwitch = false;
        /*Get the two elements you want to compare,
        one from current row and one from the next:*/
        var e = document.getElementById("sortselect").selectedIndex;
        var h = document.getElementById("sortselect").options;
        var m= h[e].index;
        x = rows[i].cells[m];
        y = rows[i + 1].cells[m];
    
        if (x.innerHTML.toLowerCase() > y.innerHTML.toLowerCase()) {
            //if so, mark as a switch and break the loop:
            shouldSwitch = true;
            break;
          }
      }
    
      if (shouldSwitch) {
        /*If a switch has been marked, make the switch
        and mark that a switch has been done:*/
        rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
        switching = true;
      }
    }
  }

 


