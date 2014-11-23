Read-10-chars({push  1 	
}{push  10 	 	 
}{call
 	3:read(1,10) 		
})Read-WS({push  0  
}{ReadChar	
	 })Read-5-chars({push  11 	 		
}{push  5 	 	
}{call
 	3:read(11,5) 		
}){end


}{Label
  FUNCTON:3:read 		
}{Dup 
 }{push  0  
}{swap 
	}{store		 }{Add	   }Loop10({Label
  2:loop 	 
}{Dup 
 }{push  0  
}{Retrieve			}{sub	  	}{ReadChar	
	 }{call
 	1:dec(mem=0)  	
}{push  0  
}{Retrieve			}{push  -1		
}{mult	  
}{jumpifneg
		2:loop 	 
}{Pop 

}{return
	
})END-OF-3:read{Label
  FUNCTION:1:dec(mem=0)  	
}{push  0  
}{Retrieve			}{push  1 	
}{sub	  	}{push  0  
}{swap 
	}{store		 }{return
	
}END-OF-1:dec